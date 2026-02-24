
file(GLOB SOURCES 
    BMPReader.cpp
)

file(GLOB HEADERS 
    BMPReader.h
)

target_sources(${project_name} PRIVATE ${SOURCES} ${HEADERS}) 
target_include_directories(${project_name} PUBLIC .)

