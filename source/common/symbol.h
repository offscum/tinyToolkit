#ifndef __COMMON__SYMBOL__H__
#define __COMMON__SYMBOL__H__


/**
 *
 * 作者: hm
 *
 * 说明: 符号
 *
 */


#if defined(_MSC_VER)
#
#  pragma warning(disable:4251)
#
#  define TOOLKIT_SYMBOL_EXPORT __declspec(dllexport)
#  define TOOLKIT_SYMBOL_IMPORT __declspec(dllimport)
#
#elif defined(__GNUC__)
#
#  define TOOLKIT_SYMBOL_EXPORT __attribute__((visibility("default")))
#  define TOOLKIT_SYMBOL_IMPORT
#
#else
#
#  define TOOLKIT_SYMBOL_EXPORT
#  define TOOLKIT_SYMBOL_IMPORT
#
#endif


#if defined(TOOLKIT_API_IMPORT)
#
#  define TOOLKIT_API TOOLKIT_SYMBOL_IMPORT
#
#else
#
#  define TOOLKIT_API TOOLKIT_SYMBOL_EXPORT
#
#endif


#endif // __COMMON__SYMBOL__H__
