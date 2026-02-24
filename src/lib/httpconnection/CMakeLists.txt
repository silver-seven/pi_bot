file(GLOB HEADERS 
    inc/httpconnection.h
)

file(GLOB SOURCES 
    src/httpconnection.cpp
)
target_sources(${project_name} PRIVATE ${SOURCES} ${HEADERS}) 

target_include_directories(${project_name}
PRIVATE
  inc/
)
