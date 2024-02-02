#include "../include/GET.h"

namespace cotton {
void GET::start_write()
  {
    if (stopped_)
      return;

    // GET does not seem to care about 
    updateOutputBuffer("/", ""); // ? how ofter these has to be set ?

    // Start an asynchronous operation to send a heartbeat message.
    boost::asio::async_write(socket_, boost::asio::buffer(output_buffer_, output_buffer_.size()),
        std::bind(&GET::handle_write, this, _1));
  }

  void GET::handle_write(const boost::system::error_code& error)
  {
    if (stopped_)
      return;

    if (!error)
    {
      // Wait some seconds before sending the next heartbeat.
      heartbeat_timer_.expires_after(std::chrono::seconds(DEADLINE_WRITE_SEC));
      heartbeat_timer_.async_wait(std::bind(&GET::start_write, this));
    }
    else
    {
      std::cout << "Error on heartbeat: " << error.message() << "\n";

      stop();
    }
  }

  void GET::updateOutputBuffer(string rawPathQS, string body)
  {
    requestRawPathQS_ = rawPathQS; // depends if we want copy-constructor each time..
    requestBody_ = body;

    updateDefaultHeader("1.2.3.4", "5.6.7.8", "9.10.11.12");    
    updateHeader(getDefaultHeader());
	
	updateRequest(type_, requestRawPathQS_, requestBody_);

    output_buffer_ = getRequest();
  }
}