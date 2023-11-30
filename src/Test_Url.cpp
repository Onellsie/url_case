#include "Test_Url.h"

void Test_Url::test_all_methods()
{
	URL u(str_u);
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "url: " << u.get_url() << std::endl;
    std::cout << "scheme: " << u.get_scheme() << std::endl;
    std::cout << "authority: " << u.get_authority() << std::endl;
    std::cout << "userinfo: " << u.get_userinfo() << std::endl;
    std::cout << "usename: " << u.get_username() << std::endl;
    std::cout << "password: " << u.get_password() << std::endl;
    std::cout << "host: " << u.get_host() << std::endl;
    std::cout << "hostname: " << u.get_hostname() << std::endl;
    std::cout << "port: " << u.get_port() << std::endl;
    std::cout << "path: " << u.get_path() << std::endl;
    std::cout << "query: " << u.get_query() << std::endl;
    std::cout << "fragment: " << u.get_fragment() << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

}
