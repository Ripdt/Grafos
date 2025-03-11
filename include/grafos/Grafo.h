#ifndef GRAFO_H
#define GRAFO_H

//------------------------------------------------------------

#include <string>
#include <vector>

//------------------------------------------------------------

class Vertice;

//------------------------------------------------------------

class Grafo
{
private:
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
  ) = 0;

  virtual void imprime() = 0;

  virtual bool inserirAresta(
    const int origem, 
    const int destino, 
    const int peso = 1
  ) = 0;

  virtual bool removerAresta(
    const int origem, 
    const int destino
  ) = 0;

  virtual bool existeAresta(
    const int origem, 
    const int destino
  ) = 0;

  virtual int pesoAresta(
    const int origem, 
    const int destino
  ) = 0;

  virtual std::vector<Vertice> vizinhosVertice(
    const int indice
  ) = 0;
};

//------------------------------------------------------------

#endif