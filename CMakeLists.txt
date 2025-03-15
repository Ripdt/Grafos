cmake_minimum_required(VERSION 3.14)
project(GrafosProjeto)

# Habilita os testes logo no início
include(CTest)
enable_testing()

# Define o padrão de compilação para C++14
set(CMAKE_CXX_STANDARD 14)

# Define os diretórios de inclusão
include_directories(${PROJECT_SOURCE_DIR}/include)

# Define os diretórios de saída para build/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Adiciona subdiretórios contendo bibliotecas
add_subdirectory(src/primitives)
add_subdirectory(src/grafos)

# Cria o executável principal
add_executable(GrafosProjeto src/grafos/Grafos.cpp)

# Linka as bibliotecas ao executável
target_link_libraries(GrafosProjeto primitives grafos)

# Define o projeto principal como projeto de inicialização
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT GrafosProjeto)

# Adiciona os testes
add_subdirectory(tests)
