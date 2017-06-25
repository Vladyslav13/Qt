cmake_minimum_required(VERSION 3.0.2)

project(NoteBookGui)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -std=c++1y")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)

set(HEADERS
    include/AddContactDlg.h
    include/AdditionalContactInfo.h
    include/DataModel.h
    include/DataModelManager.h
    include/EditMainContactInfoDlg.h
    include/MainNotebookWindow.h
    include/MainContactInfo.h
    include/NotebookWidget.h
    include/PhoneEdit.h
    include/UserMaintenanceDlg.h
    )

set(MISC
    src/pch.h
    src/pch.cpp
    )

set(SOURCE
    src/AddContactDlg.cpp
    src/AdditionalContactInfo.cpp
    src/DataModel.cpp
    src/DataModelManager.cpp
    src/EditMainContactInfoDlg.cpp
    src/Main.cpp
    src/MainNotebookWindow.cpp
    src/MainContactInfo.cpp
    src/NotebookWidget.cpp
    src/PhoneEdit.cpp
    src/UserMaintenanceDlg.cpp
    )

include_directories(
    include
    ../libnb/include
    )

add_executable(${PROJECT_NAME}
    ${MISC}
    ${SOURCE}
    ${HEADERS}
    )

qt5_use_modules(${PROJECT_NAME}
    Widgets
    Core
    )

target_link_libraries(${PROJECT_NAME}
    libnb
    ${Boost_LIBRARIES}
    ${Qt5Widgets_INCLUDES}
    )

set_target_properties(${PROJECT_NAME} PROPERTIES
    COTIRE_CXX_PREFIX_HEADER_INIT "src/pch.h")

cotire(${PROJECT_NAME})
