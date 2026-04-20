#pragma once
#include "Window.hpp"
#include "Element.hpp"


class Cursor {
public:
	sf::Vector2i _position;
	
	Cursor();
	~Cursor();

	void update();
	void handleEvent();
	void draw();
};

extern std::shared_ptr<Cursor> cursor;