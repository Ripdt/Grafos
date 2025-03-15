#include "GrafoMatriz.h"

#include "grafos/Aresta.h"
#include "primitives/Matrix.h"

#include <iostream>

//------------------------------------------------------------

GrafoMatriz::GrafoMatriz(
  const bool _ehDirecionado, 
  const bool _ehPonderado
) :
  Grafo(_ehDirecionado, _ehPonderado),
  matriz(1, 1)
{
}

//------------------------------------------------------------

bool GrafoMatriz::inserirVertice(
  const std::string label
)
{
  numeroVerticesAdicionados++;
  vertices.push_back(Vertice(numeroVerticesAdicionados, label));
  if (numeroVerticesAdicionados == 1) {
    return true;
  }

  return matriz.addRow() && matriz.addColumn();
}

//------------------------------------------------------------

bool GrafoMatriz::removerVertice(
  const int indice
)
{
  vertices.erase(vertices.begin() + indice);
  return matriz.removeRow(indice) && matriz.removeColumn(indice);
}

//------------------------------------------------------------

std::string GrafoMatriz::labelVertice(const int indice)
{
  if (indice >= vertices.size()) {
    return "";
  }

  const Vertice& vertice = vertices.at(indice);
  return vertice.getLabel();
}

//------------------------------------------------------------

void GrafoMatriz::imprime()
{
  for (const Vertice& vertice : vertices) {
    std::cout << "\t" << vertice.getLabel();
  }

  std::cout << std::endl;
  for (unsigned i = 0; i < matriz.nRows(); i++) {
    std::cout << vertices.at(i).getLabel();
    for (unsigned j = 0; j < matriz.nColumns(); j++) {
      if (matriz[i][j] == nullptr) {
        std::cout << "\t0";
      }
      else {
        std::cout << "\t" << matriz[i][j]->getPeso();
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

}

//------------------------------------------------------------

bool GrafoMatriz::inserirAresta(
  const int origem, 
  const int destino, 
  const int peso
)
{
  if (origem >= vertices.size() || destino >= vertices.size()) {
    return false;
  }

  const int pesoAresta = ehPonderado ? peso : 1;
  auto aresta = new Aresta(&vertices.at(origem), &vertices.at(destino), peso);

  matriz[origem][destino] = aresta;

  if (!ehDirecionado) {
    matriz[destino][origem] = aresta;
  }

  return true;
}

//------------------------------------------------------------

bool GrafoMatriz::removerAresta(
  const int origem, 
  const int destino
)
{
  matriz[origem][destino] = nullptr;
  if (!ehDirecionado) {
    matriz[destino][origem] = nullptr;
  }
  return false;
}

//------------------------------------------------------------

bool GrafoMatriz::existeAresta(
  const int origem, 
  const int destino
)
{
  return matriz[origem][destino] != nullptr;
}

//------------------------------------------------------------

int GrafoMatriz::pesoAresta(
  const int origem, 
  const int destino
)
{
  return matriz[origem][destino]->getPeso();
}

//------------------------------------------------------------

std::vector<Vertice> GrafoMatriz::vizinhosVertice(
  const int indice
)
{
  std::vector<Vertice> vizinhos;
  for (int i = 0; i < matriz.nRows(); i++) {
    if (matriz[i][indice] != nullptr) {
      vizinhos.push_back(*matriz[i][indice]->getOrigem());
    }
  }
  for (int j = 0; j < matriz.nRows(); j++) {
    if (matriz[indice][j] != nullptr) {
      vizinhos.push_back(*matriz[indice][j]->getOrigem());
    }
  }
  return vizinhos;
}

//------------------------------------------------------------
