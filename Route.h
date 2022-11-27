#pragma once
#include <vector>
#include <assert.h>
#include "City.h"

class Route
{
private:
	int size;
	double distance;
	double fitness;
	std::vector<City> path;
	double routeDistance();
	
public:
	Route();
	Route(int _size);
	Route(int _size, std::vector<City> _cities);
	Route(const Route& _other);
	double twoCityDistance(const City& _first, const City& _second);

	void setFitness();
	void setCityOnPlace(City _city, int _index);
	void setDistance();
	void setSize(int _size);
	void setRouteWithSettedAlreadyPath(int _size);
	void incrementSize();

	void pushBackCity(City _city);
	void pushFrontCity(City _city);

	City getCityOnPlace(int _index);
	double getFitness() const;
	double getDistance() const;
	std::vector<City> getPath() const;
	int getSize() const;

	void printCities();
	void mutate(int _indexA, int _indexB);
	std::vector<City> generatePath(std::vector<City> cities);
	City cutCity(std::vector<City>& cities);
	bool findCity(City city);
};

