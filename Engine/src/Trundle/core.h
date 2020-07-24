#pragma once

//#if defined(_WIN32)
#if defined(TRUNDLE_WINDOWS_OS)
#ifdef TRUNDLE_BUILD_LIB
#define TRUNDLE_API __declspec(dllexport)
#else
#define TRUNDLE_API __declspec(dllimport)
#endif
#else // #if !defined(_WIN32)
#define TRUNDLE_API
#endif
