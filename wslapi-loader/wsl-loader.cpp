#include "pch.h"
//
//#include <WinSock2.h>
//#include <Windows.h>
//#include <winapifamily.h>
//#include <wslapi.h>
//
//#include <string>
//
//// This error definition is present in the Spring Creators Update SDK.
//#ifndef ERROR_LINUX_SUBSYSTEM_NOT_PRESENT
//#define ERROR_LINUX_SUBSYSTEM_NOT_PRESENT 414L
//#endif // !ERROR_LINUX_SUBSYSTEM_NOT_PRESENT
//
//typedef BOOL(STDAPICALLTYPE* WSL_IS_DISTRIBUTION_REGISTERED)(PCWSTR);
//typedef HRESULT(STDAPICALLTYPE* WSL_REGISTER_DISTRIBUTION)(PCWSTR, PCWSTR);
//typedef HRESULT(STDAPICALLTYPE* WSL_CONFIGURE_DISTRIBUTION)(PCWSTR, ULONG, WSL_DISTRIBUTION_FLAGS);
//typedef HRESULT(STDAPICALLTYPE* WSL_GET_DISTRIBUTION_CONFIGURATION)(PCWSTR, ULONG*, ULONG*, WSL_DISTRIBUTION_FLAGS*, PSTR**, ULONG*);
//typedef HRESULT(STDAPICALLTYPE* WSL_LAUNCH_INTERACTIVE)(PCWSTR, PCWSTR, BOOL, DWORD*);
//typedef HRESULT(STDAPICALLTYPE* WSL_LAUNCH)(PCWSTR, PCWSTR, BOOL, HANDLE, HANDLE, HANDLE, HANDLE*);
//
//class WslApiLoader
//{
//public:
//    WslApiLoader(const std::wstring& distributionName);
//    ~WslApiLoader();
//
//    BOOL WslIsOptionalComponentInstalled();
//
//    BOOL WslIsDistributionRegistered();
//
//    HRESULT WslRegisterDistribution();
//
//    HRESULT WslConfigureDistribution(ULONG defaultUID,
//        WSL_DISTRIBUTION_FLAGS wslDistributionFlags);
//
//    HRESULT WslLaunchInteractive(PCWSTR command,
//        BOOL useCurrentWorkingDirectory,
//        DWORD* exitCode);
//
//    HRESULT WslLaunch(PCWSTR command,
//        BOOL useCurrentWorkingDirectory,
//        HANDLE stdIn,
//        HANDLE stdOut,
//        HANDLE stdErr,
//        HANDLE* process);
//
//private:
//    std::wstring _distributionName;
//    HMODULE _wslApiDll;
//    WSL_IS_DISTRIBUTION_REGISTERED _isDistributionRegistered;
//    WSL_REGISTER_DISTRIBUTION _registerDistribution;
//    WSL_CONFIGURE_DISTRIBUTION _configureDistribution;
//    WSL_LAUNCH_INTERACTIVE _launchInteractive;
//    WSL_LAUNCH _launch;
//};
//
//extern WslApiLoader g_wslApi;

//#include <iostream>
//
//WslApiLoader::WslApiLoader(const std::wstring& distributionName) :
//    _distributionName(distributionName)
//{
//    _wslApiDll = LoadLibraryEx(L"wslapi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
//    if (_wslApiDll != nullptr) {
//        _isDistributionRegistered = (WSL_IS_DISTRIBUTION_REGISTERED)GetProcAddress(_wslApiDll, "WslIsDistributionRegistered");
//        _registerDistribution = (WSL_REGISTER_DISTRIBUTION)GetProcAddress(_wslApiDll, "WslRegisterDistribution");
//        _configureDistribution = (WSL_CONFIGURE_DISTRIBUTION)GetProcAddress(_wslApiDll, "WslConfigureDistribution");
//        _launchInteractive = (WSL_LAUNCH_INTERACTIVE)GetProcAddress(_wslApiDll, "WslLaunchInteractive");
//        _launch = (WSL_LAUNCH)GetProcAddress(_wslApiDll, "WslLaunch");
//    }
//    else {
//        throw std::runtime_error("Failed to load wslapi library");
//    }
//}
//
//WslApiLoader::~WslApiLoader()
//{
//    if (_wslApiDll != nullptr) {
//        FreeLibrary(_wslApiDll);
//    }
//}
//
//BOOL WslApiLoader::WslIsOptionalComponentInstalled()
//{
//    return ((_wslApiDll != nullptr) &&
//        (_isDistributionRegistered != nullptr) &&
//        (_registerDistribution != nullptr) &&
//        (_configureDistribution != nullptr) &&
//        (_launchInteractive != nullptr) &&
//        (_launch != nullptr));
//}
//
//BOOL WslApiLoader::WslIsDistributionRegistered()
//{
//    return _isDistributionRegistered(_distributionName.c_str());
//}
//
//HRESULT WslApiLoader::WslRegisterDistribution()
//{
//    HRESULT hr = _registerDistribution(_distributionName.c_str(), L"install.tar.gz");
//    if (FAILED(hr)) {
//        std::cout << "Failed " << __FUNCTION__ << std::endl;
//    }
//
//    return hr;
//}
//
//HRESULT WslApiLoader::WslConfigureDistribution(ULONG defaultUID, WSL_DISTRIBUTION_FLAGS wslDistributionFlags)
//{
//    HRESULT hr = _configureDistribution(_distributionName.c_str(), defaultUID, wslDistributionFlags);
//    if (FAILED(hr)) {
//        std::cout << "Failed " << __FUNCTION__ << std::endl;
//    }
//
//    return hr;
//}
//
//HRESULT WslApiLoader::WslLaunchInteractive(PCWSTR command, BOOL useCurrentWorkingDirectory, DWORD* exitCode)
//{
//    HRESULT hr = _launchInteractive(_distributionName.c_str(), command, useCurrentWorkingDirectory, exitCode);
//    if (FAILED(hr)) {
//        std::cout << "Failed " << __FUNCTION__ << std::endl;
//    }
//
//    return hr;
//}
//
//HRESULT WslApiLoader::WslLaunch(PCWSTR command, BOOL useCurrentWorkingDirectory, HANDLE stdIn, HANDLE stdOut, HANDLE stdErr, HANDLE* process)
//{
//    HRESULT hr = _launch(_distributionName.c_str(), command, useCurrentWorkingDirectory, stdIn, stdOut, stdErr, process);
//    if (FAILED(hr)) {
//        std::cout << "Failed " << __FUNCTION__ << std::endl;
//    }
//
//    return hr;
//}
