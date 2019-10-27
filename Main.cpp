// Wielomian.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.

#include "pch.h"
#include <iostream>
#include <time.h>

#include "Wielomian.h"

using namespace std;

std::vector<float> RandVektor(size_t size = 3, int min = -5, int max = 5)
{
	std::vector<float> v;
	int absMM = std::abs(min) + std::abs(max);


	for (size_t i = 0; i < size; i++)
	{
		float n = std::rand() % (absMM * 10) / 10.0f - max;
		if (!v.size() && !n)
			i--;
		else v.push_back(n);
	}
	std::cout << std::endl;
	for (auto v_ : v)
	{
		std::cout << v_ << " ";
	}
	std::cout << std::endl;
	return v;
}

int main()
{
	std::vector<float> v1, v2;
	std::srand((unsigned int)time(NULL));

	v1 = RandVektor(2);
	v2 = RandVektor(2);

	// tworzenie wielomianow z wektorow
	Wielomian w1(v1);
	Wielomian w2(v2);

	// tworzenie wielomianow z tablicy
	float tab[] = { 1.0f,-5.0f,-0.4f,1.0f };
	Wielomian w3(tab, 4);

	// tworzenie wielomianow z wielomianow
	Wielomian w4(w1);

	// przeciazenie <<
	std::cout << "\nw1:\n" << w1 << "\nw2:\n" << w2 << "\nw3:\n" << w3 << "\nw4:\n" << w4 << std::endl;

	// przeciazenie operatorow matematycznych
	std::cout << "\nw1 == w4?:\n" << (w1 == w4) << std::endl;
	std::cout << "\nw1+w2:\n" << w1 + w2 << std::endl;
	std::cout << "\nw1-w2:\n" << w1 - w2 << std::endl;

	w1 += w2;
	std::cout << "\nw1+=w2:\n" << w1 << std::endl;
	std::cout << "\nw4:\n" << w4 << std::endl;
	std::cout << "\nw4/2:\n" << w4 / 2 << std::endl;

	std::cout << "\nw4 len:\n" << w4.size() << std::endl;

	w4[0] = 4.5f;
	std::cout << "\nw4[0]=4.5 len:\nw4[0]=" << w4[0] << std::endl;

	// tworzenie wielomianow z stringa

	Wielomian w5("+7,5+3x^6-2.2x^{14}-1.2x^3-12,4x");
	std::cout << "w5:" << w5 << std::endl;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie