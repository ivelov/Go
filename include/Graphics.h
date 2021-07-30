#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#define numOfM 9

using namespace sf;
class Graphics
{
    protected:
    sf::Font font;
    std::map<std::string,sf::Text> text;
    sf::CircleShape** cirTW, **cirTB, **cirW, **cirB;
    sf::RectangleShape** recW, **recB;
    sf::RectangleShape* lines, *rows;
    sf::RectangleShape mesh, passBut, continueBut, NGBut, toMenuBut, exitBut, howToPlayBut, autorsBut;
    Texture texture;
    Sprite sprite;
    public:
        Graphics();
        ~Graphics();
    void drawObjects(sf::RenderWindow& window, const int openMenu, const bool gameOver, std::map<std::string,int[numOfM][numOfM]> mp);
    void editText(const std::string _text, const std::string textName);
    void moveText(const float x, const float y, const std::string textName);
   // void draw (const sf::Drawable &drawable);

};

#endif // GRAPHICS_H
