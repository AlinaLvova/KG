// Copyright 2018 Lvova Alina
#pragma once
#include <fstream>
#include <string>
#include <math.h>

void writeTriangle(std::ofstream& fout, double x0, double y0, double z0, double x1, double y1, double z1, double x2, double y2, double z2)
{
    fout << "facet normal -1 0 0\n";
    fout << "outer loop\n";
    fout << "vertex " << std::to_string(x0) << " " << std::to_string(y0) << " " << std::to_string(z0) <<"\n";
    fout << "vertex " << std::to_string(x1) << " " << std::to_string(y1) << " " << std::to_string(z1) << "\n";
    fout << "vertex " << std::to_string(x2) << " " << std::to_string(y2) << " " << std::to_string(z2) << "\n";
    fout << "endloop\n";
    fout << "endfacet\n";
}

void writeTriangleForCylinder(std::ofstream& fout, std::string _p1, std::string _p2, std::string _p3)
{
    fout << "facet normal -1 0 0\n";
    fout << "outer loop\n";
    fout << _p1;
    fout << _p2;
    fout << _p3;
    fout << "endloop\n";
    fout << "endfacet\n";
}

void makeTriangleStl(std::string filename)
{
    std::ofstream fout(filename);
    fout << "solid ascii\n";

    //fout << "facet normal -1 0 0\n";
    //fout << "outer loop\n";
    //fout << "vertex 0 0 0\n";
    //fout << "vertex 1 0 0\n";
    //fout << "vertex 1 1 0\n";
    //fout << "endloop\n";
    //fout << "endfacet";

    writeTriangle(fout, 1, 0, 0, 1, 1, 0, 0, 0, 0);

    fout << "endsolid";
    fout.close();
}

void makeTetrahedronStl(std::string filename)
{
	std::ofstream fout(filename);
	fout << "solid ascii\n";
	
    /*fout << "facet normal -1 0 0\n";
    fout << "outer loop\n";
    fout << "vertex 0 0 0\n";
    fout << "vertex 1 0 0\n";
    fout << "vertex 1 1 0\n";
    fout << "endloop\n";
    fout << "endfacet";


    fout << "facet normal -1 0 0\n";
    fout << "outer loop\n";
    fout << "vertex 1 0 -2\n";
    fout << "vertex 1 1 0\n";
    fout << "vertex 1 0 0\n";
    fout << "endloop\n";
    fout << "endfacet";


    fout << "facet normal -1 0 0\n";
    fout << "outer loop\n";
    fout << "vertex 0 0 0\n";
    fout << "vertex 1 1 0\n";
    fout << "vertex 1 0 -2\n";
    fout << "endloop\n";
    fout << "endfacet";


    fout << "facet normal -1 0 0\n";
    fout << "outer loop\n";
    fout << "vertex 0 0 0\n";
    fout << "vertex 1 0 0\n";
    fout << "vertex 1 0 -2\n";
    fout << "endloop\n";
    fout << "endfacet";*/

    writeTriangle(fout, 0, 0, 0, 1, 0, 0, 1, 1, 0);
    writeTriangle(fout, 1, 0, -2, 1, 1, 0, 1, 0, 0);
    writeTriangle(fout, 0, 0, 0, 1, 1, 0, 1, 0, -2);
    writeTriangle(fout, 0, 0, 0, 1, 0, 0, 1, 0, -2);

	fout<<"endsolid";
	fout.close();
}

void makeCircleStl(std::ofstream& fout, int _n, double _radius, double x0, double y0, double z0)
{
    double alpha = 6.28 / _n;
    double R = _radius;
    std::string center = "vertex " + std::to_string(x0) + " " + std::to_string(y0) + " " + std::to_string(z0) + "\n";
    std::string first0 = "vertex " + std::to_string(R + x0) + " " + std::to_string(y0) + " " + std::to_string(z0) + "\n";
    std::string point01 = first0, point02 = first0;

    fout << "solid ascii\n";
    for (int i = 0; i < _n; i++)
    {
        point02 = "vertex " + std::to_string(R*cos(alpha*i) + x0) +
            " " + std::to_string(R*sin(alpha*i) + y0) + " " + std::to_string(z0) + "\n";
        writeTriangleForCylinder(fout, center, point01, point02);
        point01 = point02;
    }
    writeTriangleForCylinder(fout, first0, center, point01);
    fout << "endsolid\n";
}




void makeKonusIntegration(std::string filename, int _n, double _radius, double h)
{
    double alpha = 6.28 / _n;
    double R = _radius;
    std::string first0;
    std::string point01 = first0, point02 = first0;

    std::ofstream fout(filename);
    fout << "solid ascii\n";
    double z = 0;
    int k=0;
    double step = (R-0.3)/(h/(0.01));
    while (z < h)
    {

        first0 = "vertex " + std::to_string(R) + " 0 " + std::to_string(z) + "\n";
        point01 = first0;
        for (int i = 0; i < _n; i++)
        {
            point02 = "vertex " + std::to_string(R*cos(alpha*i)) + " " + std::to_string(R*sin(alpha*i)) + " " + std::to_string(z) + "\n";
            writeTriangleForCylinder(fout, point01, "vertex 0 0 " + std::to_string(z) + "\n", point02);
            point01 = point02;
        }
        writeTriangleForCylinder(fout, "vertex 0 0 " + std::to_string(z) + "\n", first0, point01);
        R = R - step;
        z = z + 0.01;
        k++;
    }
    fout << "endsolid";
    fout.close();
}




void makeCylinderStl(std::string filename, int _n, double _radius, double _high)
{
    double alpha = 6.28 / _n;
    double R = _radius;
    std::string first0 = "vertex " + std::to_string(_radius) + " 0 0\n";
    std::string first1 = "vertex " + std::to_string(_radius) + " 0 " + std::to_string(_high) + "\n";
    std::string point01 = first0, point02 = first0;
    std::string point11 = first1, point12 = first1;

	std::ofstream fout(filename);
	fout<< "solid ascii\n";
	
	for(int i = 0; i < _n; i++)
	{
        point02 = "vertex " + std::to_string(R*cos(alpha*i)) + " " + std::to_string(R*sin(alpha*i)) + " 0\n";
        point12 = "vertex " + std::to_string(R*cos(alpha*i)) + " " + std::to_string(R*sin(alpha*i)) + " " + std::to_string(_high) + "\n";

        /*fout << "facet normal 1 0 0\n";
        fout << "outer loop\n";
        fout << "vertex 0 0 0\n";
        fout << point01;
        fout << point02;
        fout << "endloop\n";
        fout << "endfacet\n";*/

        writeTriangleForCylinder(fout,  point01, "vertex 0 0 0\n", point02);
        writeTriangleForCylinder(fout, "vertex 0 0 4\n", point11, point12);
        writeTriangleForCylinder(fout, point01, point02, point12);
        writeTriangleForCylinder(fout, point01, point12, point11);

        point01 = point02;
        point11 = point12;
	}

    writeTriangleForCylinder(fout, "vertex 0 0 0\n", first0, point01);
    writeTriangleForCylinder(fout, first1, "vertex 0 0 4\n", point11);
    writeTriangleForCylinder(fout, point01, first0, first1);
    writeTriangleForCylinder(fout, first1, point11, point01);

    //fout << "facet normal 1 0 0\n";
    //fout << "outer loop\n";
    //fout << "vertex 0 0 0\n";
    //fout << first0;
    //fout << point01;
    //fout << "endloop\n";
    //fout << "endfacet\n";

    //fout << "facet normal 1 0 4\n";
    //fout << "outer loop\n";
    //fout << first1;
    //fout << "vertex 0 0 4\n";
    //fout << point11;
    //fout << "endloop\n";
    //fout << "endfacet\n";

    //fout << "facet normal 1 0 0\n";
    //fout << "outer loop\n";
    //fout << point01;
    //fout << first0;
    //fout << first1;
    //fout << "endloop\n";
    //fout << "endfacet\n";

    //fout << "facet normal 1 0 4\n";
    //fout << "outer loop\n";
    //fout << first1;
    //fout << point11;
    //fout << point01;
    //fout << "endloop\n";
    //fout << "endfacet\n";

	fout<<"endsolid";
	fout.close();
}
