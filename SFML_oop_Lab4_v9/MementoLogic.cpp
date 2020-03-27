#include "MementoLogic.h"
#include "Shapes.hpp"
#include <fstream>

//#include "States.h"
BasicState* MyMemento::GetState(MyShape* _ShapeTo)
{
	Circle* c = dynamic_cast<Circle*>(_ShapeTo);
	if (c != nullptr)return &CircleState(c->getPosition(), c->getFillColor(), c->getRadius());
	Rectangle* r = dynamic_cast<Rectangle*>(_ShapeTo);
	if (r != nullptr)return &RectState(r->getPosition(), r->getFillColor(), r->getSize());
}
BasicState* MyMemento::GetState()
{
	return this->State;
}
void MyMemento::SetState(MyShape* _ShapeTo)
{
	this->State = GetState(_ShapeTo);
}

MyMemento::MyMemento(BasicState* _StateTo)
{
	this->State = _StateTo;
}
MyMemento::MyMemento()
{
	this->State = nullptr;
}
std::string Caretaker::StateToString(BasicState& _state)
{
	CircleState* c = dynamic_cast<CircleState*>(&_state);
	if (c != nullptr)return ;
	RectState* r = dynamic_cast<RectState*>(&_state);
	if (r != nullptr)return ;
}
std::string MyMemento::ToString()
{
	CircleState* c = dynamic_cast<CircleState*>(State);
	if (c != nullptr)return c->ToString();
	RectState* r = dynamic_cast<RectState*>(State);
	if (r != nullptr)return r->ToString();
}
void Caretaker::SetMyMems(std::vector<MyMemento*>& _MyMems)
{
	this->MyMems = &_MyMems;
}
std::vector<MyMemento*>* Caretaker::GetMyMems()
{
	return this->MyMems;
}
void Caretaker::SaveToTxtFile(std::string _file)
{
	std::ofstream outf(_file + ".txt");
	for (auto& m : *(this->MyMems))
		outf << m->ToString() << std::endl;
	outf.close();
}
MyMemento Caretaker::StringToMemento(std::string _str)
{
	int red, green, blue;
	float posx, posy, w, h, r;
	std::string T;
	std::stringstream X(_str);
	getline(X, T, ' ');
	if (T == "Circle")
	{
		X >> posx >> posy >> red >> green >> blue >> r;
		return MyMemento(new CircleState(sf::Vector2f(posx, posy), sf::Color(red, green, blue), r));
	}
	if (T == "Rectangle")
	{
		X >> posx >> posy >> red >> green >> blue >> w >> h;
		return MyMemento(new RectState(sf::Vector2f(posx, posy), sf::Color(red, green, blue), sf::Vector2f(w, h)));
	}
}
std::vector<MyMemento*>& Caretaker::GetMementoFromTxt(std::string _file)
{
	std::vector<MyMemento*> res;
	std::string stmp;
	int red, green, blue;
	float posx, posy, w, h, r;
	std::ifstream inf(_file + ".txt");
	while (!inf.eof())
	{
		std::getline(inf, stmp);
		res.push_back(&this->StringToMemento(stmp));
	}
	inf.close();
	return res;
}
void Caretaker::RestoreMementoFromTxt(std::string _FileName)
{
	this->MyMems = &GetMementoFromTxt(_FileName);
}
void Caretaker::SetMemsFromShapes(std::vector<MyShape*>* _Shapes)
{
	std::vector<MyMemento*> ret;
	for (auto &_ShapeTo : *_Shapes)
	{
		Circle* c = dynamic_cast<Circle*>(_ShapeTo);
		if (c != nullptr)ret.push_back(&c->GetMyMem());
		Rectangle* r = dynamic_cast<Rectangle*>(_ShapeTo);
		if (r != nullptr)ret.push_back(&r->GetMyMem());
	}
	this->MyMems = &ret;
}
std::vector<MyShape*> Caretaker::GetShapesFromFile(std::string _fname)
{
	std::vector<MyShape*> ret;
	this->RestoreMementoFromTxt(_fname);
	for (auto& mem : *MyMems)
	{
		CircleState* c = dynamic_cast<CircleState*>(mem->GetState());
		if (c != nullptr)ret.push_back(new Circle(*c));
		RectState* r = dynamic_cast<RectState*>(mem->GetState());
		if (r != nullptr)ret.push_back(new Rectangle(*r));
	}
	return ret;
}