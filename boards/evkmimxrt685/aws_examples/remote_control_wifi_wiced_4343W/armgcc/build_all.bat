cmake -DCMAKE_TOOLCHAIN_FILE="../../../../../tools/cmake_toolchain_files/armgcc.cmake" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=flash_debug  .
mingw32-make -j
cmake -DCMAKE_TOOLCHAIN_FILE="../../../../../tools/cmake_toolchain_files/armgcc.cmake" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=flash_release  .
mingw32-make -j
IF "%1" == "" ( pause )
