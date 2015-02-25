# -*- cmake -*-
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


set(ADMODEL_DICTIONARY ${ADMODEL_BIN}/admodelDict)  # set dictionary path
set(LINKDEF_FILE ${ADMODEL_SRC}/LinkDef.h)  # set dictionary path



MESSAGE("Generate ADMODEL dictionary")

#SET(ADMODEL_HEADERS ${ADMODEL_SRC}/ABase.h ${ADMODEL_SRC}/AParticle.h)
ROOT_GLOB_HEADERS(ADMODEL_HEADERS *.h)

MESSAGE("After ROOT_GLOB_HEADERS: ADMODEL_HEADERS =${ADMODEL_HEADERS} ")


ROOT_GENERATE_DICTIONARY(${ADMODEL_DICTIONARY} ${ADMODEL_HEADERS} 
                          MODULE admodel LINKDEF ${LINKDEF_FILE})

#---------------------------------------------------------------------------------------------------
#---ROOT_GENERATE_DICTIONARY( dictionary headerfiles 
#                             MODULE module DEPENDENCIES dep1 dep2
#                             STAGE1 LINKDEF linkdef OPTIONS opt1 opt2 ...)
#---------------------------------------------------------------------------------------------------


FILE(GLOB admodel_src ${ADMODEL_SRC}/*.cpp)

#SET(ALEX_LIBRARIES "-L${UTIL_BIN}/ -lalexUtil -L${TUTIL_BIN}/ -lalexTUtil")
SET(ALEX_LIBRARIES "-L${BASE_BIN}/ -labase") 



# # # # Finally, create it!

MESSAGE("Creating ADMODEL library")

ROOT_LINKER_LIBRARY(admodel ${admodel_src} ${ADMODEL_DICTIONARY} 
                    LIBRARIES ${ALEX_LIBRARIES} ${LOG4CPP_LIBRARIES} ${ROOT_LIBRARIES})

# ADD_LIBRARY(irene SHARED ${irene_src} ${IRENE_DICTIONARY})
# SET_TARGET_PROPERTIES(irene PROPERTIES VERSION 1.1.0 SOVERSION 1)
# TARGET_LINK_LIBRARIES(irene ${ROOT_LIBRARIES})


# # Installation destinations (just for the lib, not the python module)
INSTALL(TARGETS admodel DESTINATION lib)
INSTALL(FILES ${ADMODEL_HEADERS} DESTINATION include/alex)
INSTALL(FILES ${CMAKE_BINARY_DIR}/admodel/libadmodel.rootmap DESTINATION lib)
INSTALL(FILES ${CMAKE_BINARY_DIR}/admodel/libadmodel_rdict.pcm DESTINATION lib)



#ADD_SUBDIRECTORY(src)


