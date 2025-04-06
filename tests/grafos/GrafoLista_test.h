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
    GrafoLista* grafoNaoDirecionalPonderado;
    GrafoLista* grafoDirecionalPonderado;
    GrafoLista* grafoNaoDirecionalNaoPonderado;
    GrafoLista* grafoDirecionalNaoPonderado;

    void SetUp() override;
    void TearDown() override;
};

//------------------------------------------------------------

#endif