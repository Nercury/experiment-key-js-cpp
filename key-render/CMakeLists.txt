project(key-render)

# if library is SHARED, uncoment following lines:
#if(WIN32)
# 	add_definitions(-DDYNAMIC_LIB)
#endif(WIN32)

add_library(key-render STATIC 
	lib_key_render.h
	RenderList.h
	RenderList.cpp
	)

target_link_libraries(key-render 
	key-common
	key-v8
	)