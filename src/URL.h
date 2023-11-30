#pragma once
#include <iostream>

class URL
{
public:
	URL(::std::string _url) { url_str = _url; parsed(); }

	std::string get_url() { return url_str; }
	std::string get_scheme() { return scheme; }
	std::string get_authority() { return authority; }
	std::string get_userinfo() { return userinfo; }
	std::string get_username() { return username; }
	std::string get_password() { return password; }
	std::string get_host() { return host; }
	std::string get_hostname() { return hostname; }
	std::string get_port() { return port; }
	std::string get_path() { return path; }
	std::string get_query() { return query; }
	std::string get_fragment() { return fragment; }

	
	
	

private:
	std::string url_str;
	std::string scheme;
	std::string authority;
	std::string userinfo;
	std::string username;
	std::string password;
	std::string host;
	std::string hostname;
	std::string port;

	std::string path;
	std::string query;
	std::string fragment;

	std::string parsed();

	std::string scheme_prs(std::string&);
	void authority_prs(std::string);
	std::string userinfo_prs(std::string&);
	void host_prs(std::string&);
	void path_prs(std::string&);
	void query_prs(std::string&);
	void fragment_prs(std::string&);

};

