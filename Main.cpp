#include "pch.h"
#include <iostream>

#include "Wielomian.h"

int main()
{
	float t1[] = { -3, -4 };
	float t2[] = { -3, -2 };
	float t3[] = { 1, 2, 3 };

	Wielomian <float> w1(t1, 2);
	std::cout << "w1: " << w1 << std::endl;


	Wielomian<float> w2(t2, 2);
	std::cout << "w2: " << w2 << std::endl;

	Wielomian<int> w3(3);
	std::cout << "w3: " << w3 << std::endl;

	Wielomian<float> w4(w1);
	std::cout << "w4: " << w4 << std::endl;

	Wielomian<float> w5("-2,5x^4-4x^{3}-5");
	std::cout << "w5: " << w5 << std::endl;

	std::vector<float> v;
	v.push_back(4);
	v.push_back(0);
	v.push_back(7);
	v.push_back(3);

	Wielomian<float> w6(v);
	std::cout << "w6: " << w6 / 2 << std::endl;

	Wielomian <float> w7(t3, 3);
	std::cout << std::endl;
	std::cout << "w1: " << w1 << std::endl;
	std::cout << "w2: " << w2 << std::endl;
}
