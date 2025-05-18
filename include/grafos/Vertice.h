#ifndef VERTICE_H
#define VERTICE_H

#include <string>

class Vertice
{
private:
  int indice;
  int cor = -1;
  int grau = 0;
  std::string label;

public:
  Vertice(
    const int _indice,
    const std::string _label
  );

  virtual ~Vertice() = default;

  bool operator<(const Vertice& other) const;
  bool operator==(const Vertice& other) const;

  Vertice& operator=(const Vertice& other);

  int getIndice() const;

  std::string getLabel() const;

  void setIndice(int novoIndice); 

  void setCor(int novaCor);

  int getCor() const;

  void aumentarGrau();
  void diminuirGrau();
  int getGrau() const;
};

#endif
