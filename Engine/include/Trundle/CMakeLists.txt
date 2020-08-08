target_precompile_headers(engine PRIVATE "trundle.hpp")

add_subdirectory(Core)
add_subdirectory(Events)
add_subdirectory(Math)
add_subdirectory(Platform)
add_subdirectory(Render)
add_subdirectory(Util)
add_subdirectory(test)
