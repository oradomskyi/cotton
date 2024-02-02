#ifndef METHOD_BYPASS_H
#define METHOD_BYPASS_H

#include "TCPFlood.h"

namespace cotton{
class BYPASS : public TCPFlood
{
public:
    BYPASS(boost::asio::io_context& io_context, tcp::resolver::results_type& endpoints)
    : TCPFlood(io_context, endpoints)
    {
        DEADLINE_WRITE_SEC = 5;
    };

    // kind-a too much
    //BYPASS(BYPASS&& other)
    //: TCPFlood(std::move(other))
    //, requestRawPathQS_(std::move(other.requestRawPathQS_))
    //, requestBody_(std::move(other.requestBody_))
    //{std::cout << "BYPASS move" << std::endl;};

private:
	const flood::RequestType type_ = flood::RequestType::BYPASS;
	string requestRawPathQS_;
	string requestBody_;

private:
    void updateOutputBuffer(string rawPathQS, string body);

protected:
	void start_read();
    void handle_read(const boost::system::error_code& error, std::size_t n);

    void start_write();
    void handle_write(const boost::system::error_code& error);
};
}
#endif