cmake_minimum_required(VERSION 3.0.2)

project(libnb)

set(HEADERS
    include/AbstractPhoneParser.h
    include/Notebook.h
    include/Person.h
    include/PhoneNum.h
    include/PhoneParser.h
    )

set(MISC
    src/pch.cpp
    src/pch.h
    )

set(SOURCE
    src/Notebook.cpp
    src/Person.cpp
    src/PhoneNum.cpp
    src/PhoneParser.cpp
    )

include_directories(
    include
    ${Boost_INCLUDE_DIRS}
    )

add_library(${PROJECT_NAME} STATIC
    ${MISC}
    ${SOURCE}
    ${HEADERS}
    )

set_target_properties(${PROJECT_NAME} PROPERTIES
    COTIRE_CXX_PREFIX_HEADER_INIT "src/pch.h")

cotire(${PROJECT_NAME})
