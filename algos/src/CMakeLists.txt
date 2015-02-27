CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(BASE_LIB "-L${BASE_BIN}/ -labase")
SET(SVC_LIB "-L${SVC_BIN}/ -lasvc")

FILE(GLOB algos_src *.cxx *.cpp)

MESSAGE("Creating Algos library with files ${algos_src}")

#ADD_LIBRARY(alexTUtil SHARED ${tutil_src})
#TARGET_LINK_LIBRARIES(alexTUtil ${ROOT_LIBRARIES})

ROOT_LINKER_LIBRARY(aalgos ${algos_src}  
                    LIBRARIES ${BASE_LIB} ${SVC_LIB} 
                      ${LOG4CPP_LIBRARIES} 
                      ${ROOT_LIBRARIES} ${IRENE_LIBRARIES}
                      ${PAOLINA_LIBRARIES})

INSTALL(TARGETS aalgos DESTINATION lib)
