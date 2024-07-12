#include "suwak.h"

#define WIDTH 100.0f
#define PADDING 50.0f
#define LINE_HEIGHT 5

unsigned int suwak::getWidth() const { return _size.x + 2 * _padding; }

suwak::suwak() : _size{ WIDTH, 0 }, _padding{ PADDING }, _position{ 0,0 }, _jasnosc{1.0f}
{
	_prostokat.setOutlineColor(sf::Color::Black);
	_prostokat.setOutlineThickness(1.0f);
	_linia.setFillColor(sf::Color::Red);
	_linia.setSize({ _size.x, LINE_HEIGHT });

	_background[0] = sf::Vertex(sf::Vector2f(_position.x, _position.y), sf::Color::Black);
	_background[1] = sf::Vertex(sf::Vector2f(_position.x + _size.x, _position.y), sf::Color::Black);
	_background[2] = sf::Vertex(sf::Vector2f(_position.x, _position.y + _size.y), sf::Color::White);
	_background[3] = sf::Vertex(sf::Vector2f(_position.x + _size.y, _position.y + _size.y), sf::Color::White);
}

void suwak::update_data(sf::Vector2u draw_area_size) {
	_size = { _size.x , (draw_area_size.y - 150.0f) - (_padding*2.0f) };
	_position = { (draw_area_size.x - _padding) - _size.x, _padding };
	_prostokat.setPosition(_position);
	_prostokat.setSize(_size);
	
	_linia.setPosition({_position.x, _position.y + (_size.y * _jasnosc)});

	_background[0] = sf::Vertex(sf::Vector2f(_position.x, _position.y), sf::Color::Black);
	_background[1] = sf::Vertex(sf::Vector2f(_position.x + _size.x, _position.y), sf::Color::Black);
	_background[2] = sf::Vertex(sf::Vector2f(_position.x + _size.x, _position.y + _size.y), sf::Color::White);
	_background[3] = sf::Vertex(sf::Vector2f(_position.x, _position.y + _size.y), sf::Color::White);
}
void suwak::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_prostokat);
	target.draw(_background, 4, sf::Quads);
	target.draw(_linia);
}

bool suwak::onSuwak(int mx, int my) const{
	if ((mx >= _position.x) && (mx <= (_position.x + _size.x))) 
		if ((my >= _position.y) && (my <= (_position.y + _size.y)))
			return true;
	return false;
}

void suwak::update_linia_pos() {
	_linia.setPosition({ _position.x, _position.y + (_size.y * _jasnosc) });
}