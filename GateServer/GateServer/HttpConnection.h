#pragma once
#include "const.h"
class HttpConnection:public std::enable_shared_from_this<HttpConnection>
{
	friend class LoginSystem;
public:
	HttpConnection(boost::asio::io_context& ioc);
	void start();
	tcp::socket& GetSocket() {
		return _socket;
	}
private:
	void CheckDeadline();//��ʱ���
	void WriteResponse(); //��
	void HandleReq();//Http������
	void PreParseGetParam();
	tcp::socket _socket;
	beast::flat_buffer buffer{ 8192 }; //8K������
	http::request<http::dynamic_body> _request;
	http::response<http::dynamic_body> _response;
	std::string _get_url;
	std::unordered_map<std::string, std::string> _get_params;
	net::steady_timer deadline_{
		_socket.get_executor(), std::chrono::seconds(60) }; // ��ʱ��

};


