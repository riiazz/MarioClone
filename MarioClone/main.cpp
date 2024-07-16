#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vec2.h"

int main()
{
    Vec2 a(3, 3);
    Vec2 b(2, 2);
    a /= b;
    std::cout << a.x << "," << a.y << std::endl;
    return 0;
}
