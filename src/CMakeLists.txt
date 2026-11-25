# Used only by the esp32dev_secure environment (framework = arduino, espidf).
FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)
idf_component_register(SRCS ${app_sources})
