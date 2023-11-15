#include "../include/workflow.hpp"


Workflow::Workflow(
        std::vector<std::vector<int> > edges, 
        std::unordered_map<std::string, int> processingTimePerType,
        std::unordered_map<int, int> dueDates,
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

            //Filling processingtimes hashMap
            for(int i = 0; i < numberOfNodes; i++){
                int nodeNumber = i + 1;
                std::string nodeType = getNodeType(nodeNumber);
                processingTimes[nodeNumber] = processingTimePerType[nodeType];
            }
    }

std::string Workflow::getNodeType(int nodeNumber){
    std::string nodeName = nodeNames[nodeNumber];
    size_t underscorePos = nodeName.find("_");
    return nodeName.substr(0, underscorePos);
}
