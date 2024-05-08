cmake_minimum_required(VERSION 3.15) # 设置CMake的最低版本为 3.10

project(JKCARNB VERSION 1.0) #设置项目名和项目版本号

set(CMAKE_CXX_COMPILER "D:/msys64/mingw64/bin/g++.exe")  #设置C++编译器位置
set(CMAKE_C_COMPILER "D:/msys64/mingw64/bin/gcc.exe") #设置C编译器位置
set(CMAKE_INSTALL_PREFIX "D:/Myself/Code/C/JKCARNB/install") #设置安装路径


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(ADWAITA REQUIRED libadwaita-1)

add_executable(JKCARNB WIN32 main.c) #设置项目的执行文件

add_subdirectory("${PROJECT_SOURCE_DIR}/Utils")
add_subdirectory("${PROJECT_SOURCE_DIR}/FuelVehicle")
add_subdirectory("${PROJECT_SOURCE_DIR}/NewEnergyVehicles")


target_link_libraries(JKCARNB PUBLIC NewEnergyVehicles FuelVehicle)

file(GLOB DEPENDENCY_DLLS "D:/msys64/mingw64/bin/*.dll")

install(TARGETS JKCARNB DESTINATION bin)
install(FILES ${DEPENDENCY_DLLS} DESTINATION bin)
install(FILES )

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${JKCARNB_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${JKCARNB_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "ZIP")
include(CPack)