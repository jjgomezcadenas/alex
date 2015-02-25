CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

FILE(GLOB base_h ${BASE_SRC}/*.h)

# Make sure the linker can find the  library once it is built. 
link_directories (${ALEX_SOURCE_DIR}) 

FILE(GLOB base_src *.cpp)

MESSAGE("Creating Base library")

#ADD_LIBRARY(alexTUtil SHARED ${tutil_src})
#TARGET_LINK_LIBRARIES(alexTUtil ${ROOT_LIBRARIES})

ROOT_LINKER_LIBRARY(abase ${base_src}  
                    LIBRARIES ${LOG4CPP_LIBRARIES} ${ROOT_LIBRARIES})

INSTALL(TARGETS abase DESTINATION lib)
INSTALL(FILES ${base_h} DESTINATION include/alex)



