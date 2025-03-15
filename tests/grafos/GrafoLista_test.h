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
    GrafoLista *grafo;

    void SetUp() override;
    void TearDown() override;
};

//------------------------------------------------------------

#endif