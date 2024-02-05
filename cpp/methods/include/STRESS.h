#ifndef METHOD_STRESS_H
#define METHOD_STRESS_H

#include "TCPFlood.h"

namespace cotton{
class STRESS : public TCPFlood
{
public:
    STRESS(io_context& io_context, tcp::resolver::results_type& endpoints, const string& url)
    : TCPFlood(io_context, endpoints, url)
    {
        DEADLINE_CONNECT_MS_ = 5000; 
        DEADLINE_READ_MS_ = 5000;
        DEADLINE_WRITE_MS_ = 2000;
    };

private:
	const flood::RequestType type_ = flood::RequestType::STRESS;

private:
    void updateOutputBuffer(const string& rawPathQS, const string& body);

protected:
	void start_read();
    void handle_read(const error_code& error, size_t n);

    void start_write();
    void handle_write(const error_code& error);
};
}
#endif