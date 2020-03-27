#pragma once
#include <SFML/Graphics/Export.hpp>
#include "MyShape.hpp"
#include "MementoLogic.h"

class Rectangle : public MyShape
{
public:

	Rectangle();

	Rectangle(const sf::Vector2f&);

	Rectangle(sf::Vector2f sizev, sf::Vector2i posv, sf::Color c);

	Rectangle(float sx, float sy, float px, float py, sf::Color c);

	Rectangle(RectState);

	void setToDefault() override;

	void setSize(const Vector2f&);

	const Vector2f& getSize() const;

	virtual std::size_t getPointCount() const;

	virtual Vector2f getPoint(std::size_t) const;

	MyShape* clone() override;
	MyMemento GetMyMem();
private:
	Vector2f m_size;
};


class Circle : public MyShape
{
public:

	Circle(MyShape* Sh);

	Circle(const std::size_t);

	Circle(const float, const std::size_t);

	Circle(float radius, sf::Vector2f position, sf::Color c);

	Circle(float, float, float, float, sf::Color);

	Circle(char c, float a, float b);

	Circle(CircleState);

	void setToDefault() override;

	void setRadius(const float&);

	const float& getRadius() const;

	virtual std::size_t getPointCount() const;

	virtual sf::Vector2f getPoint(std::size_t) const;
	MyShape* clone() override;
	MyMemento GetMyMem();
private:
	float radius;
	std::size_t points = 100;
};

class Trajectory : public MyShape
{
public:
	Trajectory(sf::Vector2f position, sf::Color c);
	MyShape* clone() override;
	void setToDefault() override;
	virtual std::size_t getPointCount() const;
	virtual sf::Vector2f getPoint(std::size_t) const;
private:
	float radius = 5;
	std::size_t points = 100;
};