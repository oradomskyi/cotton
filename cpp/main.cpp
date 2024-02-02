#include <vector>

#include <boost/fiber/all.hpp> // todo replace with only necessary includes
#include "methods/include/all.h"
#include "client/include/Client.h"

using std::vector;
using std::ref;
using boost::fibers::fiber;


int main(int argc, char* argv[])
{
  try
  {
    if (argc < 3)
    {
      std::cerr << "Usage: client <host> <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;
    tcp::resolver r(io_context);

    vector<tcp::resolver::results_type> resolver_results;
    resolver_results.reserve(2);
    
    //int i=0;
    for (int i = 0; i < 4; i+=2)
    {   
        resolver_results.push_back(std::move(r.resolve(argv[i+1], argv[i+2])));
    }
    vector<cotton::Client*> clients;
    clients.reserve(2);
    //for (int i = 0; i < 2; i++)
    //{   
        int i = 0;
        clients.push_back(new cotton::GET(io_context, resolver_results[i])); i++;
        clients.push_back(new cotton::BYPASS(io_context, resolver_results[i])); i++;
        //clients.push_back(std::move(GET(io_context, resolver_results[i])));
    //}
    
    for(int i = 0; i < 2; i++)
    {
        fiber f( ref(*(clients[i])) );//, ref(resolver_results[i]) );
        f.join();
    }
    std::cout<< "joined" << std::endl;

    io_context.run(); // main thread will halt here
    
    std::cout<< "context.run() exit" << std::endl;

  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}