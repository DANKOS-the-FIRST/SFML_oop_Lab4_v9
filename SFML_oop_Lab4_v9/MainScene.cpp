#include "MainScene.h"


bool MainScene::Editable1()
{
	return (chp[1] || chp[2]);
}
void MainScene::DrawComposite(Composite comp)
{
	//Draw all the elements from v_shapes
	for (auto& shape : comp.shapes) {
		if (dynamic_cast<Composite*>(shape)) {
			for (auto& composite_shape : *dynamic_cast<Composite*>(shape)->getShapes())
				this->draw(composite_shape);
		}
		else if (shape != nullptr)
		{
			this->draw(shape);
		}
		else {}
	}
}
bool MainScene::Drawable1()
{
	return (chp[3] || chp[4]);
}
void MainScene::DoFalse()
{
	for (size_t i = 0; i < sizeof(chp); i++)chp[i] = 0;
}
void MainScene::SetControl(int ch)
{
	if (ch >= 0 && ch < sizeof(chp))
	{
		DoFalse();
		chp[ch] = 1;
	}
}

static sf::Color colors[] =
{
	sf::Color::Red,
	sf::Color::Blue,
	sf::Color::Cyan,
	sf::Color::Green,
	sf::Color::Yellow
};
//struct Buff// buffer for obj1 and obj2
//{
//	std::vector<sf::Shape*> Objects;
//	bool rectWasFirst = false;
//	float fx;// smeschenie
//	float fy;// smeschenie
//};
void MainScene::ScaleShapes(std::vector<MyShape*>& shapes, bool inc)
{
	for (size_t i = 0; i < shapes.size(); i++)
		if (inc)(*shapes[i]).scale(1.01f, 1.01f);
		else (*shapes[i]).scale(0.99f, 0.99f);
}
void MainScene::RotateShapes(std::vector<MyShape>& shapes, bool right)
{
	for (size_t i = 0; i < shapes.size(); i++)
		if (right)shapes[i].rotate(1.0f);
		else shapes[i].rotate(-1.0f);
}
void MainScene::PositioningShapes(std::vector<MyShape*>& shapes, unsigned vec)//up-1_down-2_left-3_right-4
{
	if (vec > 4)return;
	float sx = (vec > 3) ? 1.0 : (vec == 3) ? -1.0 : 0.0;
	float sy = (vec < 2) ? -1.0 : (vec == 2) ? 1.0 : 0.0;
	//float winx = 0.0;
	//float winy = 0.0;
	float winx = this->window->getSize().x;
	float winy = this->window->getSize().y;
	float posx = 0.0;
	float posy = 0.0;
	for (size_t i = 0; i < shapes.size(); i++)
	{
		(*shapes[i]).setPosition(
			(*shapes[i]).getPosition().x + sx,
			(*shapes[i]).getPosition().y + sy
		);
		posx = (*shapes[i]).getPosition().x;
		posy = (*shapes[i]).getPosition().y;
		posx > winx ? (*shapes[i]).setPosition(posx - winx, posy) :
			posx < 0.0 ? (*shapes[i]).setPosition(posx + winx, posy) : void();
		posy > this->window->getSize().y ? (*shapes[i]).setPosition(posx, posy - this->window->getSize().y) :
			posy < 0.0 ? (*shapes[i]).setPosition(posx, posy + this->window->getSize().y) : void();
	}
}

void MainScene::ChangeColor1(MyShape& shape)
{
	for (size_t i = 0; i < sizeof(colors) / sizeof(sf::Color); i++)
		if (colors[i] == shape.getFillColor())
		{
			shape.setFillColor(
				(i + 1 >= (sizeof(colors) / sizeof(sf::Color))) ? colors[0] : colors[++i]);
			return;
		}
}
void MainScene::ChangeColor(std::vector<MyShape*>& shapes)
{
	for (size_t i = 0; i < shapes.size(); i++)
		ChangeColor1(*shapes[i]);
}
void MainScene::draw(MyShape* sh)
{
	this->window->draw(*sh);
}
sf::RenderWindow* MainScene::getWindow()
{
	return window;
}
void MainScene::controller()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:// �������� ����
			window->close();
			break;
		case sf::Event::MouseButtonPressed: // ������� ������� ����
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (chp[3])
				{
					if (!Path1.empty())Path1.clear();
					if (!coords1.empty())coords1.clear();
					coords1.push_back(sf::Mouse::getPosition(*window));
					Trajectory trc((sf::Vector2f)sf::Mouse::getPosition(*window), sf::Color::Magenta);// traectory circle
					//trc.setFillColor(sf::Color::Magenta);
					//trc.setPosition((sf::Vector2f)sf::Mouse::getPosition(*window));
					Path1.push_back(trc);
					record = true;
				}
				else if (chp[4])
				{
					if (!Path2.empty())Path2.clear();
					if (!coords2.empty())coords2.clear();
					coords2.push_back(sf::Mouse::getPosition(*window));
					Trajectory trc((sf::Vector2f)sf::Mouse::getPosition(*window), sf::Color::Cyan);// traectory circle
					/*trc.setFillColor(sf::Color::Magenta);
					trc.setPosition((sf::Vector2f)sf::Mouse::getPosition(*window));*/
					Path2.push_back(trc);
					record = true;
				}
				else if (chp[1])
				{
					//CurObjs1.clear();
					sf::Vector2f Mouse = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
					//for (size_t i = 0; i < objs1.Objects.size(); i++)
					//	if ((*objs1.Objects[i]).getGlobalBounds().contains(
					//		(sf::Vector2f)sf::Mouse::getPosition(window)))
					//		CurObjs1.push_back(objs1.Objects[i]);
					bool br = false;
					for (auto& sh : Scene1.GetAllShapes().shapes)
						if (sh->getGlobalBounds().contains(Mouse))
						{
							Scene1.AddShapeToActiveShapes(*sh);
							br = 1;
							break;
						}
					if (br)break;
					if (!br)Scene1.GetActiveShapes().shapes.clear();
				}
				else if (chp[2])
				{
					//CurObjs2.clear();
					sf::Vector2f Mouse = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
					//for (size_t i = 0; i < objs2.Objects.size(); i++)
					//	if ((*objs2.Objects[i]).getGlobalBounds().contains(
					//		(sf::Vector2f)sf::Mouse::getPosition(window)))
					//		CurObjs2.push_back(objs2.Objects[i]);
					bool br = false;
					for (auto& sh : Scene2.GetAllShapes().shapes)
						if (sh->getGlobalBounds().contains(Mouse))
						{
							Scene2.AddShapeToActiveShapes(*sh);
							br = 1;
							break;
						}
					if (br)break;
					if (!br)Scene2.GetActiveShapes().shapes.clear();
				}
			}
			break;
		case sf::Event::MouseMoved:
			if (record)
				if (chp[3])
				{
					coords1.push_back(sf::Mouse::getPosition(*window));
					Trajectory trc((sf::Vector2f)sf::Mouse::getPosition(*window), sf::Color::Magenta);// traectory circle
					trc.setFillColor(sf::Color::Magenta);
					trc.setPosition((sf::Vector2f)sf::Mouse::getPosition(*window));
					Path1.push_back(trc);
				}
				else if (chp[4])
				{
					coords2.push_back(sf::Mouse::getPosition(*window));
					Trajectory trc((sf::Vector2f)sf::Mouse::getPosition(*window), sf::Color::Cyan);// traectory circle
					trc.setFillColor(sf::Color::Cyan);
					trc.setPosition((sf::Vector2f)sf::Mouse::getPosition(*window));
					Path2.push_back(trc);
				}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left && Drawable1() && record)
			{
				record = false;
			}
			else if (event.mouseButton.button == sf::Mouse::Right && Editable1())
			{
				if (!SelectedShapes.empty())ChangeColor(SelectedShapes.shapes);
			}
			break;
		case sf::Event::MouseWheelScrolled:
			if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && Editable1())
			{
				if (!SelectedShapes.empty()) ScaleShapes(SelectedShapes.shapes, event.mouseWheelScroll.delta > 0 ? 1 : 0);
			}
			break;
		case sf::Event::KeyPressed:
			/*if (event.key.code == sf::Keyboard::R)// start repeating traectory
			{
				repeat = true;
				break;
			}*/
			if (event.key.code == sf::Keyboard::C && Editable1())// add circle to buffer
			{
				Circle circle(100.f);
				circle.setFillColor(Color::Green);
				circle.setPosition(float(sf::Mouse::getPosition(*window).x), float(sf::Mouse::getPosition(*window).y));
				if (chp[1])
				{
					Scene1.AddToAllShapes(circle);
				}
				else
				{
					Scene2.AddToAllShapes(circle);
				}
				//(chp[1]) ? circles1.push_back(circle) : circles2.push_back(circle);
				//(chp[1]) ? objs1.Objects.push_back(&circles1[circles1.size() - 1]) :
				//	objs2.Objects.push_back(&circles2[circles2.size() - 1]);
				break;
			}
			if (event.key.code == sf::Keyboard::Q && Editable1())// add quadrat to buffer
			{
				Rectangle rectangle(sf::Vector2f(300, 100), sf::Mouse::getPosition(*window), Color::Blue);
				//rectangle.setSize(Vector2f(300, 100), Color::Blue);
				//rectangle.setOutlineColor(Color::Red);
				//rectangle.setFillColor(Color::Blue);
				//rectangle.setOutlineThickness(5);
				//rectangle.setPosition(float(sf::Mouse::getPosition(*window).x), float(sf::Mouse::getPosition(*window).y));
				if (chp[1])
				{
					Scene1.AddToAllShapes(rectangle);
				}
				else
				{
					Scene2.AddToAllShapes(rectangle);
				}
				//(chp[1]) ? rects1.push_back(rectangle) : rects2.push_back(rectangle);
				//(chp[1]) ? objs1.Objects.push_back(&rects1[rects1.size()-1]) : objs2.Objects.push_back(&rects1[rects1.size() - 1]);
				break;
			}
			if (event.key.code == sf::Keyboard::Numpad0)// select chapter 0 (animation)
			{
				if ((!Scene1.GetActiveShapes().empty()) && (!Scene2.GetActiveShapes().empty()))
					SetControl(0);
				Scene1.GetActiveShapes().shapes.clear();
				Scene2.GetActiveShapes().shapes.clear();
				ANIME = true;
				break;
			}
			if (event.key.code == sf::Keyboard::Numpad1)// select chapter 1 (drawing first obj)
			{
				SetControl(1);
				break;
			}
			if (event.key.code == sf::Keyboard::Numpad2)// select chapter 2 (drawing second obj)
			{
				SetControl(2);
				break;
			}
			if (event.key.code == sf::Keyboard::Numpad3)// select chapter 3 (drawing obj1 traectory)
			{
				SetControl(3);
				break;
			}
			if (event.key.code == sf::Keyboard::Numpad4)// select chapter 4 (drawing obj2 traectory)
			{
				SetControl(4);
				break;
			}
			if (event.key.code == sf::Keyboard::Up)// move current selection  up
			{
				(Editable1()) ? 
					(chp[1]) ? Scene1.GetActiveShapes().MoveUp() :
					Scene2.GetActiveShapes().MoveUp() : void();
				break;
			}
			if (event.key.code == sf::Keyboard::Down)// move current selection down
			{
				(Editable1()) ? (chp[1]) ? Scene1.GetActiveShapes().MoveDown() : Scene2.GetActiveShapes().MoveDown() : void();
				break;
			}
			if (event.key.code == sf::Keyboard::Left)// move current selection left
			{
				(Editable1()) ? (chp[1]) ? Scene1.GetActiveShapes().MoveLeft() : Scene2.GetActiveShapes().MoveLeft() : void();
				break;
			}
			if (event.key.code == sf::Keyboard::Right)// move current selection right
			{
				(Editable1()) ? (chp[1]) ? Scene1.GetActiveShapes().MoveRight() : Scene2.GetActiveShapes().MoveRight() : void();
				break;
			}
			if (event.key.code == sf::Keyboard::D && Editable1())//clear buffer
			{
				if (chp[1]) { Scene1.ClearActive(); Scene1.ClearAllShapes(); }
				else if (chp[2]) { Scene2.ClearActive(); Scene2.ClearAllShapes(); }
				break;
			}
			break;
		default:// no another events
			break;
		}
	}
	if (chp[1])
	{
		//			for (size_t i = 0; i < objs1.Objects.size(); i++)
		//				window->draw(*objs1.Objects[i]);
		window->clear();
		//for (size_t i = 0; i < circles1.size(); i++)
		//	window->draw(circles1[i]);
		//for (size_t i = 0; i < rects1.size(); i++)
		//	window->draw(rects1[i]);
		if (!Scene1.GetAllShapes().empty())
			Scene1.GetAllShapes().drawAllShapes();

		/*for (auto& sh : CurObjs1.shapes)
			window->draw(*sh);*/
	}
	else if (chp[2])
	{
		//			for (size_t i = 0; i < objs2.Objects.size(); i++)
		//				window->draw(*objs2.Objects[i]);
		window->clear();
		/*for (size_t i = 0; i < circles2.size(); i++)
			window->draw(circles2[i]);
		for (size_t i = 0; i < rects2.size(); i++)
			window->draw(rects2[i]);*/
		if (!Scene2.GetAllShapes().empty())
			Scene2.GetAllShapes().drawAllShapes();
			//DrawComposite(CurObjs2);
		/*for (auto& sh : CurObjs2.shapes)
			window->draw(*sh);*/
	}
	else if (chp[3])
	{
		window->clear();
		for (size_t i = 0; i < Path1.size(); i++)
			window->draw(Path1[i]);
	}
	else if (chp[4])
	{
		window->clear();
		for (size_t i = 0; i < Path2.size(); i++)
			window->draw(Path2[i]);
	}
	else if (chp[0] && ANIME)
	{
		window->clear();
		//Animation(circles1, circles2, rects1, rects2, &window,
		//	coords1, coords2, objs1.rectWasFirst, objs2.rectWasFirst);
		int i(0), j(0);
		float sx1,
			sy1,
			sx2,
			sy2;
		bool end = false;
		j = 0;

		//sf::Vector2f startcoords1 = Objects1[0]->getPosition();
		//sf::Vector2f startcoords2 = Objects2[0]->getPosition();
		while (true)
		{
			if (j < coords1.size() && j < coords2.size())break;
			if (j < coords1.size())
			{
				sx1 = coords1[j].x - Scene1.GetAllShapes().shapes[0]->getPosition().x;
				sy1 = coords1[j].y - Scene1.GetAllShapes().shapes[0]->getPosition().y;
				Scene1.GetAllShapes().move(sf::Vector2f(sx1, sy1));
			}
			if (j < coords2.size())
			{
				sx2 = coords2[j].x - Scene2.GetAllShapes().shapes[0]->getPosition().x;
				sy2 = coords2[j].y - Scene2.GetAllShapes().shapes[0]->getPosition().y;
				Scene2.GetAllShapes().move(sf::Vector2f(sx2, sy2));
			}
			//std::cout << "Was displayed\n";
			bool b = false;
			int ch;
			/*std::cin >> ch;*/
			if (Scene1.GetAllShapes().IntersectsWith(&Scene2.GetAllShapes()))
			{
				Scene1.GetAllShapes().ScaleShapes(0.5f, 0.5f);
				Scene2.GetAllShapes().ScaleShapes(0.5f, 0.5f);
				b = 1;
				//return;
			}// INTERSECTION
			window->clear();
			if (!Scene1.GetAllShapes().empty())
				Scene1.GetAllShapes().drawAllShapes();
			if (!Scene2.GetAllShapes().empty())
				Scene2.GetAllShapes().drawAllShapes();
			window->display();
			if (b)
			{
				std::cout << "INTERSECTED!!!\n";
				//std::cout << "Enter any number to continue  \n";
				//std::cin >> ch;
			}
			j++;
			if (j >= coords1.size() && j >= coords2.size())
			{
				std::cout << "Animation was done !!! \n";
				end = true;
			}
			if (end)break;
		}
		ANIME = false;
	}
	if (!chp[0])window->display();
}