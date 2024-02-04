#ifndef METHOD_GET_H
#define METHOD_GET_H

#include "TCPFlood.h"

namespace cotton{
class GET : public TCPFlood
{
public:
    GET(io_context& io_context, tcp::resolver::results_type& endpoints, const string& url)
    : TCPFlood(io_context, endpoints, url)
    {
        DEADLINE_CONNECT_SEC = 100;
        DEADLINE_READ_SEC = 30;
        DEADLINE_WRITE_SEC = 100;
    };

private:
	const flood::RequestType type_ = flood::RequestType::GET;

private:
    void updateOutputBuffer(const string& rawPathQS, const string& body);

protected:
	virtual void start_read() ; // ?? does not seem to work: override and make it do nothing
    virtual void handle_read(const error_code& error, std::size_t n) ; // ??override and make it do nothing

    virtual void start_write();
    virtual void handle_write(const error_code& error);

};
}
#endif