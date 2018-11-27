#include "Event.h"

#include <iostream>

void DemoFunction(int, float)
{
	std::cout << "DemoFunction\n";
}

int main()
{
	Event<int, float> DemoEvent;
	auto Handle1 = DemoEvent += [](int, float) { std::cout << "Demo Lambda 1\n"; };
	auto Handle2 = DemoEvent += [](int, float) { std::cout << "Demo Lambda 2\n"; };
	auto Handle3 = DemoEvent += &DemoFunction;

	DemoEvent -= Handle2;

	int InputA = 5;
	float InputB = 2.1f;

	DemoEvent(InputA, InputB);
	DemoEvent(3, 3.7f);

	system("pause");

	return 0;
}
