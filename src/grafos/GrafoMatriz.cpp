#include "GrafoMatriz.h"
#include "grafos/Aresta.h"
#include <iostream>
#include <set>
#include <stdexcept>
#include "primitives/Matrix.h"

//------------------------------------------------------------

GrafoMatriz::GrafoMatriz(
  const bool _ehDirecionado, 
  const bool _ehPonderado
) :
  Grafo(_ehDirecionado, _ehPonderado),
  matriz()
{
} 

//------------------------------------------------------------

bool GrafoMatriz::inserirVertice(const std::string label) {
  for (const Vertice& v : vertices) {
      if (v.getLabel() == label) {
          return false; // Label já existe

        }
  }

  size_t novoIndice = vertices.size();
  vertices.emplace_back(novoIndice, label);

  size_t novoNumVertices = vertices.size();

  // João: Expande linhas existentes (adiciona nova coluna)
  for (auto& linha : matriz) {
      linha.resize(novoNumVertices, nullptr);
  }

  // João: Adiciona nova linha para o novo vértice
  matriz.emplace_back(novoNumVertices, nullptr);

  return true;
}

//------------------------------------------------------------

bool GrafoMatriz::removerVertice(int indiceVertice) {
  if (indiceVertice < 0 || indiceVertice >= (int)vertices.size()) {
      return false;
  }

  for (auto& linha : matriz) {
      delete linha[indiceVertice];
      linha[indiceVertice] = nullptr;
  }

  vertices.erase(vertices.begin() + indiceVertice);

  matriz.erase(matriz.begin() + indiceVertice);
  for (auto& linha : matriz) {
      linha.erase(linha.begin() + indiceVertice);
  }

  // João: Faz atualização dos items restantes
  for (int i = indiceVertice; i < vertices.size(); ++i) {
      vertices[i].setIndice(i);
  }

  return true;
}

//------------------------------------------------------------

std::string GrafoMatriz::labelVertice(const int indice) const {
  if (indice < 0 || indice >= (int)vertices.size()) {
    return "";
  }
  return vertices[indice].getLabel();
}

//------------------------------------------------------------

void GrafoMatriz::imprime() const {
  if (matriz.empty()) return;

  for (const Vertice& vertice : vertices) {
    std::cout << "\t" << vertice.getLabel();
  }
  std::cout << std::endl;

  // Linhas da matriz
  for (int i = 0; i < matriz.size(); ++i) {
    std::cout << vertices[i].getLabel();
    for (int j = 0; j < matriz[i].size(); ++j) {
      if (matriz[i][j] == nullptr) {
        std::cout << "\t0";
      } else {
        std::cout << "\t" << matriz[i][j]->getPeso();
      }
    }
    std::cout << std::endl;
  }
}

//------------------------------------------------------------

bool GrafoMatriz::inserirAresta(int origem, int destino, float peso) {
  if (origem < 0 || destino < 0 || origem >= (int)vertices.size() || destino >= (int)vertices.size()) {
      return false;
  }

  if (!ehPonderado) peso = 1; 

  if (matriz[origem][destino] != nullptr) {
      delete matriz[origem][destino];
  }

  matriz[origem][destino] = new Aresta(&vertices[origem], &vertices[destino], peso);

  if (!ehDirecionado) {
    if (matriz[destino][origem] != nullptr) {
        // João: Insere aresta reversa
          delete matriz[destino][origem];
      }
      matriz[destino][origem] = new Aresta(&vertices[destino], &vertices[origem], peso);
  }

  return true;
}

//------------------------------------------------------------

bool GrafoMatriz::removerAresta(int origem, int destino) {
  if (origem < 0 || destino < 0 || origem >= (int)vertices.size() || destino >= (int)vertices.size()) {
      return false;
  }

  if (matriz[origem][destino] == nullptr) {
      return false;
  }

  delete matriz[origem][destino];
  matriz[origem][destino] = nullptr;

  if (!ehDirecionado) {
      delete matriz[destino][origem];
      matriz[destino][origem] = nullptr;
  }

  return true;
}

//------------------------------------------------------------

float GrafoMatriz::pesoAresta(const int origem, const int destino) const {
  if (matriz[origem][destino] == nullptr) {
      throw std::runtime_error("Aresta não existe");
  }
  return matriz[origem][destino]->getPeso();
}

//------------------------------------------------------------

std::vector<Vertice> GrafoMatriz::vizinhosVertice(const int indice) const {
  std::set<Vertice> vizinhos;

  for (int i = 0; i < matriz.size(); ++i)
      if (matriz[indice][i] != nullptr)
          vizinhos.insert(*matriz[indice][i]->getDestino());

  if (!ehDirecionado) 
    for (int j = 0; j < matriz[indice].size(); ++j)
      if (matriz[j][indice] != nullptr)
        vizinhos.insert(*matriz[j][indice]->getOrigem());
  
  return std::vector<Vertice>(vizinhos.begin(), vizinhos.end());
}

//------------------------------------------------------------

bool GrafoMatriz::existeAresta(const int origem, const int destino) const {
  // Verifica se os índices são válidos
  if (origem < 0 || destino < 0 || 
      origem >= (int)matriz.size() || 
      destino >= (int)matriz[origem].size()) {
      return false;
  }
  
  return matriz[origem][destino] != nullptr;
}

//------------------------------------------------------------

const Vertice& GrafoMatriz::getVertice(
  const size_t indice
) const
{
  return *std::find_if(vertices.begin(), vertices.end(), [indice](const Vertice& v) {
    return v.getIndice() == indice; 
  });
}

//------------------------------------------------------------

size_t GrafoMatriz::numeroVertices() const
{
  return vertices.size();
}

//------------------------------------------------------------