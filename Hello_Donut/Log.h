#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>
using namespace std;

class Donut {
private:
    const int WIDTH = 80;
    const int HEIGHT = 24;
    const double R1 = 1.0;
    const double R2 = 2.0;
    const double K2 = 5.0;
    const double M_PI = 3.14;
    const string SHADES = ".,-~:;=!*#$@";

public:
    void renderFrame(double A, double B);
    void run();
};
