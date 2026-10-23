#include "CVRP.h"

using namespace std;

CVRP::CVRP(int capacity, int numVehicles, const vector<int>& demand, 
    const vector<vector<int>>& dist) : capacity(capacity), numVehicles(numVehicles), demand(demand), dist(dist) {}

int CVRP::numCustomers() const {
    return demand.size() - 1;
}

Routes CVRP::decode(const vector<int>& perm) const {
    Routes routes;
    vector<int> current;
    int load = 0;
    for (int c : perm) {
        if (load + demand[c] > capacity && !current.empty()) {
            routes.push_back(current);
            current.clear();
            load = 0;
        }
        current.push_back(c);
        load += demand[c];
    }
    if (!current.empty()) routes.push_back(current);
    return routes;
}

bool CVRP::isValidPermutation(const vector<int>& perm) const {
    int n = numCustomers();
    if ((int)perm.size() != n) return false;
    vector<bool> seen(n + 1, false);
    for (int c : perm) {
        if (c < 1 || c > n || seen[c]) return false;
        seen[c] = true;
    }
    return true;
}

bool CVRP::isFeasible(const Routes& routes) const {
    if ((int)routes.size() > numVehicles) return false;
    int served = 0;
    for (const auto& route : routes) {
        if (routeLoad(route) > capacity) return false;
        served += route.size();
    }
    return served == numCustomers();
}

int CVRP::routeLoad(const vector<int>& route) const {
    int load = 0;
    for (int c : route) {
        load += demand[c];
    }
    return load;
}

int CVRP::routeCost(const vector<int>& route) const {
    if (route.empty()) return 0;
    int cost = dist[0][route[0]];
    for (size_t i = 1; i < route.size(); i++) {
        cost += dist[route[i - 1]][route[i]];
    }
    return cost + dist[route.back()][0];
}

int CVRP::totalCost(const Routes& routes) const {
    int total = 0;
    for (const auto& route : routes){
        total += routeCost(route);
    }
    return total;
}
