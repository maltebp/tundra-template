cmake_minimum_required(VERSION 3.21)

get_filename_component(TD_GAME_DIR_ROOT ${CMAKE_CURRENT_LIST_DIR}/../.. ABSOLUTE)
get_filename_component(TUNDRA_DIR ${TD_GAME_DIR_ROOT}/external/tundra ABSOLUTE)

include(${TUNDRA_DIR}/tools/cmake/import.cmake)

get_filename_component(TD_GAME_DIR_PARENT ${TD_GAME_DIR_ROOT}/.. ABSOLUTE)
cmake_path(RELATIVE_PATH TD_GAME_DIR_ROOT BASE_DIRECTORY "${TD_GAME_DIR_PARENT}" OUTPUT_VARIABLE TD_GAME_WORKSPACE_NAME )

project(
	${TD_GAME_WORKSPACE_NAME}
	LANGUAGES    C CXX ASM
	VERSION      1.0.0
	DESCRIPTION  ""
)

include(${TD_GAME_DIR_ROOT}/sources.cmake)
include(${TD_GAME_DIR_ROOT}/assets.cmake)

foreach(source IN LISTS SOURCES)
	list(APPEND SOURCES_ABSOLUTE ${TD_GAME_DIR_ROOT}/${source})
endforeach()

psn00bsdk_add_executable(${TD_GAME_WORKSPACE_NAME} GPREL ${SOURCES_ABSOLUTE})
td_link_engine(${TD_GAME_WORKSPACE_NAME})

td_target_assets(${TD_GAME_WORKSPACE_NAME} ${TD_GAME_DIR_ROOT}/assets ${ASSETS})

# Comment out to build CD image
# NOTE: iso.xml content has to be updated to match project name
# psn00bsdk_add_cd_image(
# 	iso      # Target name
# 	${TD_GAME_WORKSPACE_NAME} # Output file name (.bin and .cue)
# 	iso.xml  # Path to config file
# 	DEPENDS ${TD_GAME_WORKSPACE_NAME} system.cnf
# )