
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>
#include <functional>
#include <type_traits>

#include <iostream>

static const size_t max_thread_size = 100;

class ThreadPool
{
public:
    using work_thread_ptr = std::shared_ptr<std::thread>;
    using task_t = std::function<void()>;
    
    ThreadPool() : m_is_stopped(false){}
    ~ThreadPool() { ThreadPool_stop(); }
    
    void ThreadPool_init(size_t num)
    {
        if (num <= 0 || num > max_thread_size) {
            std::string err_str = "Number of threads in the ranage of 1 to " + std::to_string(max_thread_size);
            throw std::invalid_argument(err_str);
        }
        
        size_t i;
        for (i = 0; i < num; ++i) {
            work_thread_ptr th = std::make_shared<std::thread>(std::bind(&ThreadPool::ThreadPool_run, this));
            m_threads.emplace_back(th);
        }
    }
    
    /** 普通函数任务 */
    template<typename Func, typename... Args>
    void ThreadPool_addTask(const Func& func, Args... args)
    {
        if (m_is_stopped) {
            throw std::runtime_error("thread pool is stopped");
        }
        
        task_t task = [&func, args...](){ return func(args...); };
        
        std::unique_lock<std::mutex> locker(m_mtx);
        m_tasks.emplace(std::move(task));
        m_cond.notify_one();
    }
    /** 函数对象任务 */
    template<typename Func, typename... Args>
    typename std::enable_if<std::is_class<Func>::value>::type ThreadPool_addTask(Func& func, Args... args)
    {
        if (m_is_stopped) {
            throw std::runtime_error("thread pool is stopped");
        }
        
        task_t task = [&func, args...](){ return func(args...); };
        
        std::unique_lock<std::mutex> locker(m_mtx);
        m_tasks.emplace(std::move(task));
        m_cond.notify_one();
    }
    /** 类成员方法任务 */
    template<typename Obj, typename Func, typename... Args>
    void ThreadPool_addTask(const Func& func, Obj* obj, Args... args)
    {
        if (m_is_stopped) {
            throw std::runtime_error("thread pool is stopped");
        }
        
        task_t task = [&obj, &func, args...](){ return (*obj.*func)(args...); };
        
        std::unique_lock<std::mutex> locker(m_mtx);
        m_tasks.emplace(std::move(task));
        m_cond.notify_one();
    }
    
    void ThreadPool_stop()
    {
        std::call_once(m_once_flag, [this](){
            std::unique_lock<std::mutex> locker(m_mtx);
            m_is_stopped = true;
            m_cond.notify_all();
            locker.unlock();
            
            for (auto& iter : m_threads) {
                if (iter != nullptr && iter->joinable()) {
                    iter->join();
                }
            }
            
            m_threads.clear();
            
            while(! m_tasks.empty()) {
                m_tasks.pop();
            }
        });
    }

    void ThreadPool_run()
    {        
        while (true) {
            task_t task = nullptr;
            std::unique_lock<std::mutex> locker(m_mtx);
                        
            m_cond.wait(locker, [this](){ return m_is_stopped || ! m_tasks.empty(); });
            
            if (m_is_stopped) {
                break;
            }
            
            if (! m_tasks.empty()) {
                task = std::move(m_tasks.front());
                m_tasks.pop();
            }
            
            locker.unlock();
            
            if (task != nullptr) {
                task();
            }
        }
    }
    
private:
    std::vector<work_thread_ptr>  m_threads;
    std::queue<task_t>            m_tasks;
    std::mutex                    m_mtx;
    std::condition_variable       m_cond;
    std::atomic<bool>             m_is_stopped;
    std::once_flag                m_once_flag;
};


/** 正式测试 */
#include <iostream>
#include <string>
#include <chrono>

void test_func(const std::string& str)
{
    std::cout << std::this_thread::get_id() << " test function. str: " << str << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

class TestFuncObj
{
public:
    void operator()(const std::string& str, int i) {
        std::cout << std::this_thread::get_id() << " test function object. str: " << str << ", i: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
};

class TestMethod
{
public:
    void print(const std::string& str, int i) {
        std::cout << std::this_thread::get_id() << " test class method. str: " << str << ", i: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
};

int main()
{
    TestFuncObj funcobj;
    TestMethod obj;
        
    std::cout << "main thread id: " << std::this_thread::get_id() << std::endl;
        
    try {
        ThreadPool pool;
        
        std::string str{"Hello World"};
        
        pool.ThreadPool_init(20);
        
        int i;
        for (i = 0; i < 10000; i++) {
            pool.ThreadPool_addTask([](){ std::cout << std::this_thread::get_id() << " test lambda." << std::endl; });
            pool.ThreadPool_addTask(test_func, str);
            pool.ThreadPool_addTask(funcobj, str, i);
            pool.ThreadPool_addTask(&TestMethod::print, &obj, str, i);
        }
        
        /** 防止主线程提出，主线程休眠一会儿 */
        std::cout << "sleep for 3 seconds" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "sleep over" << std::endl;
        std::cin.get();
    }
    catch(std::exception& e) {
        std::cout << "exception occurs: " << e.what() << std::endl;
    }
    
    std::cout << "##############END###################" << std::endl;
    
    return 0;
}
