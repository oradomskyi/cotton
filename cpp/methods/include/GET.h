#ifndef METHOD_GET_H
#define METHOD_GET_H

#include "TCPFlood.h"

namespace cotton{
class GET : public TCPFlood
{
public:
    GET(boost::asio::io_context& io_context, tcp::resolver::results_type& endpoints)
    : TCPFlood(io_context, endpoints)
    {};

    // kind-a too much
    //GET(GET&& other)
    //: TCPFlood(std::move(other))
    //, requestRawPathQS_(std::move(other.requestRawPathQS_))
    //, requestBody_(std::move(other.requestBody_))
    //{std::cout << "GET move" << std::endl;};

private:
	const flood::RequestType type_ = flood::RequestType::GET;
	string requestRawPathQS_;
	string requestBody_;

private:
    void updateOutputBuffer(string rawPathQS, string body);

protected:
	virtual void start_read() {}; // override and make it do nothing
    virtual void handle_read(const boost::system::error_code& error, std::size_t n) {}; // override and make it do nothing

    virtual void start_write();
    virtual void handle_write(const boost::system::error_code& error);

};
}
#endif