
#include <string>
#include <iostream>

/** 数据层 */
struct HttpRequestImpl
{
    std::string url;
    std::string method;
    std::string body;
};

/** 功能层 */
class HttpRequest
{
public:
    HttpRequest() : impl(new HttpRequestImpl) {}
    ~HttpRequest() { delete impl; impl = nullptr; }
    
    void setUrl(const std::string& url) { impl->url = url; }
    void setMethod(const std::string& method) { impl->method = method; }
    void setBody(const std::string& body) { impl->body = body; }
private:
    HttpRequestImpl* impl;
};

int main()
{
    /** omit */
    return 0;
}