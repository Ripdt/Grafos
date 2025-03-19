# Adiciona todos os arquivos .cpp do diretório atual
file(GLOB SOURCES "*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/include/grafos)

# Cria uma biblioteca estática para os grafos
add_library(grafos STATIC ${SOURCES})

# Define os diretórios de saída
set_target_properties(grafos PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
)

set_property(
  TARGET
  grafos
  APPEND PROPERTY
  FOLDER "projects"
)