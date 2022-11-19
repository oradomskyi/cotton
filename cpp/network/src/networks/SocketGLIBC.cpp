#include "../../include/networks/SocketGLIBC.h"

SocketGLIBC::SocketGLIBC()
    : Network()
    , m_socket(network::SocketState::SOCKET_ERROR)
{}

SocketGLIBC::SocketGLIBC(const string& address, const uint16_t& port)
    : Network(address, port)
    , m_socket(network::SocketState::SOCKET_ERROR)
{
            if(network::Result::RESULT_OK == this->Create()) {
                if(network::Result::RESULT_OK == this->Resolve()) {
                    //if(network::Result::RESULT_OK == this->Connect()) {
        		    // Que? Do I need to init network here, feels like yes, I am.
                    //} else {}
                } else {}
            } else {}

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

    this->m_socket = socket(AF_INET, SOCK_STREAM, 0); // todo move to constants
   	cout << "socket is " << this->m_socket << endl;
    if(network::SocketState::SOCKET_ERROR >= this->m_socket)
    {   
            // something is really wrong if we cannot create a file descriptor
            // https://man7.org/linux/man-pages/man2/socket.2.html
   		    cout << "err SocketGLIBC::Create()" << this->m_socket << endl;
    }
    this->m_servername.sin_family = AF_INET;
    this->m_servername.sin_port = htons (this->port);
    	
    // the below is taken from here
    // 
    // https://stackoverflow.com/questions/2597608/c-socket-connection-timeout
    long arg;
    // Set non-blocking 
  	if( (arg = fcntl(this->m_socket, F_GETFL, NULL)) < 0) { 
     	fprintf(stderr, "Error fcntl(..., F_GETFL) (%s)\n", strerror(errno)); 
     	//exit(0); 
  	} 
  	arg |= O_NONBLOCK; 
  	if( fcntl(this->m_socket, F_SETFL, arg) < 0) { 
     	fprintf(stderr, "Error fcntl(..., F_SETFL) (%s)\n", strerror(errno)); 
     	//exit(0); 
  	} 
  
    this->state = network::State::CREATED;

    cout << "ok socket is " << this->m_socket << endl;
    return network::Result::RESULT_OK;
}

network::Result SocketGLIBC::Resolve()
{
    cout << this->state << this->m_socket << "SocketGLIBC::Resolve()" << endl;
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

            cout << "ok resolved" << this->m_socket << endl;
            return network::Result::RESULT_OK;
        } 
        // https://forums.opensuse.org/showthread.php/450418-pthread_exit-c-and-FATAL-exception-not-rethrown
        catch (abi::__forced_unwind&)
        {	
        	printf("%d ", this->m_socket);
         	printf("SocketGLIBC::Connect() forced unwind, shutting down \n");
        	throw;
        }
        catch(...)
        {
  			cout << "SocketGLIBC::Resolve() failed :( " << endl;
			return network::Result::RESULT_ERROR;
        }
        
    cout << "SocketGLIBC::Resolve() failed :( " << endl;
	return network::Result::RESULT_ERROR;
}

network::Result SocketGLIBC::Connect()
{
    cout << this->state << this->m_socket << "SocketGLIBC::Connect()" << endl;
	
	if(network::State::HOST_RESOLVED == this->state)
	{
		try
        {
		    cout << this->m_servername.sin_family <<" "<<this->m_servername.sin_port << " "<< endl;///this->m_servername.sin_addr<<" " << endl;
		    int err = connect(this->m_socket
			    , (struct sockaddr *) &this->m_servername
			    , sizeof (this->m_servername));
        
        	// the below is taken from here
        	// 
        	// https://stackoverflow.com/questions/2597608/c-socket-connection-timeout
        	//
 			if (err < 0)
 			{ 
     			if (errno == EINPROGRESS)
     			{ 
        			fprintf(stderr, "EINPROGRESS in connect() - selecting\n"); 
        
        			fd_set myset; 
  					struct timeval tv; 
  					int valopt;
  					long res;
  					socklen_t lon;
  					
        			do 
        			{ 
           				tv.tv_sec = 0; 
           				tv.tv_usec = this->connect_timeout_us; 
           				FD_ZERO(&myset); 
           				FD_SET(this->m_socket, &myset); 
           				res = select(this->m_socket+1, NULL, &myset, NULL, &tv); 
           				if (res < 0 && errno != EINTR)
           				{ 
              				fprintf(stderr, "Error connecting %d - %s\n", errno, strerror(errno)); 
              				return network::Result::RESULT_ERROR;
              				//exit(0); 
           				} 
          				else if (res > 0)
          				{ 
              				// Socket selected for write 
              				lon = sizeof(int); 
              				if (getsockopt(this->m_socket, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon) < 0) 
              				{ 
                 				fprintf(stderr, "Error in getsockopt() %d - %s\n", errno, strerror(errno)); 
                 				return network::Result::RESULT_ERROR;
                                //exit(0);
              				} 
              				// Check the value returned... 
              				if (valopt)
              				{ 
                 				fprintf(stderr, "Error in delayed connection() %d - %s\n", valopt, strerror(valopt) ); 
			                    return network::Result::RESULT_ERROR;
                 				//exit(0); 
              				} 
              				break; 
           				} 
           				else
           				{ 
              				fprintf(stderr, "Timeout in select() - Cancelling!\n"); 
        			        return network::Result::RESULT_ERROR;
              				//exit(0); 
           				} 
        			}
        			while (1); 
     			} // if (errno == EINPROGRESS) 
     			else
     			{ 
        			fprintf(stderr, "Error connecting %d - %s\n", errno, strerror(errno)); 
			        return network::Result::RESULT_ERROR;
        			//exit(0); 
     			} 
  			} // if (err < 0)
  
  
    	    if (network::SocketState::SOCKET_ERROR >= err)
    	    {
		        cout << "SocketGLIBC conn failed :( " << endl;
			    return network::Result::RESULT_ERROR;
    	    }
        } 
        // https://forums.opensuse.org/showthread.php/450418-pthread_exit-c-and-FATAL-exception-not-rethrown
        catch (abi::__forced_unwind&)
        {	
        	printf("%d ", this->m_socket);
         	printf("SocketGLIBC::Connect() forced unwind, shutting down \n");
        	throw;
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
        {
            int err = write(this->m_socket, data.c_str(), data.size());
            if(network::Result::RESULT_OK >= err)
            {
                cout<<"write error, target dropped the connection, shutting down "<< this->m_socket <<endl;
                return this->Shutdown();
            }
            cout<<">>>>>>>>>>>>>> !!! BANG !!! >>>>>>>>>>>>>>>> " << "Socket=" << this->m_socket << " state=" << this->state << endl;
            return network::Result::RESULT_OK;
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

    //if(network::SocketState::SOCKET_ERROR == this->m_socket)
    //    return network::Result::RESULT_OK;
        
    try
    {
        shutdown(this->m_socket, this->shutdown_mode); // todo move to constants
    }
    // https://forums.opensuse.org/showthread.php/450418-pthread_exit-c-and-FATAL-exception-not-rethrown
    catch (abi::__forced_unwind&)
    {
    	printf("SocketGLIBC::Shutdown shutdown forced unwind\n");
        throw;
    }
    catch(...)
    {
        cout << this->m_socket << " failed to shutdown()" << endl;
    }

    try
    {
        int err = close(this->m_socket);
        if(network::SocketState::SOCKET_ERROR >= err)
        {
	   	    cout << "err close socket is " << err << endl;
            return network::Result::RESULT_ERROR;
        } 
    }
    // https://forums.opensuse.org/showthread.php/450418-pthread_exit-c-and-FATAL-exception-not-rethrown
    catch (abi::__forced_unwind&)
    {
        printf("SocketGLIBC::Shutdown close forced unwind\n");
        throw;
    }
    catch(...)
    {
	   	    cout << "err close socket is " << endl;
            return network::Result::RESULT_ERROR;
    }
	
	cout << this->m_socket <<" SocketGLIBC::Shutdown() OK " << endl;
    return network::Result::RESULT_OK;
}

network::Result SocketGLIBC::send(const string& buffer)
{
    cout << this->state << this->m_socket << " SocketGLIBC Write" << endl;

    // TODO: Refactor this shit
    switch(this->getState())    
    {
        case(network::State::ERROR): {
            if(network::Result::RESULT_OK == this->Create()) {
                if(network::Result::RESULT_OK == this->Resolve()) {
                    if(network::Result::RESULT_OK == this->Connect()) {
                        this->Write(buffer);
                    } else {}
                } else {}
            } else {}
            break;
        }
        case(network::State::CREATED): {
            if(network::Result::RESULT_OK == this->Resolve()) {
                if(network::Result::RESULT_OK == this->Connect()) {
                    this->Write(buffer);
                } else {}
            } else {}
            break;
        }
        case(network::State::HOST_RESOLVED): {
                if(network::Result::RESULT_OK == this->Connect()) {
                   this->Write(buffer);
                } else {}
            break;
        }
        case(network::State::CONNECTED): {
            this->Write(buffer);
            break;
        }
        default:
            break;
    }
    return network::Result::RESULT_OK; // is this a behavior I want to see? maybe add try catch and return error when fails?
}

network::Result SocketGLIBC::receive(string& buffer)
{
    buffer[0];
    // TODO:
    // Raise NotImplementedError
    return network::Result::RESULT_ERROR;
}
