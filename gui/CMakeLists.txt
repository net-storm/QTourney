SET( target_name "tournament" )

message(STATUS "")
colormsg(_HIBLUE_ "Configuring ${target_name}:")

include(${QT_USE_FILE})

file(GLOB ${target_name}_SRCS  ./*.cpp)
file(GLOB ${target_name}_MOC_HEADERS  ./*.hpp)
file(GLOB ${target_name}_RESOURCES   ./*.qrc)
file(GLOB ${target_name}_SETTINGS  ./data/*.txt)

qt4_wrap_cpp(
    ${target_name}_MOC_SRCS 
    ${${target_name}_MOC_HEADERS}
)

qt4_add_resources(
    ${target_name}_QRC_SOURCES 
    ${${target_name}_RESOURCES}
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(
    ${target_name} 
    ${${target_name}_SRCS}
    ${${target_name}_MOC_SRCS}
    ${${target_name}_QRC_SOURCES}
)

message(STATUS "${QT_LIBRARIES}")

target_link_libraries(
    ${target_name} 
    ${QT_LIBRARIES}
    tournament_libs
) 

file(COPY ${${target_name}_SETTINGS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
