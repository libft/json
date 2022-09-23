cmake_minimum_required(VERSION 3.24)
project(libft_json)

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

FILE(GLOB SRCS src/ft/**/*.c)

ADD_LIBRARY(ft STATIC
  ${SRCS}
)

HEADER_DIRECTORIES(header_dir_list)
target_include_directories(
  ft
  PUBLIC
  ${header_dir_list}
)
