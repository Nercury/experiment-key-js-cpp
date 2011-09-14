#ifndef H_LIBKEYWINDOW_H
#  define H_LIBKEYWINDOW_H

#  ifdef WIN32
#   ifdef DYNAMIC_LIB
#    ifdef key_window_EXPORTS
#      define LIB_KEY_WINDOW __declspec(dllexport)
#    else
#      define LIB_KEY_WINDOW __declspec(dllimport)
#    endif
#   else
#    define LIB_KEY_WINDOW
#   endif
#  else
#    define LIB_KEY_WINDOW
#  endif

#endif
