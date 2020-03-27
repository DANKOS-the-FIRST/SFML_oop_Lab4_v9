#include "MyShape.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Err.hpp>
#include <cmath>

void MyShape::setToDefault()
{
	setFillColor(sf::Color::Green);
	setPosition(100, 100);
	update();
}
sf::Vector2f computeNormal(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	sf::Vector2f normal(p1.y - p2.y, p2.x - p1.x);
	float length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
	if (length != 0.f)
		normal /= length;
	return normal;
}

float dotProduct(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return p1.x * p2.x + p1.y * p2.y;
}

using namespace sf;
MyShape::~MyShape()
{
}

MyShape::MyShape(float sx, float sy, float px, float py, sf::Color c)
{
	setScale(sx,sy);
	setPosition(px,py);
	setFillColor(c);
}

void MyShape::setTexture(const Texture* texture, bool resetRect)
{
	if (texture)
	{
		if (resetRect || (!m_texture && (m_textureRect == IntRect())))
			setTextureRect(IntRect(0, 0, texture->getSize().x, texture->getSize().y));
	}
	m_texture = texture;
}


const Texture* MyShape::getTexture() const
{
	return m_texture;
}


void MyShape::setTextureRect(const IntRect& rect)
{
	m_textureRect = rect;
	updateTexCoords();
}

const IntRect& MyShape::getTextureRect() const
{
	return m_textureRect;
}


void MyShape::setFillColor(const Color& color)
{
	m_fillColor = color;
	updateFillColors();
}

const Color& MyShape::getFillColor() const
{
	return m_fillColor;
}

void MyShape::setOutlineColor(const Color& color)
{
	m_outlineColor = color;
	updateOutlineColors();
}

const Color& MyShape::getOutlineColor() const
{
	return m_outlineColor;
}

void MyShape::setOutlineThickness(float thickness)
{
	m_outlineThickness = thickness;
	update();
}

float MyShape::getOutlineThickness() const
{
	return m_outlineThickness;
}

FloatRect MyShape::getLocalBounds() const
{
	return m_bounds;
}

FloatRect MyShape::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}


MyShape::MyShape() :
	m_texture(NULL),
	m_textureRect(),
	m_fillColor(255, 255, 255),
	m_outlineColor(255, 255, 255),
	m_outlineThickness(0),
	m_vertices(TriangleFan),
	m_outlineVertices(TriangleStrip),
	m_insideBounds(),
	m_bounds()
{
}

void MyShape::update()
{
	std::size_t count = getPointCount();
	if (count < 3)
	{
		m_vertices.resize(0);
		m_outlineVertices.resize(0);
		return;
	}

	m_vertices.resize(count + 2);

	for (std::size_t i = 0; i < count; ++i)
		m_vertices[i + 1].position = getPoint(i);
	m_vertices[count + 1].position = m_vertices[1].position;

	m_vertices[0] = m_vertices[1];
	m_insideBounds = m_vertices.getBounds();

	m_vertices[0].position.x = m_insideBounds.left + m_insideBounds.width / 2;
	m_vertices[0].position.y = m_insideBounds.top + m_insideBounds.height / 2;

	updateFillColors();

	updateTexCoords();

	updateOutline();
}


void MyShape::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = m_texture;
	target.draw(m_vertices, states);

	if (m_outlineThickness != 0)
	{
		states.texture = NULL;
		target.draw(m_outlineVertices, states);
	}
}


void MyShape::updateFillColors()
{
	for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i)
		m_vertices[i].color = m_fillColor;
}


void MyShape::updateTexCoords()
{
	for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i)
	{
		float xratio = m_insideBounds.width > 0 ? (m_vertices[i].position.x - m_insideBounds.left) / m_insideBounds.width : 0;
		float yratio = m_insideBounds.height > 0 ? (m_vertices[i].position.y - m_insideBounds.top) / m_insideBounds.height : 0;
		m_vertices[i].texCoords.x = m_textureRect.left + m_textureRect.width * xratio;
		m_vertices[i].texCoords.y = m_textureRect.top + m_textureRect.height * yratio;
	}
}


void MyShape::updateOutline()
{
	// Return if there is no outline
	if (m_outlineThickness == 0.f)
	{
		m_outlineVertices.clear();
		m_bounds = m_insideBounds;
		return;
	}

	std::size_t count = m_vertices.getVertexCount() - 2;
	m_outlineVertices.resize((count + 1) * 2);

	for (std::size_t i = 0; i < count; ++i)
	{
		std::size_t index = i + 1;

		// Get the two segments shared by the current point
		Vector2f p0 = (i == 0) ? m_vertices[count].position : m_vertices[index - 1].position;
		Vector2f p1 = m_vertices[index].position;
		Vector2f p2 = m_vertices[index + 1].position;

		// Compute their normal
		Vector2f n1 = computeNormal(p0, p1);
		Vector2f n2 = computeNormal(p1, p2);

		// Make sure that the normals point towards the outside of the shape
		// (this depends on the order in which the points were defined)
		if (dotProduct(n1, m_vertices[0].position - p1) > 0)
			n1 = -n1;
		if (dotProduct(n2, m_vertices[0].position - p1) > 0)
			n2 = -n2;

		// Combine them to get the extrusion direction
		float factor = 1.f + (n1.x * n2.x + n1.y * n2.y);
		Vector2f normal = (n1 + n2) / factor;

		// Update the outline points
		m_outlineVertices[i * 2 + 0].position = p1;
		m_outlineVertices[i * 2 + 1].position = p1 + normal * m_outlineThickness;
	}

	// Duplicate the first point at the end, to close the outline
	m_outlineVertices[count * 2 + 0].position = m_outlineVertices[0].position;
	m_outlineVertices[count * 2 + 1].position = m_outlineVertices[1].position;

	// Update outline colors
	updateOutlineColors();

	// Update the shape's bounds
	m_bounds = m_outlineVertices.getBounds();
}


////////////////////////////////////////////////////////////
void MyShape::updateOutlineColors()
{
	for (std::size_t i = 0; i < m_outlineVertices.getVertexCount(); ++i)
		m_outlineVertices[i].color = m_outlineColor;
}