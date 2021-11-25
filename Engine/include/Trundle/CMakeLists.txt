target_precompile_headers(engine PRIVATE
   "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/common.h>"
)
add_subdirectory(Core)
add_subdirectory(Events)
add_subdirectory(Platform)
add_subdirectory(Renderer)
add_subdirectory(Util)