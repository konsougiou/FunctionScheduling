#include <iostream>
#include "../include/tabuScheduler.hpp"
#include "../include/vnsScheduler.h"
#include <iostream>
#include <chrono>




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
        {"vii", 14.4762}, {"blur", 5.4955}, {"night", 18.6060},
        {"onnx", 2.7349}, {"emboss", 1.6695}, {"muse", 10.3641}, 
        {"wave", 6.3114}
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
    std::vector<int> tabuSchedule = tabuScheduler.createSchedule(tabuWorkflow, x0, 10, 20, 1000, false);
    double totalTardiness = tabuScheduler.getTotalTardiness(tabuSchedule, tabuWorkflow);
    std::cout<<"EXERCISE 2.1 TABU SCHEDULE"<<std::endl;
    std::cout<<"best tardiness: ";
    std::cout<< totalTardiness <<std::endl;
    std::cout<<"Best Schedule: "<<std::endl;
    for (int job: tabuSchedule){
        std::cout<< job << ", ";
    }
    std::cout << std::endl;
    std::cout<<std::endl;


    //////
    //AZURE MEASURED TIMES
    //////


    Workflow measuredTimesWorkflow = Workflow(
            tabuEdges, 
            measuredProcessingTimePerType,
            tabuDueDates,
            tabuNodeNames);
    std::cout<<"EXERCISE 2.2 TABU SCHEDULE"<<std::endl;
    double total = 0;
    for (auto pair: measuredTimesWorkflow.processingTimes){
        total += pair.second;
    }


    // std::vector<int> measuredTabuSchedule = tabuScheduler.createSchedule(measuredTimesWorkflow, x0, 8, 25, 1000, false);
    // std::vector<int> tmpSchedule = {30, 20, 14, 19, 10, 4, 3, 23, 9, 8, 22, 21, 18, 7, 6, 17, 16, 29, 28, 27, 13, 26, 12, 25, 24, 5, 2, 15, 11, 1, 31};
    // totalTardiness = tabuScheduler.getTotalTardiness(tmpSchedule, measuredTimesWorkflow);
    // std::cout<< totalTardiness <<std::endl;
    // for (int job: measuredTabuSchedule){
    //     std::cout<< job << ", ";
    // }
    // std::cout<<std::endl;

    std::cout<<"Measured time schedule total duration: "<<total<<std::endl;

    std::cout<<  "Parameters; gamma: 0 to 50,  L: 0 to 435, K: 190" <<std::endl;
    auto bestMeasuredTabuSchedules = tabuScheduler.createSchedulesSweepParams(measuredTimesWorkflow, x0, 0, 50, 0, 435, 190, true);
    std::cout<< "Minimum tardiness: "<<tabuScheduler.getTotalTardiness(bestMeasuredTabuSchedules[0], measuredTimesWorkflow)<<std::endl;
    std::cout<<"Number of optimal schedules found: "<<std::endl;
    std::cout<< bestMeasuredTabuSchedules.size()<<std::endl;
    std::cout<<"Best schedules: "<<std::endl;
    for (auto schedule: bestMeasuredTabuSchedules){
        std::cout<< tabuScheduler.scheduleToString(schedule) << std::endl;
    }

    ////
    //VNS
    ////


    
    std::cout<<"EXERCISE 3.1 VNS SCHEDULE"<<std::endl;

    VNSScheduler vnsScheduler = VNSScheduler();

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> vnsOptimalSchedule = vnsScheduler.createSchedule(measuredTimesWorkflow, x0, 10, 1000, 1000, true);


    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout<<"minimum tardiness: ";
    std::cout<<vnsScheduler.getTotalTardiness(vnsOptimalSchedule, measuredTimesWorkflow)<< std::endl;
    std::cout<<"best schedule: "<<std::endl;
    for (const auto& job: vnsOptimalSchedule){
        std::cout<<job<<", ";
    }
    std::cout<<std::endl;


    std::cout<<"EXERCISE 3.3 VNS REFINED SCHEDULE"<<std::endl;
    start = std::chrono::high_resolution_clock::now();

    std::vector<int> vnsOptimalRefinedSchedule = vnsScheduler.createScheduleRefined(measuredTimesWorkflow, x0, 10, 1000, 1000, 3);

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    //Output results
    //std::cout << "Execution time: " << duration << " microseconds" << std::endl;
    std::cout<<"Minimum refined VNS tardiness: ";
    std::cout<<vnsScheduler.getTotalTardiness(vnsOptimalRefinedSchedule, measuredTimesWorkflow)<< std::endl;
    std::cout<<"best refined schedule: "<<std::endl;
    for (const auto& job: vnsOptimalRefinedSchedule){
        std::cout<<job<<", ";
    }
    std::cout<<std::endl;

    std::cout<<"EXERCISE 3.3 VNS SWEEPING PARAMETERS"<<std::endl;

    std::cout<<  "Parameters; L: 1 to 10,  refineAttempts: 0 to 3, maxIters: 1000" <<std::endl;
    auto bestVNSSchedules = vnsScheduler.createSchedulesSweepParams(measuredTimesWorkflow, x0, 0, 10, 500, 1000, 0, 3,  true);
    std::cout<< "Minimum tardiness: "<<vnsScheduler.getTotalTardiness(bestVNSSchedules[0], measuredTimesWorkflow)<<std::endl;
    std::cout<<"Number of optimal schedules found: "<<std::endl;
    std::cout<< bestVNSSchedules.size()<<std::endl;
    std::cout<<"Best schedules: "<<std::endl;
    for (auto schedule: bestVNSSchedules){
        std::cout<< vnsScheduler.iterableToString(schedule) << std::endl;
    }

    return 0;
}