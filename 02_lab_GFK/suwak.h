#pragma once
#include "SFML/Graphics.hpp"

class suwak : public sf::Drawable
{
public:
	suwak();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update_data(sf::Vector2u draw_area_size);
	unsigned int getWidth() const;
	bool onSuwak(int mx, int my) const;
	void setJasnosc(int my) { 
		_jasnosc = ((my - _position.y) / _size.y); 
	}
	float getJasnosc() const { return _jasnosc; }
	void update_linia_pos();
private:
	float _padding;
	sf::Vector2f _size, _position;
	sf::RectangleShape _prostokat;
	sf::RectangleShape _linia;
	sf::Vertex _background[4];
	float _jasnosc;	// 0 - 100%
};
