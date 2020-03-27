#pragma once
#include "MementoLogic.h"
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

using namespace sf;

class  MyShape : public Drawable, public Transformable
{
public:
	virtual ~MyShape();	
	virtual MyShape* clone() = 0;
	virtual void setToDefault();

	void setTexture(const Texture*, bool resetRect = false);

	void setTextureRect(const IntRect&);

	void setFillColor(const Color&);

	void setOutlineColor(const Color&);

	void setOutlineThickness(float);

	const Texture* getTexture() const;

	const IntRect& getTextureRect() const;

	const Color& getFillColor() const;

	const Color& getOutlineColor() const;

	float getOutlineThickness() const;

	virtual std::size_t getPointCount() const = 0;

	virtual Vector2f getPoint(std::size_t) const = 0;

	FloatRect getLocalBounds() const;

	FloatRect getGlobalBounds() const;

protected:
	MyShape();
	MyShape(float, float, float, float, sf::Color);
	void update();
	
private:

	virtual void draw(RenderTarget&, RenderStates) const;

	void updateFillColors();

	void updateTexCoords();

	void updateOutline();

	void updateOutlineColors();

private:

	const Texture* m_texture;
	IntRect        m_textureRect;
	Color          m_fillColor;
	Color          m_outlineColor;
	float          m_outlineThickness;
	VertexArray    m_vertices;
	VertexArray    m_outlineVertices;
	FloatRect      m_insideBounds;
	FloatRect      m_bounds;
};