#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

//------------------------------------------------------------

#include "grafos/Grafo.h"
#include "grafos/Vertice.h"
#include "primitives/Pointer.h"
#include <map>
#include <list>

//------------------------------------------------------------

class Aresta;

class GrafoLista : public Grafo
{
private:
  std::map<int, std::list<Aresta>> listaAdjacencia;
  unsigned int numeroVerticesAdicionados = 0;

public:
  GrafoLista(
    const bool _ehDirecionado,
    const bool _ehPonderado
  );

  virtual ~GrafoLista() = default;

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