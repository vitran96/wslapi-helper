#pragma once

#ifndef WSLAPI_LIBRARY_H
#define WSLAPI_LIBRARY_H

#include "wslapi_library_def.h"

#include <WinSock2.h>
#include <Windows.h>
#include <winapifamily.h>
#include <wslapi.h>

#ifndef ERROR_LINUX_SUBSYSTEM_NOT_PRESENT
#define ERROR_LINUX_SUBSYSTEM_NOT_PRESENT 414L
#endif // !ERROR_LINUX_SUBSYSTEM_NOT_PRESENT

typedef BOOL(STDAPICALLTYPE* WSL_IS_DISTRIBUTION_REGISTERED)(PCWSTR);
typedef HRESULT(STDAPICALLTYPE* WSL_REGISTER_DISTRIBUTION)(PCWSTR, PCWSTR);
typedef HRESULT(STDAPICALLTYPE* WSL_UNREGISTER_DISTRIBUTION)(PCWSTR);
typedef HRESULT(STDAPICALLTYPE* WSL_CONFIGURE_DISTRIBUTION)(PCWSTR, ULONG, WSL_DISTRIBUTION_FLAGS);
typedef HRESULT(STDAPICALLTYPE* WSL_GET_DISTRIBUTION_CONFIGURATION)(PCWSTR, ULONG*, ULONG*, WSL_DISTRIBUTION_FLAGS*, PSTR**, ULONG*);
typedef HRESULT(STDAPICALLTYPE* WSL_LAUNCH_INTERACTIVE)(PCWSTR, PCWSTR, BOOL, DWORD*);
typedef HRESULT(STDAPICALLTYPE* WSL_LAUNCH)(PCWSTR, PCWSTR, BOOL, HANDLE, HANDLE, HANDLE, HANDLE*);

class WSLAPI_LIBRARY_API wslapi_library
{
public:
    static wslapi_library& load();

    BOOL is_distribution_registered(PCWSTR distribution_name);
    HRESULT register_distribution(PCWSTR distribution_name, PCWSTR tar_file_path);
    HRESULT unregister_distribution(PCWSTR distribution_name);
    HRESULT get_distribution_configuration(
        PCWSTR distribution_name
        , ULONG* distributionVersion
        , ULONG* defaultUID
        , WSL_DISTRIBUTION_FLAGS* wslDistributionFlags
        , PSTR** defaultEnvironmentVariables
        , ULONG* defaultEnvironmentVariableCount
    );
    HRESULT configure_distribution(
        PCWSTR distribution_name
        , ULONG default_uid
        , WSL_DISTRIBUTION_FLAGS flags
    );
    HRESULT launch_interactive(
        PCWSTR distribution_name
        , PCWSTR command
        , BOOL use_current_working_directory
        , DWORD* exit_code
    );
    HRESULT launch(
        PCWSTR distribution_name
        , PCWSTR command
        , BOOL use_current_working_directory
        , HANDLE std_In
        , HANDLE std_out
        , HANDLE std_err
        , HANDLE* process
    );

    wslapi_library(wslapi_library&) = delete;
    wslapi_library& operator=(wslapi_library&) = delete;
private:
    wslapi_library();
    ~wslapi_library();

    HMODULE _wslapi_dll;
    WSL_IS_DISTRIBUTION_REGISTERED _is_distribution_registered;
    WSL_REGISTER_DISTRIBUTION _register_distribution;
    WSL_UNREGISTER_DISTRIBUTION _unregister_distribution;
    WSL_GET_DISTRIBUTION_CONFIGURATION _get_configure_distribution;
    WSL_CONFIGURE_DISTRIBUTION _configure_distribution;
    WSL_LAUNCH_INTERACTIVE _launch_interactive;
    WSL_LAUNCH _launch;
};
#endif // !WSLAPI_LIBRARY_H
