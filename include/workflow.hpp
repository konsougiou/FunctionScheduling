#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>


class Workflow{

public:

    Workflow(
        // 0-indexed matrix
        std::vector<std::vector<int> > edges, 
        std::unordered_map<std::string, int> processingTimePerType,
        std::unordered_map<int, int> dueDates,
        std::unordered_map<int, std::string> nodeNames
        );

    std::vector<std::vector<int> > graph;

    std::unordered_map<int, std::string> nodeNames;

    std::unordered_map<int, int> dueDates;

    std::unordered_map<int, int> processingTimes;

    std::unordered_set<int> completedJobs;

    std::string getNodeType(int nodeNumber);
};