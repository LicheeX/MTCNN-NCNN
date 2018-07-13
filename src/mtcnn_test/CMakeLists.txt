aux_source_directory(. srcs)

FIND_PACKAGE( OpenMP REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")  
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")  

find_package( OpenCV REQUIRED )
find_package(OpenCV REQUIRED core highgui imgproc)

if (NOT OpenCV_FOUND)
    message(FATAL_ERROR "opencv Not Found!")
else()
    message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")
    message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
endif (NOT OpenCV_FOUND)

include_directories(${PROJECT_SOURCE_DIR}/include )
include_directories(${PROJECT_SOURCE_DIR}/include/ncnn )
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(mtcnn_test ${srcs})

target_link_libraries(mtcnn_test mtcnn)
target_link_libraries( mtcnn_test opencv_imgproc opencv_core opencv_highgui)

