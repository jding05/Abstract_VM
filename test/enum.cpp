#include <iostream>

class Car
{
public:
    struct Color
    {
        enum Type
        {
            Red,
            Blue,
            Black
        };
    };

    Color::Type getColor() { return color; }
    void setColor(Color::Type type) {color = type; }

	Color::Type	color;
};

int main()
{
	Car car;

	car.setColor(Car::Color::Red);
	std::cout << car.getColor() << std::endl;

//	car.color = car.getColor() + 1 ;
//	car.setColor(1);
	std::cout << car.getColor() << std::endl;
}	
