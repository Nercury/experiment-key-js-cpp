add_executable(key
	main.cpp)

target_link_libraries(key
key-common
key-v8
key-window
key-opengl
${SDLMAIN_LIBRARY}
)

set(VS_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR})
add_custom_command(TARGET key POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${KEYLIB_LIBRARIES}/sdl-2/SDL.dll" ${VS_OUTPUT_DIR}/SDL.dll)