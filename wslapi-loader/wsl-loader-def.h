#pragma once

#ifndef WSLAPILOADER_DEF_H
#define WSLAPILOADER_DEF_H

#ifdef WSLAPILOADER_EXPORTS
#define WSLAPILOADER_API __declspec(dllexport)
#else
#define WSLAPILOADER_API __declspec(dllimport)
#endif

#endif // !WSLAPILOADER_DEF_H
