#ifndef ALGORITMO_DIJKSTRA_H
#define ALGORITMO_DIJKSTRA_H

#include "grafos/Grafo.h"
#include "grafos/Vertice.h"
#include "primitives/Pointer.h"

#include <unordered_map>

class Caminho
{
public:
	const Vertice* verticeDestino;
	float distancia = std::numeric_limits<float>::max();
	bool marcado = false;
	std::vector<const Vertice*> caminho;

public:
	Caminho(
		const Vertice* _verticeDestino
	) :
		verticeDestino(_verticeDestino)
	{
	};
};

class AlgoritmoDijkstra
{
	private:
		const Grafo& grafo;

	public:
		AlgoritmoDijkstra(
			const Grafo& _grafo
		);

		void rodar(
			const int origem
		) const;

    const std::unordered_map<int, Pointer<Caminho>>& getCaminhos() const
    {
      return menorCaminhoAteVertice;
    }

private:

	void acharCaminhosAteVizinhos(
		const Vertice* verticeOrigem,
		const Caminho& caminhoAteOrigem,
		std::unordered_map<int, Pointer<Caminho>>& caminhoAteVertice
	) const;

	void acharCaminhosAteVizinhos(
		const Vertice* verticeOrigem,
		const Caminho& caminhoAteOrigem,
		std::unordered_map<int, Pointer<Caminho>>& caminhoAteVertice,
		std::vector<Pointer<Caminho>>& caminhosEncontrados
	) const;

	mutable std::unordered_map<int, Pointer<Caminho>> menorCaminhoAteVertice;
};

#endif