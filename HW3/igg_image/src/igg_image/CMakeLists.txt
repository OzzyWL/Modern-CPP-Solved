add_subdirectory(io_strategies)

# TODO: create image library from image.cpp.
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

message( "PNG_INCLUDE_DIR is: " ${PNG_INCLUDE_DIR} )
message( "PNG_LIBRARIES is: " ${PNG_LIBRARIES} )

add_library(dummy_s io_strategies/dummy_strategy.cpp)
add_library(png_s io_strategies/png_strategy.cpp)
add_library(ppm_s io_strategies/ppm_strategy.cpp)
add_library(image image.cpp)

# TODO: link image library to any other libraries if needed.
add_executable(main main.cpp)


target_link_libraries(main image dummy_s ppm_s png_s ${PNG_LIBRARIES})



