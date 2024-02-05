#include <vector>

#include <boost/fiber/all.hpp> // todo replace with only necessary includes
#include "methods/include/all.h"
#include "client/include/Client.h"


using std::vector;
using boost::fibers::fiber;
using std::string;


int main(int argc, char* argv[])
{
  try
  {
    if (argc < 3)
    {
      std::cerr << "Usage: client <host> <port>\n";
      return 1;
    }

    cotton::io_context io_context;
    cotton::tcp::resolver r(io_context);

    vector<cotton::tcp::resolver::results_type> resolver_results;
    resolver_results.reserve(2);
    
//string upath1e = "http://example.com/\%D1\%88\%D0\%BB\%D1\%8F\%D1\%85/\%D1\%81\%D1\%8E\%D0\%B4\%D0\%B8?\%D0\%BA\%D0\%BB\%D1\%8E\%D1\%87=\%D0\%B7\%D0\%BD\%D0\%B0\%D1\%87";
//string upath1d = "http://example.com/шлях/сюди?ключ=знач";

//string upathc = urlEncode(upath1d);
//std::cout << upath1d << '\n' << upathc <<'\n';

//string upath2 = "http://john:pass@хост.домен:8000";

    vector<string> urls = {"http://37.187.56.77", "https://api.restful-api.dev/objects", "https://httpbin.org/anything/", "http://127.0.0.1:65124", "http://127.0.0.1:65125"};
    
    //int i=0;
    for (int i = 0; i < 4; i+=2)
    {    
        resolver_results.push_back(std::move(r.resolve(argv[i+1], argv[i+2])));
    }
    
 

    vector<cotton::Client*> clients;
    int n_threads_per_target = 1000000;
    clients.reserve(n_threads_per_target);
    int i_target = 0;
    for (int i = 0; i < n_threads_per_target; i++)    
    {   
 
        clients.push_back(new cotton::GET(io_context, resolver_results[i_target], urls[0])); 
        //clients.push_back(new cotton::BYPASS(io_context, resolver_results[i], urls[1])); i++;
        //clients.push_back(new cotton::Client(io_context, resolver_results[i]));i++;
        //clients.push_back(new cotton::Client(io_context, resolver_results[i]));i++;
    
    }
    for(auto& c : clients)
    {
        fiber f( std::ref(*c) );
        f.join();

        //if (0 == i%10000)
        //io_context.poll_one();

         //   {
         //       io_context.restart();
         //       io_context.poll();
         //   }

    }
    std::cout<< "joined" << std::endl;
    
    io_context.run();//_for(std::chrono::milliseconds(100000)); // main thread will halt here
    
    std::cout<< "context.run() exit" << std::endl;
    
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}