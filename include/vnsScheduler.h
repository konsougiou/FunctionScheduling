#include "workflow.hpp"
#include <vector>

class VNSScheduler {

public:

    double getTotalTardiness(std::vector<int>& schedule, Workflow& workflow);

    std::vector<std::vector<int>> getAllFeasibleSchedules(Workflow& workflow);

    std::vector<std::vector<int>> topologicalSortHelper(Workflow& workflow, std::unordered_set<int>& visited, std::unordered_set<int>& notVisited, std::unordered_map<std::string, std::vector<std::vector<int>>>& mem,int size);

    // convert any iterable (set, vector, ect) into a comma seperated string.
    template<typename T>
    std::string iterableToString(T& schedule);

};