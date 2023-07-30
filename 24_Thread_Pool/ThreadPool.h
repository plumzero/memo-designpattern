
#include <list>
#include <thread>
#include <functional>
#include <memory>
#include <atomic>
#include "SyncQueue.h"

const int MaxTaskCount = 100;

class ThreadPool
{
public:
    using Task = std::function<void()>;
    
    ThreadPool(int numThreads = std::thread::hardware_concurrency())
        : m_queue(MaxTaskCount) {
        Start(numThreads);  
    }
    ~ThreadPool(void) {
        Stop();
    }
    void Stop() {
        /** 保证多线程情况下只执行一次 StopThreadGroup */
        std::call_once(m_flag, [this]{ StopThreadGroup(); });
    }
    void AddTask(Task&& task) {
        m_queue.Put(std::forward<Task>(task));
    }
    void AddTask(const Task& task) {
        m_queue.Put(task);
    }
private:
    void Start(int numThreads) {
        m_running = true;
        for (int i = 0; i < numThreads; i++) {
            m_threadgroup.push_back(std::make_shared<std::thread>(&ThreadPool::RunInThread, this));
        }
    }
    void RunInThread() {
        while (m_running) {
            std::list<Task> list;
            m_queue.Take(list);
            
            for (auto & task : list) {
                if (! m_running) {
                    return ;
                }
                
                task();
            }
        }
    }
    void StopThreadGroup() {
        m_queue.Stop();         // 让同步队列中的线程停止
        m_running = false;      // 设置为 false, 让内部线程跳出循环并退出
        
        for (auto thread : m_threadgroup) {
            if (thread) {
                thread->join();
            }
        }
        m_threadgroup.clear();
    }
private:
    std::list<std::shared_ptr<std::thread>> m_threadgroup;  // 处理任务的线程组
    SyncQueue<Task> m_queue;                                // 同步队列
    std::atomic<bool> m_running;
    std::once_flag m_flag;
};