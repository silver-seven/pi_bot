
find_package(Boost REQUIRED COMPONENTS system filesystem)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu")

add_executable(${project_name} ./main.cpp)

target_link_libraries(${project_name} 
  ${Boost_LIBRARIES} 
  wiringPi
)
add_subdirectory(lib/httpconnection)
add_subdirectory(lib/AdafruitGFX)
add_subdirectory(lib/drivers)
add_subdirectory(lib/BMPReader)