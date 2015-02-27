# -*- cmake -*-
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


SET(alex_src ${MAIN_SRC}/alex.cc)

SET(BASE_LIB "-L${BASE_BIN}/ -labase")
SET(ADMODEL_LIB "-L${ADMODEL_BIN}/ -ladmodel")
SET(SVC_LIB "-L${SVC_BIN}/ -lasvc")
SET(ALGOS_LIB "-L${ALGOS_BIN}/src/ -laalgos") 

MESSAGE("Creating xAlex")


ROOT_EXECUTABLE(xAlex ${alex_src} LIBRARIES 
				      ${BASE_LIB} ${SVC_LIB} ${ALGOS_LIB}
                      ${LOG4CPP_LIBRARIES} 
                      ${ROOT_LIBRARIES} ${IRENE_LIBRARIES}
                      ${PAOLINA_LIBRARIES}
                      ) 


INSTALL(TARGETS xAlex DESTINATION bin)
