#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

// https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl

template <typename T>
class Wielomian
{
	size_t size;
	T *tab;

public:
	
	// przeciazenie <<
	friend std::ostream& operator<<(std::ostream &s, const Wielomian<T> w)
	{
		auto *v = w.tab + w.size - 1;

		for (size_t pow = w.size; pow > 0; v--, pow--)
			if (*v)
			{
				std::cout << ((*v > 0 && pow != w.size) ? "+" : "");
				if (*v != 1 && *v != -1) std::cout << *v;
				else if (*v == -1) std::cout << "-";
				else if (pow == 1) std::cout << *v;
				std::string s = (pow != 2) ? "x^{" + std::to_string(pow - 1) + "}" : "x";
				std::cout << ((pow != 1) ? s : "");
			}
		return s;
	}
	
	// zablokowanie operatorow
	Wielomian<T>  operator/(const Wielomian&) = delete;
	Wielomian<T>& operator/=(const Wielomian&) = delete;
	
	T GetNumber(std::string);
	
	// konstruktory
	Wielomian(std::vector<T>&);
	Wielomian<T>(const Wielomian&);
	Wielomian(T[], size_t);
	Wielomian<T>(std::string);
	Wielomian<T>(size_t);
	
	// przeciazenie operatory matematyczne
	Wielomian<T>  operator+(const Wielomian<T>&);
	Wielomian<T>  operator-(const Wielomian<T>&);
	Wielomian<T>  operator*(const Wielomian<T>&);

	Wielomian<T>  operator*(const T);
	Wielomian<T>  operator/(const T);

	bool operator==(const Wielomian&);

	Wielomian<T>& operator+=(const Wielomian<T>&);
	Wielomian<T>& operator-=(const Wielomian<T>&);
	Wielomian<T>& operator*=(const Wielomian<T>&);

	Wielomian<T>& operator*=(const T);
	Wielomian<T>& operator/=(const T);

	// przypisanie 
	Wielomian<T>& operator=(const Wielomian<T>&);

	// get, set
	T operator[](size_t)const;
	T& operator[](size_t);

	~Wielomian();
	
};

template<typename T>
inline T Wielomian<T>::GetNumber(std::string v)
{
	if (!v.length()) return 1;
	if (v.length() == 1 && v[0] == '-')
		v.append("1");
	return std::stof(v);

}

template<typename T>
inline Wielomian<T>::Wielomian(const Wielomian &w)
{
	this->tab = new T[w.size];
	this->size = w.size;

	auto *t = this->tab,
		*f = w.tab,
		*l = f + w.size;

	for (; f != l; *t++ = *f++);
}

template<typename T>
inline Wielomian<T>::Wielomian(std::string str)
{
	std::vector<T> v;
	std::vector<std::string> strV;
	std::vector<T> MonomialW;
	std::vector<int> MonomialP;
	std::string c_str = "";
	int MAX_POW = 0;

	// zamiana , na .
	do
	{
		auto p = str.find(',');
		if (p != std::string::npos) str[p] = '.';
		else break;
	} while (true);

	// usuwanie zbednych znakow
	for (size_t i = 0; i < str.length(); i++)
		if (str[i] != ' ') c_str += str[i];

	// spawdzanie czy jest cokolwiek
	if (!c_str.length())
	{
		this->size = 1;
		this->tab = new T[1];
		this->tab[0] = 0;
		//MonomialW.push_back(0);
		//this->params = MonomialW;
	}
	else
	{
		// dzielenie po znakach i chowanie w vectory
		for (size_t i = 0; i < c_str.length(); i++)
			if ((c_str[i] == '+' || c_str[i] == '-') && i)
			{
				strV.push_back(c_str.substr(0, i));
				c_str.erase(0, i);
				i = 0;
			}
		strV.push_back(c_str);

		// wyciaganie wspolczynnikow
		for (auto v : strV)
		{
			size_t e = v.find("^");
			if (e != std::string::npos)
			{
				MonomialW.push_back(GetNumber(v.substr(0, e - 1)));
				if (v[e + 1] != '{')
					MonomialP.push_back((int)v[e + 1] - 48);
				else
				{
					size_t e_ = v.find("}");
					std::string v_ = v.substr(e + 2, e_ - e - 2);
					MonomialP.push_back(std::stoi(v_));
				}
			}
			else
			{
				size_t a = v.find("x");

				if (a != std::string::npos)
				{
					MonomialW.push_back(GetNumber(v.substr(0, a)));
					MonomialP.push_back(1);
				}
				else
				{
					MonomialW.push_back(GetNumber(v));
					MonomialP.push_back(0);
				}
			}
		}

		// wyciaganie najwyzeszej potegi
		for (auto v : MonomialP)
			MAX_POW = (v > MAX_POW) ? v : MAX_POW;

		// inicjowanie wektora
		for (int i = 0; i <= MAX_POW; i++)
			v.push_back(0);

		// wypelnianie vektora
		size_t zip = 0;

		for (auto v_ : MonomialP)
			v[MAX_POW - v_] = MonomialW[zip++];

		//this->params = v;

		// przepianie vektora do tablicy
		this->size = v.size();
		this->tab = new T[v.size()];

		for (size_t i = 0; i < v.size(); i++)
			this->tab[(this->size - 1) - i] = v[i];
	}
}

template<typename T>
inline Wielomian<T>::Wielomian(std::vector<T> &v)
{
	this->size = v.size();
	this->tab = new T[v.size()];

	auto *f = this->tab,
		*l = this->tab + v.size();

	for (size_t i = 0; f != l; *f++ = v[i++]);
}

template<typename T>
Wielomian<T>::Wielomian(T t[], size_t s)
{
	this->tab = new T[s];
	this->size = s;

	auto *f = this->tab + s,
		*l = this->tab,
		*n = t;

	for (; f-- != l; *f = *n++);
}

template<typename T>
inline Wielomian<T>::Wielomian(size_t s)
{
	this->size = s;
	this->tab = new T[s];

	auto *t = this->tab,
		*l = t + s;

	for (; t != l; *t++ = 0);
}

template<typename T>
inline Wielomian<T> Wielomian<T>::operator+(const Wielomian<T> &w)
{
	if (this->size > w.size)
	{
		Wielomian w_(*this);

		auto *f = w.tab,
			*l = w.tab + w.size,
			*n = w_.tab;

		for (; f != l; *n++ += *f++);
		return w_;
	}
	else
	{
		Wielomian w_(w);

		auto *f = this->tab,
			*l = this->tab + this->size,
			*n = w_.tab;

		for (; f != l; *n++ += *f++);
		return w_;
	}
}

template<typename T>
inline Wielomian<T> Wielomian<T>::operator-(const Wielomian<T> &w)
{
	if (this->size > w.size)
	{
		Wielomian w_(*this);

		auto *f = w.tab,
			*l = w.tab + w.size,
			*n = w_.tab;

		for (; f != l; *n++ -= *f++);
		return w_;
	}
	else
	{
		Wielomian w_(w);

		auto *f = this->tab,
			*l = this->tab + this->size,
			*n = w_.tab;

		for (; f != l; *n++ -= *f++);
		return w_;
	}
}

template<typename T>
inline Wielomian<T> Wielomian<T>::operator*(const Wielomian<T> &w)
{
	Wielomian<T> w_(this->size + w.size - 1);

	for (size_t i = 0; i < this->size; i++)
		for (size_t j = 0; j < w.size; j++)
			w_.tab[i + j] += this->tab[i] * w.tab[j];
	return w_;
}

template<typename T>
inline Wielomian<T>& Wielomian<T>::operator+=(const Wielomian<T> &w)
{
	if (this->size >= w.size)
	{
		auto *f = w.tab,
			*l = w.tab + w.size,
			*n = this->tab;

		for (; f != l; *n++ += *f++);
	}
	else
	{
		auto *t = this->tab,
			*lt = this->tab + this->size;

		this->tab = new T[w.size];
		this->size = w.size;

		auto *f = this->tab,
			*l = this->tab + this->size,
			*n = w.tab;

		for (; f != l; *f++ = *n++);

		f = this->tab;

		for (; t != lt; *f++ += *t++);
	}
	return *this;
}

template<typename T>
inline Wielomian<T>& Wielomian<T>::operator-=(const Wielomian<T> &w)
{
	if (this->size >= w.size)
	{
		auto *f = w.tab,
			*l = w.tab + w.size,
			*n = this->tab;

		for (; f != l; *n++ -= *f++);
	}
	else
	{
		auto *t = this->tab,
			*lt = this->tab + this->size;

		this->tab = new T[w.size];
		this->size = w.size;

		auto *f = this->tab,
			*l = this->tab + this->size,
			*n = w.tab;

		for (; f != l; *f++ = -*n++);

		f = this->tab;

		for (; t != lt; *f++ += *t++);
	}
	return *this;
}

template<typename T>
inline Wielomian<T>& Wielomian<T>::operator*=(const Wielomian<T> &w)
{
	T *t = this->tab;
	size_t s = this->size;

	this->tab = new T[s + w.size - 1];
	this->size = s + w.size - 1;

	auto *f = this->tab, *l = this->tab + this->size;

	for (; f != l; *f++ = 0);

	for (size_t i = 0; i < s; i++)
		for (size_t j = 0; j < w.size; j++)
			this->tab[i + j] += t[i] * w.tab[j];
	return *this;
}

template<typename T>
inline Wielomian<T>& Wielomian<T>::operator*=(const T s)
{
	auto *f = this->tab,
		*l = this->tab + this->size;
	for (; f != l; *f++ *= s);
	return *this;
}

template<typename T>
inline Wielomian<T>& Wielomian<T>::operator/=(const T s)
{
	auto *f = this->tab,
		*l = this->tab + this->size;
	for (; f != l; *f++ /= s);
	return *this;
}

template<typename T>
inline Wielomian<T> Wielomian<T>::operator*(const T s)
{
	auto *f = this->tab,
		*l = this->tab + this->size;

	for (; f != l; *f++ /= s);
	return *this;
}

template<typename T>
inline Wielomian<T> Wielomian<T>::operator/(const T s)
{
	auto *f = this->tab,
		*l = this->tab + this->size;

	for (; f != l; *f++ /= s);
	return *this;
}

template<typename T>
inline bool Wielomian<T>::operator==(const Wielomian &w)
{
	if (this->size != w.size) return false;

	auto *t = this->tab,
		*l = this->tab + this->size,
		*n = w.tab;

	for (; t != l && *t == *n; t++, n++);

	if (t != l) return false;
	else return true;
}

template<class T>
Wielomian<T>& Wielomian<T>::operator=(const Wielomian<T> &w)
{
	if (this != w)
	{
		delete[] this->tab;
		this->size = w.size;
		this->tab = new T[w.size];

		auto *t = this->tab,
			*l = t + w.size,
			*n = w.tab;

		for (; t != l; *t++ = *n++);
	}
	return *this;
}

template<class T>
inline T Wielomian<T>::operator[](size_t i) const { assert(i >= 0); return this->tab[i]; }

template<class T>
inline T & Wielomian<T>::operator[](size_t i) { assert(i >= 0); return this->tab[i]; }

template<class T>
Wielomian<T>::~Wielomian()
{
	delete[] this->tab;
	this->size = 0;
}
