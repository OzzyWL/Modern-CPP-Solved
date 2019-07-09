#First create executable to work with
add_executable(main main.cpp)

#################### Import the 'io_tools' library here ########################
# find wanted libraries
find_library(IO_TOOLS NAMES io_tools PATHS ${LIBRARY_OUTPUT_PATH})
message( "LIBRARY_OUTPUT_PATH is: " ${LIBRARY_OUTPUT_PATH} )
#################### Create a library 'image' below this line ##################
add_library(image image.cpp)
# tell the linker to bind main exe to all libraries / tools
target_link_libraries(main image ${IO_TOOLS})
