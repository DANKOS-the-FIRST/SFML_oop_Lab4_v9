#pragma once
#include <SFML/Graphics.hpp>
#include "Shapes.hpp"
#include "Composite.h"
#include "Singleton.h"
struct Buff// buffer for obj1 and obj2
{
	std::vector<MyShape*> Objects;
	float fx;// smeschenie
	float fy;// smeschenie
};
class MainScene
{
private:
	FigureController Scene1;
	FigureController Scene2;
	std::vector<Trajectory> Path1;
	std::vector<Trajectory> Path2;
public:
	//Control
	bool chp[5]; // chapters

	bool Editable1();
	bool Drawable1();
	void DoFalse();
	void SetControl(int ch);
	//From main
	void ScaleShapes(std::vector<MyShape*>& shapes, bool inc);
	void RotateShapes(std::vector<MyShape>& shapes, bool right);
	void PositioningShapes(std::vector<MyShape*>& shapes, unsigned vec);//up-1_down-2_left-3_right-4
	static void ChangeColor1(MyShape& shape);
	static void ChangeColor(std::vector<MyShape*>& shapes);
	//MainScene
private:
	sf::RenderWindow* window;

	//From main
	//Buff objs1;
	//Buff objs2;

	//std::vector<sf::Shape*> CurObjs1;// current objects1 (selection)
	//std::vector<sf::Shape*> CurObjs2;// current objects2 (selection)
	Composite SelectedShapes;
	std::vector<sf::Vector2i> coords1;
	std::vector<sf::Vector2i> coords2;
	bool record = false;
	bool repeat = false;
	bool ANIME = false;
	bool drawingTraectory = false;
	//	std::vector<RectangleShape>
public:
	void draw(MyShape*);
	sf::RenderWindow* getWindow();
	void controller();
	void DrawComposite(Composite comp);
};