project(key-common)

# if library is SHARED, uncoment following lines:
#if(WIN32)
# 	add_definitions(-DDYNAMIC_LIB)
#endif(WIN32)

add_library(key-common STATIC 
	lib_key_common.h
	types.h
	app.h
	app.cpp
	)

target_link_libraries(key-common 
	${V8_LIBRARIES}
	${BULLET_LIBRARIES}
	${OPENAL_LIBRARIES}
	)