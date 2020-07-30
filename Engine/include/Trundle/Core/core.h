#pragma once

#if defined(TRUNDLE_OS_WINDOWS)
#if defined(TRUNDLE_BUILD_LIB)
#define TRUNDLE_API __declspec(dllexport)
#else
#define TRUNDLE_API __declspec(dllimport)
#endif
#else // #if !defined(TRUNDLE_OS_WINDOWS)
#define TRUNDLE_API
#endif
