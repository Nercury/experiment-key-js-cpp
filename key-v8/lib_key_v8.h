#ifndef H_LIBKEYV8_H
#  define H_LIBKEYV8_H

#  ifdef WIN32
#   ifdef DYNAMIC_LIB
#    ifdef key_v8_EXPORTS
#      define LIB_KEY_V8 __declspec(dllexport)
#    else
#      define LIB_KEY_V8 __declspec(dllimport)
#    endif
#   else
#    define LIB_KEY_V8
#   endif
#  else
#    define LIB_KEY_V8
#  endif

#endif
