#include "Composite.h"
#include <fstream>
#include <string>

Composite::Composite()
{
	update();
}

void Composite::MoveRight()
{
	for (auto& sh : this->shapes)
		sh->move(sf::Vector2f(1.0, 0.0));
}

void Composite::MoveDown()
{
	for (auto& sh : this->shapes)
		sh->move(sf::Vector2f(0.0, -1.0));
}

void Composite::MoveLeft()
{
	for (auto& sh : this->shapes)
		sh->move(sf::Vector2f(-1.0, 0.0));
}

void Composite::MoveUp()
{
	for (auto& sh : this->shapes)
		sh->move(sf::Vector2f(0.0, 1.0));
}

Composite::Composite(MyShape* shape)
{
	addShape(shape);
	update();
}

void Composite::ScaleShapes(float a, float b)
{
	for (auto& sh : shapes)
		sh->scale(a, b);
}

bool Composite::IntersectsWith(Composite comp2)
{
	for (auto& sh1 : shapes)
		for (auto& sh2 : comp2.shapes)
			if (sh1->getGlobalBounds().intersects(sh2->getGlobalBounds()))return true;
	return false;
}

bool Composite::empty()
{
	return shapes.empty();
}



void Composite::addShape(MyShape* shape)
{
	shapes.push_back(shape);
}

Composite::Composite(Composite& container)
{
	for (auto& shape : container.shapes)
	{
		if(shape!=nullptr && &container !=nullptr)
		container.addShape
		(shape->clone()
		);
	}
}
void Composite::setFillColor(const sf::Color& color)
{
	for (auto& shape : shapes)
		if (shape != nullptr)
			shape->setFillColor(color);
}

void Composite::move(const sf::Vector2f& offset)
{
	for (auto& shape : shapes)
		shape->move(offset);
}

std::size_t Composite::getPointCount() const
{
	for (auto& shape : shapes)
		return shape->getPointCount();
	return 0;
}
sf::Vector2f Composite::getPoint(std::size_t index) const
{
	for (auto& shape : shapes)
		return shape->getPoint(index);
}

void Composite::setMemento(Memento& memento) const
{
	memento.shots.clear();
	for (auto& elem : shapes)
	{
		memento.shots.push_back(elem->clone());
	}
}

std::vector<MyShape*>* Composite::getShapes()
{
	return &shapes;
}

Composite* Composite::clone()
{
	return new Composite(*this);
}

void Composite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& shape : shapes)
		target.draw(*shape);
}
void Composite::drawAllShapes(sf::RenderTarget& target)
{
	sf::RenderStates states = sf::RenderStates();
	this->draw(target, states);
}