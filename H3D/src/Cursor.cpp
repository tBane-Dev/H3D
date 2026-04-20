#include "Cursor.hpp"

Cursor::Cursor() {

	_position = sf::Mouse::getPosition(*window);
}

Cursor::~Cursor() {

}

void Cursor::update() {
	_position = sf::Mouse::getPosition(*window);
}

void Cursor::handleEvent() {

	
}

void Cursor::draw() {

}

std::shared_ptr<Cursor> cursor;