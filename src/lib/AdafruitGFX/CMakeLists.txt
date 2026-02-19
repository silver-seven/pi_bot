
file(GLOB SOURCES 
    Adafruit_GFX.cpp
    glcdfont.c
)

file(GLOB HEADERS 
    Adafruit_GFX.h
    gfxfont.h
)

target_sources(${project_name} PRIVATE ${SOURCES} ${HEADERS}) 
target_include_directories(${project_name} PUBLIC .)

