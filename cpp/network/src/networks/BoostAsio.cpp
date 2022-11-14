#include "../../include/networks/BoostAsio.h"

BoostAsio::BoostAsio()
    : Network()
	, address("")
	, port(0)
    , stopped(false)
{
}

BoostAsio::BoostAsio(const string& address, const uint16_t& port)
    : Network()
	, address(address)
	, port(port)
    , stopped(false)
{
    // the io_context is initialised together with members before executing
    // the code below. I believe..
    
    cout << this->state << "BoostAsio::Create()" << endl;
    // for some reason does not work in initialization constructor above
    this->deadline = new steady_timer(this->io);
    this->heartbeat_timer = new steady_timer(this->io);
    this->tcp_resolver = new tcp::resolver(this->io);
    this->socket = new tcp::socket(this->io);

    this->state = network::State::CREATED;

    cout << this->state  << "BoostAsio::Resolve()" << endl;

    // meanwhile endpoint could be assignegned
    this->endpoints = this->tcp_resolver->resolve(this->address.c_str(), to_string(this->port).c_str());
    
    if(0 >= this->endpoints.size())
    {
        cout << "BoostAsio() cannot resolve host! Exiting constructor!" << endl;
        this->state = network::State::ERROR;
        return;
    }

    this->state = network::State::CREATED;

    cout << this->state << "BoostAsio::Connect()" << endl;
	
    this->start();

    this->io.run();

    cout << "BoostAsio ctor" << endl;
}

BoostAsio::~BoostAsio()
{
    this->stop();

    this->deadline->~basic_waitable_timer();
    this->heartbeat_timer->~basic_waitable_timer();
    this->tcp_resolver->~basic_resolver();
    this->socket->~basic_stream_socket();

    cout << "BoostAsio dtor" << endl;
}

void BoostAsio::start_connect(tcp::resolver::results_type::iterator endpoint_iter)
{   
    // https://www.boost.org/doc/libs/1_74_0/doc/html/boost_asio/example/cpp11/timeouts/async_tcp_client.cpp
    
    if (endpoint_iter != this->endpoints.end())
    {
      cout << "Trying " << endpoint_iter->endpoint() << endl;

      // Set a deadline for the connect operation.
      this->deadline->expires_after(std::chrono::seconds(3));

      // Start the asynchronous connect operation.
      this->socket->async_connect(endpoint_iter->endpoint(),
          std::bind(&BoostAsio::handle_connect,
            this, _1, endpoint_iter));
    }
    else
    {
      // There are no more endpoints to try. Shut down the client.
      this->stop();

      // restart the client
      this->start();
    }
}

void BoostAsio::check_deadline()
{
    if (this->stopped)
      return;

    // Check whether the deadline has passed. We compare the deadline against
    // the current time since a new asynchronous operation may have moved the
    // deadline before this actor had a chance to run.
    if (this->deadline->expiry() <= steady_timer::clock_type::now())
    {
        cout<< "deadline passed" <<endl;
      // The deadline has passed. The socket is closed so that any outstanding
      // asynchronous operations are cancelled.
      this->socket->close();

      // There is no longer an active deadline. The expiry is set to the
      // maximum time point so that the actor takes no action until a new
      // deadline is set.
      //this->deadline->expires_at(steady_timer::time_point::max());

      // There are no more endpoints to try. Shut down the client.
      this->stop();
      // restart the client
      this->start();  
    }

    // Put the actor back to sleep.
    this->deadline->async_wait(std::bind(&BoostAsio::check_deadline, this));
  }

void BoostAsio::handle_connect(const boost::system::error_code& error,
      tcp::resolver::results_type::iterator endpoint_iter)
  {
    if (this->stopped)
      return;

    // The async_connect() function automatically opens the socket at the start
    // of the asynchronous operation. If the socket is closed at this time then
    // the timeout handler must have run first.
    if (!this->socket->is_open())
    {
      cout << "Connect timed out\n";

      // Try the next available endpoint.
      this->start_connect(++endpoint_iter);
    }

    // Check if the connect operation failed before the deadline expired.
    else if (error)
    {
      cout << "Connect error: " << error.message() << endl;

      // We need to close the socket used in the previous connection attempt
      // before starting a new one.
      this->socket->close();

      // Try the next available endpoint.
      this->start_connect(++endpoint_iter);
    }

    // Otherwise we have successfully established a connection.
    else
    {
      cout << "Connected to " << endpoint_iter->endpoint() << endl;

      this->state = network::State::CONNECTED;

      // Start the input actor.
      /////start_read();

      // Start the heartbeat actor.
      //this->start_write();
    }
  }


void BoostAsio::start_write(const string& buffer)
  {
    if (this->stopped)
      return;

    // Start an asynchronous operation to send a heartbeat message.
    //const string buffer(_buffer);
    //const int sz = buffer.size();    
    boost::asio::async_write(*(this->socket), boost::asio::buffer(buffer, buffer.size()),
        std::bind(&BoostAsio::handle_write, this, _1, buffer));
  }

  void BoostAsio::handle_write(const boost::system::error_code& error, const string& buffer)
  {
    if (this->stopped)
      return;

    if (!error)
    {
      // Wait 10 seconds before sending the next heartbeat.
      this->heartbeat_timer->expires_after(std::chrono::seconds(1));
      this->heartbeat_timer->async_wait(std::bind(&BoostAsio::start_write, this, buffer));
    }
    else
    {
      std::cout << "Error on heartbeat: " << error.message() << "\n";

      this->stop();
    }
  }

void BoostAsio::start()
{
    // Start the connect actor.
    this->start_connect(this->endpoints.begin());

    // Start the deadline actor. You will note that we're not setting any
    // particular deadline here. Instead, the connect and input actors will
    // update the deadline prior to each asynchronous operation.
    this->deadline->async_wait(std::bind(&BoostAsio::check_deadline, this));
}

void BoostAsio::stop()
{
	this->state = network::State::ERROR;

    this->stopped = true;
    boost::system::error_code ignored_error;
    socket->close(ignored_error);
    deadline->cancel();
    heartbeat_timer->cancel();

	cout <<" BoostAsio::stop() OK " << endl;
    //return network::Result::RESULT_OK;
}

network::Result BoostAsio::send(const string& buffer)
{ 
    //buffer[0];
    cout << this->state  << " BoostAsio Write" << endl;

    this->start_write(buffer);
    //this->timer = boost::asio::steady_timer(this->io, boost::asio::chrono::seconds(1));
    
    cout << buffer << endl;
    return network::Result::RESULT_OK;
}

network::Result BoostAsio::receive(string& buffer)
{
    buffer[0];
    cout << this->state  << " BoostAsio Read" << endl;

    return network::Result::RESULT_OK;
}
