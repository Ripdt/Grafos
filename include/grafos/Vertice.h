#ifndef VERTICE_H
#define VERTICE_H

#include <string>

class Vertice
{
private:
  const int indice;
  const std::string label;

public:
  Vertice(
    const int _indice,
    const std::string _label
  );

  virtual ~Vertice() = default;

  int getIndice() const;

  std::string getLabel() const;
};

#endif
