include_guard(GLOBAL)

##################################################
# Include directories:
##################################################

include_directories(
	${CMAKE_CURRENT_LIST_DIR}
)

##################################################
# Libraries:
##################################################

add_library(
	mm_can
	SHARED
	${CMAKE_CURRENT_LIST_DIR}/mmCAN.cpp
	${CMAKE_CURRENT_LIST_DIR}/mmCAN.h
	)
target_link_libraries(
	mm_can
	Threads::Threads
	)

