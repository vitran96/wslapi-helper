#include <wslapi_library.h>

#include <iostream>
#include <string>

int main()
{
    try
    {
        std::wstring distro_name(L"Ubuntu-18.04");

        BOOL is_registered = wslapi_library::load().is_distribution_registered(distro_name.c_str());
        std::wcout << L"Is " << distro_name << " registered? " << is_registered << L"\r\n";
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << "\r\n";
        return 1;
    }
}
