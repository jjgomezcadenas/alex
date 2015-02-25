# -*- cmake -*-
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(ALEX)

MESSAGE("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
#Set compilier flags
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
   # Mac OS X specific code
   SET(CMAKE_CXX_FLAGS "-Wall -g -O2 -std=c++11" )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Linux specific code
    SET(CMAKE_CXX_FLAGS "-Wall -g -O2 -std=c++0x" )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")


SET(CMAKE_VERBOSE_MAKEFILE ON)
#SET(CMAKE_BUILD_TYPE ${CMAKE_CXX_FLAGS})

MESSAGE("CMAKE source dir: ${CMAKE_SOURCE_DIR}")
MESSAGE("CMAKE binary dir: ${CMAKE_BINARY_DIR}")

MESSAGE("CMAKE compiler: ${CMAKE_CXX_COMPILER}")
MESSAGE("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
MESSAGE("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")


# Set where to look for external packages 
set (CMAKE_MODULE_PATH $ENV{CMODULES}) 
MESSAGE("CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")

# Set where where to install 
SET(CMAKE_INSTALL_PREFIX $ENV{INSTALL})
MESSAGE("CMAKE_INSTALL_PREFIX set to: ${CMAKE_INSTALL_PREFIX}")

# Set working (algos) dir
SET(ALEX_WDIR $ENV{AWDIR}
)

# Look for root

find_package(ROOT REQUIRED)

if(CMAKE_SYSTEM_NAME MATCHES Darwin)
  # To avoid to set ld_Library_path to locate the test libraries
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,@loader_path/.")
endif()


MESSAGE("ROOT include directories: ${ROOT_INCLUDE_DIR}")
MESSAGE("ROOT libraries: ${ROOT_LIBRARIES}")

MESSAGE("ROOT Found: ${ROOT_FOUND}")
MESSAGE("ROOT CINT: ${ROOTCINT_EXECUTABLE}")

include(RootNewMacros)


# Look for Irene, Paolina, Log4CPP and TinyXML2
find_package(Irene REQUIRED)
find_package(Paolina REQUIRED)
find_package(Log4CPP REQUIRED)
find_package(TinyXML2 REQUIRED)

# find_package(RecPack REQUIRED)
# find_package(CLHEP REQUIRED)


MESSAGE("Irene include directories: ${IRENE_INCLUDE_DIR}")
MESSAGE("Paolina include directories: ${PAOLINA_INCLUDE_DIR}")
MESSAGE("Log4CPP include directories: ${LOG4CPP_INCLUDE_DIR}")
MESSAGE("TinyXML2 include directories: ${TINYXML2_INCLUDE_DIR}")
MESSAGE("ROOT include directories: ${ROOT_INCLUDE_DIR}")

# MESSAGE("RecPack include directories: ${RECPACK_INCLUDE_DIR}")
# MESSAGE("CLHEP include directories: ${CLHEP_INCLUDE_DIR}")


MESSAGE("Irene libraries: ${IRENE_LIBRARIES}")
MESSAGE("Paolina libraries: ${PAOLINA_LIBRARIES}")
MESSAGE("LOG4CPP libraries: ${LOG4CPP_LIBRARIES}")
MESSAGE("TinyXML2 libraries: ${TINYXML2_LIBRARIES}")
MESSAGE("ROOT libraries: ${ROOT_LIBRARIES}")

# MESSAGE("RecPack libraries: ${RECPACK_LIBRARIES}")
# MESSAGE("CLHEP libraries: ${CLHEP_LIBRARIES}")

 

# SET(GALEX galex) # Define the galex directory

# SET(TSVC ${CMAKE_SOURCE_DIR}/tsvc) # Define the tsvc directory

# SET(ASVC ${CMAKE_SOURCE_DIR}/asvc) # Define the tsvc directory

#Make symbolic links in alex/ to all header files
EXECUTE_PROCESS(
  COMMAND mkdir -p alex)

#FILE(GLOB alex_headers util/*.h tutil/*.h admodel/*.h)
FILE(GLOB alex_headers base/*.h admodel/*.h)

FOREACH(file ${alex_headers})
  EXECUTE_PROCESS(
    COMMAND ln -s -f ${file} alex)
ENDFOREACH(file)

#names for src and bin directories

set(ADMODEL_SRC ${CMAKE_SOURCE_DIR}/admodel)
# set(UTIL_SRC ${CMAKE_SOURCE_DIR}/util)
# set(TUTIL_SRC ${CMAKE_SOURCE_DIR}/tutil)
set(CONFIG_SRC ${CMAKE_SOURCE_DIR}/config)
set(BASE_SRC ${CMAKE_SOURCE_DIR}/base)

set(ADMODEL_BIN ${CMAKE_BINARY_DIR}/admodel)
# set(UTIL_BIN ${CMAKE_BINARY_DIR}/util)
# set(TUTIL_BIN ${CMAKE_BINARY_DIR}/tutil)
set(CONFIG_BIN ${CMAKE_BINARY_DIR}/config)
set(BASE_BIN ${CMAKE_BINARY_DIR}/base)


# Directories that will be searched for headers during compilation
# INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR} ${TSVC}
#           ${ALEX_WDIR} ${GALEX} ${ASVC}
# 					${IRENE_INCLUDE_DIR} ${PAOLINA_INCLUDE_DIR} 
# 					${ROOT_INCLUDE_DIR} ${TINYXML2_INCLUDE_DIR} 
# 					${LOG4CPP_INCLUDE_DIR} ${RECPACK_INCLUDES_DIR} ${CLHEP_INCLUDE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR} 
          ${IRENE_INCLUDE_DIR} ${PAOLINA_INCLUDE_DIR} 
          ${ROOT_INCLUDE_DIR} ${TINYXML2_INCLUDE_DIR} 
          ${LOG4CPP_INCLUDE_DIR} ${CONFIG_SRC})


#  FILE(GLOB alex_src . util/*.cpp config/*.cpp base/*.cpp isvc/*.cpp psvc/*.cpp
#  asvc/*.cpp tsvc/*.cpp )


# # # # Finally, create it!

# MESSAGE("Creating Alex library")

# ADD_LIBRARY(alex SHARED ${alex_src} ${TSVC_DICTIONARY})

# #ADD_LIBRARY(alex SHARED ${alex_src})

# SET_TARGET_PROPERTIES(alex PROPERTIES VERSION 1.1.0 SOVERSION 1)
# TARGET_LINK_LIBRARIES(alex ${LOG4CPP_LIBRARIES} ${IRENE_LIBRARIES} ${PAOLINA_LIBRARIES} 
# 	${RECPACK_LIBRARIES} ${ROOT_LIBRARIES} ${CLHEP_LIBRARIES} ${TINYXML2_LIBRARIES})


# MESSAGE("Creating xConfigure")
# add_executable (xConfigure config/xConfigure.cxx)
# target_link_libraries (xConfigure alex)

# MESSAGE("Creating gConfigure")
# add_executable (gConfigure galex/gConfigure.cxx)
# target_link_libraries (gConfigure alex)


# MESSAGE("Executing xConfigure")
# EXEC_PROGRAM(${CMAKE_BINARY_DIR}/xConfigure
#         ARGS ${ALEX_WDIR})
#         #OUTPUT_VARIABLE CLHEP_PREFIX)




# ADD_SUBDIRECTORY(util)
# ADD_SUBDIRECTORY(tutil)
ADD_SUBDIRECTORY(base)
ADD_SUBDIRECTORY(admodel)
ADD_SUBDIRECTORY(config) 

#ADD_SUBDIRECTORY(${ALEX_WDIR})
#ADD_SUBDIRECTORY(alexMain)
#ADD_SUBDIRECTORY(galex)
#ADD_SUBDIRECTORY(asvc)
#ADD_SUBDIRECTORY(test)
#ADD_SUBDIRECTORY(exampleConf)
#ADD_SUBDIRECTORY(example)
#ADD_SUBDIRECTORY(exampleMain)

INSTALL(FILES ${alex_headers} DESTINATION include/alex)
# # Installation destinations (just for the lib, not the python module)
# INSTALL(TARGETS alex LIBRARY DESTINATION lib)
# INSTALL(FILES ${alex_headers} DESTINATION include/alex)

# # Get ready for creating a package
# INCLUDE(CPack)