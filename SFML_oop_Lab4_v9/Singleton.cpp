#include "Singleton.h"
void FigureController::AddMyShapeTo(Circle& _c, std::vector<MyShape*>& _vec)
{
	_vec.push_back(&_c);
}
void FigureController::AddMyShapeTo(Rectangle& _r, std::vector<MyShape*>& _vec)
{
	_vec.push_back(&_r);
}
void FigureController::AddShapeToVector(MyShape& _MSh, std::vector<MyShape*>& _vec)
{
	Circle* c = dynamic_cast<Circle*>(&_MSh);
	if (c != nullptr)return AddMyShapeTo(*c, _vec);
	Rectangle* r = dynamic_cast<Rectangle*>(&_MSh);
	if (r != nullptr)return AddMyShapeTo(*r, _vec);
}
void FigureController::AddShapeToActiveShapes(MyShape& _MSh)
{
	AddShapeToVector(_MSh, this->ActiveShapes.shapes);
}
void FigureController::AddToAllShapes(MyShape& _MSh)
{
	AddShapeToVector(_MSh, this->AllShapes.shapes);
}
void FigureController::DeleteShapeFromActiveShapes(MyShape& _MSh)
{
	for (auto it = this->ActiveShapes.shapes.begin(); it != this->ActiveShapes.shapes.end(); ++it)
		if (*it == &_MSh)
			return (void)this->ActiveShapes.shapes.erase(it);
}
void FigureController::DeleteShapeFromAllShapes(MyShape& _MSh)
{
	for (auto it = this->AllShapes.shapes.begin(); it != this->AllShapes.shapes.end(); ++it)
		if (*it == &_MSh)
			return (void)this->AllShapes.shapes.erase(it);
}
void FigureController::ClearAllShapes()
{
	this->AllShapes.shapes.clear();
}
void FigureController::ClearActive()
{
	this->ActiveShapes.shapes.clear();
}
Composite FigureController::GetAllShapes()
{
	return this->AllShapes;
}
Composite FigureController::GetActiveShapes()
{
	return this->ActiveShapes;
}