

struct Connection : public std::enable_shared_from_this<Connection>
{

    friend class ConnectionPool;

    typedef std::function<void()> OnDone;

    Connection()
        : fd(-1)
        , inflightCount(0)
        , responsesReceived(0)
        , connectionState_(NotConnected)
    {
        state_.store(static_cast<uint32_t>(State::Idle));
    }

    struct RequestData {

        RequestData(
                Async::Resolver resolve, Async::Rejection reject,
                const Http::Request& request,
                std::chrono::milliseconds timeout,
                OnDone onDone)
            : resolve(std::move(resolve))
            , reject(std::move(reject))
            , request(request)
            , timeout(timeout)  
            , onDone(std::move(onDone))
        { }
        Async::Resolver resolve;
        Async::Rejection reject;

        Http::Request request;
        std::chrono::milliseconds timeout;
        OnDone onDone;
    };

    enum State : uint32_t {
        Idle,
        Used
    };

    enum ConnectionState {
        NotConnected,
        Connecting,
        Connected
    };

    void connect(Address addr);
    void close();
    bool isIdle() const;
    bool isConnected() const;
    bool hasTransport() const;
    void associateTransport(const std::shared_ptr<Transport>& transport);

    Async::Promise<Response> perform(
            const Http::Request& request,
            std::chrono::milliseconds timeout,
            OnDone onDone);

    void performImpl(
            const Http::Request& request,
            std::chrono::milliseconds timeout,
            Async::Resolver resolve,
            Async::Rejection reject,
            OnDone onDone);

    Fd fd;

    void handleResponsePacket(const char* buffer, size_t totalBytes);
    void handleError(const char* error);
    void handleTimeout();

    std::string dump() const;

private:
    std::atomic<int> inflightCount;
    std::atomic<int> responsesReceived;
    struct sockaddr_in saddr;


    void processRequestQueue();

    struct RequestEntry {
        RequestEntry(
                Async::Resolver resolve, Async::Rejection reject,
                std::shared_ptr<TimerPool::Entry> timer,
                OnDone onDone)
          : resolve(std::move(resolve))
          , reject(std::move(reject))
          , timer(std::move(timer))
          , onDone(std::move(onDone))
        { }

        Async::Resolver resolve;
        Async::Rejection reject;
        std::shared_ptr<TimerPool::Entry> timer;
        OnDone onDone;
    };

    std::atomic<uint32_t> state_;
    ConnectionState connectionState_;
    std::shared_ptr<Transport> transport_;
    Queue<RequestData> requestsQueue;

    std::deque<RequestEntry> inflightRequests;

    TimerPool timerPool_;
    Private::Parser<Http::Response> parser_;
};

class ConnectionPool
{
public:
    void init(size_t maxConnsPerHost);
    std::shared_ptr<Connection> pick_conn(const std::string& domain);
    void release_conn(const std::shared_ptr<Connection>& connection);

    size_t used_conns(const std::string& domain) const;
    size_t idle_conns(const std::string& domain) const;

    size_t avail_conns(const std::string& domain) const;

    void close_idle_conns(const std::string& domain);

private:
    using Connections=std::vector<std::shared_ptr<Connection>>;

    mutable std::mutex m_mtx;
    std::unordered_map<std::string, Connections> m_conns;
    size_t m_max_conns;
};