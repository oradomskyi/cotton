#include "../../include/networks/BoostAsio.h"

// https://www.boost.org/doc/libs/1_78_0/doc/html/boost_asio/example/cpp11/timeouts/async_tcp_client.cpp

BoostAsioIO* BoostAsioIO::_instance = nullptr;
mutex BoostAsioIO::_mutex;

BoostAsioIO::BoostAsioIO()
{}

BoostAsioIO* BoostAsioIO::getInstance()
{
	lock_guard<mutex> lock(_mutex);
	if(nullptr == _instance)
	{
		_instance = new BoostAsioIO();
	}
	return _instance;
}

boost::asio::io_context* BoostAsioIO::getContext()
{
    return &io;
}

BoostAsio::BoostAsio()
    : Network()
    , tcp_resolver(*(BoostAsioIO::getInstance()->getContext()))
    , socket(*(BoostAsioIO::getInstance()->getContext()))
{}

BoostAsio::BoostAsio(const string& address, const uint16_t& port)
    : Network(address, port)
    , tcp_resolver(*(BoostAsioIO::getInstance()->getContext()))
    , socket(*(BoostAsioIO::getInstance()->getContext()))
{
    this->state = network::State::CREATED;
    this->endpoints = this->tcp_resolver.resolve(this->address->c_str(), to_string(*(this->port)).c_str());
    if(0 >= this->endpoints.size())
    {
        cout << "BoostAsio() cannot resolve host! Exiting constructor!" << endl;
        this->state = network::State::ERROR;
        return;
    }
    this->state = network::State::CREATED;

    this->start_connect(this->endpoints.begin());
}

BoostAsio::~BoostAsio()
{
    this->state = network::State::ERROR;

    boost::system::error_code ignored_error;
    this->socket.close(ignored_error);
}

void BoostAsio::start_connect(tcp::resolver::results_type::iterator endpoint_iter)
{   
    if (endpoint_iter != this->endpoints.end())
    {
      // Start the asynchronous connect operation.
      this->socket.async_connect(endpoint_iter->endpoint(),
          std::bind(&BoostAsio::handle_connect,
            this, _1, endpoint_iter));
    }
    else
    {
      // There are no more endpoints to try.
      this->state = network::State::ERROR;
    }
}

void BoostAsio::handle_connect(const boost::system::error_code& error,
      tcp::resolver::results_type::iterator endpoint_iter)
{
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
    }
}


void BoostAsio::handle_write(const boost::system::error_code& error)
{
	if(!error)
	{
    	this->state = network::State::READY;
	}
	else
	{
        cout << "err write\n";
    }
}


void BoostAsio::handle_read(const boost::system::error_code& error)
{
	if(!error)
	{
    	this->state = network::State::READY;
	}
	else
    {
        cout << "err read\n";
    }
}

network::Result BoostAsio::send(const string& buffer)
{
    if(network::State::BUSY == this->state)
        return network::Result::RESULT_ERROR;

    if(BoostAsioIO::getInstance()->getContext()->stopped())
        BoostAsioIO::getInstance()->getContext()->restart();

    { 
        this->state = network::State::BUSY;
        boost::asio::async_write(this->socket
            , boost::asio::buffer(buffer, buffer.size())
            , std::bind(&BoostAsio::handle_write, this, _1));

        BoostAsioIO::getInstance()->getContext()->poll();
    }

    return network::Result::RESULT_OK;
}

network::Result BoostAsio::receive(string* buffer)
{
    if(network::State::BUSY == this->state)
        return network::Result::RESULT_ERROR;

    if(BoostAsioIO::getInstance()->getContext()->stopped())
        BoostAsioIO::getInstance()->getContext()->restart();

    { 
        this->state = network::State::BUSY;
        boost::asio::async_read_until(this->socket
            , boost::asio::dynamic_buffer(*buffer)
            , '\n'
            , std::bind(&BoostAsio::handle_read, this, _1));

        BoostAsioIO::getInstance()->getContext()->poll();
    }

    return network::Result::RESULT_OK;
}
