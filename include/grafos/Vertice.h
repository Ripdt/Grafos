#ifndef VERTICE_H
#define VERTICE_H

#include <string>

class Vertice
{
private:
  int indice;
  std::string label;

public:
  Vertice(
    const int _indice,
    const std::string _label
  );

  virtual ~Vertice() = default;

  Vertice& operator=(const Vertice& other);

  int getIndice() const;

  std::string getLabel() const;
};

#endif
