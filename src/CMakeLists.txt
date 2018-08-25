set(LIB_SOURCES
        good.c
        )

set(MAIN_SOURCES
        main.c
        )

set(HEADERS
        ${CONFIG_HEADER}
        good.h
        )

add_library(good STATIC ${LIB_SOURCES} ${HEADERS})

add_executable(main ${HEADERS} ${MAIN_SOURCES})
target_link_libraries(main good)

install(TARGETS good
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/good.h DESTINATION include)
