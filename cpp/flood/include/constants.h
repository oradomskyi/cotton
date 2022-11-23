#ifndef FLOODCONSTANTS_H
#define FLOODCONSTANTS_H

#include <vector>
#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;
using std::pair;
using std::vector;

static const string rn = "\\r\\n";

namespace flood
{

enum State {
      ERROR = -1
  	, READY
	, RUNNING
	, HALT
};

enum RequestType {
	  GET
	, RGET
	, POST
    , BYPASS
	, NONE
};

static const unordered_map<RequestType, string> RequestTypeStr = { 
	  { RequestType::GET    , "GET"  }
	, { RequestType::RGET   , "RGET" }
	, { RequestType::POST   , "POST" }
    , { RequestType::BYPASS , "BYPASS"  }
	, { RequestType::NONE   , ""     }
};

// several methods are using custom values for 'User-Agent' and 'Content-Length'
// so there is a chance I will have to switch to a unordered_map<string, string>
static const string TCPHeaderBase = 
   string("Accept") + ": " + "*/*" + rn
        + "Accept-Encoding" + ": " + "gzip, deflate, br" + rn
        + "Accept-Language" + ": "+ "ru-RU,ru;q=0.9,en-US,en;q=0.7" + rn
        + "Cache-Control" + ": " + "max-age=0" + rn
        + "Connection" + ": " + "Keep-Alive" + rn
        + "Sec-Fetch-Dest" + ": " + "document" + rn
        + "Sec-Fetch-Mode" + ": " + "navigate" + rn
        + "Sec-Fetch-Site" + ": " + "same-origin" + rn
        + "Sec-Fetch-User" + ": " + "?1" + rn
        + "Pragma" + ": " + "no-cache" + rn
;

} // flood
#endif
