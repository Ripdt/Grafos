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
  ) override;

  bool removerVertice(
    const int indice
  ) override;

  std::string labelVertice(
    const int indice
  ) const override;

  void imprime() const override;

  bool inserirAresta(
    const int origem,
    const int destino,
    const float peso = 1.f
  ) override;

  bool removerAresta(
    const int origem,
    const int destino
  ) override;

  bool existeAresta(
    const int origem,
    const int destino
  ) const override;

  float pesoAresta(
    const int origem,
    const int destino
  ) const override;

  std::vector<Vertice*> vizinhosVertice(
    const int indice
  ) const override;

  Vertice* getVertice(
    const size_t indice
  ) const override;

  size_t numeroVertices() const override;

  void resetarCores() override;

  GrafoMatriz* clonar() const;
};

//------------------------------------------------------------

#endif

