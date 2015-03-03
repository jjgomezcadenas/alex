# -*- cmake -*-
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


FILE(GLOB config_src ${CONFIG_SRC}/*.cpp)
SET(xconfigure_src ${CONFIG_SRC}/xConfigure.cc)
SET(config_h ${CONFIG_SRC}/AlexConfigure.h)

MESSAGE("Creating Configure library")

ROOT_LINKER_LIBRARY(aconf ${config_src} 
                    LIBRARIES ${BASE_LIB} 
                    ${LOG4CPP_LIBRARIES} ${TINYXML2_LIBRARIES})

#------------------------------------------------------------------------------------------
#---ROOT_EXECUTABLE( <name> source1 source2 ... LIBRARIES library1 library2 ...)
#------------------------------------------------------------------------------------------

ROOT_EXECUTABLE(xConfigure ${xconfigure_src} LIBRARIES aconf ${BASE_LIB} 
                    ${LOG4CPP_LIBRARIES} ${TINYXML2_LIBRARIES}) 

# ADD_LIBRARY(irene SHARED ${irene_src} ${IRENE_DICTIONARY})
# SET_TARGET_PROPERTIES(irene PROPERTIES VERSION 1.1.0 SOVERSION 1)
# TARGET_LINK_LIBRARIES(irene ${ROOT_LIBRARIES})


# # Installation destinations (just for the lib, not the python module)
INSTALL(TARGETS aconf DESTINATION lib)
INSTALL(TARGETS xConfigure DESTINATION bin)
INSTALL(FILES ${config_h} DESTINATION include/alex)
