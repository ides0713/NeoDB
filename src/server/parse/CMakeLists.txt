find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

# bison_target(yacc yacc.y ${CMAKE_CURRENT_SOURCE_DIR}/yacc.tab.cpp
#         DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/yacc.tab.h)
# flex_target(lex lex.l ${CMAKE_CURRENT_SOURCE_DIR}/lex.yy.cpp)
# add_flex_bison_dependency(lex yacc)

file(GLOB PARSE_SOURCE *.cpp)
set(SOURCES ${BISON_yacc_OUTPUT_SOURCE} ${FLEX_lex_OUTPUTS} ${PARSE_SOURCE})
add_library(parse STATIC ${SOURCES})