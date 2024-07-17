#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vec2.h"
#include "Entity.h"

int main()
{
    Entity e("test", 1);
    e.addComponent<CLifespan>(CLifespan(100));
    auto& get = e.getComponent<CLifespan>();
    std::cout << get.remaining << "," << get.total << "," << get.has << std::endl;
    e.removeComponent<CLifespan>();
    std::cout << get.remaining << "," << get.total << "," << get.has << std::endl;
    e.addComponent<CLifespan>(CLifespan(100));
    std::cout << get.remaining << "," << get.total << "," << get.has << std::endl;
    std::cout << e.hasComponent<CLifespan>() << std::endl;
    std::cout << "id: " << e.getId() << std::endl;
    std::cout << "tag: " << e.getTag() << std::endl;
    std::cout << "alive: " << e.isActive() << std::endl;
    e.destroy();
    std::cout << "alive: " << e.isActive() << std::endl;
    
    return 0;
}
