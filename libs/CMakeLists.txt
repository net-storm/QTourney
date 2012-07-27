SET( target_name "tournament_libs" )

message(STATUS "")
colormsg(_HIBLUE_ "Configuring ${target_name}:")

file(GLOB_RECURSE ${target_name}_SRCS  ./*.cpp)
file(GLOB_RECURSE ${target_name}_HEADERS  ./*.hpp)

add_library(
    ${target_name} 
    ${${target_name}_SRCS}
    ${${target_name}_HEADERS}
)
