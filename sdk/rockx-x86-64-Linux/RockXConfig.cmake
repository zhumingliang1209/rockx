
set(RockX_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/include)

if (CMAKE_SYSTEM_NAME MATCHES "Android")
    file(GLOB RockX_LIBS_FILE ${CMAKE_CURRENT_LIST_DIR}/arm64-v8a/*.so)
else()
    file(GLOB RockX_LIBS_FILE ${CMAKE_CURRENT_LIST_DIR}/lib64/*.so)
endif()

set(RockX_LIBS ${RockX_LIBS_FILE})