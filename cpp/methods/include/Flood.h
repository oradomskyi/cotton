#ifndef FLOOD_H
#define FLOOD_H

#include "constants.h"
#include "Target.h"
#include "../../client/include/Client.h"

namespace cotton{
class Flood : public Client 
{
protected:
    Target target_;

public:
    Flood(io_context& io_context, tcp::resolver::results_type& endpoints, const string& url)
    : Client(io_context, endpoints)
    , target_(url)
    {};

        
};
}
#endif