
#<>cmake不同版本之间的兼容
cmake_minimum_required(VERSION 2.8)

#识别当前文件名，将当前文件夹名设置为项目名称
string(REGEX REPLACE ".*/\(.*\)" "\\1" CURDIR_NAME ${CMAKE_CURRENT_SOURCE_DIR})

project(${CURDIR_NAME})

#设置子项目，假设所有库都位于同一层级，且具有相同的文件结构

# 位于<com_repo>/com_lib的库
set(LIST_COM_LIB

  )

# 位于<com_repo>/private_lib的库
set(LIST_PRIVATE_LIB
  )

# 位于<com_repo>/public_lib的库
set(LIST_PUBLIC_LIB
  cppgc
  )

# 编译选项
set( CMAKE_CXX_FLAGS "-std=c++11" )
#编译输出路径
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

#预设<com_repo>路径 使用cmake 时可以通过cmake . -DPATH_COM_REPO=<com_repo>进行自定义设置
SET(PATH_COM_REPO "/home/sxy/Work/com_repo/scripts/com_repo_init/../../" CACHE STRING "Some user-specified option")

#包含文件，以便头文件能够被识别
# <>该处需要优化，可能具有风险
include_directories(${PATH_COM_REPO})

#将依赖的库添加到当前项目
FOREACH(MYSUBLIB ${LIST_COM_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${PATH_COM_REPO}/com_lib/${MYSUBLIB}/ ${CMAKE_CURRENT_BINARY_DIR}/${MYSUBLIB}.out/)
endif()
ENDFOREACH(MYSUBLIB)

FOREACH(MYSUBLIB ${LIST_PRIVATE_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${PATH_COM_REPO}/private_lib/${MYSUBLIB}/ ${CMAKE_CURRENT_BINARY_DIR}/${MYSUBLIB}.out/)
endif()
ENDFOREACH(MYSUBLIB)

FOREACH(MYSUBLIB ${LIST_PUBLIC_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${PATH_COM_REPO}/public_lib/${MYSUBLIB}/ ${CMAKE_CURRENT_BINARY_DIR}/${MYSUBLIB}.out/)
endif()
ENDFOREACH(MYSUBLIB)

# 暂时将编译的目标库设置为静态库
# <>该处可以优化
add_library(${CURDIR_NAME} STATIC "")

# # 将当前文件文件夹下的所有cpp和.h文件添加到一个列表，编译动态库时将包含所有cpp
file(GLOB_RECURSE CPP_LIB "${CMAKE_CURRENT_SOURCE_DIR}/src/*")
file(GLOB_RECURSE H_LIB "${CMAKE_CURRENT_SOURCE_DIR}/include/*")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR})

if (DEFINED CMAKE_VERSION AND NOT "${CMAKE_VERSION}" VERSION_LESS "2.8.11")
  target_include_directories(${CURDIR_NAME}      INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
endif()

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
 #  find_package(PkgConfig REQUIRED)
 find_package(GTK2 REQUIRED )
 message(STATUS "----- GTK2_INCLUDE_DIRS: ${GTK2_INCLUDE_DIRS}")
 message(STATUS "----- GKT3_LIBRARIES: ${GTK2_LIBRARIES}")
 message(STATUS "----- GTK2_LINK_LIBRARIES: ${GTK2_LINK_LIBRARIES}")
 include_directories(${GTK2_INCLUDE_DIRS})
 link_directories(${GTK2_LIBRARY_DIRS})
 list(APPEND FC_DEP_LIBS ${GTK2_LIBRARIES})
elseif (CMAKE_SYSTEM_NAME MATCHES "Win")
 #export PKG_CONFIG_PATH="$(brew --prefix libffi)/lib/pkgconfig/"
 #    set(ENV{PKG_CONFIG_PATH} /usr/local/opt/libffi/lib/pkgconfig)
 find_package(PkgConfig REQUIRED)
 pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
 message(STATUS "----- GKT3_LIBRARIES: ${GTK2_LIBRARIES}")
 message(STATUS "----- GTK2_LINK_LIBRARIES: ${GTK2_LINK_LIBRARIES}")
 include_directories(${GTK2_INCLUDE_DIRS})
 list(APPEND FC_DEP_LIBS ${GTK2_LINK_LIBRARIES})
endif()
add_definitions (${GTK2_CFLAGS_OTHER})


# 将所有.cpp与.h文件添加到项目
# <>以后需要添加.c与.hpp的文件
# <>有待研究
target_sources(
  ${CURDIR_NAME}
  PRIVATE
  ${CPP_LIB}
  PUBLIC
  ${H_LIB}
  )

# <> 待研究
target_include_directories(
  ${CURDIR_NAME}
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  )

# 本本项目链接相应的库
target_link_libraries(
  ${CURDIR_NAME}
  ${LIST_COM_LIB}
  ${LIST_PRIVATE_LIB}
  ${LIST_PUBLIC_LIB}
  ${FC_DEP_LIBS}
  )
