#include "URL.h"

std::string URL::scheme_prs(std::string& url_rest)
{
	size_t scheme_signature_pos = url_str.find("://");
	if (scheme_signature_pos == std::string::npos) return "";

	std::string scheme_str = url_str.substr(0, scheme_signature_pos);
	if (scheme_str.find(':') != std::string::npos || scheme_str.find('/') != std::string::npos) return "";

	url_rest = url_str.substr(scheme_signature_pos + 3, url_str.length());
	return scheme_str;
}

void URL::authority_prs(std::string url_rest)
{
	size_t sl = url_rest.find('/');
	size_t q = url_rest.find('?');
	size_t oc = url_rest.find('#');

	size_t good = std::min({ sl, q, oc });
	if (good == std::string::npos) authority = url_rest;
	authority = url_rest.substr(0, good);
	

	//if (url_rest.find('/') == std::string::npos) authority = url_rest;
	//authority = url_rest.substr(0, url_rest.find('/'));
}

std::string URL::userinfo_prs(std::string& url_rest)
{
	if (url_rest.find('@') == std::string::npos) return "";
	
	bool fl_colom = false;
	for (int i = 0; i < url_rest.length(); i++)
	{
		if (url_rest[i] == '/') { username = ""; return ""; }

		if (url_rest[i] == '@' && fl_colom)
		{	
			password = url_rest.substr(username.length() + 1, i - username.length() - 1);
			if (username.empty() && password.empty()) return "";
			url_rest = url_rest.substr(username.length() + password.length() + 2, url_rest.length());
			return username + ':' + password; 			
		}

		if (url_rest[i] == ':' && !fl_colom)
		{
			fl_colom = true;
			username = url_rest.substr(0, i);
		}
	}
}

void URL::host_prs(std::string& url_rest)
{
	size_t oc = url_rest.find('#');
	size_t q = url_rest.find('?');
	size_t sl = url_rest.find('/');


	size_t index_slash = std::min({ sl,oc,q });
	size_t url_colom = url_rest.find(':');

	if (url_colom == std::string::npos && index_slash == std::string::npos)
	{
		host = url_rest.substr(0, index_slash);
		hostname = host;
		port = "";	
	}

	else if (url_colom != std::string::npos && index_slash == std::string::npos)
	{
		host = url_rest.substr(0, url_rest.length());
		hostname = url_rest.substr(0, url_colom);
		port = url_rest.substr(url_colom + 1, url_rest.length() - url_colom - 1);
	}

	else if (url_colom != std::string::npos && index_slash != std::string::npos)
	{
		host = url_rest.substr(0, index_slash);
		hostname = url_rest.substr(0, url_colom);
		port = url_rest.substr(url_colom + 1, index_slash - hostname.length() - 1);
	}

	else if (url_colom == std::string::npos && index_slash != std::string::npos)
	{
		host = url_rest.substr(0, index_slash);
		hostname = host;
		port = "";
	}

	if (index_slash == std::string::npos) url_rest = "";
	else url_rest = url_rest.substr(host.length(), url_rest.length() - host.length());
}

void URL::path_prs(std::string& url_rest)
{
	
	size_t end = url_rest.find('?');

	if (end == std::string::npos)
	{
		end = url_rest.find('#');
		if (end == std::string::npos)
		{
			path = url_rest;
			url_rest = "";
			return;
		}
	}

	path = url_rest.substr(0, end);
	url_rest = url_rest.substr(path.length(), url_rest.length() - path.length());
}

void URL::query_prs(std::string& url_rest)
{
	size_t sl = url_rest.find('/');
	size_t oc = url_rest.find('#');

	if (sl == oc)
	{
		query = url_rest.substr(1, url_rest.length() - 1);
		url_rest = "";
		return;
	}

	size_t good = std::min(sl, oc);
	query = url_rest.substr(0, good);
	url_rest = url_rest.substr(good, url_rest.length() - good);



}

void URL::fragment_prs(std::string& url_rest)
{
	fragment = url_rest;
	url_rest = "";

}


std::string URL::parsed()
{
	/*
	scheme + authority + path,
	sheme + path,
	path
	*/

	std::string url_rest = url_str;


	scheme = scheme_prs(url_rest);
	if (url_rest.empty()) return "";
	//std::cout << "rest: " <<  url_rest << std::endl;

	authority_prs(url_rest);
	if (url_rest.empty()) return "";

	userinfo = userinfo_prs(url_rest);
	if (url_rest.empty()) return "";
	//std::cout << "rest: " << url_rest << std::endl;

	host_prs(url_rest);
	if (url_rest.empty()) return "";
	//std::cout << "rest: " << url_rest << std::endl;

	if (url_rest[0] == '?')
	{
		url_rest = url_rest.substr(1);
		query_prs(url_rest);
		if (url_rest.empty()) return "";
		//std::cout << "rest: " << url_rest << std::endl;
		if (url_rest[0] == '#') {
			url_rest = url_rest.substr(1);
			fragment_prs(url_rest);
		}


	}
	else if (url_rest[0] == '#')
	{
		url_rest = url_rest.substr(1);
		fragment_prs(url_rest);

	}
	else if (url_rest[0] == '/')
	{
		url_rest = url_rest.substr(1);
		path_prs(url_rest);
		if (url_rest.empty()) return "";
		//std::cout << "rest: " << url_rest << std::endl;
		if (url_rest[0] == '#') {
			url_rest = url_rest.substr(1);
			fragment_prs(url_rest);
		}
		else if (url_rest[0] == '?')
		{
			url_rest = url_rest.substr(1);
			query_prs(url_rest);
			if (url_rest.empty()) return "";
			//std::cout << "rest: " << url_rest << std::endl;
			if (url_rest[0] == '#') {
				url_rest = url_rest.substr(1);
				fragment_prs(url_rest);
			}

		}

	}

	return url_rest;	
}
