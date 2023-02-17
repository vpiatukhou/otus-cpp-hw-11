add_library(join_server STATIC CombinationTransformer.cpp 
                               CommandController.cpp 
                               Dao.cpp 
                               DataSource.cpp
                               DbConnection.cpp
                               RequestParser.cpp 
                               Server.cpp 
                               TcpConnection.cpp)
add_executable(join_server_cli main.cpp)
#rename the executable to "join_server"
set_target_properties(join_server_cli PROPERTIES OUTPUT_NAME join_server)

target_include_directories(join_server PUBLIC ${SQLITE_INCLUDE})
target_link_libraries(join_server_cli PRIVATE join_server)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS system) #TODO do we need it?
target_link_libraries(join_server sqlite Boost::system)

#BEGIN release
install(TARGETS join_server_cli join_server) #TODO verify which files are packed into *.deb package

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
#END
