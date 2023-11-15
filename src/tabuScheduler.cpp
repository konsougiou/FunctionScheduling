#include "../include/tabuScheduler.hpp"
#include <cmath>
#include <deque>


int TabuScheduler::getTotalTardiness(std::vector<int>& schedule, Workflow& workflow){
        int costSoFar = 0;
        int totalTardiness = 0;
        for(int job: schedule){
            costSoFar += workflow.processingTimes[job];
            int lateness = costSoFar - workflow.dueDates[job];
            int tardiness = std::max(lateness, 0);
            totalTardiness += tardiness;
        }
        return totalTardiness;
    };


std::vector<int> TabuScheduler::createSchedule(Workflow& workflow, std::vector<int> x0, int gamma, int L){
    //representing job pairs as strings of the format "i_j"
    std::deque<std::string> tabuList;
    int k = 0;
    int g_best = getTotalTardiness(x0, workflow);

    return {};
};