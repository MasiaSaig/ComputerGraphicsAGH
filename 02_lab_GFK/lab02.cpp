//Uwaga! Co najmniej C++17!!!
//Project-> ... Properties->Configuration Properties->General->C++ Language Standard == ISO C++ 17 Standard (/std:c++17)

#include "hexagon.h"
#include "suwak.h"
#include "SFML/Graphics.hpp"
#include "ShareTechMono-Regular.h"
#include <numeric>
#include <iostream>

//Tak – dobrze państwo widzą – TO jest zmienna globalna! Czytanie i przetwarzanie fontów w SFML jest bardzo kosztowne. Dlatego zrobimy to raz. 
//Co nie zmienia faktu, że można by to zrobić bez zmiennej globalnej i to całkiem ładnie. Jak? To już dla Państwa :-)
std::shared_ptr<sf::Font> font;

#define JAS static_cast<unsigned int>(255.0f*jas)

class hexagon_RGB : public hexagon
{
public:
    hexagon_RGB(unsigned int pos, std::shared_ptr<sf::Font>(font), std::string title) : hexagon(pos, font, title), jasnosc{ 1 }
    {
        
    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update_data(sf::Vector2u draw_area_size, unsigned int suwak_width, float jas=1) override;
private:
    //sf::Text kolor;

    float jasnosc;
    sf::Vertex _romb0[4];
    sf::Vertex _romb1[4];
    sf::Vertex _romb2[4];
};

void hexagon_RGB::update_data(sf::Vector2u draw_area_size, unsigned int suwak_width, float jas) {
    hexagon::update_data(draw_area_size, suwak_width);
    jasnosc = jas;

    _romb0[0].position = p[0];
    _romb0[0].color = sf::Color(255 , 0 , 0, JAS );
    _romb0[1].position = p[1];
    _romb0[1].color = sf::Color(255 , 255 , 0 , JAS);
    _romb0[2].position = center;
    _romb0[2].color = sf::Color(255 , 255 , 255, JAS );
    _romb0[3].position = p[5];
    _romb0[3].color = sf::Color(255 , 0 , 255, JAS);

    _romb1[0].position = p[1];
    _romb1[0].color = sf::Color(255 , 255 , 0 , JAS);
    _romb1[1].position = p[2];
    _romb1[1].color = sf::Color(0 ,255 ,0 , JAS);
    _romb1[2].position = p[3];
    _romb1[2].color = sf::Color(0 , 255 , 255, JAS);
    _romb1[3].position = center;
    _romb1[3].color = sf::Color(255 , 255 , 255 , JAS);

    _romb2[0].position = p[3];
    _romb2[0].color = sf::Color(0 , 255, 255, JAS);
    _romb2[1].position = p[4];
    _romb2[1].color = sf::Color(0, 0, 255, JAS);
    _romb2[2].position = p[5];
    _romb2[2].color = sf::Color(255,0,255, JAS);
    _romb2[3].position = center;
    _romb2[3].color = sf::Color(255,255,255, JAS);
}


void hexagon_RGB::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Tu trzeba narysować sześciokąt RGB.
    Draw_Border(target, states, "RGB");
    //float alfa, beta;
    //sf::VertexArray point(sf::Points, 1);

    target.draw(_romb0, 4, sf::Quads);
    target.draw(_romb1, 4, sf::Quads);
    target.draw(_romb2, 4, sf::Quads);
    /*for (float i = p[1].x; i < p[1].x+(p[0].x - p[1].x) * 2; ++i) {
        for (float j = p[0].y; j < p[0].y+(p[1].y - p[0].y) * 2; ++j) {
            if (rhombus(p[0], p[1], { i,j }, alfa, beta)) {
                float var_X = alfa;
                float var_Y = beta;
                float var_Z = 100 / 100;

                float var_R = var_X * 3.2406 + var_Y * -1.5372 +var_Z * -0.4986;
                float var_G = var_X * -0.9689 + var_Y * 1.8758 +var_Z * 0.0415;
                float var_B = var_X * 0.0557 + var_Y * -0.2040 +var_Z * 1.0570;

                if (var_R > 0.0031308) var_R = (1.055f * std::pow(var_R, 1.0f / 2.4f)) - 0.055f;
                else                     var_R = 12.92f * var_R;
                if (var_G > 0.0031308) var_G = (1.055f * std::pow(var_G, 1.0f / 2.4f)) - 0.055f;
                else                     var_G = 12.92f * var_G;
                if (var_B > 0.0031308) var_B = (1.055f * std::pow(var_B, 1.0f / 2.4f)) - 0.055f;
                else                     var_B = 12.92f * var_B;

                float sR = var_R * 255;
                float sG = var_G * 255;
                float sB = var_B * 255;
                point[0].color = sf::Color(sR, sG, sB);
                point[0].position = sf::Vector2f(i, j);
                target.draw(point);
            }
        }
    }*/
    
}

class hexagon_CMY : public hexagon
{
public:
    hexagon_CMY(unsigned int pos, std::shared_ptr<sf::Font>(font), std::string title) : hexagon(pos, font, title), jasnosc{ 1 } {
        _back.setPointCount(6);
        _back.setFillColor(sf::Color::White);

        kolor.setFont(*font);
        kolor.setCharacterSize(16);
        kolor.setFillColor(sf::Color::Black);
    };
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update_data(sf::Vector2u draw_area_size, unsigned int suwak_width, float jas=1) override;
    void getColor(int mx, int my);
private:
    sf::Text kolor;

    float jasnosc;
    sf::ConvexShape _back;
    sf::Vertex _romb0[4];
    sf::Vertex _romb1[4];
    sf::Vertex _romb2[4];
};

void hexagon_CMY::getColor(int mx, int my) {
    float alfa, beta;
    if (rhombus(p[0], p[1], { static_cast<float>(mx), static_cast<float>(my) }, alfa, beta)) {
        kolor.setString("c: " + std::to_string(255.0f * jasnosc) + "\nm: " + std::to_string(alfa * 255.0f * jasnosc) + "\ny: " + std::to_string(beta * 255.0f * jasnosc));
    }
    else if (rhombus(p[2], p[3], { static_cast<float>(mx), static_cast<float>(my) }, alfa, beta)) {
        kolor.setString("c: " + std::to_string(beta * 255 * jasnosc) + "\nm: " + std::to_string(255 * jasnosc) + "\ny: " + std::to_string(alfa * 255 * jasnosc));
    }
    else if (rhombus(p[4], p[5], { static_cast<float>(mx), static_cast<float>(my) }, alfa, beta)) {
        kolor.setString("c: " + std::to_string(alfa * 255 * jasnosc) + "\nm: " + std::to_string(beta * 255 * jasnosc) + "\ny: " + std::to_string(255 * jasnosc));
    }
    else {
        kolor.setString("c: x, m: x, y: x");
    }
}

static constexpr unsigned int RGB_to_CMY(unsigned int RGB_val) {
    return (1 - (RGB_val / 255)) * 255;
}

void hexagon_CMY::update_data(sf::Vector2u draw_area_size, unsigned int suwak_width, float jas) {
    hexagon::update_data(draw_area_size, suwak_width);
    jasnosc = jas;
    kolor.setPosition(draw_area_size.x - 150, draw_area_size.y - 150);

    _back.setPoint(0, p[0]);
    _back.setPoint(1, p[1]);
    _back.setPoint(2, p[2]);
    _back.setPoint(3, p[3]);
    _back.setPoint(4, p[4]);
    _back.setPoint(5, p[5]);

    _romb0[0].position = p[0];
    _romb0[0].color = sf::Color(RGB_to_CMY(255), RGB_to_CMY(0) , RGB_to_CMY(0) , JAS);
    _romb0[1].position = p[1];
    _romb0[1].color = sf::Color(RGB_to_CMY(255) , RGB_to_CMY(255) , RGB_to_CMY(0) , JAS);
    _romb0[2].position = center;
    _romb0[2].color = sf::Color(RGB_to_CMY(255) , RGB_to_CMY(255) , RGB_to_CMY(255) , JAS);
    _romb0[3].position = p[5];
    _romb0[3].color = sf::Color(RGB_to_CMY(255) , RGB_to_CMY(0) , RGB_to_CMY(255) , JAS);

    _romb1[0].position = p[1];
    _romb1[0].color = sf::Color(RGB_to_CMY(255) , RGB_to_CMY(255) , RGB_to_CMY(0) , JAS);
    _romb1[1].position = p[2];
    _romb1[1].color = sf::Color(RGB_to_CMY(0) , RGB_to_CMY(255) , RGB_to_CMY(0) , JAS);
    _romb1[2].position = p[3];
    _romb1[2].color = sf::Color(RGB_to_CMY(0) , RGB_to_CMY(255) , RGB_to_CMY(255) , JAS);
    _romb1[3].position = center;
    _romb1[3].color = sf::Color(RGB_to_CMY(255) , RGB_to_CMY(255) , RGB_to_CMY(255) , JAS);

    _romb2[0].position = p[3];
    _romb2[0].color = sf::Color(RGB_to_CMY(0) , RGB_to_CMY(255) , RGB_to_CMY(255) , JAS);
    _romb2[1].position = p[4];
    _romb2[1].color = sf::Color(RGB_to_CMY(0) , RGB_to_CMY(0) , RGB_to_CMY(255) , JAS);
    _romb2[2].position = p[5];
    _romb2[2].color = sf::Color(RGB_to_CMY(255) , RGB_to_CMY(0) , RGB_to_CMY(255) , JAS);
    _romb2[3].position = center;
    _romb2[3].color = sf::Color(RGB_to_CMY(255) , RGB_to_CMY(255) , RGB_to_CMY(255) , JAS);
}

void hexagon_CMY::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Tu trzeba narysować sześciokąt CMY.
    Draw_Border(target, states, "CMY");
    target.draw(_back);
    target.draw(_romb0, 4, sf::Quads);
    target.draw(_romb1, 4, sf::Quads);
    target.draw(_romb2, 4, sf::Quads);
    target.draw(kolor);
}

class hexagon_HSL : public hexagon
{
public:
    hexagon_HSL(unsigned int pos, std::shared_ptr<sf::Font>(font), std::string title) : hexagon(pos, font, title), jasnosc{1} {};
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update_data(sf::Vector2u draw_area_size, unsigned int suwak_width, float jas=1) override;
    float jasnosc;
private:
    //sf::Vertex _romb0[4];
    //sf::Vertex _romb01[4];
    //sf::Vertex _romb1[4];
    sf::Vertex _romb2[4];
};

//static constexpr unsigned int RGB_to_L(unsigned int R, unsigned int G, unsigned int B) {
//    float var_R = (R / 255.0f);
//    float var_G = (G / 255.0f);
//    float var_B = (B / 255.0f);
//
//    //Min. value of RGB
//    float var_Min = var_R;
//    if (var_G < var_R)
//        var_Min = var_G;
//    if (var_B < var_Min)
//        var_Min = var_B;
//    //Max. value of RGB
//    float var_Max = var_R;
//    if (var_G > var_R)
//        var_Max = var_G;
//    if (var_B > var_Min)
//        var_Max = var_B;
//    float del_Max = var_Max - var_Min;             //Delta RGB value
//
//    return static_cast<unsigned int>(((var_Max + var_Min) / 2)*255);
//};
//
//static constexpr unsigned int RGB_to_S(unsigned int R, unsigned int G, unsigned int B) {
//    float var_R = (R / 255.0f);
//    float var_G = (G / 255.0f);
//    float var_B = (B / 255.0f);
//
//    //Min. value of RGB
//    float var_Min = var_R;
//    if (var_G < var_R)
//        var_Min = var_G;
//    if (var_B < var_Min)
//        var_Min = var_B;
//    //Max. value of RGB
//    float var_Max = var_R;
//    if (var_G > var_R)
//        var_Max = var_G;
//    if (var_B > var_Min)
//        var_Max = var_B;
//    float del_Max = var_Max - var_Min;             //Delta RGB value
//
//    float L = (var_Max + var_Min) / 2;
//
//    float H = 0;                        //This is a gray, no chroma...
//    float S = 0;
//    if (del_Max != 0) {                  //Chromatic data...
//        if (L < 0.5) S = del_Max / (var_Max + var_Min);
//        else         S = del_Max / (2 - var_Max - var_Min);
//    }
//    return static_cast<unsigned int>(S*255);
//}
//
//static constexpr unsigned int RGB_to_H(unsigned int R, unsigned int G, unsigned int B) {
//    float var_R = (R / 255.0f);
//    float var_G = (G / 255.0f);
//    float var_B = (B / 255.0f);
//
//    //Min. value of RGB
//    float var_Min = var_R;
//    if (var_G < var_R)
//        var_Min = var_G;
//    if (var_B < var_Min)
//        var_Min = var_B;
//    //Max. value of RGB
//    float var_Max = var_R;
//    if (var_G > var_R)
//        var_Max = var_G;
//    if (var_B > var_Min)
//        var_Max = var_B;
//    float del_Max = var_Max - var_Min;             //Delta RGB value
//
//    float L = (var_Max + var_Min) / 2;
//
//    float H = 0;                        //This is a gray, no chroma...
//    float S = 0;
//    if (del_Max != 0) {                  //Chromatic data...
//        if (L < 0.5) S = del_Max / (var_Max + var_Min);
//        else         S = del_Max / (2 - var_Max - var_Min);
//
//        float del_R = (((var_Max - var_R) / 6) + (del_Max / 2)) / del_Max;
//        float del_G = (((var_Max - var_G) / 6) + (del_Max / 2)) / del_Max;
//        float del_B = (((var_Max - var_B) / 6) + (del_Max / 2)) / del_Max;
//
//        if (var_R == var_Max) H = del_B - del_G;
//        else if (var_G == var_Max) H = (1.0f / 3.0f) + del_R - del_B;
//        else if (var_B == var_Max) H = (2.0f / 3.0f) + del_G - del_R;
//
//        if (H < 0) H += 1;
//        if (H > 1) H -= 1;
//    }
//    return static_cast<unsigned int>(H*255);
//}
//
//static constexpr float Hue_2_RGB(float v1, float v2, float vH)             //Function Hue_2_RGB
//{
//    if (vH < 0) vH += 1;
//    if (vH > 1) vH -= 1;
//    if ((6 * vH) < 1) return (v1 + (v2 - v1) * 6 * vH);
//    if ((2 * vH) < 1) return (v2);
//    if ((3 * vH) < 2) return (v1 + (v2 - v1) * ((2 / 3) - vH) * 6);
//    return (v1);
//}

void hexagon_HSL::update_data(sf::Vector2u draw_area_size, unsigned int suwak_width, float jas) {
    hexagon::update_data(draw_area_size, suwak_width);
    jasnosc = jas;

    /*sf::Vector2f mid_l = { p[1].x + (center.x - p[1].x) / 2, p[1].y + (center.y - p[1].y) / 2 };
    sf::Vector2f mid_r = { p[0].x + (p[5].x - p[0].x) / 2, p[0].y + (p[5].y - p[0].y) / 2 };
    _romb0[0].position = p[0];
    _romb0[0].color = sf::Color(0,0,0, JAS);
    _romb0[1].position = p[1];
    _romb0[1].color = sf::Color(0,0,0, JAS);
    _romb0[2].position = mid_l;
    _romb0[2].color = sf::Color(255,0,0,JAS);
    _romb0[3].position = mid_r;
    _romb0[3].color = sf::Color(128,128,128, JAS);
    
    _romb01[0].position = mid_r;
    _romb01[0].color = sf::Color(127,127,127, JAS);
    _romb01[1].position = mid_l;
    _romb01[1].color = sf::Color(255,0,0, JAS);
    _romb01[2].position = center;
    _romb01[2].color = sf::Color(255,255,255,JAS);
    _romb01[3].position = p[5];
    _romb01[3].color = sf::Color(255,255,255, JAS);*/
    
    /*_romb1[0].position = p[1];
    r = 255; g = 255; b = 0;
    _romb1[0].color = sf::Color(RGB_to_H(r, g, b), RGB_to_S(r, g, b), RGB_to_L(r, g, b), JAS);
    _romb1[1].position = p[2];
    r = 0; g = 255; b = 0;
    _romb1[1].color = sf::Color(RGB_to_H(r, g, b), RGB_to_S(r, g, b), RGB_to_L(r, g, b), JAS);
    _romb1[2].position = p[3];
    r = 0; g = 255; b = 255;
    _romb1[2].color = sf::Color(RGB_to_H(r, g, b), RGB_to_S(r, g, b), RGB_to_L(r, g, b), JAS);
    _romb1[3].position = center;
    r = 255; g = 255; b = 255;
    _romb1[3].color = sf::Color(RGB_to_H(r, g, b), RGB_to_S(r, g, b), RGB_to_L(r, g, b), JAS);*/

    _romb2[0].position = p[3];
    _romb2[0].color = sf::Color(255,255,255, JAS);
    _romb2[1].position = p[4];
    _romb2[1].color = sf::Color(255,255,255, JAS);
    _romb2[2].position = p[5];
    _romb2[2].color = sf::Color(255,255,255, JAS);
    _romb2[3].position = center;
    _romb2[3].color = sf::Color(255,255,255, JAS);
}

static float Hue_2_RGB(float v1, float v2, float vH)             //Function Hue_2_RGB
{
    if (vH < 0) vH += 1;
    if (vH > 1) vH -= 1;
    if ((6.0f * vH) < 1) return (v1 + (v2 - v1) * 6.0f * vH);
    if ((2.0f * vH) < 1) return (v2);
    if ((3.0f * vH) < 2) return (v1 + (v2 - v1) * ((2.0f / 3.0f) - vH) * 6.0f);
    return (v1);
}

void hexagon_HSL::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Tu trzeba narysować sześciokąt HSL.
    Draw_Border(target, states, "HSL");
    //target.draw(_romb0, 4, sf::Quads);
    //target.draw(_romb01, 4, sf::Quads);
    target.draw(_romb2, 4, sf::Quads);
    float alfa, beta;
    sf::VertexArray point(sf::Points, 1);

    for (float j = p[0].y; j < center.y; ++j) {
        for (float i = p[1].x; i < p[5].x; ++i) {
            if (rhombus(p[0], p[1], { i,j }, alfa, beta)) {
                // L - beta
                // H - 1
                // S - alfa
                float R, G, B;
                if (alfa == 0) {
                    R = beta * 255; 
                    G = beta * 255;
                    B = beta * 255;
                }
                else {
                    float var_2, var_1;
                    if (beta < 0.5)
                        var_2 = beta * (1+alfa);
                    else
                        var_2 = (alfa+beta) - (alfa*beta);

                    var_1 = 2 * beta - var_2;

                    R = 255.0f * Hue_2_RGB(var_1, var_2, 1 + (1.0f / 3.0f));
                    G = 255.0f * Hue_2_RGB(var_1, var_2, 1);
                    B = 255.0f * Hue_2_RGB(var_1, var_2, 1 - (1.0f / 3.0f));
                }

                point[0].color = sf::Color(R, G, B, jasnosc * 255);
                point[0].position = sf::Vector2f(i, j);
                target.draw(point);
            }
        }
    }

    for (float j = p[1].y; j < p[3].y; ++j) {
        for (float i = p[1].x; i < center.x; ++i) {
            if (rhombus(p[2], p[3], { i,j }, alfa, beta)) {
                float var_2, var_1;
                if (alfa < 0.5) 
                    var_2 = alfa * (2);
                else         
                    var_2 = (alfa + 1) - (alfa);

                var_1 = 2 * alfa - var_2;

                float R = 255.0f * Hue_2_RGB(var_1, var_2, beta + (1.0f / 3.0f));
                float G = 255.0f * Hue_2_RGB(var_1, var_2, beta);
                float B = 255.0f * Hue_2_RGB(var_1, var_2, beta - (1.0f / 3.0f));
                
                point[0].color = sf::Color(R,G,B, jasnosc * 255);
                point[0].position = sf::Vector2f(i, j);
                target.draw(point);
            }
        }
    }

    //for (float j = p[1].y; j < p[3].y; ++j) {
    //    for (float i = p[1].x; i < center.x; ++i) {
    //        if (rhombus(p[2], p[3], { i,j }, alfa, beta)) {
    //            // S - beta
    //            // H - alfa
    //            // L - 1
    //            float R, G, B;
    //            if (beta == 0) {
    //                R = 255;
    //                G = 255;
    //                B = 255;
    //            }else{
    //                float var_2, var_1;
    //                var_2 = 1;

    //                var_1 = 1;

    //                R = 255.0f * Hue_2_RGB(var_1, var_2, alfa + (1.0f / 3.0f));
    //                G = 255.0f * Hue_2_RGB(var_1, var_2, alfa);
    //                B = 255.0f * Hue_2_RGB(var_1, var_2, alfa - (1.0f / 3.0f));
    //            }
    //            point[0].color = sf::Color(R, G, B, jasnosc * 255);
    //            point[0].position = sf::Vector2f(i, j);
    //            target.draw(point);
    //        }
    //    }
    //}
    
}

class hexagon_HSB : public hexagon
{
public:
    //hexagon_HSB(unsigned int pos, std::shared_ptr<sf::Font>(font), std::string title, sf::Vector2u draw_area_size, unsigned int suwak_width, float jas);
    hexagon_HSB(unsigned int pos, std::shared_ptr<sf::Font>(font), std::string title) : hexagon(pos, font, title), jasnosc{ 1 } {};
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update_data(sf::Vector2u draw_area_size, unsigned int suwak_width, float jas = 1) override;
    ~hexagon_HSB();
    
private:
    float jasnosc;
    //sf::Uint8* pixels;
    //mutable sf::RenderTexture texture;
    //sf::Sprite hex;
    
};
hexagon_HSB::~hexagon_HSB() {
    //delete [] pixels;
}

//hexagon_HSB::hexagon_HSB(unsigned int pos, std::shared_ptr<sf::Font>(font), std::string title, sf::Vector2u draw_area_size, unsigned int suwak_width, float jas) :
//    hexagon(pos, font, title), jasnosc{ 1 } 
//{
//    update_data(draw_area_size, suwak_width, jas);
//
//    pixels = new sf::Uint8[(right_bottom.x - left_top.x) * (right_bottom.y - left_top.y) * 4];
//    texture.create(right_bottom.x - left_top.x, right_bottom.y - left_top.y);
//}

void hexagon_HSB::update_data(sf::Vector2u draw_area_size, unsigned int suwak_width, float jas) {
    hexagon::update_data(draw_area_size, suwak_width);
    jasnosc = jas;

    //delete[] pixels;
    //pixels = new sf::Uint8[(right_bottom.x - left_top.x) * (right_bottom.y - left_top.y) * 4];
    //float alfa, beta;
    //sf::VertexArray point(sf::Points, 1);
    //float r, g, b;
    //texture.clear(sf::Color::Red);
    ////int idx_i = 0;
    ////int idx_j = 0;
    ////int idx = (p[0].y - left_top.y)*(p[1].x - left_top.x)*4;
    //for (int j = p[0].y; j < center.y; ++j) {
    //    for (int i = p[1].x; i < p[5].x; ++i) {
    //        /*pixels[idx] = 0;
    //        pixels[idx + 1] = 0;
    //        pixels[idx + 2] = 0;
    //        pixels[idx + 3] = 0;*/
    //        if (rhombus(p[0], p[1], { static_cast<float>(i),static_cast<float>(j) }, alfa, beta)) {
    //            //H - 1
    //            //S - alfa
    //            //B/V - beta
    //            float k = std::floor(6.0f);
    //            float f = 6.0f - k;
    //            float p = beta * (1.0f - alfa);
    //            float q = beta * (1.0f - f * alfa);
    //            float t = beta * (1.0f - (1.0f - f) * alfa);
    //            switch (static_cast<int>(k) % 6) {
    //            case 0: r = beta, g = t, b = p; break;
    //            case 1: r = q, g = beta, b = p; break;
    //            case 2: r = p, g = beta, b = t; break;
    //            case 3: r = p, g = q, b = beta; break;
    //            case 4: r = t, g = p, b = beta; break;
    //            case 5: r = beta, g = p, b = q; break;
    //            }
    //            r = std::round(r * 255.0f);
    //            g = std::round(g * 255.0f);
    //            b = std::round(b * 255.0f);
    //            point[0].color = sf::Color(r, g, b, jasnosc * 255);
    //            //point[0].position = sf::Vector2f(idx_i, idx_j);
    //            point[0].position = sf::Vector2f(i,j);
    //            texture.draw(point);
    //            /*pixels[idx] = r;
    //            pixels[idx + 1] = g;
    //            pixels[idx + 2] = b;
    //            pixels[idx + 3] = jas;*/
    //        }
    //        //++idx_i;
    //        //idx += 4;
    //    }
    //    //++idx_j;
    //}
    ////idx_i = p[1].x - left_top.x;
    ////idx_j = p[1].y - left_top.y;
    ////idx = (p[1].x - left_top.x) * (p[0].y - left_top.y) * 4;
    //for (int j = p[0].y; j < p[3].y; ++j) {
    //    for (int i = p[1].x; i < center.x; ++i) {
    //        /*pixels[idx] = 0;
    //        pixels[idx + 1] = 0;
    //        pixels[idx + 2] = 0;
    //        pixels[idx + 3] = 0;*/
    //        if (rhombus(p[2], p[3], { static_cast<float>(i),static_cast<float>(j) }, alfa, beta)) {
    //            //H - beta
    //            //S - 1
    //            //B/V - alfa
    //            float k = std::floor(beta * 6.0f);
    //            float f = beta * 6.0f - k;
    //            float p = 0;
    //            float q = alfa * (1.0f - f);
    //            float t = alfa * (1.0f - (1.0f - f));
    //            switch (static_cast<int>(k) % 6) {
    //            case 0: r = alfa, g = t, b = p; break;
    //            case 1: r = q, g = alfa, b = p; break;
    //            case 2: r = p, g = alfa, b = t; break;
    //            case 3: r = p, g = q, b = alfa; break;
    //            case 4: r = t, g = p, b = alfa; break;
    //            case 5: r = alfa, g = p, b = q; break;
    //            }
    //            r = std::round(r * 255.0f);
    //            g = std::round(g * 255.0f);
    //            b = std::round(b * 255.0f);
    //            point[0].color = sf::Color(r, g, b, jasnosc * 255);
    //            //point[0].position = sf::Vector2f(idx_i, idx_j);
    //            point[0].position = sf::Vector2f(i,j);
    //            texture.draw(point);
    //            /*pixels[idx] = r;
    //            pixels[idx + 1] = g;
    //            pixels[idx + 2] = b;
    //            pixels[idx + 3] = jas;*/
    //        }
    //        //++idx_i;
    //        //idx += 4;
    //    }
    //    //++idx_j;
    //}
    ////idx_i = center.x - left_top.x;
    ////idx_j = p[5].y - left_top.y;
    ////idx = (p[5].y - left_top.y) * (center.x - left_top.x)*4;
    //for (int i = center.x; i < p[5].x; ++i) {
    //    for (int j = p[5].y; j < p[3].y; ++j) {
    //        /*pixels[idx] = 0;
    //        pixels[idx + 1] = 0;
    //        pixels[idx + 2] = 0;
    //        pixels[idx + 3] = 0;*/
    //        if (rhombus(p[4], p[5], { static_cast<float>(i),static_cast<float>(j) }, alfa, beta)) {
    //            //H - alfa
    //            //S - beta
    //            //B/V = 1
    //            float k = std::floor(alfa * 6.0f);
    //            float f = alfa * 6.0f - k;
    //            float p = 1.0f - beta;
    //            float q = (1.0f - f * beta);
    //            float t = (1.0f - (1.0f - f) * beta);
    //            switch (static_cast<int>(k) % 6) {
    //            case 0: r = 1, g = t, b = p; break;
    //            case 1: r = q, g = 1, b = p; break;
    //            case 2: r = p, g = 1, b = t; break;
    //            case 3: r = p, g = q, b = 1; break;
    //            case 4: r = t, g = p, b = 1; break;
    //            case 5: r = 1, g = p, b = q; break;
    //            }
    //            r = std::round(r * 255);
    //            g = std::round(g * 255);
    //            b = std::round(b * 255);
    //            point[0].color = sf::Color(r, g, b, jasnosc * 255);
    //            //point[0].position = sf::Vector2f(idx_i, idx_j);
    //            point[0].position = sf::Vector2f(i,j);
    //            texture.draw(point);
    //            /*pixels[idx] = r;
    //            pixels[idx + 1] = g;
    //            pixels[idx + 2] = b;
    //            pixels[idx + 3] = jas;*/
    //        }
    //        //++idx_i;
    //        //idx += 4;
    //    }
    //    //++idx_j;
    //}
    //texture.display();
    //hex.setTexture(texture.getTexture());
    //hex.setPosition(left_top);
}

void hexagon_HSB::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Tu trzeba narysować sześciokąt HSB.
    Draw_Border(target, states, "HSB");

    //target.draw(hex);

    float alfa, beta;
    sf::VertexArray point(sf::Points, 1);
    float r, g, b;
    for (float j = p[0].y; j < center.y; ++j) {
        for (float i = p[1].x; i < p[5].x; ++i) {
            if (rhombus(p[0], p[1], { i,j }, alfa, beta)) {
                //H - 1
                //S - alfa
                //B/V - beta
                float k = std::floor(6.0f);
                float f = 6.0f - k;
                float p = beta*(1.0f - alfa);
                float q = beta * (1.0f - f*alfa);
                float t = beta * (1.0f - (1.0f - f)*alfa);
                switch (static_cast<int>(k) % 6) {
                case 0: r = beta, g = t, b = p; break;
                case 1: r = q, g = beta, b = p; break;
                case 2: r = p, g = beta, b = t; break;
                case 3: r = p, g = q, b = beta; break;
                case 4: r = t, g = p, b = beta; break;
                case 5: r = beta, g = p, b = q; break;
                }
                r = std::round(r * 255.0f);
                g = std::round(g * 255.0f);
                b = std::round(b * 255.0f);
                point[0].color = sf::Color(r, g, b, jasnosc * 255);
                point[0].position = sf::Vector2f(i, j);
                target.draw(point);
            }
        }
    }
    for (float j = p[0].y; j < p[3].y; ++j){
        for (float i = p[1].x; i < center.x; ++i) {
            if (rhombus(p[2], p[3], { i,j }, alfa, beta)) {
                //H - beta
                //S - 1
                //B/V - alfa
                float k = std::floor(beta * 6.0f);
                float f = beta * 6.0f - k;
                float p = 0;
                float q = alfa * (1.0f - f);
                float t = alfa * (1.0f - (1.0f - f));
                switch (static_cast<int>(k) % 6) {
                case 0: r = alfa, g = t, b = p; break;
                case 1: r = q, g = alfa, b = p; break;
                case 2: r = p, g = alfa, b = t; break;
                case 3: r = p, g = q, b = alfa; break;
                case 4: r = t, g = p, b = alfa; break;
                case 5: r = alfa, g = p, b = q; break;
                }
                r = std::round(r * 255.0f);
                g = std::round(g * 255.0f);
                b = std::round(b * 255.0f);
                point[0].color = sf::Color(r,g,b, jasnosc * 255);
                point[0].position = sf::Vector2f(i, j);
                target.draw(point);
            }
        }
    }
    for (float i = center.x; i < p[5].x; ++i) {
        for (float j = p[5].y; j < p[3].y; ++j) {
            if (rhombus(p[4], p[5], { i,j }, alfa, beta)) {
                //H - alfa
                //S - beta
                //B/V = 1
                float k = std::floor(alfa * 6.0f);
                float f = alfa * 6.0f - k;
                float p = 1.0f - beta;
                float q = (1.0f - f*beta);
                float t = (1.0f - (1.0f - f)*beta);
                switch (static_cast<int>(k) % 6) {
                case 0: r = 1, g = t, b = p; break;
                case 1: r = q, g = 1, b = p; break;
                case 2: r = p, g = 1, b = t; break;
                case 3: r = p, g = q, b = 1; break;
                case 4: r = t, g = p, b = 1; break;
                case 5: r = 1, g = p, b = q; break;
                }
                r = std::round(r * 255);
                g = std::round(g * 255);
                b = std::round(b * 255);
                point[0].color = sf::Color(r,g,b, jasnosc * 255);
                point[0].position = sf::Vector2f(i, j);
                target.draw(point);
            }
        }
    }
}

int main()
{   
 sf::RenderWindow window(sf::VideoMode(800, 600), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
 
 font = std::make_shared<sf::Font>();
 font->loadFromMemory(&(ShareTechMono_Regular_ttf[0]), ShareTechMono_Regular_ttf.size());
 suwak suwaczek;
 suwaczek.update_data(window.getSize());
 hexagon_RGB h_RGB(0, font, "RGB");
 hexagon_CMY h_CMY(1, font, "CMY");
 hexagon_HSL h_HSL(2, font, "HSL");
 hexagon_HSB h_HSB(3, font, "HSB");
 //hexagon_HSB h_HSB(3, font, "HSB", window.getSize(), suwaczek.getWidth(), suwaczek.getJasnosc());
 

 sf::Clock frame_clock, around_half_secound_clock;
 sf::Int64 mean_frames_time = 0;
 std::vector<sf::Int64> frame_times;
 sf::Text text;
 sf::RectangleShape zaslona;
 zaslona.setOutlineColor(sf::Color::White);
 zaslona.setOutlineThickness(1.0f);
 zaslona.setSize({ 100, 100 });
 zaslona.setPosition({0,0});

 text.setFont(*font);
 text.setCharacterSize(21);
 text.setFillColor(sf::Color::Black);

 //Nie mogę uniknąć tych "magic numbers" bo bym zdradził w ten sposób co ma być w sf::Event::Resize. A tego byśmy nie chcieli - prawda? :-D
 text.setPosition({ window.getSize().x - 100.0f, window.getSize().y - 50.0f });
 h_RGB.Set_Borders(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(300.0f,294.0f));
 h_CMY.Set_Borders(sf::Vector2f(300.0f, 0.0f), sf::Vector2f(600.0f, 294.0f));
 h_HSL.Set_Borders(sf::Vector2f(0.0f, 294.0f), sf::Vector2f(300.0f, 588.0f));
 h_HSB.Set_Borders(sf::Vector2f(300.0f, 294.0f), sf::Vector2f(600.0f, 588.0f));

 h_RGB.update_data(window.getSize(), suwaczek.getWidth());
 h_CMY.update_data(window.getSize(), suwaczek.getWidth());
 h_HSL.update_data(window.getSize(), suwaczek.getWidth());
 h_HSB.update_data(window.getSize(), suwaczek.getWidth());

 around_half_secound_clock.restart();

 while (window.isOpen())
 {
  sf::Event event;
  window.clear(sf::Color::White);

  frame_clock.restart(); // Start pomiaru czasu.

  while (window.pollEvent(event))
  {
      if (event.type == sf::Event::Closed) window.close();
      // Tu trzeba obsłużyć zdarzenia: zmianę rozmiaru okna oraz klikanie w „suwaczek”. 
      if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
          if (suwaczek.onSuwak(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
              suwaczek.setJasnosc(sf::Mouse::getPosition(window).y);
              suwaczek.update_linia_pos();

              h_RGB.update_data(window.getSize(), suwaczek.getWidth(), suwaczek.getJasnosc());
              h_CMY.update_data(window.getSize(), suwaczek.getWidth(), suwaczek.getJasnosc());
              h_HSL.update_data(window.getSize(), suwaczek.getWidth(), suwaczek.getJasnosc());
              h_HSB.update_data(window.getSize(), suwaczek.getWidth(), suwaczek.getJasnosc());
          }
          h_CMY.getColor(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
      }
      if (event.type == sf::Event::Resized) {
          if((window.getSize().x < 800) && (window.getSize().y < 600)){
              window.setSize({ 800, 600 });
          }
          else if (window.getSize().x < 800) {
              window.setSize({800, window.getSize().y});
          }
          else if (window.getSize().y < 600) {
              window.setSize({ window.getSize().x, 600 });
          }
          float width = static_cast<float>(event.size.width);
          float height = static_cast<float>(event.size.height);
          window.setView(sf::View(sf::FloatRect(0, 0, width, height)));

          suwaczek.update_data(window.getSize());
          text.setPosition({ window.getSize().x - 100.0f, window.getSize().y - 50.0f });

          h_RGB.update_data(window.getSize(), suwaczek.getWidth(), suwaczek.getJasnosc());
          h_CMY.update_data(window.getSize(), suwaczek.getWidth(), suwaczek.getJasnosc());
          h_HSL.update_data(window.getSize(), suwaczek.getWidth(), suwaczek.getJasnosc());
          h_HSB.update_data(window.getSize(), suwaczek.getWidth(), suwaczek.getJasnosc());;
      }
      
  }
  
  window.draw(h_RGB);
  window.draw(h_CMY);
  window.draw(h_HSL);
  window.draw(h_HSB);
  // Pewnie tu gdzieś wypadało by dorysować jeszcze suwaczek... 
  window.draw(suwaczek);
  text.setString(std::to_string(mean_frames_time)+ "us");
  window.draw(text);

  // Pomiar czasu uśrednimy w okresie około 1/2 sekundy.
  frame_times.push_back(frame_clock.getElapsedTime().asMicroseconds());
  if (around_half_secound_clock.getElapsedTime().asSeconds() >= 0.5f && frame_times.size() >=1)
  {
      mean_frames_time = (sf::Int64)((float)std::reduce(frame_times.begin(), frame_times.end()) / (float)frame_times.size());
      frame_times.clear();
      around_half_secound_clock.restart();
  }

  frame_clock.restart(); // Stop pomiaru czasu.
  window.display();
 }

 //Hmmm ... :-/
 font.reset();
 
 return 0;
}