find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

file(GLOB PARSE_SOURCE *.cpp)
set(PARSE_ALL_SOURCE ${BISON_yacc_OUTPUT_SOURCE} ${FLEX_lex_OUTPUTS} ${PARSE_SOURCE})
add_library(neo0parse SHARED ${PARSE_ALL_SOURCE})
target_include_directories(neo0parse PUBLIC ${PROJECT_INCLUDE_DIR}/server)