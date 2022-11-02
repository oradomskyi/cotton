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
        cout << "SocketGLIBC ctor" << endl;
}

SocketGLIBC::~SocketGLIBC()
{
    this->Shutdown();
    cout << "SocketGLIBC dtor" << endl;
}

network::Result SocketGLIBC::Create()
{
	// taken from here
	// https://www.gnu.org/software/libc/manual/html_node/Byte-Stream-Example.html

    cout << this->state << " SocketGLIBC create" << endl;

	// TCP SOCK_STREAM
	// UDP SOCK_DGRAM
    try
    {
        this->m_socket = socket(PF_INET, SOCK_STREAM, 0); // todo move to constants
   	    cout << "socket is " << this->m_socket << endl;
        if(network::SocketState::SOCKET_ERROR >= this->m_socket)
        {
            this->state = network::State::ERROR;
   		    cout << "err socket is " << this->m_socket << endl;
            return network::Result::RESULT_ERROR;
        }
      	this->m_servername.sin_family = AF_INET;
      	this->m_servername.sin_port = htons (this->port);
    	
        this->state = network::State::CREATED;

        cout << "ok socket is " << this->m_socket << endl;
        return network::Result::RESULT_OK;
    }
    catch(...)
    {
        this->state = network::State::ERROR;
   		cout << "err socket is " << this->m_socket << endl;
        return network::Result::RESULT_ERROR;    
    }
}

network::Result SocketGLIBC::Resolve()
{
    cout << this->state << this->m_socket << "SocketGLIBC resolve" << endl;
    try
    {
	    struct hostent* hostinfo = gethostbyname (this->address.c_str());
	    cout<<"host addr " << this->address << ", h_name " << hostinfo->h_name<< " port "<<this->port<< endl;
  	    if (hostinfo == nullptr)
        {
		    cout<<"Unknown host " << this->address << endl;
    		return network::Result::RESULT_ERROR;
        }

	    this->m_servername.sin_addr = *(struct in_addr *) hostinfo->h_addr;

	    this->state = network::State::HOST_RESOLVED;
    }
    catch(...)
    {
		cout<<"Unknown host " << this->address << endl;
        return network::Result::RESULT_ERROR;
    }

    cout << "ok resolved" << this->m_socket << endl;
    return network::Result::RESULT_OK;
    
}

network::Result SocketGLIBC::Connect()
{
    cout << this->state << this->m_socket << "SocketGLIBC connect" << endl;
	
	if(network::State::HOST_RESOLVED == this->state)
	{
        try
        {
		    cout << this->m_servername.sin_family <<" "<<this->m_servername.sin_port << " "<< endl;///this->m_servername.sin_addr<<" " << endl;
		    int err = connect(this->m_socket
			    , (struct sockaddr *) &this->m_servername
			    , sizeof (this->m_servername));
        
    	    if (network::SocketState::SOCKET_ERROR >= err)
    	    {
		        cout << "SocketGLIBC conn failed :( " << endl;
			    return network::Result::RESULT_ERROR;
    	    }
        }
        catch(...)
        {
            cout << "SocketGLIBC conn failed :( " << endl;
			return network::Result::RESULT_ERROR;
        }
	}
    this->state = network::State::CONNECTED;

    cout << "ok connect " << endl;
    return network::Result::RESULT_OK;
}

network::Result SocketGLIBC::Write(const string& data)
{ 
    cout << this->state << this->m_socket << " SocketGLIBC Write" << endl;
    if(network::State::CONNECTED == this->state)
    {
        try
        {
            write(this->m_socket, data.c_str(), data.size());
            cout<<">>>>>>>>>>>>>> !!! BANG !!! >>>>>>>>>>>>>>>> " << "Socket=" << this->m_socket << " state=" << this->state << endl;
            return network::Result::RESULT_OK;
        }
        catch(...)
        {
            return network::Result::RESULT_ERROR;    
        }
    }
    return network::Result::RESULT_ERROR;
}

network::Result SocketGLIBC::Disconnect()
{
    cout << this->state << this->m_socket <<" SocketGLIBC disconnect" << endl;
    return this->Shutdown();
}

network::Result SocketGLIBC::Shutdown()
{
	cout << this->state << this->m_socket <<" SocketGLIBC shutdown" << endl;
    this->state = network::State::ERROR;

    if(network::SocketState::SOCKET_ERROR == this->m_socket)
        return network::Result::RESULT_OK;
        
    try
    {
        shutdown(this->m_socket, this->shutdown_mode); // todo move to constants
    }
    catch(...)
    {
        cout << this->m_socket << " failed to shutdown()" << endl;
    }

    try
    {
        this->m_socket = network::SocketState::SOCKET_ERROR; 
        
        int err = close(this->m_socket);
        if(network::SocketState::SOCKET_ERROR >= err)
        {
	   	    cout << "err close socket is " << err << endl;
            return network::Result::RESULT_ERROR;
        } 
    }
    catch(...)
    {
	   	    cout << "err close socket is " << endl;
            return network::Result::RESULT_ERROR;
    }

    return network::Result::RESULT_OK;
}
