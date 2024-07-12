#include "hexagon.h"

#define LETTER_SHIFT 25.0f
#define TITLE_SHIFT 20
#define PADDING 5

hexagon::hexagon(unsigned int pos, std::shared_ptr<sf::Font>( font), std::string title) : _pos{pos}
{
    _ramka.setOutlineColor(sf::Color::Black);
    _ramka.setOutlineThickness(1.0f);

    _title.setFont(*font);
    _title.setCharacterSize(21);
    _title.setFillColor(sf::Color::Black);
    _title.setString(title);

    A.setFont(*font);
    A.setCharacterSize(21);
    A.setFillColor(sf::Color::Black);
    A.setString(title[0]);
    A.setPosition({ 0,0 });

    B.setFont(*font);
    B.setCharacterSize(21);
    B.setFillColor(sf::Color::Black);
    B.setString(title[1]);
    B.setPosition({ 0,0 });

    C.setFont(*font);
    C.setCharacterSize(21);
    C.setFillColor(sf::Color::Black);
    C.setString(title[2]);
    C.setPosition({ 0,0 });

    /*_border = sf::VertexArray(sf::LinesStrip, 7);
    _border[0].position = sf::Vector2f(0.0f, 0.0f);     _border[0].color = sf::Color::Black;
    _border[1].position = sf::Vector2f(0.0f, 0.0f);     _border[1].color = sf::Color::Black;
    _border[2].position = sf::Vector2f(0.0f, 0.0f);     _border[2].color = sf::Color::Black;
    _border[3].position = sf::Vector2f(0.0f, 0.0f);     _border[3].color = sf::Color::Black;
    _border[4].position = sf::Vector2f(0.0f, 0.0f);     _border[4].color = sf::Color::Black;
    _border[5].position = sf::Vector2f(0.0f, 0.0f);     _border[5].color = sf::Color::Black;
    _border[6].position = sf::Vector2f(0.0f, 0.0f);     _border[6].color = sf::Color::Black;*/

    _background.setPointCount(6);
    _background.setFillColor(sf::Color::Black);
}

//Trochê matematyki jeszcze nikomu nie zaszkodzi³o. Wiêc dwie kolejne metody to czysta matematyka.
float hexagon::d_coefficient(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p) const
{
    float A = p0.y - p1.y;
    float B = p1.x - p0.x;
    float C = p0.x * (p1.y - p0.y) - p0.y * (p1.x - p0.x);

    return 2 * ((A * p.x + B * p.y + C) / sqrt(A * A + B * B)) / sqrt(3.0f);
}

bool hexagon::rhombus(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p, float& alpha, float& beta) const
{
    float L = sqrt((p1.x - p0.x) * (p1.x - p0.x) + (p1.y - p0.y) * (p1.y - p0.y));
    sf::Vector2f p3(0.5f * (p0.x - p1.x) + 0.5f * sqrt(3.0f) * (p1.y - p0.y) + p0.x, 0.5f * sqrt(3.0f) * (p0.x - p1.x) - 0.5f * (p1.y - p0.y) + p0.y);

    beta = -d_coefficient(p0, p1, p) / L;
    alpha = d_coefficient(p0, p3, p) / L;

    if ((alpha > 1.0f) || (beta > 1.0f) || (alpha < 0.0f) || (beta < 0.0f)) return false; 
    else return true;
}

void hexagon::Set_Borders(sf::Vector2f _left_top, sf::Vector2f _right_bottom)
{
    left_top = _left_top;
    right_bottom = _right_bottom;
    float a = ((right_bottom.y - left_top.y) / 2.0f + 0.5f) - 20.0f;
    center = left_top + sf::Vector2f((right_bottom.x - left_top.x) / 2.0f + 0.5f, (right_bottom.y - left_top.y) / 2.0f + 0.5f + 10);

    p[0] = center - sf::Vector2f(0.0f, a);
    p[1] = center - sf::Vector2f(0.5f * sqrt(3.0f) * a, 0.5f * a);
    p[2] = center - sf::Vector2f(0.5f * sqrt(3.0f) * a, -0.5f * a);
    p[3] = center + sf::Vector2f(0.0f, a);
    p[4] = center + sf::Vector2f(0.5f * sqrt(3.0f) * a, 0.5f * a);
    p[5] = center + sf::Vector2f(0.5f * sqrt(3.0f) * a, -0.5f * a);
}

void hexagon::Draw_Border(sf::RenderTarget& target, sf::RenderStates states, sf::String name) const
{
    // Tu trzeba narysowaæ ramkê. I napisy.
    target.draw(_ramka);
    target.draw(_background);
    target.draw(_title);
    target.draw(A);
    target.draw(B);
    target.draw(C);
}

void hexagon::update_data(sf::Vector2u draw_area_size, unsigned int suwak_width, float jasnosc) {
    float min_size = std::min(((draw_area_size.x - suwak_width) - 4*PADDING) / 2, (draw_area_size.y-TITLE_SHIFT - (PADDING*3)) / 2);
    if (draw_area_size.x - suwak_width < draw_area_size.y-TITLE_SHIFT) {
        // width min
        if (_pos < 2) {
            left_top = { PADDING+(min_size+PADDING*2) * static_cast<float>(_pos % 2), ((draw_area_size.y - (2.0f * min_size)- 4 * PADDING) / 4.0f) + TITLE_SHIFT };
        }else {
            left_top = { PADDING+(min_size+PADDING*2) * static_cast<float>(_pos % 2), ((draw_area_size.y - (2.0f * min_size) - 4 * PADDING) / 4) * 3 + min_size + TITLE_SHIFT };
        }
    }else {
        //height min
        if (_pos < 2) {
            left_top = { ((draw_area_size.x - (min_size * 2.0f) - 4 * PADDING) / 4.0f) + ((min_size + PADDING * 2) * (_pos % 2)), TITLE_SHIFT };
        }else {
            left_top = { ((draw_area_size.x - (min_size * 2.0f) - 4*PADDING) / 4.0f) + ((min_size+PADDING*2) * (_pos % 2)), min_size+TITLE_SHIFT+PADDING*2 };
        }
    }
    right_bottom = { left_top.x + min_size, left_top.y + min_size };
    center = { left_top.x + (min_size / 2.0f), left_top.y + (min_size / 2.0f) };
    _ramka.setPosition(left_top);
    _ramka.setSize({ min_size, min_size });

    Set_Borders(left_top, right_bottom);

    _title.setPosition(left_top);
    A.setPosition({ p[0].x - LETTER_SHIFT, p[0].y - LETTER_SHIFT });
    B.setPosition({ p[2].x - LETTER_SHIFT, p[2].y });
    C.setPosition(p[4]);
    
    /*_border[0].position = sf::Vector2f(p[0]);
    _border[1].position = sf::Vector2f(p[1]);
    _border[2].position = sf::Vector2f(p[2]);
    _border[3].position = sf::Vector2f(p[3]);
    _border[4].position = sf::Vector2f(p[4]);
    _border[5].position = sf::Vector2f(p[5]);
    _border[6].position = sf::Vector2f(p[0]);*/
#define THICK 2
    _background.setPoint(0, { p[0].x, p[0].y - THICK});
    _background.setPoint(1, { p[1].x - THICK, p[1].y - THICK });
    _background.setPoint(2, { p[2].x - THICK, p[2].y + THICK });
    _background.setPoint(3, { p[3].x, p[3].y + THICK });
    _background.setPoint(4, { p[4].x + THICK, p[4].y + THICK });
    _background.setPoint(5, { p[5].x + THICK, p[5].y - THICK });

}
