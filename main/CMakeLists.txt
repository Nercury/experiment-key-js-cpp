add_executable(key
	main.cpp)

target_link_libraries(key
key-v8
key-common
key-window
${SDLMAIN_LIBRARY}
)