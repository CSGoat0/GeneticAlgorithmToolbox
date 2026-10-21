#pragma once
#include <vector>

struct Point {
    int id;
    double x, y;
};

class CVRP {
public:
    std::vector<Point> customers;
    int vehicleCapacity;
    
    CVRP(int capacity) : vehicleCapacity(capacity) {}
    void addCustomer(int id, double x, double y) { customers.push_back({id, x, y}); }
};