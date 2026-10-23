#pragma once
#include <vector>

using namespace std;
using Routes = vector<vector<int>>;
class CVRP {
public:
    int capacity;
    int numVehicles;
    vector<int> demand;
    vector<vector<int>> dist;

    CVRP(int capacity, int numVehicles, const vector<int>& demand,
         const vector<vector<int>>& dist);

    int numCustomers() const;
    Routes decode(const vector<int>& perm) const;
    bool isValidPermutation(const vector<int>& perm) const;
    bool isFeasible(const Routes& routes) const;
    int routeLoad(const vector<int>& route) const;
    int routeCost(const vector<int>& route) const;
    int totalCost(const Routes& routes) const;
};