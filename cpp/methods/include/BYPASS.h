#ifndef METHOD_BYPASS_H
#define METHOD_BYPASS_H

#include "TCPFlood.h"

namespace cotton{
class BYPASS : public TCPFlood
{
public:
    BYPASS(io_context& io_context, tcp::resolver::results_type& endpoints, const string& url)
    : TCPFlood(io_context, endpoints, url)
    {
        DEADLINE_WRITE_MS_=100;
    };

private:
	const flood::RequestType type_ = flood::RequestType::BYPASS;

private:
    void updateOutputBuffer(const string& rawPathQS, const string& body);

protected:
	void start_read();
    void handle_read(const error_code& error, std::size_t n);

    void start_write();
    void handle_write(const error_code& error);
};
}
#endif