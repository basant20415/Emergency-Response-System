cmake_minimum_required(VERSION 3.0)


project(PRINT) # change project name

set(CMAKE_CXX_STANDARD 17)

include_directories(includes/ utils/)


set(SOURCE

src/main.cpp
src/aws.cpp
src/ecall.cpp
src/server.cpp
)
find_package(PahoMqttCpp REQUIRED)
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} PahoMqttCpp::paho-mqttpp3)