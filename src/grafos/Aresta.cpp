#include "Aresta.h"

Aresta::Aresta(Vertice* _origem, Vertice* _destino, const float _peso)
    : origem(_origem), destino(_destino), peso(_peso) {}

//------------------------------------------------------------
    
bool Aresta::operator==(const Aresta& aresta) const {
    return origem == aresta.origem && destino == aresta.destino && peso == aresta.peso;
}

//------------------------------------------------------------

bool Aresta::operator<(const Aresta& outra) const {
    if (origem->getIndice() != outra.origem->getIndice()) {
        return origem->getIndice() < outra.origem->getIndice();
    }
    return destino->getIndice() < outra.destino->getIndice();
}

//------------------------------------------------------------

Vertice* Aresta::getOrigem() const {
    return origem;
}

//------------------------------------------------------------

Vertice* Aresta::getDestino() const {
    return destino;
}

//------------------------------------------------------------

float Aresta::getPeso() const {
    return peso;
}