//Uwaga! Co najmniej C++17!!!
//Project-> ... Properties->Configuration Properties->General->C++ Language Standard = ISO C++ 17 Standard (/std:c++17)

#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>

#define getIDX(idx) (static_cast<int>(idx))

enum class Field { VOID, FLOOR, WALL, BOX, PARK, PLAYER, FIELD_NUMBERS};

class Sokoban : public sf::Drawable
{
public:
	Sokoban();
	void LoadMapFromFile(std::string fileName);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void SetDrawParameters(sf::Vector2u draw_area_size);
	void Move_Player_Left();
	void Move_Player_Right();
	void Move_Player_Up();
	void Move_Player_Down();
	bool Is_Victory() const;

	void updateTime();
	void showVictory(const sf::Vector2u& draw_area_size);
	mutable bool gameWon;
private:
	std::vector<std::vector<Field>> map;
	// shift - przesunięcie planszy względem górnego lewego rogu, aby była na środku
	// tile_size - wielkość rysowanych kwadradów
	sf::Vector2f shift, tile_size;
	sf::Vector2i player_position;
	std::vector<sf::Vector2i> park_positions;

	// Rysunki konkretnych pól. Można zastąpić teksturami
	mutable sf::RectangleShape drawings[static_cast<unsigned int>(Field::FIELD_NUMBERS)];

	// Czas gry
	const unsigned int TILES_FOR_TEXT = 1;
	sf::Clock _clock;
	sf::Time _elapsed;
	sf::Font _font;
	sf::Text _czas_gry;
	sf::Text _wygrana_text;

	void move_player(int dx, int dy);
};
Sokoban::Sokoban() {
	for (int i = 0; i < static_cast<int>(Field::FIELD_NUMBERS); ++i) {
		drawings[i].setOutlineColor(sf::Color::Black);
		drawings[i].setOutlineThickness(1.0f);
	}
	drawings[getIDX(Field::VOID)].setFillColor(sf::Color(128, 128, 128));
	drawings[getIDX(Field::FLOOR)].setFillColor(sf::Color(150, 75, 0));
	drawings[getIDX(Field::WALL)].setFillColor(sf::Color(102, 51, 0));
	drawings[getIDX(Field::BOX)].setFillColor(sf::Color(204, 204, 0));
	drawings[getIDX(Field::PARK)].setFillColor(sf::Color(0, 0, 200));
	drawings[getIDX(Field::PLAYER)].setFillColor(sf::Color(0, 200, 0));

	_font.loadFromFile("garota_bonita.ttf");
	_czas_gry.setFont(_font);
	_czas_gry.setFillColor(sf::Color::Red);
	_czas_gry.setPosition(0, 0);
	_czas_gry.setString("0");
	_wygrana_text.setFont(_font);
	_wygrana_text.setFillColor(sf::Color::Red);
	_wygrana_text.setString("W");
	gameWon = false;
}

void Sokoban::LoadMapFromFile(std::string fileName)
{
	std::string str;
	std::vector<std::string> vos;

	std::ifstream in(fileName.c_str());
	while (std::getline(in, str)) { vos.push_back(str); }
	in.close();

	map.clear();
	map.resize(vos.size(), std::vector<Field>(vos[0].size()));
	for (auto [row, row_end, y] = std::tuple{ vos.cbegin(), vos.cend(), 0 }; row != row_end; ++row, ++y)
		for (auto [element, end, x] = std::tuple{ row->begin(), row->end(), 0 }; element != end; ++element, ++x)
			switch (*element)
			{
			case 'X': map[y][x] = Field::WALL; break;
			case '*': map[y][x] = Field::VOID; break;
			case ' ': map[y][x] = Field::FLOOR; break;
			case 'B': map[y][x] = Field::BOX; break;
			case 'P': map[y][x] = Field::PARK; park_positions.push_back(sf::Vector2i(x, y));  break;
			case 'S': map[y][x] = Field::PLAYER; player_position = sf::Vector2i(x, y);  break;
			}
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Tu niewątpliwie powinno coś być : -) Tu należy narysować wszystko. O tak jakoś :
	//target.draw(....);

	//Przydatna może być pętla :
	target.clear();
	for (int y = 0; y < map.size(); ++y)
		for (int x = 0; x < map[y].size(); ++x)
		{
			sf::Vector2f drawing_position = { x * tile_size.x, y * tile_size.y };
			drawing_position += shift;

			//Teraz map[y][x] mówi nam CO mamy narysować.
			drawings[getIDX(map[y][x])].setPosition(drawing_position);
			target.draw(drawings[getIDX(map[y][x])]);
		}
	
	target.draw(_czas_gry);
	if (gameWon) {
		drawings[getIDX(Field::VOID)].setPosition({ 0, (target.getSize().y / 2) - (_wygrana_text.getLocalBounds().height / 2)});
		sf::Vector2f temp_size = drawings[getIDX(Field::VOID)].getSize();
		drawings[getIDX(Field::VOID)].setSize( {static_cast<float>(target.getSize().x), _wygrana_text.getLocalBounds().height});
		target.draw(drawings[getIDX(Field::VOID)]);
		target.draw(_wygrana_text);
		drawings[getIDX(Field::VOID)].setSize(temp_size);
	}
}


void Sokoban::SetDrawParameters(sf::Vector2u draw_area_size)
{
	_czas_gry.setCharacterSize((draw_area_size.y / map.size()) * TILES_FOR_TEXT);
	
	this->tile_size = sf::Vector2f(
		std::min(std::floor((float)draw_area_size.x / (float)map[0].size()), std::floor((float)draw_area_size.y / (float)map.size())),
		std::min((std::floor((float)draw_area_size.x - _czas_gry.getLocalBounds().height) / (float)(map[0].size())), (std::floor((float)draw_area_size.y - _czas_gry.getLocalBounds().height) / (float)map.size()))
	);
	this->shift = sf::Vector2f(
		((float)draw_area_size.x - this->tile_size.x * map[0].size()) / 2.0f,
		(((float)draw_area_size.y + _czas_gry.getLocalBounds().height) - this->tile_size.y * (map.size())) / 2.0f
	);

	// Zmiana rozmiaru rysunków
	for (int i = 0; i < getIDX(Field::FIELD_NUMBERS); ++i) {
		drawings[i].setSize(sf::Vector2f(tile_size));
	}

	_czas_gry.setCharacterSize(_czas_gry.getLocalBounds().height);
	_wygrana_text.setCharacterSize(_czas_gry.getLocalBounds().height);
	_wygrana_text.setPosition((draw_area_size.x / 2) - (_wygrana_text.getLocalBounds().width / 2), (draw_area_size.y / 2) - (_wygrana_text.getLocalBounds().height / 2));
}

void Sokoban::Move_Player_Left()
{
	move_player(-1, 0);
}

void Sokoban::Move_Player_Right()
{
	move_player(1, 0);
}

void Sokoban::Move_Player_Up()
{
	move_player(0, -1);
}

void Sokoban::Move_Player_Down()
{
	move_player(0, 1);
}

void Sokoban::move_player(int dx, int dy)
{
	bool allow_move = false; // Pesymistyczne załóżmy, że gracz nie może się poruszyć.
	sf::Vector2i new_pp(player_position.x + dx, player_position.y + dy); //Potencjalna nowa pozycja gracza.
	Field fts = map[new_pp.y][new_pp.x]; //Element na miejscu na które gracz zamierza przejść.


	//Gracz może się poruszyć jeśli pole na którym ma stanąć to podłoga lub miejsce na skrzynki.
	if (fts == Field::FLOOR || fts == Field::PARK) allow_move = true;
	//Jeśli pole na które chce się poruszyć gracz zawiera skrzynkę to może się on poruszyć jedynie 
	//jeśli kolejne pole jest puste lub zawiera miejsce na skrzynkę  - bo wtedy może przepchnąć skrzynkę.
	if (fts == Field::BOX) {
		//Element na miejscu ZA miejscem na które gracz zamierza przejść. :-D
		Field ftsa = map[new_pp.y + dy][new_pp.x + dx];
		if (ftsa == Field::FLOOR || ftsa == Field::PARK)
		{
			allow_move = true;
			//Przepychamy skrzynkę.
			map[new_pp.y + dy][new_pp.x + dx] = Field::BOX;
			//Oczywiście pole na którym stała skrzynka staje się teraz podłogą.
			map[new_pp.y][new_pp.x] = Field::FLOOR;
		}
	}
	if (allow_move)
	{
		//Przesuwamy gracza.
		map[player_position.y][player_position.x] = Field::FLOOR;
		player_position = new_pp;
		map[player_position.y][player_position.x] = Field::PLAYER;
	}

	//Niestety w czasie ruchu mogły „ucierpieć” miejsca na skrzynkę. ;-(
	//Po przesunięciu skrzynki, powstaje FLOOR dlatego trzeba, dla każdego PARK sprawdzić 
	// czy nie został przypadkiem zmieniony na FLOOR
	for (auto park_position : park_positions)
		if (map[park_position.y][park_position.x] == Field::FLOOR)
			map[park_position.y][park_position.x] = Field::PARK;
}

bool Sokoban::Is_Victory() const
{
	//Tym razem dla odmiany optymistycznie zakładamy, że gracz wygrał.
	//No ale jeśli na którymkolwiek miejscu na skrzynki nie ma skrzynki to chyba założenie było zbyt optymistyczne... : -/
	for (auto park_position : park_positions) if (map[park_position.y][park_position.x] != Field::BOX) return false;
	gameWon = true;
	return true;
}

void Sokoban::updateTime() {
	_elapsed = _clock.getElapsedTime();
	_czas_gry.setString(std::to_string(static_cast<unsigned int>(_elapsed.asSeconds())));
}

void Sokoban::showVictory(const sf::Vector2u& draw_area_size) {
	_wygrana_text.setString("Wygrales w czasie " + _czas_gry.getString().toAnsiString() + " sekundy!");
	_wygrana_text.setPosition((draw_area_size.x / 2) - (_wygrana_text.getLocalBounds().width / 2), (draw_area_size.y / 2) - (_wygrana_text.getLocalBounds().height / 2));
}
int main()
{
	sf::RenderWindow window(
		sf::VideoMode(800, 600),
		"GFK Lab 01",
		sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	Sokoban sokoban;

	sokoban.LoadMapFromFile("plansza.txt");
	sokoban.SetDrawParameters(window.getSize());
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
			{
				float width = static_cast<float>(event.size.width);
				float height = static_cast<float>(event.size.height);
				window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
				sokoban.SetDrawParameters(window.getSize());
			}
			//Oczywiście tu powinny zostać jakoś obsłużone inne zdarzenia.
			//Na przykład jak gracz naciśnie klawisz w lewo powinno pojawić się wywołanie metody :
			//sokoban.Move_Player_Left();
			//W dowolnym momencie mogą Państwo sprawdzić czy gracz wygrał:
			//sokoban.Is_Victory();
			if ((event.type == sf::Event::Closed) || (event.key.code == sf::Keyboard::Escape)) window.close();
			if (event.type == sf::Event::KeyPressed && !sokoban.gameWon) {
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					sokoban.Move_Player_Up();
					break;
				case sf::Keyboard::Right:
					sokoban.Move_Player_Right();
					break;
				case sf::Keyboard::Down:
					sokoban.Move_Player_Down();
					break;
				case sf::Keyboard::Left:
					sokoban.Move_Player_Left();
					break;
				default:
					break;
				}
				if (sokoban.Is_Victory()) {
					sokoban.showVictory(window.getSize());
				}
			}
		}
		if (!sokoban.gameWon) {
			sokoban.updateTime();
		}
		window.draw(sokoban);
		window.display();
	}

	return 0;
}