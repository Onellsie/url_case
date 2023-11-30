#pragma once
#include <iostream>
#include "URL.h"

class Test_Url
{
public:
	Test_Url(std::string u) { str_u = u; }

	void test_all_methods();

private:
	std::string str_u;
};

