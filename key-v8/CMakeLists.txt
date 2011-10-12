project(key-v8)

# if library is SHARED, uncoment following lines:
#if(WIN32)
# 	add_definitions(-DDYNAMIC_LIB)
#endif(WIN32)

add_library(key-v8 STATIC 
	lib_key_v8.h
	reflect.hpp
	KeyV8.h
	KeyV8.cpp
	PersistentV8.h
	expose_headers.hpp
	exception.h
	exception.cpp
	)

target_link_libraries(key-v8 
	key-common
	${V8_LIBRARIES}
	)