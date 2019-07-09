#First create executable to work with 
add_executable(main main.cpp) 
add_library(dc digit_counting.cpp) 
# tell the linker to bind main exe to all libraries 
target_link_libraries(main dc)
