#include "../include/tabuScheduler.hpp"
#include <cmath>
#include <deque>
#include <iostream>


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


int TabuScheduler::getNextAvailableSwap(int currSwapIdx, std::vector<int>& schedule, Workflow& workflow){
    int swapIdx = currSwapIdx % (schedule.size() - 1); // schedule.size() - 1 since we need to loop back before we reach the last job,
    int jobA = schedule[swapIdx];                       // i.e (3, 4) -> (1, 2)
    int jobB = schedule[swapIdx + 1];
    auto jobBDependencies = workflow.dependenciesPerJob[jobB];

    while (jobBDependencies.find(jobA) != jobBDependencies.end()){
        swapIdx = (swapIdx + 1) % (schedule.size() - 1);
        // Went full circle. No possible adjacent swap without breaking dependencies
        if (swapIdx == currSwapIdx) return -1;
        jobA = schedule[swapIdx];
        jobB = schedule[swapIdx + 1];
        jobBDependencies = workflow.dependenciesPerJob[jobB];
    }
    return swapIdx;
}



std::vector<int> TabuScheduler::createSchedule(Workflow& workflow, std::vector<int> x0, int gamma, int L, int K){
    //representing job pairs as strings of the format "i_j"
    std::deque<std::string> tabuList;
    int k = 0;
    int g_best = getTotalTardiness(x0, workflow);
    int g_x_k = g_best;
    std::cout<< g_best<<std::endl;
    int swapIdx = 0;
    std::vector<int> x_k = x0;
    std::vector<int> x_best = x_k;
    std::vector<int> y = x_k;
    while (k < K){
        int swapIdx = getNextAvailableSwap(swapIdx, y, workflow);
        // No available adjacent swap
        if (swapIdx == -1) return x_best;
        std::swap(y[swapIdx], y[swapIdx + 1]);
        int g_y = getTotalTardiness(y, workflow);
        int Delta = g_x_k - g_y;
        std::string swap_pair = std::to_string(swapIdx) + "_" + std::to_string(swapIdx + 1);
        bool pairInList = std::find(tabuList.begin(), tabuList.end(), swap_pair) != tabuList.end();
        swapIdx++;
        while (g_y >= g_best && (Delta <= -gamma || pairInList)){
            // reset y to x_k, before performing swap
            y = x_k;
            swapIdx = getNextAvailableSwap(swapIdx, y, workflow);
            if (swapIdx == -1) return x_best;
            std::swap(y[swapIdx], y[swapIdx + 1]);
            g_y = getTotalTardiness(y, workflow);
            Delta = g_x_k - g_y;
            swap_pair = std::to_string(swapIdx) + "_" + std::to_string(swapIdx + 1);
            pairInList = std::find(tabuList.begin(), tabuList.end(), swap_pair) != tabuList.end();
            swapIdx++;
        }
        tabuList.push_back(swap_pair);
        if (tabuList.size() > L) tabuList.pop_front();

        if (g_y < g_best){
            g_best = g_y;
            x_best = y;
        }
        x_k = y;
        g_x_k = g_y;
        k++;
    }
    std::cout<< g_best<<std::endl;
    return x_best;
};