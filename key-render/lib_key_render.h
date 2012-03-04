#ifndef H_LIBKEYRENDER_H
#  define H_LIBKEYRENDER_H

#  ifdef WIN32
#   ifdef DYNAMIC_LIB
#    ifdef key_render_EXPORTS
#      define LIB_KEY_RENDER __declspec(dllexport)
#    else
#      define LIB_KEY_RENDER __declspec(dllimport)
#    endif
#   else
#    define LIB_KEY_RENDER
#   endif
#  else
#    define LIB_KEY_RENDER
#  endif

#endif
