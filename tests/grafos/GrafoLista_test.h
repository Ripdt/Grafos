#ifndef GRAFOLISTA_TEST_H
#define GRAFOLISTA_TEST_H

//------------------------------------------------------------

#include <gtest/gtest.h>

//------------------------------------------------------------

class GrafoLista;

//------------------------------------------------------------

class GrafoListaTest : public ::testing::Test
{
  protected:
    GrafoLista* grafoNaoDirecionalPonderado = nullptr;
    GrafoLista* grafoDirecionalPonderado = nullptr;
    GrafoLista* grafoNaoDirecionalNaoPonderado = nullptr;
    GrafoLista* grafoDirecionalNaoPonderado = nullptr;

    void SetUp() override;
    void TearDown() override;
};

//------------------------------------------------------------

#endif