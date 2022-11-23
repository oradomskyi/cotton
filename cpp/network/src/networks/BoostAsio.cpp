#include "../../include/networks/BoostAsio.h"

// https://www.boost.org/doc/libs/1_78_0/doc/html/boost_asio/example/cpp11/timeouts/async_tcp_client.cpp

BoostAsio::BoostAsio()
    : Network()
    , tcp_resolver(this->io)
    , socket(this->io)
{}

BoostAsio::BoostAsio(const string& address, const uint16_t& port)
    : Network(address, port)
    , tcp_resolver(this->io)
    , socket(this->io)
{
    //cout << this->state << "BoostAsio::Create()" << endl;
    this->state = network::State::CREATED;

    //cout << this->state  << "BoostAsio::Resolve()" << endl;
    this->endpoints = this->tcp_resolver.resolve(this->address->c_str(), to_string(*(this->port)).c_str());
    
    //cout << "this->endpoints.size() " << this->endpoints.size() << endl;
    if(0 >= this->endpoints.size())
    {
        cout << "BoostAsio() cannot resolve host! Exiting constructor!" << endl;
        this->state = network::State::ERROR;
        return;
    }

    this->state = network::State::CREATED;

    this->start_connect(this->endpoints.begin());

    this->io.poll();
    //cout << this->io.stopped()<< endl;
    //cout << "BoostAsio ctor" << endl;
}

BoostAsio::~BoostAsio()
{
    //cout << "BoostAsio::~BoostAsio()" << endl;
    this->state = network::State::ERROR;

    boost::system::error_code ignored_error;
    this->socket.close(ignored_error);

    //cout << "BoostAsio dtor" << endl;
}

void BoostAsio::start_connect(tcp::resolver::results_type::iterator endpoint_iter)
{   
    //cout << "BoostAsio::start_connect()" << endl;
    // https://www.boost.org/doc/libs/1_74_0/doc/html/boost_asio/example/cpp11/timeouts/async_tcp_client.cpp
    if (endpoint_iter != this->endpoints.end())
    {
      //cout << "Trying " << endpoint_iter->endpoint() << endl;
      // Start the asynchronous connect operation.
      this->socket.async_connect(endpoint_iter->endpoint(),
          std::bind(&BoostAsio::handle_connect,
            this, _1, endpoint_iter));
    }
    else
    {
      // There are no more endpoints to try. Shut down the client.
      //this->io.stop();
      this->state = network::State::ERROR;
    }
}

void BoostAsio::handle_connect(const boost::system::error_code& error,
      tcp::resolver::results_type::iterator endpoint_iter)
{
    //cout << "BoostAsio::handle_connect()" << endl;

    // The async_connect() function automatically opens the socket at the start
    // of the asynchronous operation. If the socket is closed at this time then
    // the timeout handler must have run first.
    if (!this->socket.is_open())
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
      this->socket.close();

      // Try the next available endpoint.
      this->start_connect(++endpoint_iter);
    }

    // Otherwise we have successfully established a connection.
    else
    {
      cout << "Connected to " << endpoint_iter->endpoint() << endl;
      
      // Put the socket into non-blocking mode.
      this->socket.non_blocking(true);

      this->state = network::State::CONNECTED;
      this->io.stop();
      //cout << this->io.stopped()<< endl;
    }
}


void BoostAsio::handle_write()
{
    this->state = network::State::READY;
    //this->io.stop();
}


void BoostAsio::handle_read()
{
    this->state = network::State::READY;
    //this->io.stop();
}

network::Result BoostAsio::send(const string& buffer)
{
    //cout << "BoostAsio::send()" << this->state << endl;
    if(this->state == network::State::BUSY)
        return network::Result::RESULT_ERROR;

    if(this->io.stopped())
        this->io.restart();

    // add condition if needed
    { 
        this->state = network::State::BUSY;
        //cout << "BoostAsio::send() run_one() A" << this->state << endl; 
        boost::asio::async_write(this->socket
            , boost::asio::buffer(buffer, buffer.size())
            , std::bind(&BoostAsio::handle_write, this));
        
        this->io.poll_one();
    }

    return network::Result::RESULT_OK;
}

network::Result BoostAsio::receive(string* buffer)
{
    //cout << "BoostAsio::receive()" << this->state << endl;
    if(this->state == network::State::BUSY)
        return network::Result::RESULT_ERROR;

    if(this->io.stopped())
        this->io.restart();

    // add condition if needed
    { 
        this->state = network::State::BUSY;
        //cout << "BoostAsio::send() run_one() A" << this->state << endl; 
        boost::asio::async_read_until(this->socket
            , boost::asio::dynamic_buffer(*buffer)
            , '\n'
            , std::bind(&BoostAsio::handle_read, this));
        
        this->io.poll_one();
    }

    return network::Result::RESULT_OK;
}
