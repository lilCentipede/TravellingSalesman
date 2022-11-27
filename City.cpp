#include "City.h"

City::City(double _x, double _y) : x(_x), y(_y) {}

City::City(const City& _other) {
	x = _other.x;
	y = _other.y;
}
void City::print() {
	std::cout << '(' << x << "," << y << ')';
}

double City::distance(const City& _other) const {
	double x_distance = abs(x - _other.x);
	double y_distance = abs(y - _other.y);
	return sqrt((x_distance * x_distance) + (y_distance * y_distance));
}

City City::generateCity(double lower, double upper) {
	double rand_x = randomDouble(lower, upper);
	double rand_y = randomDouble(lower, upper);
	return City(rand_x, rand_y);
}

std::vector<City> City::generateCities(int _size) {
	std::vector<City> res_city;
		for (int i = 0; i < _size; i++) {
		res_city.push_back(City::generateCity(0, (double)_size));
	}
	return res_city;
}

bool operator==(const City& _first, const City& _second) {
	return _first.x == _second.x && _first.y == _second.y;
}
bool operator!=(const City& _first, const City& _second) {
	return !(_first == _second);
}