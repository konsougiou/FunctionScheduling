#include "../include/vnsScheduler.h"
#include <iostream>
#include <unordered_set>
#include <unordered_map>

// // recursive helper that populated all feasible solutions vector with schedules
// void VNSScheduler::topologicalSortHelper(Workflow& workflow, std::vector<int>& currSchedule, std::vector<std::vector<int>>& results, std::unordered_set<int>& visited,int size){
//     // for (const auto& res: results){
//     //     for (const auto& job: res){
//     //         std::cout<< job <<", ";
//     //     }
//     // std::cout<<std::endl;
//     // }
//     // std::cout<<"------------------------------"<<std::endl;


//     for (int job = 1; job <= size; job++){
//         if (visited.find(job) == visited.end()){
//             auto& dependencies = workflow.dependenciesPerJob[job];
//             bool hasDependency = false;
//             for (int otherJob = 1; otherJob <= size; otherJob++){
//                 //only concerned about unvisited jobs.
//                 if (visited.find(otherJob) != visited.end() || job == otherJob) continue;
//                 if (dependencies.find(otherJob) != dependencies.end()){
//                     hasDependency = true;
//                     break;
//                 }
//             }
//             if (!hasDependency){
//                 //Found job that can go next in schedule
//                 if (currSchedule.size() == size - 1){
//                     auto feasibleSchedule = currSchedule;
//                     feasibleSchedule.push_back(job);
//                     results.push_back(feasibleSchedule);
//                 }
//                 else{
//                     currSchedule.push_back(job);
//                     visited.insert(job);
//                     topologicalSortHelper(workflow, currSchedule, results, visited, size);
//                     currSchedule.pop_back();
//                     visited.erase(job);
//                 }
//             }
//         }
//     }
    
// };

// recursive helper that populated all feasible solutions vector with schedules
std::vector<std::vector<int>> VNSScheduler::topologicalSortHelper(Workflow& workflow, 
    std::unordered_set<int>& visited,
    std::unordered_set<int>& notVisited,
    std::unordered_map<std::string, std::vector<std::vector<int>>>& mem, int size){
    std::vector<std::vector<int>> res;
    if (notVisited.size() == 0){
        return res;
    }
    if (notVisited.size() == 1){
        int job = *notVisited.begin();
        std::vector<int> end = {job};
        res.push_back(end);
        return res;
    }

    //Convert current notVisited set into string of comma seperated jobs, so that
    //it can be uniquely hashed inside the mem map.
    std::vector<int> notVisitedVec(notVisited.begin(), notVisited.end());
    std::sort(notVisitedVec.begin(), notVisitedVec.end());
    auto strNotVisited = iterableToString(notVisitedVec);
    if (mem.find(strNotVisited) != mem.end()){
        return mem[strNotVisited];
    }

    for (int job = 1; job <= size; job++){
        if (notVisited.find(job) == notVisited.end()) continue;
        auto& dependencies = workflow.dependenciesPerJob[job];
        bool hasDependency = false;
        for (const auto otherJob: notVisited){
            if (job == otherJob) continue;
            if (dependencies.find(otherJob) != dependencies.end()){
                hasDependency = true;
                break;
            }
        }
        if (!hasDependency){
            if (notVisited.size() == size - 1){
                std::cout<<":"<<job<<std::endl;
            }
            else if (notVisited.size() == size - 2){
                std::cout<<" :"<<job<<std::endl;
            }
            else if (notVisited.size() == size - 3){
                std::cout<<"  :"<<job<<std::endl;
            }
            //Found job that can go next in schedule
            notVisited.erase(job);
            notVisitedVec.erase(std::remove(notVisitedVec.begin(), notVisitedVec.end(), job), notVisitedVec.end());
            auto strCurrSchedule = iterableToString(notVisitedVec);
            if (mem.find(strCurrSchedule) != mem.end()){
                auto subSchedules = mem[strCurrSchedule];
                for (auto& s: subSchedules){
                    s.insert(s.begin(), job);
                    res.push_back(s);
                }
            }
            else{
                auto subSchedules = topologicalSortHelper(workflow, visited, notVisited, mem, size);
                for (auto& s: subSchedules){
                    s.insert(s.begin(), job);
                    res.push_back(s);
                }
            }
            notVisited.insert(job);
        }
    }
    mem[strNotVisited] = res;
    return res;
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

std::vector<std::vector<int>> VNSScheduler::getAllFeasibleSchedules(Workflow& workflow){
        std::vector<std::vector<int>> feasibleSchedules;
        int size = workflow.graph.size();
        std::unordered_set<int> visited;
        std::unordered_set<int> notVisited;
        for (int job = 1; job <= workflow.graph.size(); job++) notVisited.insert(job);
        std::unordered_map<std::string, std::vector<std::vector<int>>> mem;
        std::vector<int> currSchedule;
        return topologicalSortHelper(workflow, visited, notVisited, mem, size);
    };

template<typename T>
std::string VNSScheduler::iterableToString(T& schedule){
        std::string strSchedule = "";
        for (const auto& job: schedule){
            strSchedule += (std::to_string(job) + ",");
        }
        auto res = strSchedule.substr(0, strSchedule.length() - 2);
        return res;
    }


