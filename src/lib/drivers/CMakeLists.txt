
file(GLOB SOURCES 
    Adafruit_IL19341.cpp
    PiWiringSPIDriver.cpp
)

file(GLOB HEADERS 
    Adafruit_IL19341.h
    PiWiringSPIDriver.h
)

target_sources(${project_name} PRIVATE ${SOURCES} ${HEADERS}) 
target_include_directories(${project_name} PUBLIC .)

