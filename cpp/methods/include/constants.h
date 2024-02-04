#ifndef FLOODCONSTANTS_H
#define FLOODCONSTANTS_H

#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::vector;
using std::unordered_map;

static const string rn = "\r\n";

namespace flood
{

enum RequestType {
	  GET
	, RGET
	, POST
    , BYPASS
	, NONE
};

/*
    def getMethodType(method: str) -> str:
        return "GET" if {method.upper()} & {"CFB", "CFBUAM", "GET", "COOKIE", "OVH", "EVEN",
                                            "DYN", "SLOW", "PPS", "APACHE",
                                            "BOT", } \
            else "POST" if {method.upper()} & {"POST", "XMLRPC", "STRESS"} \
            else "HEAD" if {method.upper()} & {"GSB", "HEAD"} \
            else "REQUESTS"
*/
static const unordered_map<RequestType, string> RequestTypeStr = { 
	  { RequestType::GET    , "GET"  }
	, { RequestType::RGET   , "RGET" }
	, { RequestType::POST   , "POST" }
    , { RequestType::BYPASS , "GET"  }
	, { RequestType::NONE   , ""     }
};

/*
        self._payload = (self._defaultpayload +
                         'Accept-Encoding: gzip, deflate, br\r\n'
                         'Accept-Language: en-US,en;q=0.9\r\n'
                         'Cache-Control: max-age=0\r\n'
                         'Connection: Keep-Alive\r\n'
                         'Sec-Fetch-Dest: document\r\n'
                         'Sec-Fetch-Mode: navigate\r\n'
                         'Sec-Fetch-Site: none\r\n'
                         'Sec-Fetch-User: ?1\r\n'
                         'Sec-Gpc: 1\r\n'
                         'Pragma: no-cache\r\n'
                         'Upgrade-Insecure-Requests: 1\r\n')
*/
// several methods are using custom values for 'User-Agent' and 'Content-Length'
// so there is a chance I will have to switch to a unordered_map<string, string>
static const string TCPHeaderBase = 
   string("Accept") + ": " + "*/*" + rn
        + "Accept-Encoding" + ":" + "gzip, deflate, br" + rn
        + "Accept-Language" + ":"+ "ru-RU,ru;q=0.9,en-US,en;q=0.7" + rn
        + "Cache-Control" + ":" + "no-cache" + rn // "max-age=0" + rn
        + "Connection" + ":" + "Keep-Alive" + rn
        + "Sec-Fetch-Dest" + ":" + "document" + rn
        + "Sec-Fetch-Mode" + ":" + "navigate" + rn
        + "Sec-Fetch-Site" + ":" + "none" + rn //"same-origin" + rn
        + "Sec-Fetch-User" + ":" + "?1" + rn
        + "Pragma" + ":" + "no-cache" + rn
        + "Upgrade-Insecure-Requests" + ":" +"1" + rn
;


} // flood
#endif