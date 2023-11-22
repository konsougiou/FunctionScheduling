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

    std::unordered_map<std::string, double> measuredProcessingTimePerType = {
        {"vii", 14.5901}, {"blur", 5.6323}, {"night", 18.5314},
        {"onnx" ,2.7707}, {"emboss", 1.6893}, {"muse", 10.3133}, 
        {"wave", 6.2833}
    };

    std::unordered_map<std::string, double> preSetProcessingTimePerType = {
        {"vii", 14.0}, {"blur", 5.0}, {"night", 18.0},
        {"onnx" ,3.0}, {"emboss", 2.0}, {"muse", 10.0}, 
        {"wave", 6.0}
    };

    std::unordered_map<int, double> tabuDueDates = {
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
        preSetProcessingTimePerType,
        tabuDueDates,
        tabuNodeNames);


    std::vector<int> x0 = {30, 29, 23, 10, 9, 14, 13, 12, 4, 20,
                            22, 3, 27, 28, 8, 7, 19, 21, 26, 18, 25,
                            17, 15, 6, 24, 16, 5, 11, 2, 1, 31};

    auto tabuScheduler = TabuScheduler();
    auto tabuSchedule = tabuScheduler.createSchedule(tabuWorkflow, x0, 10, 20, 1000, false);
    double totalTardiness = tabuScheduler.getTotalTardiness(tabuSchedule, tabuWorkflow);
    std::cout<< totalTardiness <<std::endl;
    for (int job: tabuSchedule){
        std::cout<< job << ", ";
    }
    std::cout << std::endl;
    std::cout << std::endl;


    //////
    //MEASURED TIMES
    //////


    Workflow measuredTimesTabuWorkflow = Workflow(
            tabuEdges, 
            measuredProcessingTimePerType,
            tabuDueDates,
            tabuNodeNames);

    double total = 0;
    for (auto pair: measuredTimesTabuWorkflow.processingTimes){
        total += pair.second;
    }
    std::cout<< "Completion time: " << total <<std::endl;

    auto measuredTabuSchedule = tabuScheduler.createSchedule(measuredTimesTabuWorkflow, x0, 8, 25, 1000, false);
    totalTardiness = tabuScheduler.getTotalTardiness(measuredTabuSchedule, measuredTimesTabuWorkflow);
    std::cout<< totalTardiness <<std::endl;
    for (int job: measuredTabuSchedule){
        std::cout<< job << ", ";
    }

    std::cout << std::endl;
    std::cout << std::endl;

    auto bestMeasuredTabuSchedule = tabuScheduler.createScheduleSweepParams(measuredTimesTabuWorkflow, x0, 1, 50, 0, 435, 250, true);
    for (int job: bestMeasuredTabuSchedule){
        std::cout<< job << ", ";
    }

    ////
    //TESTING
    ////

    std::unordered_map<std::string, double> testProcessingTimePerType = {
        {"vii", 10.0}, {"blur", 10.0}, {"night", 13.0},
        {"onnx" ,4.0}};

    std::unordered_map<int, double> testTabuDueDates = {
      {1, 4}, {2, 2}, {3, 1}, {4, 12}};

    std::unordered_map<int, std::string> testTabuNodeNames = {
        {1, "vii"}, {2, "blur"}, {3, "night"}, {4, "onnx"} 
    }; 
    std::vector<std::vector<int> > testTabuEdges;

    Workflow testTabuWorkflow = Workflow(
            testTabuEdges, 
            testProcessingTimePerType,
            testTabuDueDates,
            testTabuNodeNames);

    x0 = {2, 1, 4, 3};

    auto testTaboScheduler = TabuScheduler();
    //schedule = testTaboScheduler.createSchedule(testTabuWorkflow, x0, 10, 5, 20, true);
    //std::cout<< testTaboScheduler.getTotalTardiness(schedule, testTabuWorkflow) <<std::endl;
    // for (int job: schedule){
    //     std::cout<< job << ", ";
    // }


    return 0;
}