#include <vector>
#include "workflow.hpp"

class TabuScheduler {

public:
    std::vector<int> createSchedule(Workflow workflow, std::vector<int> x0, int gamma, int L);
};