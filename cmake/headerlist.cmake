file(GLOB_RECURSE HEADER_FILES
	LIST_DIRECTORIES false
	CONFIGURE_DEPENDS
	"src/*.h"
)


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src
	PREFIX "Header Files"
	FILES ${HEADER_FILES})