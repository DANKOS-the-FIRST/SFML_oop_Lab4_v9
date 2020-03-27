#pragma once
#include "States.h"
#include "MyShape.hpp"
#include <string>
#include <vector>
class MyMemento
{
private:
	BasicState* State;
public:
	BasicState* GetState(MyShape*);
	BasicState* GetState();
	void SetState(MyShape*);
	MyMemento(BasicState*);
	MyMemento();
	std::string ToString();
};
class Caretaker
{
private:
	std::vector<MyMemento*>* MyMems;
public:
	void SetMemsFromShapes(std::vector<MyShape*>*);
	std::vector<MyShape*> GetShapesFromFile(std::string);
	std::vector<MyMemento*>* GetMyMems();
	std::string StateToString(BasicState&);
	void SetMyMems(std::vector<MyMemento*>&);
	void SaveToTxtFile(std::string);
	std::vector<MyMemento*>& GetMementoFromTxt(std::string);
	MyMemento StringToMemento(std::string);
	void RestoreMementoFromTxt(std::string);
};