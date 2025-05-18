#ifndef GRAFO_STREAMER_H
#define GRAFO_STREAMER_H

#include <string>
#include <exception>

class Grafo;

enum Adjacencia {
  MATRIZ = 0,
  LISTA = 1
};

class GrafoStreamer
{
private:;
  const Adjacencia tipo;
public:
  GrafoStreamer(
    const Adjacencia _tipo
  );

  ~GrafoStreamer() = default;

  Grafo* ler(
    const std::string& caminho
  );

private:

  Grafo* criarGrafo(
    const std::string& line
  ) const;
};

#endif

