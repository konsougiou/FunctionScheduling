#include <vector>
#include "workflow.hpp"

class TabuScheduler {

public:
    
    int getTotalTardiness(std::vector<int>& schedule, Workflow& workflow);

    int getNextAvailableSwap(int currSwapIdx, std::vector<int>& schedule, Workflow& workflow);

    std::vector<int> createSchedule(Workflow& workflow, std::vector<int> x0, int gamma, int L, int K);
};