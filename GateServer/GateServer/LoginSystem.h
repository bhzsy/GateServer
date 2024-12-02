#include "Singleton.h"
#include <functional>
#include <map>
#include "const.h"

class HttpConnection;
typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;
class LoginSystem :public Singleton<LoginSystem>
{
    friend class Singleton<LoginSystem>;
public:
    ~LoginSystem();
    bool HandleGet(std::string, std::shared_ptr<HttpConnection>);
    bool HandlePost(std::string, std::shared_ptr<HttpConnection>);
    void RegGet(std::string, HttpHandler handler);
    void RegPost(std::string, HttpHandler handler);
private:
    LoginSystem();
    std::map<std::string, HttpHandler> _post_handlers;
    std::map<std::string, HttpHandler> _get_handlers;
};