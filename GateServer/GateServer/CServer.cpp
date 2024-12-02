#include "CServer.h"
#include <iostream>
#include "HttpConnection.h"
#include "AsioIOServicePool.h"
CServer::CServer(net::io_context& ioc, unsigned short& port):_ioc(ioc),
_acceptor(ioc,tcp::endpoint(tcp::v4(),port))
{

}
void CServer::start()
{
	auto self = shared_from_this();
	auto& ioc_context = AsioIOServicePool::GetInstance()->GetIOService();
	std::shared_ptr<HttpConnection> ioc_con = std::make_shared<HttpConnection>(ioc_context);
	_acceptor.async_accept(ioc_con->GetSocket(), [self, ioc_con](beast::error_code ec)
		{
			try {
				if (ec)
				{
					self->start();
					return;
				}
				ioc_con->start();
				self->start();
			}
			catch (std::exception& exp) {
				std::cout << "eception is" << exp.what() << "\n";
				self->start();
			}
		}
	);

}

