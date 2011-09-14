#pragma once

#include <key-common/lib_key_common.h>
#include <string>

#ifdef WIN32
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif

LIB_KEY_COMMON void setAppPath(char p[]);
LIB_KEY_COMMON std::string fullPathTo(const std::string& file);
LIB_KEY_COMMON std::string getAppPath();
LIB_KEY_COMMON std::string joinPath(const std::string& root, const std::string& file);
LIB_KEY_COMMON bool stringFromFile(std::string & output, const std::string& filename);