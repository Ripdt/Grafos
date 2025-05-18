#ifndef COLORACAO_H
#define COLORACAO_H

#include <memory>
#include <vector>

class Grafo;

class Coloracao
{
public:
  Coloracao(
    const Grafo& _grafo
  );

  std::vector<int> colorir() const;

private:

  bool coloracaoValida(const std::vector<int>& cores) const;

  bool proximaCombinacao(std::vector<int>& cores, int numCores) const;

  const Grafo& grafo;
};

#endif

