project(oi.client.webcam VERSION 0.1 LANGUAGES CXX)

LIST(APPEND CMAKE_MODULE_PATH ${OI_NATIVE_MODULE_PATH} ) 

FIND_PACKAGE(ASIO REQUIRED)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DASIO_STANDALONE=YES" )
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(TurboJPEG REQUIRED)

file(GLOB SRC "src/*.cpp")
file(GLOB HEADERS "include/*.hpp" "src/*.hpp")
add_executable(${PROJECT_NAME} ${SRC} ${HEADERS})
source_group("Header Files" FILES ${HEADERS})
target_link_libraries(${PROJECT_NAME} oi.core oi.network oi.rgbd)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${TurboJPEG_LIBRARIES})


target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

INCLUDE_DIRECTORIES(${OI_LIB_DIR})
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${ASIO_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${TurboJPEG_INCLUDE_DIRS})


if (APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
endif()


# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS ${PROJECT_NAME} EXPORT OIClientWebcamConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT OIClientWebcamConfig DESTINATION share/OIRGBD/cmake)

# This makes the project importable from the build directory
export(TARGETS ${PROJECT_NAME} FILE OIClientWebcamConfig.cmake)
