SET( target_name "form_pairs" )

message(STATUS "")
colormsg(_HIBLUE_ "Configuring ${target_name}:")

add_executable (
    ${target_name}
    main.cpp 
    application.cpp
    application.hpp
)

if(MSVC)
    target_link_libraries(
        ${target_name}
        tournament_libs
    )
else()
    #message(STATUS "${Boost_LIBRARIES}")

    target_link_libraries( 
        ${target_name} 
        ${Boost_LIBRARIES} 
        tournament_libs 
    )
endif()

# functional tests

# collect initial data
file(GLOB ${target_name}_TEST_INPUT_DATA  tests/* )
file(COPY ${${target_name}_TEST_INPUT_DATA} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests)

# define a macro to simplify adding tests, then use it
macro (do_test test_name result)
add_test (
	NAME ${target_name}_${test_name}
	COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target_name} -f ${test_name}
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests/
)
set_tests_properties (
	${target_name}_${test_name}
	PROPERTIES PASS_REGULAR_EXPRESSION ${result}
)
endmacro (do_test)

do_test(smoke "Player1.*% *challenges *%.*Player2")
do_test(error_open_file "error: Unable to open file")
do_test(real_big_one "(%.*%)+")
