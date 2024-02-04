#ifndef COTTON_TARGET_H
#define COTTON_TARGET_H

#include <boost/url/detail/url_impl.hpp>
#include <string>
#include <boost/url.hpp>

using boost::core::string_view;
using boost::system::result;
using boost::urls::url_view;
using boost::urls::parse_uri;

namespace cotton 
{
class Target : public url_view
{
public:
    Target(const std::string& url)
        : url_view(parse_uri(string_view(url)).value())
    {
        //std::cout << host_ipv4_address();
    };

};

} // namespace
#endif