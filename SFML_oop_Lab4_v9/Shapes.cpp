#include "Shapes.hpp"

Rectangle::Rectangle()
{
	setToDefault();
}

Rectangle::Rectangle(const sf::Vector2f& sz)
{
	setSize(sz);
	update();
}

Rectangle::Rectangle(float sx, float sy, float px, float py, sf::Color c)
{
	setScale(sx, sy);
	setPosition(px, py);
	setFillColor(c);
}

Rectangle::Rectangle(sf::Vector2f sizev, sf::Vector2i posv, sf::Color c)
{
	setSize(sizev);
	setPosition(sf::Vector2f(posv));
	setFillColor(c);
	update();
}
Rectangle::Rectangle(RectState _Mem)
{
	setSize(_Mem.GetSize());
	setPosition(_Mem.GetPosition());
	setFillColor(_Mem.GetColor());
	update();
}
MyShape* Rectangle::clone() 
{
	return new Rectangle(*this);
}

void Rectangle::setToDefault()
{
	setSize(sf::Vector2f(100, 100));
	setFillColor(sf::Color::Green);
	setPosition(200, 200);
	setOrigin(100 / 2, 100 / 2);
	update();
}

void Rectangle::setSize(const Vector2f& size)
{
	m_size = size;
	update();
}


const Vector2f& Rectangle::getSize() const
{
	return m_size;
}


std::size_t Rectangle::getPointCount() const
{
	return 4;
}


Vector2f Rectangle::getPoint(std::size_t index) const
{
	switch (index)
	{
	default:
	case 0: return Vector2f(0, 0);
	case 1: return Vector2f(m_size.x, 0);
	case 2: return Vector2f(m_size.x, m_size.y);
	case 3: return Vector2f(0, m_size.y);
	}
}

//Circle

Circle::Circle(const std::size_t pts = 100)
{
	radius = pts;
	setToDefault();
	update();
}
Circle::Circle(const float rds, const std::size_t pts = 100)
{
	radius = rds;
	points = pts;
	update();
}

Circle::Circle(float sx, float sy, float px, float py, sf::Color c)
{
	setScale(sx, sy);
	setPosition(px, py);
	setFillColor(c);
	update();
}

Circle::Circle(float radius, sf::Vector2f position, sf::Color c)
{
	setRadius(radius);
	setPosition(position);
	setFillColor(c);
	update();
}

Circle::Circle(CircleState _Mem)
{
	setRadius(_Mem.GetRadius());
	setPosition(_Mem.GetPosition());
	setFillColor(_Mem.GetColor());
	update();
}
void Circle::setToDefault()
{
	setRadius(100.0f);
	setFillColor(sf::Color::Red);
	setPosition(500, 500);
	setOrigin(100, 100);
	update();
}

void Circle::setRadius(const float& rds)
{
	radius = rds;
	update();
}

const float& Circle::getRadius() const
{
	return radius;
}

std::size_t Circle::getPointCount() const
{
	return points;
}

sf::Vector2f Circle::getPoint(std::size_t index) const
{
	static const float pi = 3.141592654f;

	float angle = index * 2 * pi / getPointCount() - pi / 2;
	float x = std::cos(angle) * radius;
	float y = std::sin(angle) * radius;

	return { radius + x, radius + y };
}

MyShape* Circle::clone()
{
	return new Circle(*this);
}

Trajectory::Trajectory(sf::Vector2f position, sf::Color c)
{
	setPosition(position);
	setFillColor(c);
	update();
}

MyShape* Trajectory::clone()
{
	return new Trajectory(*this);
}

sf::Vector2f Trajectory::getPoint(std::size_t index) const
{
	static const float pi = 3.141592654f;

	float angle = index * 2 * pi / getPointCount() - pi / 2;
	float x = std::cos(angle) * radius;
	float y = std::sin(angle) * radius;

	return { radius + x, radius + y };
}
void Trajectory::setToDefault()
{
	radius = 5;
	setFillColor(sf::Color::Red);
	setPosition(500, 500);
	setOrigin(100, 100);
	update();
}
std::size_t Trajectory::getPointCount() const
{
	return 100;
}