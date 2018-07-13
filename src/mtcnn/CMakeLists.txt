aux_source_directory(. srcs)

include_directories(${PROJECT_SOURCE_DIR}/include )
include_directories(${PROJECT_SOURCE_DIR}/include/ncnn )
link_directories(${PROJECT_SOURCE_DIR}/lib)


set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_library(mtcnn SHARED ${srcs})
add_library(mtcnn_static STATIC ${srcs})

target_link_libraries(mtcnn ncnn)
target_link_libraries(mtcnn_static ncnn)

set_target_properties(mtcnn_static PROPERTIES OUTPUT_NAME "mtcnn")
set_target_properties(mtcnn PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(mtcnn PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(mtcnn PROPERTIES VERSION 1.0 SOVERSION 1)
