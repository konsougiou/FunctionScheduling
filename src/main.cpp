#include <iostream>
#include "../include/tabuScheduler.hpp"


int main(){


    std::vector<std::vector<int> > tabuEdges = {
        {1, 31}, {2, 1}, {3, 8}, {4, 3}, {5, 2},
        {6, 16}, {7, 6}, {8, 7}, {9, 8}, {10, 9},
        {11, 1}, {12, 5}, {13, 12}, {14, 13}, {15, 11},
        {16, 5}, {17, 16}, {17, 15}, {18, 17}, {19, 18}, {20, 19},
        {21, 18}, {22, 21}, {23, 22}, {24, 5}, {25, 24},
        {26, 25}, {27, 26}, {28, 26}, {29, 28}, {30, 4},
        {30, 10}, {30, 14}, {30, 20}, {30, 23}, {29, 27},
        {30, 29}
    };

    std::unordered_map<std::string, int> tabuProcessingTimePerType = {
        {"vii", 14}, {"blur", 5}, {"night", 18},
        {"onnx" ,3}, {"emboss", 2}, {"muse", 10}, 
        {"wave", 6}
    };

    std::unordered_map<int, int> tabuDueDates = {
        {1, 172}, {2, 82}, {3, 18}, {4, 61}, {5, 93},
        {6, 71}, {7, 217}, {8, 295}, {9, 290}, {10, 287},
        {11, 253}, {12, 307}, {13, 279}, {14, 73}, {15, 355},
        {16, 34}, {17, 233}, {18, 77}, {19, 88}, {20, 122},
        {21, 71}, {22, 181}, {23, 340}, {24, 141}, {25, 209},
        {26, 217}, {27, 256}, {28, 144}, {29, 307}, {30, 329},
        {31, 269}
    };

    std::unordered_map<int, std::string> tabuNodeNames = {
        {1, "onnx_1"}, {2, "muse_1"}, {3, "emboss_1"}, {4, "emboss_2"}, {5, "blur_1"},
        {6, "emboss_3"}, {7, "vii_1"}, {8, "blur_2"}, {9, "wave_1"}, {10, "blur_3"},
        {11, "blur_4"}, {12, "emboss_4"}, {13, "onnx_2"}, {14, "onnx_3"}, {15, "blur_5"},
        {16, "wave_2"}, {17, "wave_3"}, {18, "wave_4"}, {19, "emboss_5"}, {20, "onnx_4"},
        {21, "emboss_6"}, {22, "onnx_5"}, {23, "vii_2"}, {24, "blur_6"}, {25, "night_1"},
        {26, "muse_2"}, {27, "emboss_7"}, {28, "onnx_6"}, {29, "wave_5"}, {30, "emboss_8"},
        {31, "muse_3"}
    };

    Workflow tabuWorkflow = Workflow(
        tabuEdges, 
        tabuProcessingTimePerType,
        tabuDueDates,
        tabuNodeNames);

    // for(auto pair: tabuWorkflow.dependenciesPerJob){
    //     std::cout<< "Job "<<pair.first<<": "<<std::endl;
    //     for (auto dep: pair.second){
    //         std::cout<<dep <<", ";
    //     }
    //     std::cout<<std::endl;
    // }

    std::vector<int> x0 = {30, 29, 23, 10, 9, 14, 13, 12, 4, 20,
                            22, 3, 27, 28, 8, 7, 19, 21, 26, 18, 25,
                            17, 15, 6, 24, 16, 5, 11, 2, 1, 31};

    auto taboScheduler = TabuScheduler();
    auto schedule = taboScheduler.createSchedule(tabuWorkflow, x0, 10, 20, 70);
    std::cout<< taboScheduler.getTotalTardiness(schedule, tabuWorkflow) <<std::endl;
    for (int job: schedule){
        std::cout<< job << ", ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    return 0;
};





