#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

//------------------------------------------------------------

#include "grafos/Grafo.h"
#include "grafos/Vertice.h"
#include "primitives/Pointer.h"

//------------------------------------------------------------

template <typename T>
class Matrix;
class Aresta;

//------------------------------------------------------------

class GrafoMatriz : public Grafo
{
private:
  Pointer<Matrix<Aresta*>> matriz;
  unsigned int numeroVerticesAdicionados = 0;

public:
  GrafoMatriz(
    const bool _ehDirecionado,
    const bool _ehPonderado
  );

  virtual ~GrafoMatriz() = default;

  bool inserirVertice(
    const std::string label
  );

  bool removerVertice(
    const int indice
  );

  std::string labelVertice(
    const int indice
  );

  void imprime();

  bool inserirAresta(
    const int origem,
    const int destino,
    const int peso = 1
  );

  bool removerAresta(
    const int origem,
    const int destino
  );

  bool existeAresta(
    const int origem,
    const int destino
  );

  int pesoAresta(
    const int origem,
    const int destino
  );

  std::vector<Vertice> vizinhosVertice(
    const int indice
  );
};

//------------------------------------------------------------

#endif

