#pragma once
#include "Route.h"
class Population
{
	//move it later to a Start class
	//std::vector<City> initial_cities;
private:
	int population_size;
	int total_cities;
	Route bestRoute;
	std::vector<Route> routes;
	std::vector<double> routes_fitness;
public:
	//Population();
	//we use this one
	Population(int _population_size, std::vector<City> _cities, int total_cities);
	Population(const Population& _other);
	void initPopulationAndSetFitness(std::vector<City> _cities);
	void setPopulation_Fitness_BestRoute();
	void printBestRoute();
	std::vector<Route> getRoutes();
	void print();

	Route nextPopulation();
	Route crossOver(Route& _parent1, Route& _parent2);
	void mutate(Route& _route, double _mutationRate);

	//first route is with shortest distance and best fitness
	static double insertRouteOrderedByDistanceAndReturnItsFitness(std::vector<Route>& _routes,const Route& insert_route);
	static Route sliceVector(Route _vec, int _indexA, int _indexB);

	void normalizeFitness(double _sum);
	Route pickOne();
	void generationLoop(int _turns);
};

