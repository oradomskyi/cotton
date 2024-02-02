#ifndef COTTON_CLIENTINTERFACE_H
#define COTTON_CLIENTINTERFACE_H

namespace cotton {
class ClientInterface 
{
public:
        
    virtual void operator()() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};
}
#endif