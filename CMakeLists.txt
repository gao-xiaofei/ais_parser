cmake_minimum_required (VERSION 3.22)
project(ais)

include_directories(./include/ )

aux_source_directory(./src/ DIR_LIB_SRCS)

add_library (aisparser ${DIR_LIB_SRCS})

add_executable(parser_vdm_test ./test/parser_vdm_test.c)
target_link_libraries(parser_vdm_test aisparser)