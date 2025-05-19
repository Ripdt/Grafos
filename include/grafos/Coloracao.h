#ifndef COLORACAO_H
#define COLORACAO_H

#include <memory>
#include <vector>
#include <list>

class Grafo;
class Vertice;

class Coloracao
{
public:
  Coloracao(
    Grafo& _grafo
  );

  void colorir_BruteForce() const;

  void colorir_WelshPowell() const;

  void colorir_DSatur() const;

private:

  bool coloracaoValida(const std::vector<int>& cores) const;

  bool proximaCombinacao(std::vector<int>& cores, int numCores) const;

  std::list<Vertice*> verticesOrdenadosPorGrau() const;

  Vertice* verticeComMaiorSaturacao(
    const std::list<Vertice*>& vertices
  ) const;

  Grafo& grafo;
};

#endif

