CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

FILE(GLOB svc_h *.h)
FILE(GLOB svc_src *.cpp)

MESSAGE("Creating Svc library")

#ADD_LIBRARY(alexTUtil SHARED ${tutil_src})
#TARGET_LINK_LIBRARIES(alexTUtil ${ROOT_LIBRARIES})

ROOT_LINKER_LIBRARY(asvc ${svc_src}  
                    LIBRARIES ${BASE_LIB} ${ADMODEL_LIB} ${LOG4CPP_LIBRARIES} 
                    ${ROOT_LIBRARIES} ${IRENE_LIBRARIES}
                    ${PAOLINA_LIBRARIES})

INSTALL(TARGETS asvc DESTINATION lib)
INSTALL(FILES ${svc_h} DESTINATION include/alex)



