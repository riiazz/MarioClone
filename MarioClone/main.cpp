#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity/EntityManager.h"

int main()
{
    EntityManager e;
    e.addEntity("enemy");
    e.addEntity("player");
    auto& a = e.getEntities();
    std::cout << a.size() << std::endl;
    e.update();
    std::cout << a.size() << std::endl;
    e.getEntities("enemy").front()->destroy();
    std::cout << a.size() << std::endl;
    e.update();
    std::cout << a.size() << std::endl;
}
