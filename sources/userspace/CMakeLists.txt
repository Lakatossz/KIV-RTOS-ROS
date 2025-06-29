﻿CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT(kiv_os_rpios_userspace C CXX ASM)

SET(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/link.ld")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}")

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../kernel/include/")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../stdlib/include/")

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../stdutils/include/")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../kernel/include/board/rpi0/")
ADD_DEFINITIONS(-DRPI0)

SET(ABI_FILES cxxabi.cpp)
SET(CRT_FILES crt0.s crt0.c)

IF(NOT COMPLETE_BUILD)
	SET(STDLIB_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../build/stdlib/libkivrtos_stdlib.a)
ELSE()
	SET(STDLIB_FILES kivrtos_stdlib)
ENDIF()

FUNCTION(ADD_USERSPACE_EXECUTABLE target_name file_list)
	SET(file_list ${ARGV})
	LIST(REMOVE_AT file_list 0)

	ADD_EXECUTABLE(${target_name} ${CRT_FILES} ${ABI_FILES} ${file_list})
	TARGET_LINK_LIBRARIES(${target_name} ${STDLIB_FILES} gcc)

	SET_TARGET_PROPERTIES(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

	IF (COMPLETE_BUILD)
		ADD_CUSTOM_COMMAND(
			TARGET ${target_name} POST_BUILD
			COMMAND ${CMAKE_OBJCOPY} ${CMAKE_CURRENT_SOURCE_DIR}/build/${target_name}${CMAKE_EXECUTABLE_SUFFIX} -O binary ${CMAKE_CURRENT_SOURCE_DIR}/build/${target_name}.bin
			COMMAND ${CMAKE_OBJDUMP} -l -S -D ${CMAKE_CURRENT_SOURCE_DIR}/build/${target_name}${CMAKE_EXECUTABLE_SUFFIX} > ${CMAKE_CURRENT_SOURCE_DIR}/build/${target_name}.asm
			COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/build && xxd -i ./${target_name}${CMAKE_EXECUTABLE_SUFFIX} > ${CMAKE_CURRENT_SOURCE_DIR}/build/src_${target_name}.h
			WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
	ELSE()
		ADD_CUSTOM_COMMAND(
			TARGET ${target_name} POST_BUILD
			COMMAND ${CMAKE_OBJCOPY} ${CMAKE_CURRENT_SOURCE_DIR}/build/${target_name}${CMAKE_EXECUTABLE_SUFFIX} -O binary ${CMAKE_CURRENT_SOURCE_DIR}/build/${target_name}.bin
			COMMAND ${CMAKE_OBJDUMP} -l -S -D ${CMAKE_CURRENT_SOURCE_DIR}/build/${target_name}${CMAKE_EXECUTABLE_SUFFIX} > ${CMAKE_CURRENT_SOURCE_DIR}/build/${target_name}.asm
			COMMAND xxd -i ${CMAKE_CURRENT_SOURCE_DIR}/build/${target_name}${CMAKE_EXECUTABLE_SUFFIX} > ${CMAKE_CURRENT_SOURCE_DIR}/build/src_${target_name}.h
			WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
	ENDIF()

	IF(COMPLETE_BUILD)
	    ADD_DEPENDENCIES(kernel ${target_name})
	ENDIF()
ENDFUNCTION(ADD_USERSPACE_EXECUTABLE)

# init task - systemovy task, musi byt pritomen
ADD_USERSPACE_EXECUTABLE(init_task init_task/main.cpp)

ADD_USERSPACE_EXECUTABLE(io_task 
	insulin_pump/src/insulin_pump/user_interface/io_task.cpp 
	insulin_pump/src/insulin_pump/pump_settings/pump_settings.cpp
	insulin_pump/src/insulin_pump/basal/basal_profile.cpp)

ADD_USERSPACE_EXECUTABLE(display_task insulin_pump/src/insulin_pump/user_interface/display_task.cpp)

ADD_USERSPACE_EXECUTABLE(hw_control_task insulin_pump/src/insulin_pump/insulin_pump/control_tasks/hw_control_task.cpp)
ADD_USERSPACE_EXECUTABLE(sw_control_task insulin_pump/src/insulin_pump/insulin_pump/control_tasks/sw_control_task.cpp)

ADD_USERSPACE_EXECUTABLE(air_in_line_task insulin_pump/src/insulin_pump/air_in_line/air_in_line_task.cpp)

ADD_USERSPACE_EXECUTABLE(logger_task insulin_pump/src/utils/logger/logger_task.cpp)

ADD_USERSPACE_EXECUTABLE(insulin_pump_task 
	insulin_pump/src/main.cpp
	insulin_pump/src/insulin_pump/basal/basal_profile.cpp
	insulin_pump/src/insulin_pump/cgm_sensor/cgm_sensor.cpp
	insulin_pump/src/insulin_pump/insulin_pump/insulin_pump.cpp
	insulin_pump/src/insulin_pump/motor/motor.cpp
	insulin_pump/src/insulin_pump/pid_regulator/pid_regulator.cpp
	insulin_pump/src/insulin_pump/pump_settings/pump_settings.cpp
	insulin_pump/src/insulin_pump/user_interface/zero_mate_user_interface.cpp
	insulin_pump/src/math/math.cpp
	insulin_pump/src/utils/logger/logger.cpp
)

# volitelne tasky pro ruzne ulohy
#ADD_USERSPACE_EXECUTABLE(sos_task sos_task/main.cpp)
#ADD_USERSPACE_EXECUTABLE(oled_task oled_task/main.cpp)
#ADD_USERSPACE_EXECUTABLE(logger_task logger_task/main.cpp)
#ADD_USERSPACE_EXECUTABLE(counter_task counter_task/main.cpp)
#ADD_USERSPACE_EXECUTABLE(tilt_task tilt_task/main.cpp)
