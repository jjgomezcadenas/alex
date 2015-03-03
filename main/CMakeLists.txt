# -*- cmake -*-
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


SET(alex_src ${MAIN_SRC}/alex.cc ${MAIN_SRC}/AlexConf.cxx)

MESSAGE("Creating xAlex")


ROOT_EXECUTABLE(xAlex ${alex_src} LIBRARIES 
				      ${BASE_LIB} ${SVC_LIB} ${ALGOS_LIB} ${ADMODEL_LIB}
                      ${LOG4CPP_LIBRARIES} 
                      ${ROOT_LIBRARIES} ${IRENE_LIBRARIES}
                      ${PAOLINA_LIBRARIES}
                      ) 


INSTALL(TARGETS xAlex DESTINATION bin)
