#include "../include/STRESS.h"
#include <boost/asio/write.hpp>
#include <boost/asio.hpp>
#include <chrono>
namespace cotton {

    void STRESS::start_read()
  {
    // Set a deadline for the read operation.
    deadline_.expires_after(std::chrono::milliseconds(DEADLINE_READ_MS_));

    // Start an asynchronous operation to read a newline-delimited message.
    boost::asio::async_read_until(socket_,
        boost::asio::dynamic_buffer(input_buffer_), '\n',
        std::bind(&STRESS::handle_read, this, _1, _2));
  }

  void STRESS::handle_read(const error_code& error, std::size_t n)
  {
    if (stopped_)
      return;

    if (!error)
    {
      // Extract the newline-delimited message from the buffer.
      std::string line(input_buffer_.substr(0, n - 1));
      input_buffer_.erase(0, n); // why do we care?

      // Empty messages are heartbeats and so ignored.
      if (!line.empty())
      {
        std::cout << "Received: " << line << "\n";
      }

      start_read();
    }
    else
    {
      std::cout << "Error on receive: " << error.message() << "\n";

      stop(); // connected endpoint is not accessible anymore 
    }
    
  }
  
void STRESS::start_write()
  {
    if (stopped_)
      return;

    updateOutputBuffer("/", ""); // ? how ofter these has to be set ?

        // Start an asynchronous operation to send a heartbeat message.
        boost::asio::async_write(socket_, boost::asio::buffer(output_buffer_, output_buffer_.size()),
            std::bind(&STRESS::handle_write, this, _1));
  }

  void STRESS::handle_write(const boost::system::error_code& error)
  {
    if (stopped_)
      return;

    if (!error)
    {
      // Wait some seconds before sending the next heartbeat.
      heartbeat_timer_.expires_after(std::chrono::milliseconds(DEADLINE_WRITE_MS_));
      heartbeat_timer_.async_wait(std::bind(&STRESS::start_write, this));
    }
    else
    {
      std::cout << "Error on heartbeat: " << error.message() << "\n";

      stop(); // connected endpoint is not accessible anymore 
    }
  }

  void STRESS::updateOutputBuffer(const string& rawPathQS, const string& body)
  {
    //updateDefaultHeader("1.2.3.4", "5.6.7.8", "9.10.11.12"); // ??? ip origin and raw_authority ??? 
    //updateHeader(flood::TCP_HEADER_BASE);
	
	//updateRequest(type_, rawPathQS, body);

    //output_buffer_ = getRequest();        
    std::stringstream sstr;

    sstr << "Content-Length: 524\r\n"
            << "X-Requested-With: XMLHttpRequest\r\n"
            << "Content-Type: application/json\r\n\r\n"
            << "{\"data\":";
    
// https://api.restful-api.dev/objects
   //sstr<<"\"name\": \"Apple MacBook Pro 16\","
   //<<"\"data\": {"
   //<<"\"year\": 2019,"
   // << "\"price\": 1849.99,"
   // << "\"CPU model\": \"Intel Core i9\","
   // << "\"Hard disk size\": \"1 TB\""
   //<<"}";

    for(int i = 0; i < 512; i++)        
        sstr<<(char)(33+rand()%(126-33));
        
    sstr<< "}";

    string other = sstr.str();
    preparePayload(type_, rawPathQS, other);

    output_buffer_ = payload_;
    std::cout << ">>"<<payload_<<"<<";    
  }
}