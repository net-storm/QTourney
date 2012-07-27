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
