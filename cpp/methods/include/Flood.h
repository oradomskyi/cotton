#ifndef FLOOD_H
#define FLOOD_H


#include "constants.h"
#include "../../client/include/Client.h"

namespace cotton{
class Flood : public Client 
{
public:
    Flood(boost::asio::io_context& io_context, tcp::resolver::results_type& endpoints)
    : Client(io_context, endpoints)
    {};

    // kind-a too much
    //Flood(Flood&& other)
    //: Client(std::move(other))
    //{std::cout << "Flood move" << std::endl;};

};
}
#endif