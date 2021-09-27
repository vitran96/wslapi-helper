#include "pch.h"
#include "framework.h"

#include "wslapi_library.h"

#include <stdexcept>

wslapi_library& wslapi_library::load()
{
    static wslapi_library wslapilib;
    return wslapilib;
}

wslapi_library::wslapi_library()
{
    _wslapi_dll = LoadLibraryEx(L"wslapi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (_wslapi_dll == nullptr)
    {
        throw std::runtime_error("Failed to load wslapi.dll. Try target x64 (amd64)");
    }

    _is_distribution_registered = (WSL_IS_DISTRIBUTION_REGISTERED)GetProcAddress(_wslapi_dll, "WslIsDistributionRegistered");
    _register_distribution = (WSL_REGISTER_DISTRIBUTION)GetProcAddress(_wslapi_dll, "WslRegisterDistribution");
    _unregister_distribution = (WSL_UNREGISTER_DISTRIBUTION)GetProcAddress(_wslapi_dll, "WslUnregisterDistribution");
    _get_configure_distribution = (WSL_GET_DISTRIBUTION_CONFIGURATION)GetProcAddress(_wslapi_dll, "WslGetDistributionConfiguration");
    _configure_distribution = (WSL_CONFIGURE_DISTRIBUTION)GetProcAddress(_wslapi_dll, "WslConfigureDistribution");
    _launch_interactive = (WSL_LAUNCH_INTERACTIVE)GetProcAddress(_wslapi_dll, "WslLaunchInteractive");
    _launch = (WSL_LAUNCH)GetProcAddress(_wslapi_dll, "WslLaunch");
}

wslapi_library::~wslapi_library()
{
    if (_wslapi_dll != nullptr)
    {
        FreeLibrary(_wslapi_dll);
    }
}

BOOL wslapi_library::is_distribution_registered(PCWSTR distribution_name)
{
    if (_is_distribution_registered == nullptr)
    {
        throw std::runtime_error("Cannot get procedure WslIsDistributionRegistered");
    }

    return _is_distribution_registered(distribution_name);
}
HRESULT wslapi_library::register_distribution(PCWSTR distribution_name, PCWSTR tar_file_path)
{
    if (_register_distribution == nullptr)
    {
        throw std::runtime_error("Cannot get procedure WslRegisterDistribution");
    }

    return _register_distribution(distribution_name, tar_file_path);
}

HRESULT wslapi_library::unregister_distribution(PCWSTR distribution_name)
{
    if (_unregister_distribution == nullptr)
    {
        throw std::runtime_error("Cannot get procedure WslUnregisterDistribution");
    }

    return _unregister_distribution(distribution_name);
}

HRESULT wslapi_library::get_distribution_configuration(
    PCWSTR distribution_name
    , ULONG* distributionVersion
    , ULONG* defaultUID
    , WSL_DISTRIBUTION_FLAGS* wslDistributionFlags
    , PSTR** defaultEnvironmentVariables
    , ULONG* defaultEnvironmentVariableCount
) {
    if (_get_configure_distribution == nullptr)
    {
        throw std::runtime_error("Cannot get procedure WslGetDistributionConfiguration");
    }

    return _get_configure_distribution(
        distribution_name
        , distributionVersion
        , defaultUID
        , wslDistributionFlags
        , defaultEnvironmentVariables
        , defaultEnvironmentVariableCount
    );
}

HRESULT wslapi_library::configure_distribution(
    PCWSTR distribution_name
    , ULONG default_uid
    , WSL_DISTRIBUTION_FLAGS flags
) {
    if (_configure_distribution == nullptr)
    {
        throw std::runtime_error("Cannot get procedure WslConfigureDistribution");
    }

    return _configure_distribution(
        distribution_name
        , default_uid
        , flags
    );
}

HRESULT wslapi_library::launch_interactive(
    PCWSTR distribution_name
    , PCWSTR command
    , BOOL use_current_working_directory
    , DWORD* exit_code
) {
    if (_launch_interactive == nullptr)
    {
        throw std::runtime_error("Cannot get procedure WslLaunchInteractive");
    }

    return _launch_interactive(
        distribution_name
        , command
        , use_current_working_directory
        , exit_code
    );
}

HRESULT wslapi_library::launch(
    PCWSTR distribution_name
    , PCWSTR command
    , BOOL use_current_working_directory
    , HANDLE std_In
    , HANDLE std_out
    , HANDLE std_err
    , HANDLE* process
) {
    if (_launch == nullptr)
    {
        throw std::runtime_error("Cannot get procedure WslLaunch");
    }

    return _launch(
        distribution_name
        , command
        , use_current_working_directory
        , std_In
        , std_out
        , std_err
        , process
    );
}
