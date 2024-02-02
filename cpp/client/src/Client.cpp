# include "../include/Client.h"

// https://www.boost.org/doc/libs/1_78_0/doc/html/boost_asio/example/cpp11/timeouts/async_tcp_client.cpp

//
// This class manages socket timeouts by applying the concept of a deadline.
// Some asynchronous operations are given deadlines by which they must complete.
// Deadlines are enforced by an "actor" that persists for the lifetime of the
// client object:
//
//  +----------------+
//  |                |
//  | check_deadline |<---+
//  |                |    |
//  +----------------+    | async_wait()
//              |         |
//              +---------+
//
// If the deadline actor determines that the deadline has expired, the socket
// is closed and any outstanding operations are consequently cancelled.
//
// Connection establishment involves trying each endpoint in turn until a
// connection is successful, or the available endpoints are exhausted. If the
// deadline actor closes the socket, the connect actor is woken up and moves to
// the next endpoint.
//
//  +---------------+
//  |               |
//  | start_connect |<---+
//  |               |    |
//  +---------------+    |
//           |           |
//  async_-  |    +----------------+
// connect() |    |                |
//           +--->| handle_connect |
//                |                |
//                +----------------+
//                          :
// Once a connection is     :
// made, the connect        :
// actor forks in two -     :
//                          :
// an actor for reading     :       and an actor for
// inbound messages:        :       sending heartbeats:
//                          :
//  +------------+          :          +-------------+
//  |            |<- - - - -+- - - - ->|             |
//  | start_read |                     | start_write |<---+
//  |            |<---+                |             |    |
//  +------------+    |                +-------------+    | async_wait()
//          |         |                        |          |
//  async_- |    +-------------+       async_- |    +--------------+
//   read_- |    |             |       write() |    |              |
//  until() +--->| handle_read |               +--->| handle_write |
//               |             |                    |              |
//               +-------------+                    +--------------+
//
// The input actor reads messages from the socket, where messages are delimited
// by the newline character. The deadline for a complete message is 30 seconds.
//
// The heartbeat actor sends a heartbeat (a message that consists of a single
// newline character) every 10 seconds. In this example, no deadline is applied
// to message sending.
//

namespace cotton {

Client::Client(boost::asio::io_context& io_context, tcp::resolver::results_type& endpoints)
    : endpoints_(endpoints)
    , socket_(io_context)
    , deadline_(io_context)
    , heartbeat_timer_(io_context)
  {
  }

  // Called by the user of the client class to initiate the connection process.
  // The endpoints will have been obtained using a tcp::resolver.
  void Client::start()//tcp::resolver::results_type endpoints)
  {
    // Start the connect actor.
    //endpoints_ = endpoints;
    start_connect(endpoints_.begin());

    // Start the deadline actor. You will note that we're not setting any
    // particular deadline here. Instead, the connect and input actors will
    // update the deadline prior to each asynchronous operation.
    deadline_.async_wait(std::bind(&Client::check_deadline, this));
  }

  // This function terminates all the actors to shut down the connection. It
  // may be called by the user of the client class, or by the class itself in
  // response to graceful termination or an unrecoverable error.
  void Client::stop()
  {
    stopped_ = true;
    boost::system::error_code ignored_error;
    socket_.close(ignored_error);
    deadline_.cancel();
    heartbeat_timer_.cancel();
  }

void Client::start_connect(tcp::resolver::results_type::iterator endpoint_iter)
  {
    if (endpoint_iter != endpoints_.end())
    {
      std::cout << "Trying " << endpoint_iter->endpoint() << "...\n";

      // Set a deadline for the connect operation.
      deadline_.expires_after(std::chrono::seconds(DEADLINE_CONNECT_SEC));

      // Start the asynchronous connect operation.
      socket_.async_connect(endpoint_iter->endpoint(),
          std::bind(&Client::handle_connect,
            this, _1, endpoint_iter));
    }
    else
    {
      // There are no more endpoints to try. Shut down the client.
      stop();
    }
  }

  void Client::handle_connect(const boost::system::error_code& error,
      tcp::resolver::results_type::iterator endpoint_iter)
  {
    if (stopped_)
      return;

    // The async_connect() function automatically opens the socket at the start
    // of the asynchronous operation. If the socket is closed at this time then
    // the timeout handler must have run first.
    if (!socket_.is_open())
    {
      std::cout << "Connect timed out\n";

      // Try the next available endpoint.
      start_connect(++endpoint_iter);
    }

    // Check if the connect operation failed before the deadline expired.
    else if (error)
    {
      std::cout << "Connect error: " << error.message() << "\n";

      // We need to close the socket used in the previous connection attempt
      // before starting a new one.
      socket_.close();

      // Try the next available endpoint.
      start_connect(++endpoint_iter);
    }

    // Otherwise we have successfully established a connection.
    else
    {
      std::cout << "Connected to " << endpoint_iter->endpoint() << "\n";

      // Start the input actor.
      start_read();

      // Start the heartbeat actor.
      start_write();
    }
  }

  void Client::start_read()
  {
    // Set a deadline for the read operation.
    deadline_.expires_after(std::chrono::seconds(DEADLINE_READ_SEC));

    // Start an asynchronous operation to read a newline-delimited message.
    boost::asio::async_read_until(socket_,
        boost::asio::dynamic_buffer(input_buffer_), '\n',
        std::bind(&Client::handle_read, this, _1, _2));
  }

  void Client::handle_read(const boost::system::error_code& error, std::size_t n)
  {
    if (stopped_)
      return;

    if (!error)
    {
      // Extract the newline-delimited message from the buffer.
      std::string line(input_buffer_.substr(0, n - 1));
      input_buffer_.erase(0, n);

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

      stop();
    }
  }

  void Client::start_write()
  {
    if (stopped_)
      return;

    // Start an asynchronous operation to send a heartbeat message.
    boost::asio::async_write(socket_, boost::asio::buffer(output_buffer_, output_buffer_.size()),
        std::bind(&Client::handle_write, this, _1));
  }

  void Client::handle_write(const boost::system::error_code& error)
  {
    if (stopped_)
      return;

    if (!error)
    {
      // Wait some seconds before sending the next heartbeat.
      heartbeat_timer_.expires_after(std::chrono::seconds(DEADLINE_WRITE_SEC));
      heartbeat_timer_.async_wait(std::bind(&Client::start_write, this));
    }
    else
    {
      std::cout << "Error on heartbeat: " << error.message() << "\n";

      stop();
    }
  }

  void Client::check_deadline()
  {
    if (stopped_)
      return;

    // Check whether the deadline has passed. We compare the deadline against
    // the current time since a new asynchronous operation may have moved the
    // deadline before this actor had a chance to run.
    if (deadline_.expiry() <= steady_timer::clock_type::now())
    {
      // The deadline has passed. The socket is closed so that any outstanding
      // asynchronous operations are cancelled.
      socket_.close();

      // There is no longer an active deadline. The expiry is set to the
      // maximum time point so that the actor takes no action until a new
      // deadline is set.
      deadline_.expires_at(steady_timer::time_point::max());
    }

    // Put the actor back to sleep.
    deadline_.async_wait(std::bind(&Client::check_deadline, this));
  }

void Client::operator()()//tcp::resolver::results_type endpoints)
{
    start();//endpoints);
}

} // cotton