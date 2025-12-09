cmake_minimum_required(VERSION 3.16)
project(CppLearningIDE VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/EditorWidget.cpp
    src/SyntaxHighlighter.cpp
    src/ProjectManager.cpp
    src/BuildSystem.cpp
    src/RunManager.cpp
    src/DocsPanel.cpp
    src/LessonsPanel.cpp
    src/ChallengesPanel.cpp
)

set(HEADERS
    src/MainWindow.h
    src/EditorWidget.h
    src/SyntaxHighlighter.h
    src/ProjectManager.h
    src/BuildSystem.h
    src/RunManager.h
    src/DocsPanel.h
    src/LessonsPanel.h
    src/ChallengesPanel.h
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)

if(MINGW)
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,--allow-multiple-definition)
endif()

# Copy resources to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
