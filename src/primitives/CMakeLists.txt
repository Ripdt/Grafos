# Adiciona todos os arquivos .cpp do diretório atual
file(GLOB SOURCES "*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/include/primitives)

# Cria uma biblioteca estática para as estruturas de dados
add_library(primitives STATIC ${SOURCES})

# Define os diretórios de saída
set_target_properties(primitives PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
)

set_property(
  TARGET
  primitives
  APPEND PROPERTY
  FOLDER "projects"
)
