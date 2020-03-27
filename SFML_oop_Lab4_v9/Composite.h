#pragma once
#include "Shapes.hpp"
#include "Memento.h"
#include <SFML/Graphics.hpp>

void moving(MyShape*, RenderWindow*);
class Composite : public MyShape
{
public:

	Composite();

	Composite(MyShape*);

	Composite(Composite&);

	void addShape(MyShape*);

	void setFillColor(const sf::Color&);

	void move(const sf::Vector2f&);

	virtual std::size_t getPointCount() const;

	virtual sf::Vector2f getPoint(std::size_t) const;

	void setMemento(Memento&) const;

	std::vector<MyShape*>* getShapes();

	Composite* clone();

	bool empty();

	void setToDefault() override {};

	bool IntersectsWith(Composite);

	void ScaleShapes(float a, float b);
	void drawAllShapes(sf::RenderTarget& target);

	void MoveUp();
	void MoveRight();
	void MoveLeft();
	void MoveDown();

	std::vector<MyShape*> shapes;
private:
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

};