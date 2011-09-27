#ifndef H_LIBKEYOPENGL_H
#  define H_LIBKEYOPENGL_H

#  ifdef WIN32
#   ifdef DYNAMIC_LIB
#    ifdef key_opengl_EXPORTS
#      define LIB_KEY_OPENGL __declspec(dllexport)
#    else
#      define LIB_KEY_OPENGL __declspec(dllimport)
#    endif
#   else
#    define LIB_KEY_OPENGL
#   endif
#  else
#    define LIB_KEY_OPENGL
#  endif

#endif
