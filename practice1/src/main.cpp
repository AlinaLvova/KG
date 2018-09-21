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
    makeKonusIntegration("KonusI.stl", 10, 2, 2);

    std::ofstream fout("Сircles.stl");
    makeCircleStl(fout, 15, 4, 0, 0, 0);
    makeCircleStl(fout, 150, 8, 10, -5, 6);
    fout.close();
    
    return 0;
}
