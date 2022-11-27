#pragma once
#include <iostream>
#include "Random.h"

class City {
public:
	double x;
	double y;
	City(double _x, double _y);
	City(const City& _other);
	void print();
	double distance(const City& _other) const;
	static City generateCity(double _lower, double _upper);
	static std::vector<City> generateCities(int _size);
	friend bool operator==(const City& _first, const City& second);
	friend bool operator!=(const City& _first, const City& _second);
};
