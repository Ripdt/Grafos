#include "Aresta.h"

Aresta::Aresta(const Vertice* _origem, const Vertice* _destino, const int _peso)
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

const Vertice* Aresta::getOrigem() const {
    return origem;
}

//------------------------------------------------------------

const Vertice* Aresta::getDestino() const {
    return destino;
}

//------------------------------------------------------------

int Aresta::getPeso() const {
    return peso;
}