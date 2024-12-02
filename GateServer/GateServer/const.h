#pragma once;
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <unordered_map>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "Singleton.h"
#include <map>
#include <queue>
#include <unordered_map>
#include <functional>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/exception.h>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "hiredis.h"
#include <chrono>
#include <assert.h>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

enum ErrorCodes {
    Success = 0,
    Error_Json = 1001,  //Json��������
    RPCFailed = 1002,  //RPC�������
    VarifyExpired = 1003, //��֤�����
    VarifyCodeErr = 1004, //��֤�����
    UserExist = 1005,     //�û��Ѿ�����
    PasswdErr = 1006,     //�������
    EmailNotMatch = 1007,  //���䲻ƥ��
    PasswdUpFailed = 1008,  //�����������
    PasswdInvalid = 1009,   //�������ʧ��
    RPCGetFailed = 1010, //RP
};
class ConfigMgr;
extern ConfigMgr gcfgMgr;
class Defer {
public:
    // ����һ��lambda���ʽ���ߺ���ָ��
    Defer(std::function<void()> func) : func_(func) {}

    // ����������ִ�д���ĺ���
    ~Defer() {
        func_();
    }

private:
    std::function<void()> func_;
};
#define CODEPREFIX "code_"