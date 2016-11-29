/*#include <cstdio>
#include <SFML/Graphics.hpp>
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(300, 400), "JEZU CO JA ROBIE");
    sf::CircleShape shape(20.f);
    shape.setFillColor(sf::Color::Red);
 
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
 
        window.clear();
        window.draw(shape);
        window.display();
    }
 
    return 0;
}

*/

#include <SFML/Graphics.hpp>
#include <cmath>
 
#define PI 3.14159265
#define SPEED 30
#define SENSITIVITY 3000
 
 
sf::Keyboard::Key rotLeftButton = sf::Keyboard::Left;
sf::Keyboard::Key rotRightButton = sf::Keyboard::Right;
sf::Keyboard::Key moveButton = sf::Keyboard::Down;
 
 
/**
    Zamiana stopni na radiany
*/
inline float toRad(float degrees)
{
    return (degrees*PI) / 180.f;
}
 
 
/**
    Pobranie wektora przemieszczenia na podstawie kąta podanego w stopniach
*/
sf::Vector2f getMovementVector(float rotation)
{
    sf::Vector2f v;
    float rad = toRad(rotation);
 
    v.x = std::sin(rad);
    v.y = std::cos(rad);
 
    return v;
}
 
 
/*
    Wciśnięcie przycisku odpowiedzialnego za poruszanie
*/
void onMoveButtonPressed(sf::Transformable *transform, const float& delta_time)
{
    sf::Vector2f v;
    sf::Vector2f w = getMovementVector(transform->getRotation());
    
    v.x = w.x * SPEED * delta_time;
    v.y = w.y * SPEED * delta_time;
 
    transform->move(v);
}
 
 
int main()
{
    // przygotowanie obiektu, którym będziemy poruszać
    sf::ConvexShape player(4);
    player.setOutlineColor(sf::Color::White);
    player.setOutlineThickness(3.f);
    player.setFillColor(sf::Color::Transparent);
    
    player.setPoint(0, sf::Vector2f(60, 100));
    player.setPoint(1, sf::Vector2f(80, 120));
    player.setPoint(2, sf::Vector2f(60, 60));
    player.setPoint(3, sf::Vector2f(40, 120));
 
    player.setOrigin(60, 100);
    player.setPosition(640, 360);
 
 
    // ustawienie okna
    sf::ContextSettings c;
    c.antialiasingLevel = 1;
 
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Ustalanie wektora pemieszczenia na podstawie rotacji | szymonsiarkiewicz.pl", 7U, c);
    sf::Clock time;
    float delta = 0;
 
    while (window.isOpen())
    {
        sf::Event event;
 
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
 
        // sterowanie graczem
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == rotLeftButton)
                player.rotate(-SENSITIVITY * delta);
            else if (event.key.code == rotRightButton)
                player.rotate(SENSITIVITY * delta);
 
            if (event.key.code == moveButton)
                onMoveButtonPressed(&player, delta);
        }
 
        window.clear(sf::Color(47,47,47));
        window.draw(player);
        window.display();
 
        delta = time.getElapsedTime().asSeconds();
        time.restart();
    }
}