#include "../include/vnsScheduler.h"
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>


std::vector<int> VNSScheduler::createScheduleRefined(Workflow& workflow, std::vector<int>& x0, int L, int K, int maxIters, int maxRefineAttempts){

    double best_g = getTotalTardiness(x0, workflow);
    std::vector<int> bestSchedule = x0;
    int k = 0;
    if (L == 1) return getRandomFeasibelSchedule(workflow);

    // the vector storing the index of each job in X0
    std::vector<int> x0JobToIdx(x0.size() + 1, 0);
    for (int i = 0; i < x0.size(); i++){
        int job = x0[i];
        x0JobToIdx[job] = i;
    }
    int maxPossibleDistance = getMaxPossibleDistance(x0.size());
    int neighbouringRadiusIncrease = (maxPossibleDistance / 2) / (L - 1);
    std::vector<int> pickedSchedule;
    std::vector<int> refineCandiateSchedule;
    while (k <= K){
        int i = 1;
        if (k % 100 == 0){
            std::cout<<k<<std::endl;
            std::cout<<best_g<<std::endl;
        }
        int radius = neighbouringRadiusIncrease;
        while (i < L){
            pickedSchedule = getNextSchedule(workflow, x0, x0JobToIdx, radius, maxIters);
            double tardiness = getTotalTardiness(pickedSchedule, workflow);
            int refineAttemps = 0;
            //Check if we can find a better schedule within this neighbourhoud
            while(refineAttemps <  maxRefineAttempts){
                refineCandiateSchedule = getNextSchedule(workflow, x0, x0JobToIdx, radius, maxIters);
                double newTardiness = getTotalTardiness(refineCandiateSchedule, workflow);
                if (newTardiness < tardiness){
                    pickedSchedule = refineCandiateSchedule;
                    tardiness = newTardiness;
                    break;
                }
                refineAttemps++;
            }

            if (tardiness < best_g){
                best_g = tardiness;
                bestSchedule = pickedSchedule;
            }
            radius += neighbouringRadiusIncrease;
            i++;
        }
        // Finally select from NL, i.e the whole feasible set
        pickedSchedule = getRandomFeasibelSchedule(workflow);
        double tardiness = getTotalTardiness(pickedSchedule, workflow);

        //Refine
        int refineAttemps = 0;
        while(refineAttemps <  maxRefineAttempts){
            refineCandiateSchedule = getNextSchedule(workflow, x0, x0JobToIdx, radius, maxIters);
            double newTardiness = getTotalTardiness(refineCandiateSchedule, workflow);
            if (newTardiness < tardiness){
                pickedSchedule = refineCandiateSchedule;
                tardiness = newTardiness;
                break;
            }
            refineAttemps++;
        }
        if (tardiness < best_g){
            best_g = tardiness;
            bestSchedule = pickedSchedule;
        }
        k++;
    }
    return bestSchedule;
    }



std::vector<int> VNSScheduler::createSchedule(Workflow& workflow, std::vector<int>& x0, int L, int K, int maxIters, bool enablePrint){

    double best_g = getTotalTardiness(x0, workflow);
    std::vector<int> bestSchedule = x0;
    int k = 0;
    if (L == 1) return getRandomFeasibelSchedule(workflow);
    std::unordered_set<std::string> visitedList;

    // the vector storing the index of each job in X0
    std::vector<int> x0JobToIdx(x0.size() + 1, 0);
    for (int i = 0; i < x0.size(); i++){
        int job = x0[i];
        x0JobToIdx[job] = i;
    }

    int maxPossibleDistance = getMaxPossibleDistance(x0.size());
    int neighbouringRadiusIncrease = (maxPossibleDistance / 2) / (L - 1);
    std::vector<int> pickedSchedule;
    while (k <= K){
        int i = 1;
        if (k % 100 == 0){
            std::cout<<k<<std::endl;
            std::cout<<best_g<<std::endl;
        }
        int radius = neighbouringRadiusIncrease;
        while (i < L){
            pickedSchedule = getNextSchedule(workflow, x0, x0JobToIdx, radius, maxIters);
            double tardiness = getTotalTardiness(pickedSchedule, workflow);
            printAlgorithmState(k, i, L, best_g, tardiness, pickedSchedule);
            if (tardiness < best_g){
                best_g = tardiness;
                bestSchedule = pickedSchedule;
            }
            radius += neighbouringRadiusIncrease;
            i++;
        }
        // Finally select from NL, i.e the whole feasible set
        pickedSchedule = getRandomFeasibelSchedule(workflow);
        double tardiness = getTotalTardiness(pickedSchedule, workflow);
        printAlgorithmState(k, L, L, best_g, tardiness, pickedSchedule);
        if (tardiness < best_g){
            best_g = tardiness;
            bestSchedule = pickedSchedule;
        }
        k++;
    }
    return bestSchedule;
    };

std::vector<std::vector<int>> VNSScheduler::createSchedulesSweepParams(Workflow& workflow, std::vector<int>& x0, int min_L,int max_L, int K, int maxIters, int minRefineAttempts, int maxRefineAttempts, bool enablePrint){
    std::unordered_set<std::string> bestSchedules;
    std::vector<int> currSchedule;
    // List of <gamma, L, schedule> combinations which all achieve the lowest cost
    std::vector<std::tuple<int, int, std::string>> bestParams; 
    double g_best = getTotalTardiness(x0, workflow);
    for (int L = min_L; L <= max_L; L++){
        // No refine attempts, run normal VNS
        if (!maxRefineAttempts){
            currSchedule = createSchedule(workflow, x0,  L, K, maxIters, false);
            double g = getTotalTardiness(currSchedule, workflow);
            if (g == g_best){
                std::string strSchedule = iterableToString(currSchedule);
                bestSchedules.insert(strSchedule);
                bestParams.push_back(std::make_tuple(L, 0, iterableToString(currSchedule)));
            }
            else if(g < g_best){
                g_best = g;
                bestParams.clear();
                bestSchedules.clear();
                std::string strSchedule = iterableToString(currSchedule);
                bestSchedules.insert(strSchedule);
                bestParams.push_back(std::make_tuple(L, 0,  iterableToString(currSchedule)));
            }
        }
        else{
            for (int refineAttempts = minRefineAttempts; refineAttempts <= maxRefineAttempts; refineAttempts++){
                currSchedule = createScheduleRefined(workflow, x0,  L, K, maxIters, refineAttempts);
                double g = getTotalTardiness(currSchedule, workflow);
                if (g == g_best){
                    std::string strSchedule = iterableToString(currSchedule);
                    bestSchedules.insert(strSchedule);
                    bestParams.push_back(std::make_tuple(L, refineAttempts, iterableToString(currSchedule)));
                }
                else if(g < g_best){
                    g_best = g;
                    bestParams.clear();
                    bestSchedules.clear();
                    std::string strSchedule = iterableToString(currSchedule);
                    bestSchedules.insert(strSchedule);
                    bestParams.push_back(std::make_tuple(L, refineAttempts, iterableToString(currSchedule)));
                }
            }
        }
    }
    if (enablePrint){
        std::cout<< "best_g: "<< g_best << std::endl;
        std::cout<<"parameter combinations found: "<<bestParams.size()<<std::endl;
        std::cout<< "----------------------------------------------" <<std::endl;
        for (const auto& comb: bestParams){
            std::cout<< "L: "<< std::get<0>(comb) <<" ";
            std::cout<< "refineAttempts: "<< std::get<1>(comb) <<" ";
            std::cout<< "Schedule: "<< std::endl <<std::get<2>(comb) <<std::endl;
            std::cout<< "----------------------------------------------" <<std::endl;
        }
    }
    std::vector<std::vector<int>> schedules;
    for (auto& schedule: bestSchedules){
        schedules.push_back(stringToSchedule(schedule));
    }
    return schedules;
};

//Generate a solution in the neighbourhoud that includes up to "radius" perturbations 
//from X0. This is done by randomly swapping job(only feasible swaps), so that the distance between the 
// positions of the jobs in the new schedules, and X0 is a radnom number up to "radius"
std::vector<int> VNSScheduler::getNextSchedule(Workflow& workflow, std::vector<int>& x0, std::vector<int>& jobsToIdx, int radius, int maxIters){
    int distance = (std::rand() % radius) + 1;
    //job number to index in X0
    //make the distance even, since only event distance achieveable , 
    //each swap gives 2 * (difference in index between two elements)
    distance -= (distance % 2);
    if (distance == 0){
        return x0;
    }
    auto currSchedule = x0;
    int k = 0;
    while (true){
        int jobAIdx = std::rand() % x0.size();
        int jobBIdx = std::rand() % x0.size();
        if (jobAIdx == jobBIdx) continue;
        if (!isValidSwap(currSchedule, workflow, jobAIdx, jobBIdx )) continue;

        std::swap(currSchedule[jobAIdx], currSchedule[jobBIdx]);
        int currScheduleDistance = getDistanceFromX0(currSchedule, jobsToIdx);
        if (currScheduleDistance == distance){
            return currSchedule;
        }
        else if(currScheduleDistance > distance){
            //swap back if distance too high
            std::swap(currSchedule[jobAIdx], currSchedule[jobBIdx]);
        }
        k++;
        //failsafe mechanism, in case no available schedule was found within maxIters
        if (k == maxIters){
            radius = radius / 2;
            int distance = (std::rand() % radius) + 1;
            distance -= (distance % 2);
            if (distance == 0){
                return x0;
            }
            k = 0;
        }
    }
    return x0;
};

std::vector<int> VNSScheduler::getRandomFeasibelSchedule(Workflow& workflow){
    int numJobs = workflow.graph.size();
    std::vector<int> schedule;
    std::unordered_set<int> included;
    for(const auto& pair: workflow.dependenciesPerJob){
        if (pair.second.size() == 0){
            schedule.push_back(pair.first);
            included.insert(pair.first);
        }
    }
    while(schedule.size() < numJobs){
        int randJob = (std::rand() % numJobs) + 1;
        if (included.find(randJob) != included.end()) continue;
        auto deps = workflow.dependenciesPerJob[randJob];
        bool isIndependant = true;
        for (const auto& job: deps){
            if (included.find(job) == included.end()){
                isIndependant = false;
                break;
            }
        }
        if (isIndependant){
            schedule.push_back(randJob);
            included.insert(randJob);
        }
    }
    return schedule;
};

bool VNSScheduler::isValidSwap(std::vector<int>& schedule, Workflow& workflow, int Idx1, int Idx2){

    if (Idx1 == Idx2) return false;
    int IdxB = std::max(Idx1, Idx2);
    int IdxA = std::min(Idx1, Idx2);
    
    int jobA = schedule[IdxA];
    int jobB = schedule[IdxB];
    auto jobBDeps = workflow.dependenciesPerJob[jobB];
    if (jobBDeps.find(jobA) != jobBDeps.end()) return false;

    for (int i = IdxA + 1; i < IdxB; i++){
        int middleJob = schedule[i];
        auto middleJobDeps = workflow.dependenciesPerJob[middleJob];
        if (middleJobDeps.find(jobA) != middleJobDeps.end() || 
        jobBDeps.find(middleJob) != jobBDeps.end()){
            return false;
        }
    }
    return true;
};

int VNSScheduler::getDistanceFromX0(std::vector<int>& schedule, std::vector<int>& x0JobToIdx){
    int distance = 0;
    for (int i = 0; i < schedule.size(); i++){
        int job = schedule[i];
        int IdxInX0 = x0JobToIdx[job];
        distance += std::abs(IdxInX0 - i);
    }
    return distance;
};

// get maxium possible distance between to vectors of size n.
// Distance is defined as the absolute distance between the index of each element in the first vector,
// compared to its index in the second vector, summed over all elements
// This is achieved when the one vecotr is the reverse of the second, and the distance between them
// can be expressed as an arithmetic series sum.
int VNSScheduler::getMaxPossibleDistance(int size){
    int total = 0;
    int term = (size + 1) % 2;
    while(term <= size - 1){
        total += term;
        term += 2;
    }
    return total * 2;
};

double VNSScheduler::getTotalTardiness(std::vector<int>& schedule, Workflow& workflow){
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

template<typename T>
std::string VNSScheduler::iterableToString(T& schedule){
        std::string strSchedule = "";
        for (const auto& job: schedule){
            strSchedule += (std::to_string(job) + ", ");
        }
        auto res = strSchedule.substr(0, strSchedule.length() - 2);
        return res;
    };

std::vector<int> VNSScheduler::stringToSchedule(std::string strSchedule){
    int commaIdx = strSchedule.find(',');
    std::vector<int> schedule;
    std::string word;
    while (commaIdx != std::string::npos){
        std::string word = strSchedule.substr(0, commaIdx);
        strSchedule.erase(0, commaIdx + 2);
        schedule.push_back(stoi(word));
        commaIdx = strSchedule.find(',');
    }
    word = stoi(strSchedule);
    return schedule;
};

void VNSScheduler::printAlgorithmState(int k, int i, int L, double best_g, double curr_g, std::vector<int>& pickedSchedule){
    std::cout<<"k: "<<k<<std::endl;
    std::cout<<"i: "<<i<<" out of "<< L <<std::endl;
    std::cout<<"best_tardiness: "<<best_g<<std::endl;
    std::cout<<"picked schedule tardiness: "<<curr_g<<std::endl;
    std::cout<<"picked schedule: ";
    for(int job: pickedSchedule){
        std::cout<<job<<", ";
    }
    std::cout<<std::endl;
    std::cout<<"-------------------------"<<std::endl;
};

