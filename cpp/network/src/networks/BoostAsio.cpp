#include "../../include/networks/BoostAsio.h"

void boostasio::run(const boost::system::error_code& e,boost::asio::steady_timer* t, int* count)
{
    cout << "boostasio::run" <<" "<< e <<" "<<t<<" "<<count<< endl;
/*
    if(*count < 5)
    {
    cout << *count << " "<< e << endl;
    ++(*count);

        t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
        t->async_wait(boost::bind(boostasio::run, boost::asio::placeholders::error, t, count));
    }*/
}

BoostAsio::BoostAsio()
    : Network()
	, address("")
	, port(0)

{}

BoostAsio::BoostAsio(const string& address, const uint16_t& port)
    : Network()
	, address(address)
	, port(port)

{

    this->timer = new boost::asio::steady_timer(this->io, boost::asio::chrono::seconds(1));

    int count = 0;
    this->timer->async_wait(boost::bind(boostasio::run, boost::asio::placeholders::error, this->timer, &count));

    this->io.run();

    cout << "BoostAsio ctor" << endl;
}

BoostAsio::~BoostAsio()
{
    this->timer->~basic_waitable_timer();

    this->Shutdown();
    cout << "BoostAsio dtor" << endl;
}

network::Result BoostAsio::Create()
{
	// taken from here
	// https://www.gnu.org/software/libc/manual/html_node/Byte-Stream-Example.html

    cout << this->state << " BoostAsio create" << endl;
    
    this->state = network::State::CREATED;
    return network::Result::RESULT_OK;
}

network::Result BoostAsio::Resolve()
{
    cout << this->state  << "BoostAsio::Resolve()" << endl;
    this->state = network::State::HOST_RESOLVED;
	return network::Result::RESULT_OK;
}

network::Result BoostAsio::Connect()
{
    cout << this->state<< "BoostAsio::Connect()" << endl;
	
    cout << "ok connect " << endl;
    this->state = network::State::CONNECTED;
    return network::Result::RESULT_OK;
}

network::Result BoostAsio::Write(const string& data)
{ 
    cout << this->state  << " BoostAsio Write" << endl;

    //this->timer = boost::asio::steady_timer(this->io, boost::asio::chrono::seconds(1));
    cout << data << endl;
    return network::Result::RESULT_OK;
}

network::Result BoostAsio::Disconnect()
{
    cout << this->state <<" BoostAsio disconnect" << endl;
    return this->Shutdown();
}

network::Result BoostAsio::Shutdown()
{
	this->state = network::State::ERROR;
	cout <<" BoostAsio::Shutdown() OK " << endl;
    return network::Result::RESULT_OK;
}
