#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

//------------------------------------------------------------

#include "grafos/Aresta.h"
#include "grafos/Grafo.h"
#include "primitives/Matrix.h"
#include "primitives/Pointer.h"

//------------------------------------------------------------
#include <vector>
#include "Grafo.h"
#include "Aresta.h"

class GrafoMatriz : public Grafo {
private:
    std::vector<std::vector<Aresta*>> matriz; 
    std::vector<Vertice> vertices;            

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

