

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <map>

class Shape
{
public:
	virtual void draw() = 0;
};

class Circle : public Shape
{
private:
	std::string color;
	int x;
	int y;
	int radius;

public:
	Circle(std::string color) { this->color = color; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	void setRadius(int radius) { this->radius = radius; }
	
	void draw() {
		std::cout << "Circle(" << this << "): draw() [Color:" << 
			color << ", x:" << x << ", y:" << y << ", radius:" << 
			radius << std::endl;
	}
};

class ShapeFactory
{
private:
	static std::map<std::string, Shape*> circleMap;
public:
	static Shape* getCircle(std::string color)
	{
		Circle* circle = dynamic_cast<Circle*>(circleMap[color]);
		if (circle == nullptr) {
			circle = new Circle(color);
			circleMap[color] = circle;
			std::cout << "Creating circle of color : " << color << std::endl;
		}
		return circle;
	}
	~ShapeFactory() {
		for (std::map<std::string, Shape*>::iterator it = circleMap.begin(); it != circleMap.end(); it++)
		{
			std::cout << "=============================" << std::endl;
			if (it->second != nullptr)
				delete it->second;
			it->second = nullptr;
		}
		circleMap.clear();
		std::cout << "over ----------------------------- over" << std::endl;
	}
};

std::map<std::string, Shape*> ShapeFactory::circleMap = std::map<std::string, Shape*>();


static std::string colors[] = { "Red", "Green", "Blue", "White", "Black" };

int main()
{
	srand(time(NULL));
	int i;
	for (i = 0; i < 20; i++) {
		Circle* circle = 
			dynamic_cast<Circle*>(ShapeFactory::getCircle(colors[rand() % (sizeof(colors) / sizeof(*colors))]));
		circle->setX(rand() % 100);
		circle->setY(rand() % 100);
		circle->setRadius(100);
		circle->draw();
	}	
	
	return 0;
}