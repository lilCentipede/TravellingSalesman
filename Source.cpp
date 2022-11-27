#include <iostream>
#include "Population.h"


int main() {
	int total_cities;
	std::cin >> total_cities;
	assert(total_cities >= 1);
	srand(time(NULL));
	std::vector<City> init_cities = City::generateCities(total_cities);
	Population pop(300, init_cities, total_cities);
	pop.generationLoop(500);

	return 0;
}
