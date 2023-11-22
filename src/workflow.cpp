#include "../include/workflow.hpp"
#include <iostream>


Workflow::Workflow(
        std::vector<std::vector<int> > edges, 
        std::unordered_map<std::string, double> processingTimePerType,
        std::unordered_map<int, double> dueDates,
        std::unordered_map<int, std::string> nodeNames
        ): dueDates(dueDates), nodeNames(nodeNames){
            
            //Filling graph matrix
            int numberOfNodes = nodeNames.size();
            graph.resize(numberOfNodes, std::vector<int>(numberOfNodes, 0));
            for (auto egde: edges){
                // Subtracting 1 for zero indexing
                int from = egde[0] - 1;
                int to = egde[1] - 1;
                graph[from][to] = 1;
            }

            //Filling processingTimes hashMap
            for(int i = 0; i < numberOfNodes; i++){
                int nodeNumber = i + 1;
                std::string nodeType = getNodeType(nodeNumber);
                processingTimes[nodeNumber] = processingTimePerType[nodeType];
            }
            populateDependenciesPerJob();
    }

void Workflow::populateDependenciesPerJob(){
    std::unordered_set<int> firstLevel;
    for (int col_idx = 0; col_idx < graph.size(); col_idx++){
        bool foundParent = false;
        for (int row_idx = 0; row_idx < graph.size(); row_idx++){
            if(graph[row_idx][col_idx] == 1){
                foundParent = true;
                break;
            }
        }
        if (!foundParent) firstLevel.insert(col_idx + 1); // +1 to col to get job number
    }

    for(int job: firstLevel){
        dependenciesPerJob[job] = {};
    }
    auto currLevel = firstLevel;
    std::unordered_set<int> nextLevel;
    // This loop goes through the parent jobs in the current level, finds their children and
    // add the parent job, as well as it's dependencies to the childs dependencies.
    while (currLevel.size() != 0){
        for(int parent: currLevel){
            auto row = graph[parent - 1]; //  - 1 to get graph indexing
            // Search for current level job children
            for(int j = 0; j < row.size(); j++){
                int edge = row[j];
                if (edge == 1){
                    int child = j + 1;
                    nextLevel.insert(child);
                    auto parentDependencies = dependenciesPerJob[parent];
                    if (dependenciesPerJob.count(child)){
                        dependenciesPerJob[child].insert(parent);
                        dependenciesPerJob[child].insert(parentDependencies.begin(), parentDependencies.end());
                    }
                    else{
                        auto parentDependencies = dependenciesPerJob[parent];
                        dependenciesPerJob[child] = parentDependencies;
                        dependenciesPerJob[child].insert(parent);
                    }
                }
            }
        }
        currLevel = nextLevel;
        nextLevel.clear();
    }

}

std::string Workflow::getNodeType(int nodeNumber){
    std::string nodeName = nodeNames[nodeNumber];
    size_t underscorePos = nodeName.find("_");
    return nodeName.substr(0, underscorePos);
}
