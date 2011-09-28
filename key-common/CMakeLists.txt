project(key-common)

# if library is SHARED, uncoment following lines:
#if(WIN32)
# 	add_definitions(-DDYNAMIC_LIB)
#endif(WIN32)

add_library(key-common STATIC 
	lib_key_common.h
	types.h
	doc.hpp
	app.h
	app.cpp
	SsJsonConfig.h
	SsJsonConfig.cpp
	JsonFile.h
	JsonFile.cpp
	)

target_link_libraries(key-common 
	${V8_LIBRARIES}
	${JSON_LIBRARY}
	${BULLET_LIBRARIES}
	${OPENAL_LIBRARIES}
	)