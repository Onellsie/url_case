#include "URL.h"
#include "Test_Url.h"
#include <fstream>
#include <string> 
#include <windows.h>

int main()
{
    std::string url;

    std::ifstream in("urls.txt");
    if (in.is_open())
    {
        while (std::getline(in, url)) { Test_Url t(url); t.test_all_methods(); }
    }
    in.close(); 
    system("pause");
}


