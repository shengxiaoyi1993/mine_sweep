# Install script for directory: /home/sxy/Codeup/mine_sweep/descibe_mine_sweep_distriction

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/sxy/Codeup/mine_sweep/descibe_mine_sweep_distriction/build-descibe_mine_sweep_distriction-not_config_default_compiler_5_9_7_GCC_64bit-Default/include/")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/sxy/Codeup/mine_sweep/descibe_mine_sweep_distriction/build-descibe_mine_sweep_distriction-not_config_default_compiler_5_9_7_GCC_64bit-Default/include" TYPE DIRECTORY FILES "/home/sxy/Codeup/mine_sweep/descibe_mine_sweep_distriction/include/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/sxy/Codeup/mine_sweep/descibe_mine_sweep_distriction/build-descibe_mine_sweep_distriction-not_config_default_compiler_5_9_7_GCC_64bit-Default/lib/libdescibe_mine_sweep_distriction.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/sxy/Codeup/mine_sweep/descibe_mine_sweep_distriction/build-descibe_mine_sweep_distriction-not_config_default_compiler_5_9_7_GCC_64bit-Default/lib" TYPE STATIC_LIBRARY FILES "/home/sxy/Codeup/mine_sweep/descibe_mine_sweep_distriction/build-descibe_mine_sweep_distriction-not_config_default_compiler_5_9_7_GCC_64bit-Default/libdescibe_mine_sweep_distriction.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/sxy/Codeup/mine_sweep/descibe_mine_sweep_distriction/build-descibe_mine_sweep_distriction-not_config_default_compiler_5_9_7_GCC_64bit-Default/share/Finddescibe_mine_sweep_distriction.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/sxy/Codeup/mine_sweep/descibe_mine_sweep_distriction/build-descibe_mine_sweep_distriction-not_config_default_compiler_5_9_7_GCC_64bit-Default/share" TYPE FILE FILES "/home/sxy/Codeup/mine_sweep/descibe_mine_sweep_distriction/cmake/Finddescibe_mine_sweep_distriction.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/sxy/Codeup/mine_sweep/descibe_mine_sweep_distriction/build-descibe_mine_sweep_distriction-not_config_default_compiler_5_9_7_GCC_64bit-Default/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
