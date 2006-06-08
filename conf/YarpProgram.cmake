

MACRO(YarpProgram name no_console)


FOREACH(X ${NEED_LIBS})
	INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/lib${X}/include)
ENDFOREACH(X ${NEED_LIBS})
SET(header_path ${CMAKE_SOURCE_DIR}/src/lib${name}/include)
INCLUDE_DIRECTORIES(${header_path})


FILE(GLOB folder_source *.cpp)
FILE(GLOB folder_header *.h)
SOURCE_GROUP("Source Files" FILES ${folder_source})
SOURCE_GROUP("Header Files" FILES ${folder_header})

IF (${no_console})
  ADD_EXECUTABLE(${name} WIN32 ${folder_source} ${folder_header}) #WIN32 in windows creates an application without console, this flag is probably ignored in linux
ELSE (${no_console})
  ADD_EXECUTABLE(${name} ${folder_source} ${folder_header})
ENDIF (${no_console})

TARGET_LINK_LIBRARIES(${name} ${NEED_LIBS} ${ACE_LINK_FLAGS})


ENDMACRO(YarpProgram)

