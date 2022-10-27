#include "../../include/networks/SocketGLIBC.h"

SocketGLIBC::SocketGLIBC()
    : Network()
    , m_socket(-1) // todo move to constants
{
    cout << "TypeA ctor" << endl;
}

SocketGLIBC::~SocketGLIBC()
{
    cout << "TypeA dtor" << endl;
}

void SocketGLIBC::connect()
{
    cout << "TypeA conn" << endl;


    int sock = socket(PF_INET, SOCK_DGRAM, 0); // todo move to constants

   cout << "socket is " << sock << endl;


    if(0 > sock)
    {
        this->setState(network::State::ERROR);
   cout << "err socket is " << sock << endl;

        return;
    }
    
    
    this->m_socket = sock;
    this->setState(network::State::CONNECTED);
}

void SocketGLIBC::write()
{
    this->setState(network::State::READY);
}

void SocketGLIBC::disconnect()
{
cout << "TypeA disconn" << endl;

    int err = shutdown(this->m_socket, this->shutdown_mode); // todo move to constants
    this->m_socket = -1; // todo move to constants

    if(0 > err)
    {
   cout << "err close socket is " << err << endl;

        this->setState(network::State::ERROR);
    }

    this->setState(network::State::READY); 
}
