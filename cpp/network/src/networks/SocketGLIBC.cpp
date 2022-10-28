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

	// make socket
    int _socket = socket(PF_INET, SOCK_STREAM, 0); // todo move to constants
	
   	cout << "socket is " << _socket << endl;

    if(network::SocketState::SOCKET_ERROR >= _socket)
    {
        this->setState(network::State::ERROR);
   		cout << "err socket is " << _socket << endl;

        return;
    }

    this->m_socket = _socket;

	// make server name
  	this->m_servername.sin_family = AF_INET;
  	this->m_servername.sin_port = htons (this->port);
  	
	struct hostent* hostinfo = gethostbyname (this->address.c_str());
	cout<<"host addr " << this->address << ", h_name " << hostinfo->h_name<< endl;
  	if (hostinfo == nullptr)
    {
		this->setState(network::State::ERROR);
 		cout<<"Unknown host " << this->address << endl;
		return;
    }

	this->m_servername.sin_addr = *(struct in_addr *) hostinfo->h_addr;
	cout<<"h_addr " << hostinfo->h_addr << endl;

	/*// convert server address into bit-format
	int err = inet_pton(AF_INET, this->address.c_str(), &this->m_servername.sin_addr);

	if (network::SocketState::SOCKET_ERROR >= err)
	{
		this->setState(network::State::ERROR);
 		cout<<"Cannot get binary representation inet_pton() of server" << this->address << endl;
	}
	*/
	char buff[1024];
	//memset(buff, '0', sizeof(buff));

	recv(this->m_socket, buff, sizeof(buff)-1, MSG_OOB);
	for(int i =0; i<1024;i++)
		cout<< buff[i];

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
		cout << this->m_servername.sin_family <<" "<<this->m_servername.sin_port << " "<< endl;///this->m_servername.sin_addr<<" " << endl;
		int err = connect(this->m_socket
			, (struct sockaddr *) &this->m_servername
			, sizeof (this->m_servername));
		cout << err << endl;
    	if (network::SocketState::SOCKET_ERROR >= err)
    	{
			this->setState(network::State::ERROR);
		  	cout << "SocketGLIBC conn failed :( " << endl;
			return;
    	}

	}

    this->setState(network::State::CONNECTED);
	cout<<"conn state " << this->state << endl;
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
