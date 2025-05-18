#ifndef ARESTA_H
#define ARESTA_H

#include "grafos/Vertice.h"

class Aresta {
private:
    Vertice* origem;
    Vertice* destino;
    bool estaAtiva = false;
    const float peso;

public:
    Aresta(Vertice* _origem, Vertice* _destino, const float _peso);

    bool operator==(const Aresta& aresta) const;
    bool operator<(const Aresta& outra) const; // Declaração apenas

    virtual ~Aresta() = default;

    Vertice* getOrigem() const;
    Vertice* getDestino() const;
    float getPeso() const;
};

#endif