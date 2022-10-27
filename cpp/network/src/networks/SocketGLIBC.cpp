#include "../../include/networks/SocketGLIBC.h"

SocketGLIBC::SocketGLIBC()
    : Network()
	, address("")
	, port(0)
    , m_socket(network::SocketState::SOCKET_ERROR)
{}

SocketGLIBC::SocketGLIBC(const string& address, const uint16_t& port)
    : Network()
	, address(address)
	, port(port)
    , m_socket(network::SocketState::SOCKET_ERROR)
{
	// taken from here
	// https://www.gnu.org/software/libc/manual/html_node/Byte-Stream-Example.html

    cout << "SocketGLIBC ctor" << endl;

	// TCP SOCK_STREAM
	// UDP SOCK_DGRAM

    int _socket = socket(PF_INET, SOCK_STREAM, 0); // todo move to constants
	
   	cout << "socket is " << _socket << endl;

    if(network::SocketState::SOCKET_ERROR >= _socket)
    {
        this->setState(network::State::ERROR);
   		cout << "err socket is " << _socket << endl;

        return;
    }

    this->m_socket = _socket;

  	this->m_servername.sin_family = AF_INET;
  	this->m_servername.sin_port = htons (this->port);
  	
	struct hostent* hostinfo = gethostbyname (this->address.c_str());
  	if (hostinfo == nullptr)
    {
		this->setState(network::State::ERROR);
 		cout<<"Unknown host " << this->address << endl;
		return;
    }

	this->m_servername.sin_addr = *(struct in_addr *) hostinfo->h_addr;

	this->setState(network::State::READY);

	cout<<"ctor state " << this->state << endl;
}

SocketGLIBC::~SocketGLIBC()
{
    cout << "SocketGLIBC dtor" << endl;
}

void SocketGLIBC::Connect()
{
    cout << "SocketGLIBC conn" << endl;
	
	if(network::State::READY == this->state)
	{
		cout << "SocketGLIBC conn network::State::READY" << endl;
		int err = connect(this->m_socket
			, (struct sockaddr *) &this->m_servername
			, sizeof (this->m_servername));

    	if (network::SocketState::SOCKET_ERROR >= err)
    	{
			this->setState(network::State::ERROR);
		  	cout << "SocketGLIBC conn failed :( " << endl;
			return;
    	}

	}
    this->setState(network::State::CONNECTED);
}

void SocketGLIBC::Write()
{
    this->setState(network::State::READY);
}

void SocketGLIBC::Disconnect()
{
	cout << "SocketGLIBC dconn" << endl;

    int err = shutdown(this->m_socket, this->shutdown_mode); // todo move to constants

    this->m_socket = network::SocketState::SOCKET_ERROR; 

    if(network::SocketState::SOCKET_ERROR >= err)
    {
	   	cout << "err close socket is " << err << endl;

		this->setState(network::State::ERROR);
    }

    this->setState(network::State::READY); 
}
