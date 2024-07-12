#pragma once
#include "SFML/Graphics.hpp"

class hexagon : public sf::Drawable
{
protected:
    sf::Vector2f left_top, right_bottom, center;
    sf::Vector2f p[6]; // Kolejnoœæ punktów opisana w pliku PDF do laboratorium.

    //sf::Vertex _romb0[4];
    //sf::Vertex _romb1[4];
    //sf::Vertex _romb2[4];
public:
    hexagon(unsigned int pos, std::shared_ptr<sf::Font>(font), std::string title);
    void Set_Borders(sf::Vector2f _left_top, sf::Vector2f _right_bottom);
    void Draw_Border(sf::RenderTarget& target, sf::RenderStates states, sf::String name) const;
    bool rhombus(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p, float& alpha, float& beta) const;
    virtual void update_data(sf::Vector2u draw_area_size, unsigned int suwak_width, float jasnosc=1);
private:
    float d_coefficient(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p) const;
    unsigned int _pos;
    sf::RectangleShape _ramka;
    //sf::VertexArray _border;
    sf::ConvexShape _background;

    sf::Text _title;
    sf::Text A, B, C;
};