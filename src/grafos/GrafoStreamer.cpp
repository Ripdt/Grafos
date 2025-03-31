#include "GrafoStreamer.h"

#include "grafos/Grafo.h"
#include "grafos/GrafoLista.h"
#include "grafos/GrafoMatriz.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace Utils
{
  std::vector<std::string> split(
    const std::string& s,
    const char delimiter
  )
  {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
      tokens.push_back(token);
    }
    return tokens;
  }
}

GrafoStreamer::GrafoStreamer(
  const Adjacencia _tipo
) :
  tipo(_tipo)
{
}

Grafo* GrafoStreamer::ler(
  const std::string& path
)
{
  Grafo* grafo = nullptr;
  try {
    std::ifstream file(path);

    if (!file.is_open())
    {
      const std::string msg = "Falha ao tentar abrir o arquivo: " + path;
      throw std::exception(msg.c_str());
    }

    std::string line;
    std::getline(file, line);

    grafo = criarGrafo(line);

    while (std::getline(file, line))
    {
      const std::vector<std::string> tokens = Utils::split(line, ' ');
      if (tokens.size() != 3)
      {
        std::cerr << "Aresta inválida: " << line << std::endl;
        throw std::exception();
      }
      const int origem = std::stoi(tokens[0]);
      const int destino = std::stoi(tokens[1]);
      const int peso = std::stoi(tokens[2]);
      grafo->inserirAresta(origem, destino, peso);
    }

    file.close();
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
  }

  return grafo;
}

Grafo* GrafoStreamer::criarGrafo(
  const std::string& line
) const
{
  const std::vector<std::string> tokens = Utils::split(line, ' ');
  if (tokens.size() != 4) {
    const std::string msg = "Grafo inválido: " + line;
    throw std::exception(msg.c_str());
  }

  const size_t numeroVertices = std::stoi(tokens[0]);
  const bool ehDirecionado = std::stoi(tokens[2]) == 1;
  const bool ehPonderado = std::stoi(tokens[3]) == 1;

  Grafo* grafo = nullptr;
  if (tipo == Adjacencia::MATRIZ)
    grafo = new GrafoMatriz(ehDirecionado, ehPonderado);
  else if (tipo == Adjacencia::LISTA)
    grafo = new GrafoLista(ehDirecionado, ehPonderado);
  
  for (int i = 0; i < numeroVertices; i++)
    grafo->inserirVertice(std::to_string(i));

  return grafo;
}
