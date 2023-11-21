#include "../include/tabuScheduler.hpp"
#include <cmath>
#include <deque>
#include <iostream>


double TabuScheduler::getTotalTardiness(std::vector<int>& schedule, Workflow& workflow){
        double costSoFar = 0;
        double totalTardiness = 0;
        for(int job: schedule){
            costSoFar += workflow.processingTimes[job];
            double lateness = costSoFar - workflow.dueDates[job];
            double tardiness = std::max(lateness, 0.0);
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
};

void TabuScheduler::printAlgorithmState(int k, std::vector<int>& y, double g_y, std::deque<std::string>& tabuList, double g_best, std::string swap_pair,bool isTabu){
    std::cout<<"k: "<<k<<std::endl;
    std::cout<<"y: ";
    for(int job: y){
        std::cout<<job<<", ";
    }
    std::cout<<std::endl;
    std::cout<<"g_y: "<<g_y<<" g_best: "<<g_best<<std::endl;
    std::cout<<"tabuList: ";
    for(auto pair: tabuList){
        std::cout<<pair<<", ";
    }
        std::cout<<std::endl;
    std::cout<<"swap_pair: "<<swap_pair<<std::endl;
    std::cout<<"tabu? : "<<isTabu<<std::endl;
};



std::vector<int> TabuScheduler::createSchedule(Workflow& workflow, std::vector<int> x0, int gamma, int L, int K, bool enablePrint){
    //representing job pairs as strings of the format "jobA_jobB", where jobA < jobB, representing both A<->B and B<->A swaps
    std::deque<std::string> tabuList;
    int k = 0;
    double g_best = getTotalTardiness(x0, workflow);
    double g_x_k = g_best;
    int swapIdx = 0;
    std::vector<int> x_k = x0;
    std::vector<int> x_best = x_k;
    std::vector<int> y = x_k;
    if (enablePrint){
        printAlgorithmState(k, y, g_best, tabuList, g_best, "",false);
        std::cout<<"----------------------------------------------"<<std::endl;
    }

    while (k < K){
        int swapIdx = getNextAvailableSwap(swapIdx, y, workflow);
        // No available adjacent swap
        if (swapIdx == -1) return x_best;
        std::swap(y[swapIdx], y[swapIdx + 1]);
        double g_y = getTotalTardiness(y, workflow);
        double Delta = g_x_k - g_y;

        std::string swap_pair;
        if (y[swapIdx]< y[swapIdx + 1]){
            swap_pair = std::to_string(y[swapIdx]) + "_" + std::to_string(y[swapIdx + 1]);
        }else{
            swap_pair = std::to_string(y[swapIdx + 1]) + "_" + std::to_string(y[swapIdx]);
        }

        bool pairInList = std::find(tabuList.begin(), tabuList.end(), swap_pair) != tabuList.end();
        swapIdx++;
        while (g_y >= g_best && (Delta <= -gamma || pairInList)){
            k++;
            if (enablePrint){
                printAlgorithmState(k, y, g_y, tabuList, g_best, swap_pair, pairInList);
            }
            if (k >= K) return x_best;
            // reset y to x_k, before performing swap
            y = x_k;
            swapIdx = getNextAvailableSwap(swapIdx, y, workflow);
            if (swapIdx == -1) return x_best;
            std::swap(y[swapIdx], y[swapIdx + 1]);
            g_y = getTotalTardiness(y, workflow);
            Delta = g_x_k - g_y;

            if (y[swapIdx]< y[swapIdx + 1]){
                swap_pair = std::to_string(y[swapIdx]) + "_" + std::to_string(y[swapIdx + 1]);
            }else{
                swap_pair = std::to_string(y[swapIdx + 1]) + "_" + std::to_string(y[swapIdx]);
            }

            pairInList = std::find(tabuList.begin(), tabuList.end(), swap_pair) != tabuList.end();
            swapIdx++;
        }

        if (g_y < g_best){
            g_best = g_y;
            x_best = y;
        }
        x_k = y;
        g_x_k = g_y;
        k++;

        if (enablePrint){
            printAlgorithmState(k, y, g_y, tabuList, g_best, swap_pair, pairInList);
            std::cout<<"----------------------------------------------"<<std::endl;
        }
        // Add element only if not in list
        if (!pairInList) tabuList.push_back(swap_pair);
        if (tabuList.size() > L) tabuList.pop_front();

    }
    //std::cout<< g_best<<std::endl;
    return x_best;
};

 std::vector<int> TabuScheduler::createScheduleSweepParams(Workflow& workflow, std::vector<int> x0, int min_gamma, int max_gamma, int min_L, int max_L, int K, bool enablePrint){
    int best_gamma;
    int best_L;
    std::vector<int> bestSchedule;
    std::vector<int> currSchedule;
    int g_best = getTotalTardiness(x0, workflow);
    for (int gamma = min_gamma; gamma <= max_gamma; gamma++){
        for (int L = min_L; L <= max_L; L++){
            currSchedule = createSchedule(workflow, x0, gamma, L, K, false);
            int g = getTotalTardiness(currSchedule, workflow);
            if (g <= g_best){
                g_best = g;
                bestSchedule = currSchedule;
                best_gamma = gamma;
                best_L = L;
            }
        }
    }
    if (enablePrint){
        std::cout<< "best_gamma: "<< best_gamma << std::endl;
        std::cout<< "best_L: "<< best_L << std::endl;
        std::cout<< "best_g: "<< g_best << std::endl;
    }
    return bestSchedule;
 }