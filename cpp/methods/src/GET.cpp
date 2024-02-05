#include "../include/GET.h"
#include <boost/asio/write.hpp>
#include <boost/asio.hpp>
#include <chrono>
namespace cotton {

    void GET::start_read()
  {
    // Set a deadline for the read operation.
    deadline_.expires_after(std::chrono::milliseconds(DEADLINE_READ_MS_));

    // Start an asynchronous operation to read a newline-delimited message.
    boost::asio::async_read_until(socket_,
        boost::asio::dynamic_buffer(input_buffer_), '\n',
        std::bind(&GET::handle_read, this, _1, _2));
  }

  void GET::handle_read(const error_code& error, std::size_t n)
  {
    if (stopped_)
      return;

    if (!error)
    {
      // Extract the newline-delimited message from the buffer.
      //std::string line(input_buffer_.substr(0, n - 1));
      input_buffer_.erase(0, n); // why do we care?

      // Empty messages are heartbeats and so ignored.
      //if (!line.empty())
      {
        //std::cout << "Received: " << line << "\n";
      }

      start_read();
    }
    else
    {
      //std::cout << "Error on receive: " << error.message() << "\n";

      stop(); // connected endpoint is not accessible anymore 
    }
    
  }
  
void GET::start_write()
  {
    if (stopped_)
      return;

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
      heartbeat_timer_.expires_after(std::chrono::milliseconds(DEADLINE_WRITE_MS_));
      heartbeat_timer_.async_wait(std::bind(&GET::start_write, this));
    }
    else
    {
      //std::cout << "Error on heartbeat: " << error.message() << "\n";

      stop(); // connected endpoint is not accessible anymore 
    }
  }

  void GET::updateOutputBuffer(const string& rawPathQS, const string& body)
  {

    updateDefaultHeader("1.2.3.4", "5.6.7.8", "9.10.11.12"); // ??? ip origin and raw_authority ??? 
    updateHeader(getDefaultHeader());
	
	updateRequest(type_, rawPathQS, body);

    output_buffer_ = getRequest();
    
    //preparePayload(type_, rawPathQS, "");

    //output_buffer_ = payload_;
    ///std::cout << output_buffer_; 
  }
}