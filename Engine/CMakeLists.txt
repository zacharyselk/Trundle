add_subdirectory(include)
add_subdirectory(src)

#target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#target_include_directories(engine PRIVATE
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#    $<INSTALL_INTERFACE:include>
#    PRIVATE src)
target_include_directories(engine PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE+CURRENT_SOURCE_DIR}>
    PRIVATE src)