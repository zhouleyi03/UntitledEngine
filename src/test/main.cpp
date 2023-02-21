#include "Engine.h"
#include "core/math/Matrix3x3.h"
#include "core/math/Matrix4x4.h"

#include <iostream>

int main(int argc, char* argv[])
{
    Untitled::Engine engine;
    Untitled::Matrix4x4 m(8.0f);
    std::cout << m.determinant();
    return 0;
}