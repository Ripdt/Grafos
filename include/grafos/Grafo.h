#ifndef GRAFO_H
#define GRAFO_H

//------------------------------------------------------------

#include <string>
#include <vector>

//------------------------------------------------------------

class Vertice;
class Aresta;

//------------------------------------------------------------

class Grafo
{
protected:
  const bool ehPonderado;
  const bool ehDirecionado;

public:
  Grafo(
    const bool _ehDirecionado,
    const bool _ehPonderado
  ) :
    ehPonderado(_ehPonderado),
    ehDirecionado(_ehDirecionado)
  {
  }

  virtual ~Grafo() = default;

  virtual bool inserirVertice(
    const std::string label
  ) = 0;

  virtual bool removerVertice(
    const int indice
  ) = 0;

  virtual std::string labelVertice(
    const int indice
  ) const = 0;

  virtual void imprime() const = 0;

  virtual bool inserirAresta(
    const int origem,
    const int destino,
    const float peso = 1.f
  ) = 0;

  virtual bool removerAresta(
    const int origem,
    const int destino
  ) = 0;

  virtual bool existeAresta(
    const int origem,
    const int destino
  ) const = 0;

  virtual float pesoAresta(
    const int origem,
    const int destino
  ) const = 0;

  virtual std::vector<Vertice*> vizinhosVertice(
    const int indice
  ) const = 0;

  virtual size_t numeroVertices() const = 0;

  virtual Vertice* getVertice(
    const size_t indice
  ) const = 0;

  virtual void resetarCores() = 0;

  virtual Grafo* clonar() const = 0;

  virtual std::vector<Aresta*> getArestas() const = 0;
};

//------------------------------------------------------------

#endif