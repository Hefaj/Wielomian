#pragma once

#include <vector>
#include<string>
#include <iostream>
#include <cassert>

class Wielomian
{
private:
	std::vector<float> params;

public:

	// zablokowanie operatorow
	Wielomian  operator/(const Wielomian&) = delete;
	Wielomian& operator/=(const Wielomian&) = delete;

	const int size(); // zwraca stopien wielomianu

	// konstruktory
	Wielomian(std::vector<float>&);
	Wielomian(const Wielomian&);
	Wielomian(float[], int);
	Wielomian(std::string);

	// przeciazenie <<
	friend std::ostream& operator<<(std::ostream& s, Wielomian w);

	// przeciazenie operatory matematyczne
	Wielomian  operator+(const Wielomian&);
	Wielomian  operator-(const Wielomian&);
	Wielomian  operator*(const Wielomian&);

	Wielomian  operator*(const float);
	Wielomian  operator/(const float);

	bool operator==(const Wielomian&);

	Wielomian& operator+=(const Wielomian&);
	Wielomian& operator-=(const Wielomian&);
	Wielomian& operator*=(const Wielomian&);

	Wielomian& operator*=(const float);
	Wielomian& operator/=(const float);

	// przypisanie 
	Wielomian& operator=(const Wielomian&);

	// get, set
	float operator[](size_t)const;
	float& operator[](size_t);

	~Wielomian();
};
