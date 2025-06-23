#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

//------------------------------------------------------------

#include "grafos/Aresta.h"
#include "grafos/Grafo.h"
#include "primitives/Pointer.h"
#include <map>
#include <set>

//------------------------------------------------------------

typedef std::set<Aresta> ListaArestas;
typedef std::map<Vertice*, ListaArestas> ListaAdjacencia;
typedef std::vector<Pointer<Vertice>> Vertices;

//------------------------------------------------------------

class GrafoLista : public Grafo
{
private:
  ListaAdjacencia listaAdjacencia;
  Vertices vertices;
public:
  GrafoLista(
    const bool _ehDirecionado,
    const bool _ehPonderado
  );

  virtual ~GrafoLista() = default;

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

  GrafoLista* clonar() const;

  std::vector<Aresta*> getArestas() const override;

private:
  Vertice* buscaVertice(const size_t indice) const;

  const Aresta* buscaAresta(
    Vertice* origem,
    const int destino
  ) const;
};

//------------------------------------------------------------

#endif