
#ifndef PHP_CALLEE_H
#define PHP_CALLEE_H

extern zend_module_entry callee_module_entry;
#define phpext_callee_ptr &callee_module_entry

#define PHP_CALLEE_VERSION "0.1.0"

#ifdef PHP_WIN32
#    define PHP_CALLEE_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#    define PHP_CALLEE_API __attribute__ ((visibility("default")))
#else
#    define PHP_CALLEE_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#if defined(ZTS) && defined(COMPILE_DL_CALLEE)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif
