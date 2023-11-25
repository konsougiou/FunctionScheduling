#include <vector>
#include <deque>
#include "workflow.hpp"

class TabuScheduler {

public:
    
    double getTotalTardiness(std::vector<int>& schedule, Workflow& workflow);

    int getNextAvailableSwap(int currSwapIdx, int& swapAttemptsSoFar, std::vector<int>& schedule, Workflow& workflow);

    void printAlgorithmState(int k, std::vector<int>& y, double g_y, std::deque<std::string>& tabuList, double g_best, std::string swap_pair, bool isTabu);

    // return optimal schedule, and populated a vector with tardinesses over iterations
    std::vector<int> createSchedule(Workflow& workflow, std::vector<int> x0, std::vector<double>& tardinessHistory, int samplingFactor, int gamma, int L, int K, bool enablePrint);

    std::unordered_set<std::string> createSchedulesSweepParams(Workflow& workflow, std::vector<int> x0, int min_gamma, int max_gamma, int min_L, int max_L, int K, bool enablePrint);

    // Get a vector with optimal tardiness measured when keeping L and K constant, and sweeping gamma.
    std::vector<double> getMinCostsOverGamma(Workflow& workflow, std::vector<int> x0, int min_gamma, int max_gamma,int step, int L, int K);

    std::string scheduleToString(std::vector<int>& schedule);

};