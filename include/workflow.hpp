#ifndef WORKFLOW_HPP
#define WORKFLOW_HPP

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>


class Workflow{

public:

    Workflow(
        std::vector<std::vector<int> > edges, 
        std::unordered_map<std::string, double> processingTimePerType,
        std::unordered_map<int, double> dueDates,
        std::unordered_map<int, std::string> nodeNames
        );
    // 0-indexed matrix
    std::vector<std::vector<int> > graph;

    std::unordered_map<int, std::string> nodeNames;

    std::unordered_map<int, double> dueDates;

    std::unordered_map<int, double> processingTimes;

    // In the constructor of the workflow, we find for each job, all the jobs in depends on.
    // Although this introduces an bigO(numJobs^2) memory cost in the worst case, it saves a 
    // lot of runtime during the algorithm execution
    std::unordered_map<int, std::unordered_set<int> > dependenciesPerJob;

    std::string getNodeType(int nodeNumber);

    void populateDependenciesPerJob();
};

#endif