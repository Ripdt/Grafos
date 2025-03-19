# Pasta de testes
file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/grafos/*.cpp")
file(GLOB TEST_SOURCES_PRIMITIVES "${CMAKE_CURRENT_SOURCE_DIR}/primitives/*.cpp")

# Verificando se os arquivos de teste foram encontrados
message(STATUS "Test files found: ${TEST_SOURCES} ${TEST_SOURCES_PRIMITIVES}")

# Declara o GoogleTest e o baixa
include(FetchContent)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)

# Criação dos executáveis de teste
add_executable(GrafosTests ${TEST_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/grafos/GrafosTest.cpp)
add_executable(PrimitivesTests ${TEST_SOURCES_PRIMITIVES})

# Configuração dos diretórios de inclusão para os testes 
target_include_directories(GrafosTests PRIVATE ${CMAKE_SOURCE_DIR}/tests/grafos)
target_include_directories(PrimitivesTests PRIVATE ${CMAKE_SOURCE_DIR}/tests/primitives)

# Linkando as bibliotecas de grafos e primitivas aos testes
target_link_libraries(GrafosTests PRIVATE grafos gtest gtest_main)
target_link_libraries(PrimitivesTests PRIVATE primitives gtest gtest_main)

set_property(
  TARGET
  GrafosTests
  APPEND PROPERTY
  FOLDER "tests"
)

set_property(
  TARGET
  PrimitivesTests
  APPEND PROPERTY
  FOLDER "tests"
)

set_property(
  TARGET
  gtest
  APPEND PROPERTY
  FOLDER "tests/google"
)

set_property(
  TARGET
  gtest_main
  APPEND PROPERTY
  FOLDER "tests/google"
)

# Registrando os testes com CTest
add_test(NAME GrafosTests COMMAND GrafosTests)
add_test(NAME PrimitivesTests COMMAND PrimitivesTests)