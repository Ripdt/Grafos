#ifndef GRAFOMATRIZ_TEST_H
#define GRAFOMATRIZ_TEST_H

//------------------------------------------------------------

#include <gtest/gtest.h>

//------------------------------------------------------------

class GrafoMatriz;

//------------------------------------------------------------

class GrafoMatrizTest : public ::testing::Test
{
protected:
    GrafoMatriz *grafo;

    void SetUp() override;
    void TearDown() override;
};

//------------------------------------------------------------

#endif