#include "Route.h"
#include <random>

Route::Route() : size(0), distance(0),fitness(0) {}
Route::Route(int _size, std::vector<City> _cities) : size(_size) {
	path = generatePath(_cities);
	distance = routeDistance();
	setFitness();
}
Route::Route(const Route& _other) :
	size(_other.size),
	path(_other.path),
	distance(_other.distance),
	fitness(_other.fitness)
{}

double Route::twoCityDistance(const City& _first, const City& _second) {
	return _first.distance(_second);
}

double Route::routeDistance() {
	double result_distance = 0;
	for (int i = 0; i < size - 1; i++) {
		result_distance += twoCityDistance(path[i], path[i + 1]);
	}
	return result_distance;
}

void Route::setFitness() {
	assert(distance != 0);
	fitness = 1 / distance;
}
void Route::setDistance() {
	distance = routeDistance();
}
void Route::setSize(int _size) {
	size = _size;
}
void Route::setRouteWithSettedAlreadyPath(int _size) {
	setSize(_size);
	setDistance();
	setFitness();
}

void Route::incrementSize() {
	size++;
}
double Route::getFitness() const{
	return fitness;
}
double Route::getDistance() const {
	return distance;
}
std::vector<City> Route::getPath() const {
	return path;
}
int Route::getSize() const {
	return size;
}

void Route::setCityOnPlace(City _city, int _index) {
	path[_index] = _city;
}

void Route::pushBackCity(City _city) {
	path.push_back(_city);
}

void Route::pushFrontCity(City _city) {
	path.insert(path.begin(), _city);
}
City Route::getCityOnPlace(int _index) {
	return path[_index];
}

void Route::printCities() {
	for (int i = 0; i < size; i++) {
		std::cout << "City[" << i << "] = ";
		path[i].print();
		std::cout << '\n';
	}
}

std::vector<City> Route::generatePath(std::vector<City> cities) {
	std::vector<City> res_path;
	while (cities.size() > 0) {
		City push_city = cutCity(cities);
		res_path.push_back(push_city);
	}
	return res_path;
}
City Route::cutCity(std::vector<City>& cities) {
	int i = randomInteger(0, cities.size());
	City res_city = cities[i];
	cities.erase(cities.begin() + i);
	return res_city;
}

void Route::mutate(int _indexA, int _indexB) {
	std::swap(path[_indexA], path[_indexB]);
}

bool Route::findCity(City city) {
	assert(path.size() > 0);
	for (int i = 0; i < size; i++) {
		if (path[i] == city) {
			return true;
		}
	}
	return false;
}

