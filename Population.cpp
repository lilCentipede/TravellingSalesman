#include "Population.h"

Route Population::sliceVector(Route _vec, int _indexA, int _indexB) {
    Route res_vec;
    assert(_vec.getSize() > _indexB);
    for (int i = _indexA; i <= _indexB; i++) {
        res_vec.pushBackCity(_vec.getCityOnPlace(i));
    }
    res_vec.setRouteWithSettedAlreadyPath(res_vec.getPath().size());
    return res_vec;
}
Population::Population(int population_size, std::vector<City> _cities, int total_cities ) :
    population_size(population_size),
    total_cities(total_cities) {
    initPopulationAndSetFitness(_cities);
}


Population::Population(const Population& _other) :
    population_size(_other.population_size),
    routes(_other.routes),
    total_cities(_other.total_cities),
    routes_fitness(_other.routes_fitness)
{}

void Population::printBestRoute() {
    std::cout << bestRoute.getDistance()<<'\n';
}
void Population::initPopulationAndSetFitness(std::vector<City> cities) {
    double sum = 0;
    for (int i = 0; i < population_size; i++) {
        sum += insertRouteOrderedByDistanceAndReturnItsFitness(routes, Route(total_cities, cities));
    }
    bestRoute = routes[0];
    normalizeFitness(sum);
}

std::vector<Route> Population::getRoutes() { 
    return routes;
}


void Population::print() {
    for (int i = 0; i < population_size; i++) {
        std::cout << "------------------------------------\n";
        std::cout << "Route[" << i << "]'s distance:"<<routes[i].getDistance() << ", fitness:" <<routes[i].getFitness() << '\n';
        routes[i].printCities();
        std::cout<<routes_fitness[i]<<'\n';
        std::cout << "------------------------------------\n";
    }
}


void Population::normalizeFitness(double _sum) {
    assert(population_size == routes.size());
    for (int i = 0; i < population_size; i++) {
        routes_fitness.push_back(routes[i].getFitness() / _sum);
    }
}

Route Population::pickOne() {
    double randomD = randomDouble(0, 1);
    int index = 0;

    while (randomD >= 0) {
        randomD -= routes_fitness[index++];
    }
    --index;
    if (index >= routes.size())
        index = routes.size() - 1;
    return routes[index];
}

Route Population::nextPopulation() {
    std::vector<Route> newPopulation;
    double sum = 0;
    for (int i = 0; i < population_size; i++) {
        Route parent1 = pickOne();
        Route parent2 = pickOne();
        Route child = crossOver(parent1, parent2);
        mutate(child, 0.3);
        sum += insertRouteOrderedByDistanceAndReturnItsFitness(newPopulation, child);
    }
    routes = newPopulation;
    bestRoute = routes[0];
    normalizeFitness(sum);
    return bestRoute;
}

Route Population::crossOver(Route& _parent1, Route& _parent2) {
    assert(total_cities >= 2);
    int start = 0, end = total_cities - 1;
    while (start == 0 && end == total_cities - 1 ) {
        start = randomInteger(0, total_cities - 1);
        end = randomInteger(start + 1, total_cities);
    }
    assert(_parent1.getSize() == total_cities);
    Route child = sliceVector(_parent1, start, end);
    Route takeFrom = _parent2;

    for (int j = 0; j < total_cities; j++) {
        if (!child.findCity(takeFrom.getPath()[j])) {
            if (j < start) {
                child.pushFrontCity(takeFrom.getPath()[j]);
            }
            else {
                child.pushBackCity(takeFrom.getPath()[j]);
            }
            child.incrementSize();
        }
    }
    child.setRouteWithSettedAlreadyPath(total_cities);
    assert(child.getPath().size() == total_cities);
    return child;
}

void Population::mutate(Route& _route, double _mutationRate) {
    for (int i = 0; i < total_cities; i++) {
        assert(_mutationRate <= 1);
        if (randomDouble(0, 1) < _mutationRate) {
            int indexA = randomInteger(0,total_cities);
            int indexB = (indexA + 1) % total_cities;
            _route.mutate(indexA, indexB);
        }
    }
}
void Population::generationLoop(int _turns) {
    Route currentBestRoute = bestRoute;
    std::cout << "Start:\n";
    std::cout << currentBestRoute.getDistance() << '\n';
    
    for (int i = 0; i < _turns; i++) {
        Route _bestRoute = nextPopulation();
        if (currentBestRoute.getDistance() > _bestRoute.getDistance()) {
            currentBestRoute = _bestRoute;
            std::cout << "[" << i << "]:";
            std::cout << currentBestRoute.getDistance() << '\n';
        }
    }
    std::cout << "End:\n";
    std::cout << currentBestRoute.getDistance() << '\n';
}


//static
double Population::insertRouteOrderedByDistanceAndReturnItsFitness(std::vector<Route>& _routes, const Route& insert_route) {
    if (_routes.size() == 0) {
        _routes.push_back(insert_route);
        return insert_route.getFitness();
    }
    else {
        for (int i = 0; i < _routes.size(); i++) {
            if (_routes[i].getDistance() > insert_route.getDistance()) {
                _routes.insert(_routes.begin() + i, insert_route);
                return insert_route.getFitness();
            }
        }
    }
    _routes.push_back(insert_route);
    return insert_route.getFitness();
}