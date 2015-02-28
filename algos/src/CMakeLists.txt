CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

FILE(GLOB algos_src *.cxx *.cpp)

MESSAGE("Creating Algos library with files ${algos_src}")

#ADD_LIBRARY(alexTUtil SHARED ${tutil_src})
#TARGET_LINK_LIBRARIES(alexTUtil ${ROOT_LIBRARIES})

ROOT_LINKER_LIBRARY(aalgos ${algos_src}  
                    LIBRARIES ${BASE_LIB} ${SVC_LIB} ${ADMODEL_LIB} 
                      ${LOG4CPP_LIBRARIES} 
                      ${ROOT_LIBRARIES} ${IRENE_LIBRARIES}
                      ${PAOLINA_LIBRARIES})

INSTALL(TARGETS aalgos DESTINATION lib)
