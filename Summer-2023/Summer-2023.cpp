#include "Summer-2023.h"

float changeGravity(float gravity, float value) {
    return gravity + value < -1. ? -1. : gravity + value;
}

void gravit(sf::CircleShape* circle, float gravity, bool grounded) {
    if (!grounded)
        circle->move(0, gravity);
}

void move(sf::Keyboard::Key key, sf::CircleShape* circle, float gravity, bool grounded) {
    if (grounded)
        gravity = 0;
    switch (key)
    {
    case sf::Keyboard::Left:
        circle->move(-5, gravity);
        break;
    case sf::Keyboard::Right:
        circle->move(5, gravity);
        break;
    default:
        break;
    }
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Jumpy shit");
    window.setSize(sf::Vector2u(1024, 768));
    sf::CircleShape circle{sf::CircleShape(10.f)};
    circle.setFillColor(sf::Color::White);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(300, 200);

    float gravity = .1;

    while (window.isOpen())
    {
        sf::Event event;
        bool grounded;
        if (circle.getPosition().y < window.getSize().y - circle.getRadius())
            grounded = false;
        else
            grounded = true;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Up) {
                    gravity = changeGravity(gravity, -1.f);
                    grounded = false;
                }
                else { 
                    move(event.key.code, &circle, gravity, grounded);
                }
        }
        gravit(&circle, gravity, grounded);
        if (gravity <= .1)
            gravity += .005;

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }

    return 0;
}
