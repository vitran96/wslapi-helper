#pragma once

#ifndef WSLAPI_LIBRARY_DEF_H
#define WSLAPI_LIBRARY_DEF_H

#ifdef WSLAPI_LIBRARY_EXPORTS
#define WSLAPI_LIBRARY_API __declspec(dllexport)
#else
#define WSLAPI_LIBRARY_API __declspec(dllimport)
#endif

#endif // !WSLAPI_LIBRARY_DEF_H
