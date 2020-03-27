#pragma once
#include <vector>;
#include <map>;
#include "MyShape.hpp";
#include "Shapes.hpp";
#include "Composite.h"


class FigureController
{
private:
	/*std::vector<MyShape*> AllShapes;
	std::vector<MyMemento*> AllShapesMemento;
	std::vector<MyShape*> ActiveShapes;
	std::vector<MyMemento*> ActiveShapesMemento;*/
	Composite AllShapes;//All shapes of current scene
	Composite ActiveShapes;//Choosen shapes of current scene

public:
	void AddShapeToActiveShapes(MyShape&);
	void AddToAllShapes(MyShape&);

	void AddMyShapeTo(Circle&, std::vector<MyShape*>&);
	void AddMyShapeTo(Rectangle&, std::vector<MyShape*>&);

	void AddShapeToVector(MyShape&, std::vector<MyShape*>&);

	void DeleteShapeFromActiveShapes(MyShape&);
	void DeleteShapeFromAllShapes(MyShape&);

	void ClearAllShapes();
	void ClearActive();

	Composite GetAllShapes();
	Composite GetActiveShapes();

};