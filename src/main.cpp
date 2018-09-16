// Copyright 2018 Lvova Alina
#include <iostream>
#include "solid.h"

int main()
{
    double radius = 2.3, high = 4;
    int n = 100;
    std::cout << "Hello, this is STL!" << std::endl;
    makeTriangleStl("Triangle.stl");
    makeTetrahedronStl("Tetrahedron.stl");
    makeCylinderStl("Cylinder.stl", 100, 2.3, 4);
    makeRingStl("Ring.stl", 40, 2);
    return 0;
}
