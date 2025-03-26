# Specify the target system as Windows
set(CMAKE_SYSTEM_NAME Windows)

# Specify the cross-compilers
set(CMAKE_C_COMPILER /usr/bin/x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/x86_64-w64-mingw32-g++)

# Specify the target linker
set(CMAKE_RC_COMPILER /usr/bin/x86_64-w64-mingw32-windres)

# Adjust the search path for libraries and includes
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

# Modify the search behavior
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Link libraries directly from MinGW paths
link_directories(/usr/x86_64-w64-mingw32/lib)
