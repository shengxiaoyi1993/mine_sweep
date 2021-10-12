
cmake_policy(VERSION 3.6)
project(demo_call_com VERSION 0.1)
cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)  #编译.ui程序相关

SET(PATH_COM_REPO "/home/sxy/Work/com_repo/scripts/com_repo_init/../../" CACHE STRING "Some user-specified option")
SET(PATH_COMPILER_SDX "" CACHE STRING "Some user-specified option")

include_directories(${PATH_COM_REPO})

#set(CMAKE_PREFIX_PATH $ENV{QTDIR594})
#find_package(Qt5 COMPONENTS
#  Core
#  Gui
#  Network
#  Widgets
#  Quick
#  Qml
#  WebSockets
#  REQUIRED) #Qml Quick

#if (CMAKE_SYSTEM_NAME MATCHES "Linux")
#  #  find_package(PkgConfig REQUIRED)
#  find_package(GTK2 REQUIRED )
#  message(STATUS "----- GTK2_INCLUDE_DIRS: ${GTK2_INCLUDE_DIRS}")
#  message(STATUS "----- GKT3_LIBRARIES: ${GTK2_LIBRARIES}")
#  message(STATUS "----- GTK2_LINK_LIBRARIES: ${GTK2_LINK_LIBRARIES}")
#  include_directories(${GTK2_INCLUDE_DIRS})
#  link_directories(${GTK2_LIBRARY_DIRS})
#  list(APPEND FC_DEP_LIBS ${GTK2_LIBRARIES})
#elseif (CMAKE_SYSTEM_NAME MATCHES "Win")
#  #export PKG_CONFIG_PATH="$(brew --prefix libffi)/lib/pkgconfig/"
#  #    set(ENV{PKG_CONFIG_PATH} /usr/local/opt/libffi/lib/pkgconfig)
#  find_package(PkgConfig REQUIRED)
#  pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
#  message(STATUS "----- GKT3_LIBRARIES: ${GTK2_LIBRARIES}")
#  message(STATUS "----- GTK2_LINK_LIBRARIES: ${GTK2_LINK_LIBRARIES}")
#  include_directories(${GTK2_INCLUDE_DIRS})
#  list(APPEND FC_DEP_LIBS ${GTK2_LINK_LIBRARIES})
#endif()


# 位于<com_repo>/com_lib的库
set(LIST_COM_LIB
  cjsonobject
  glog
  )

# 位于<com_repo>/private_lib的库
set(LIST_PRIVATE_LIB
#  encrypt
  )

# 位于<com_repo>/public_lib的库
set(LIST_PUBLIC_LIB
#  uio
#  msgchannel
#  toml
  )

# 本地的模块
set(LIST_LOCAL_LIB
#  def
#  basic
#  tool
#  http_def
#  json_explain
  )


set(HEADERS
  ../src/main.cpp
#  ../../src/main/main.cpp
#  ../../src/main/mainwindow.cpp
#  ../../src/network/dm_httpobject.cpp
#  ../../src/network/websocketserver.cpp
#  #../../../common/def/def.cpp \
#  #../../../common/cjsonobject/CJsonObject.cpp \
#  #../../../common/cjsonobject/cJSON.cpp \
#  #../../../common/json_explain/json_explain.cpp \
#  #    ../../../test/convert/convert.cpp
#  #../../../common/http_def/http_def.cpp \
#  #../../../common/lib_encrypt/aes/aes.cpp \
#  #    #../../../common/lib_encrypt/cjsonobject/cJSON.cpp \
#  #    #../../../common/lib_encrypt/cjsonobject/cJSONcpp.cpp \
#  #    #../../../common/lib_encrypt/cjsonobject/CJsonObject.cpp \
#  #../../../common/lib_encrypt/hex/hex.cpp \
#  #../../../common/lib_encrypt/aes_cpp.cpp \
#  #../../../common/lib_encrypt/response_data.cpp \
#  #    #../../../common/def/config_def.cpp \
#  #../../../common/basic/basic.cpp \
#  ../../src/broadcast/broadcastclient.cpp
#  #../../../common/toml/src/toml.cpp \
#  #../../../common/cppgc/cppgc.cpp \
#  ../../src/sdk/sdk.cpp

  )

set(SOURCES
#  ../../src/main/mainwindow.h
#  ../../src/network/dm_httpobject.h
#  ../../src/network/websocketserver.h
  #../../../common/def/def.h \
  #../../../common/cjsonobject/CJsonObject.h \
  #../../../common/cjsonobject/cJSON.h \
  #../../../common/json_explain/json_explain.h \
  #../../../common/http_def/http_def.h \
  #../../../common/lib_encrypt/aes/aes.h \
  #../../../common/lib_encrypt/hex/hex.h \
  #../../../common/lib_encrypt/aes_cpp.h \
  #../../../common/lib_encrypt/com_client_debug.h \
  #../../../common/lib_encrypt/response_data.h \
  #../../../common/lib_encrypt/sha256.h \
  #../../../common/basic/basic.h \
#  ../../src/broadcast/broadcastclient.h
  #../../../common/toml/src/toml.h \
  #../../../common/cppgc/cppgc.h \
#  ../../src/sdk/sdk.h
  )

set(RESOURCES
  #    qml.qrc
  )

set(QMLS
  #    main.qml
  )

set(UIS
#  ../../src/main/mainwindow.ui
  )

STRING(REGEX REPLACE ".+/(.+)\\.*" "\\1" COMPILER_SUFFIX ${CMAKE_C_COMPILER})
message("COMPILER_SUFFIX:"${COMPILER_SUFFIX})



#将依赖的库添加到当前项目
FOREACH(MYSUBLIB ${LIST_COM_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${PATH_COM_REPO}/com_lib/${MYSUBLIB}/ ${PATH_COM_REPO}/com_lib_out/${MYSUBLIB}_${COMPILER_SUFFIX}.out/)
endif()
ENDFOREACH(MYSUBLIB)

FOREACH(MYSUBLIB ${LIST_PRIVATE_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${PATH_COM_REPO}/private_lib/${MYSUBLIB}/ ${PATH_COM_REPO}/private_lib_out/${MYSUBLIB}_${COMPILER_SUFFIX}.out/)
endif()
ENDFOREACH(MYSUBLIB)

FOREACH(MYSUBLIB ${LIST_PUBLIC_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${PATH_COM_REPO}/public_lib/${MYSUBLIB}/ ${PATH_COM_REPO}/public_lib_out/${MYSUBLIB}_${COMPILER_SUFFIX}.out/)
endif()
ENDFOREACH(MYSUBLIB)

FOREACH(MYSUBLIB ${LIST_LOCAL_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../../common/${MYSUBLIB}/ ${CMAKE_CURRENT_BINARY_DIR}/${MYSUBLIB}_${COMPILER_SUFFIX}.out/)
endif()
ENDFOREACH(MYSUBLIB)



#add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${RESOURCES} ${QMLS})
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${RESOURCES} ${UIS})

target_link_libraries(${PROJECT_NAME}
  -lpthread
#  Qt5::Core
#  Qt5::Gui
#  Qt5::Network
#  Qt5::Widgets
#  Qt5::Quick
#  Qt5::Qml
#  Qt5::WebSockets
#  ${FC_DEP_LIBS}
  ${LIST_COM_LIB}
  ${LIST_PRIVATE_LIB}
  ${LIST_PUBLIC_LIB}
  ${LIST_LOCAL_LIB}
  #-mwindows  #不显示命令行窗口
  ) #Qt5::Qml Qt5::Quick

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
elseif (CMAKE_SYSTEM_NAME MATCHES "Win")
  target_link_libraries(${PROJECT_NAME}
    -mwindows
    )
endif()

set( CMAKE_BUILD_TYPE Debug )

message("PATH_COMPILER_SDX:${PATH_COMPILER_SDX}")

