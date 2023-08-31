if(WIN32)
    set(OS_NAME WINDOWS)
    set(WINDOWS TRUE)
elseif (UNIX AND NOT APPLE)
    set(OS_NAME LINUX)
    set(LINUX TRUE)
elseif (UNIX AND APPLE)
    set(OS_NAME MACOS)
    set(MACOS TRUE)
endif ()

if (CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "AMD64" OR
        CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(${OS_NAME}_x86_64 TRUE)
elseif (CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "aarch64" OR
        CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64")
    set(${OS_NAME}_ARM64 TRUE)
endif ()