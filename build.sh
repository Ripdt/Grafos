#!/bin/bash

# Diretório de compilação
BUILD_DIR="build"

# Criar diretório de compilação, se não existir
mkdir -p $BUILD_DIR
cd $BUILD_DIR

# Executar CMake para gerar os arquivos de compilação
cmake ..
make -j$(nproc)

# Verificar se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    echo "Compilação concluída com sucesso!"
else
    echo "Erro na compilação!"
    exit 1
fi
