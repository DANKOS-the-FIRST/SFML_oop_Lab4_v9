#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>
#include <sstream>
class BasicState
{
public:
	BasicState()
	{
		this->Position = sf::Vector2f();
		this->Color = sf::Color();
	}
	BasicState(sf::Vector2f _Position, sf::Color _Color)
	{
		this->Position = _Position;
		this->Color = _Color;
	}
	sf::Vector2f GetPosition()
	{
		return this->Position;
	}
	sf::Color GetColor()
	{
		return this->Color;
	}
	virtual std::string ToString();
protected:
	sf::Vector2f Position;
	sf::Color Color;
};

class RectState : public BasicState
{
public:
	RectState(sf::Vector2f _Position, sf::Color _Color, sf::Vector2f _Size)
	{
		this->Position = _Position;
		this->Color = _Color;
		this->Size = _Size;
	}
	std::string ToString()
	{
		std::stringstream ss;
		ss << "Rectangle" << " " << this->Position.x << " " << this->Position.y << " "
			<< this->Color.r << " " << this->Color.g << " " << this->Color.b << " " <<
			this->Size.x << " " << this->Size.y;
		return ss.str();
	}
	sf::Vector2f GetSize()
	{
		return this->Size;
	}
private:
	sf::Vector2f Size;
};

class CircleState : public BasicState
{
public:
	CircleState(sf::Vector2f _Position, sf::Color _Color, float _Radius)
	{
		this->Position = _Position;
		this->Color = _Color;
		this->Radius = _Radius;
	}
	std::string ToString()
	{
		std::stringstream ss;
		ss << "Circle" << " " << this->Position.x << " " << this->Position.y << " "
			<< this->Color.r << " " << this->Color.g << " " << this->Color.b << " " <<
			this->Radius;
		return ss.str();
	}
	float GetRadius()
	{
		return this->Radius;
	}
private:
	float Radius;
};