#ifndef ARESTA_H
#define ARESTA_H

#include "grafos/Vertice.h"

class Aresta {
private:
    const Vertice* origem;
    const Vertice* destino;
    bool estaAtiva = false;
    const float peso;

public:
    Aresta(const Vertice* _origem, const Vertice* _destino, const float _peso);

    bool operator==(const Aresta& aresta) const;
    bool operator<(const Aresta& outra) const; // Declaração apenas

    virtual ~Aresta() = default;

    const Vertice* getOrigem() const;
    const Vertice* getDestino() const;
    float getPeso() const;
};

#endif