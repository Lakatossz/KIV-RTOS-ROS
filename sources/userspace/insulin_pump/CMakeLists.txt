cmake_minimum_required(VERSION 3.14)
project(insulin_pump)

# specifikujeme linker skript - potrebujeme vlastni definici pametoveho layoutu
SET(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/link.ld")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}")

# Cesty k knihovnám
set(STDLIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../stdlib")
set(STDUTILS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../stdutils")
set(HAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../kernel/include/board/rpi0")  # Předpokládaná cesta k hal
set(KERNEL "${CMAKE_CURRENT_SOURCE_DIR}/../../kernel")

IF(NOT COMPLETE_BUILD)
    SET(STDLIB_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../build/stdlib/libkivrtos_stdlib.a)
ELSE()
    SET(STDLIB_FILES kivrtos_stdlib)
ENDIF()

# Přidání include adresářů
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${STDLIB_DIR}/include
    ${STDUTILS_DIR}/include
    ${HAL_DIR}
    ${KERNEL}/include
)

# Nalezení zdrojových souborů
file(GLOB_RECURSE STDLIB_SOURCES 
    "${STDLIB_DIR}/src/*.c" 
    "${STDLIB_DIR}/src/*.cpp"
)
file(GLOB_RECURSE STDUTILS_SOURCES 
    "${STDUTILS_DIR}/src/*.c" 
    "${STDUTILS_DIR}/src/*.cpp"
)

# Kontrola nalezení zdrojových souborů
if(NOT STDLIB_SOURCES)
    message(STATUS "Varování: Nebyly nalezeny žádné zdrojové soubory pro stdlib_lib v ${STDLIB_DIR}/src")
    set(EMPTY_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/empty_stdlib.c")
    file(WRITE ${EMPTY_SOURCE} "/* Prázdný soubor pro stdlib_lib */\n")
    set(STDLIB_SOURCES ${EMPTY_SOURCE})
endif()

if(NOT STDUTILS_SOURCES)
    message(STATUS "Varování: Nebyly nalezeny žádné zdrojové soubory pro stdutils_lib v ${STDUTILS_DIR}/src")
    set(EMPTY_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/empty_stdutils.c")
    file(WRITE ${EMPTY_SOURCE} "/* Prázdný soubor pro stdutils_lib */\n")
    set(STDUTILS_SOURCES ${EMPTY_SOURCE})
endif()

# Vytvoření knihoven
add_library(stdlib_lib STATIC ${STDLIB_SOURCES})
add_library(stdutils_lib STATIC ${STDUTILS_SOURCES})

# Nalezení zdrojových souborů insulin_pump
file(GLOB_RECURSE INSULIN_PUMP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Vytvoření spustitelného souboru
add_executable(insulin_pump ${INSULIN_PUMP_SOURCES})

# Propojení knihoven
target_link_libraries(insulin_pump
    stdlib_lib
    stdutils_lib
    #gcc
)

# Nastavení výstupního adresáře
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
