
void
ConnectionPool::init(size_t maxConns)
{
    m_max_conns = maxConns;
}

std::shared_ptr<Connection>
ConnectionPool::pick_one(const std::string& domain)
{
    Connections pool;

    {
        std::lock_guard<std::mutex> guard(m_mtx);
        auto poolIt = m_conns.find(domain);
        if (poolIt == std::end(m_conns)) {
            Connections connections;
            for (size_t i = 0; i < m_max_conns; ++i) {
                connections.push_back(std::make_shared<Connection>());
            }

            poolIt = m_conns.insert(std::make_pair(domain, std::move(connections))).first;
        }
        pool = poolIt->second;
    }

    for (auto& conn: pool) {
        auto& state = conn->state_;
        auto curState = static_cast<uint32_t>(Connection::State::Idle);
        auto newState = static_cast<uint32_t>(Connection::State::Used);
        if (state.compare_exchange_strong(curState, newState)) {
            return conn;
        }
    }

    return nullptr;
}

void
ConnectionPool::release_conn(const std::shared_ptr<Connection>& connection)
{
    connection->state_.store(static_cast<uint32_t>(Connection::State::Idle));
}

size_t
ConnectionPool::used_conns(const std::string& domain) const
{
    Connections pool;
    {
        std::lock_guard<std::mutex> guard(m_mtx);
        auto it = m_conns.find(domain);
        if (it == std::end(m_conns)) {
            return 0;
        }
        pool = it->second;
    }

    return std::count_if(pool.begin(), pool.end(), [](const std::shared_ptr<Connection>& conn) {
        return conn->isConnected();
    });
}

size_t
ConnectionPool::idle_conns(const std::string& domain) const
{
    Connections pool;
    {
        std::lock_guard<std::mutex> guard(m_mtx);
        auto it = m_conns.find(domain);
        if (it == std::end(m_conns)) {
            return 0;
        }
        pool = it->second;
    }

    return std::count_if(pool.begin(), pool.end(), [](const std::shared_ptr<Connection>& conn) {
        return conn->isIdle();
    });
}

size_t
ConnectionPool::avail_conns(const std::string& domain) const
{
    return 0;
}

void
ConnectionPool::close_idle_conns(const std::string& domain) 
{
}
