#include "pch.h"
#include "Wielomian.h"

float GetNumber(std::string v)
{
	if (!v.length()) return 1;
	if (v.length() == 1 && v[0] == '-')
		v.append("1");
	return std::stof(v);
}

const int Wielomian::size()
{
	return this->params.size() - 1;
}

Wielomian::Wielomian(std::vector<float>& v)
{
	this->params = v;
}

Wielomian::Wielomian(const Wielomian& w)
{
	// czy to jest plytkie czy glegokie kopiowanie? - glegokie kopiowanie
	this->params = w.params;
}

Wielomian::Wielomian(float t[], int len)
{
	for (int i = 0; i < len; i++)
		this->params.push_back(t[i]);
}

Wielomian::Wielomian(std::string str)
{
	std::vector<float> v;
	std::vector<std::string> strV;
	std::vector<float> MonomialW;
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
		MonomialW.push_back(0);
		this->params = MonomialW;
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

		this->params = v;
	}
}

Wielomian Wielomian::operator+(const Wielomian& w)
{
	std::vector<float> v, v_;
	size_t t_l = this->params.size(), w_l = w.params.size();
	size_t MIN_LEN;

	if (t_l > w_l)
	{
		MIN_LEN = w_l;
		v = this->params;
		v_ = w.params;
	}
	else
	{
		MIN_LEN = t_l;
		v = w.params;
		v_ = this->params;
	}

	for (size_t i = 1, vl = v.size(), v_l = v_.size(); i <= MIN_LEN; i++)
	{
		v[vl - i] += v_[v_l - i];
	}
	return Wielomian(v);
}

Wielomian Wielomian::operator-(const Wielomian& w)
{
	std::vector<float> v, v_;
	size_t t_l = this->params.size(), w_l = w.params.size();
	size_t MIN_LEN;

	if (t_l > w_l)
	{
		MIN_LEN = w_l;
		v = this->params;
		v_ = w.params;
	}
	else
	{
		MIN_LEN = t_l;
		v = w.params;
		v_ = this->params;
	}

	for (size_t i = 1, vl = v.size(), v_l = v_.size(); i <= MIN_LEN; i++)
	{
		v[vl - i] -= v_[v_l - i];
	}
	return Wielomian(v);
}

Wielomian Wielomian::operator*(const Wielomian& w)
{
	std::vector<float> v;
	for (size_t i = 0; i < this->params.size() + w.params.size() - 1; i++)
		v.push_back(0);

	for (size_t i = 0; i < this->params.size(); i++)
		for (size_t j = 0; j < w.params.size(); j++)
			v[i + j] += (this->params[i] * w.params[j]);
	return Wielomian(v);
}

Wielomian Wielomian::operator*(const float a)
{
	std::vector<float> v = this->params;
	for (size_t i = 0; i < this->params.size(); i++)
		v[i] *= a;
	return Wielomian(v);
}

Wielomian Wielomian::operator/(const float a)
{
	std::vector<float> v = this->params;
	for (size_t i = 0; i < this->params.size(); i++)
		v[i] /= a;
	return Wielomian(v);
}

bool Wielomian::operator==(const Wielomian& w)
{
	if (this->params == w.params)
		return true;
	return false;
}

std::ostream& operator<<(std::ostream& s, Wielomian w)
{
	size_t pow = w.params.size();

	for (auto v : w.params)
	{
		if (v)
		{
			std::cout << ((v > 0 && pow != w.params.size()) ? "+" : "");
			if (v != 1 && v != -1) std::cout << v;
			else if (v == -1) std::cout << "-";
			else if (pow == 1) std::cout << v;
			std::string s = (pow != 2) ? "x^{" + std::to_string(pow - 1) + "}" : "x";
			std::cout << ((pow != 1) ? s : "");
		}
		pow--;
	}
	return s;
}

Wielomian& Wielomian::operator+=(const Wielomian& w)
{
	this->params = (*this + w).params;
	return *this;
}

Wielomian& Wielomian::operator-=(const Wielomian& w)
{
	this->params = (*this - w).params;
	return *this;
}

Wielomian& Wielomian::operator*=(const Wielomian& w)
{
	this->params = (*this * w).params;
	return *this;
}

Wielomian& Wielomian::operator*=(const float a)
{
	for (size_t i = 0; i < this->params.size(); i++)
		this->params[i] *= a;
	return *this;
}

Wielomian& Wielomian::operator/=(const float a)
{
	for (size_t i = 0; i < this->params.size(); i++)
		this->params[i] /= a;
	return *this;
}

Wielomian& Wielomian::operator=(const Wielomian& w)
{
	this->params = w.params;
	return *this;
}

float  Wielomian::operator[](size_t i) const { assert(i >= 0); return this->params[i]; }
float& Wielomian::operator[](size_t i)       { assert(i >= 0); return this->params[i]; }

Wielomian::~Wielomian()
{
	// nic nie trzeba zwalniac bo mamy vektory <3, tfu wskazniki
	// "Jezeli nie musisz uzywac wskaznikow, to tego nie rob."
}
