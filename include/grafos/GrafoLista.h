#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

//------------------------------------------------------------

#include "grafos/Aresta.h"
#include "grafos/Grafo.h"
#include "primitives/Pointer.h"
#include <map>
#include <list>

//------------------------------------------------------------

typedef std::pair<Pointer<Vertice>, std::list<Pointer<Aresta>>> ArestasPorVertice;
typedef std::map<Pointer<Vertice>, std::list<Pointer<Aresta>>> ListaAdjacencia;

//------------------------------------------------------------

class GrafoLista : public Grafo
{
private:
  ListaAdjacencia listaAdjacencia;
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