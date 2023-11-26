#include "workflow.hpp"
#include <vector>
#include <cstdlib>

class VNSScheduler {

public:

    double getTotalTardiness(std::vector<int>& schedule, Workflow& workflow);
    // convert any iterable (set, vector, ect) into a comma seperated string.
    template<typename T>
    std::string iterableToString(T& schedule);

    std::vector<int> getNextSchedule(Workflow& workflow, std::vector<int>& x0, std::vector<int>& jobsToIdx, int radiusm, int maxIters);

    bool isValidSwap(std::vector<int>& schedule, Workflow& workflow, int Idx1, int Idx2);

    int getDistanceFromX0(std::vector<int>& schedule, std::vector<int>& x0JobToIdx);

    std::vector<int> createSchedule(Workflow& workflow, std::vector<int>& x0, int L, int K, int maxIters);

    std::vector<int> createScheduleRefined(Workflow& workflow, std::vector<int>& x0, int L, int K, int maxIters);

    std::vector<int> getRandomFeasibelSchedule(Workflow& workflow);

    int getMaxPossibleDistance(int size);
};