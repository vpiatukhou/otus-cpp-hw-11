find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

add_library(join_server STATIC CommandController.cpp
                               Dao.cpp
                               DataSource.cpp
                               DbConnection.cpp
                               EntityJoinTransformer.cpp
                               InsertCommand.cpp
                               IntersectionCommand.cpp
                               RequestParser.cpp
                               Server.cpp
                               SymmetricDifferenceCommand.cpp
                               TcpConnection.cpp
                               TruncateCommand.cpp)
add_executable(join_server_cli main.cpp)
#rename the executable to "join_server"
set_target_properties(join_server_cli PROPERTIES OUTPUT_NAME join_server)

target_include_directories(join_server PUBLIC ${Boost_INCLUDE_DIRS})
target_include_directories(join_server PUBLIC ${SQLITE_INCLUDE})
target_link_libraries(join_server sqlite ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(join_server_cli PRIVATE join_server)

#BEGIN release
install(TARGETS join_server_cli join_server)
install(FILES ${DB_FILE} DESTINATION var/lib)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
#END
