/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Erin Bailey(433.01) and Zach Miller(433.02)
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */

#include "scheduler_rr.h"
#include <deque>

/**
 * @brief Construct a new SchedulerRR object
 */
SchedulerRR::SchedulerRR(int time_quantum){
    this->time_quantum = time_quantum;
}

/**
 * @brief Destroy the SchedulerRR object
 */
SchedulerRR::~SchedulerRR() {}

/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void SchedulerRR::init(std::vector<PCB>& process_list) {
    for(PCB A: process_list){
        proc_li.push_back(A);
        count++;
        times.push_back({0,0});
    }
}

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerRR::print_results() {

    for(int i = 0; i < count; i++){
        int ttime = times.at(i).at(0);
        int wtime = times.at(i).at(0) - times.at(i).at(1);
        avg_turnaround += ttime;
        avg_wait += wtime;

        std::cout << "T" << i + 1 << " turn-around time = " << ttime << ", waiting time = " << wtime << std::endl;
    }

    avg_turnaround = avg_turnaround / count;
    avg_wait = avg_wait / count;
    std::cout << "Average turn-around time = " << avg_turnaround << ", Average waiting time = " << avg_wait << std::endl;

}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerRR::simulate() {
    while(proc_li.size() > 0){
        
        if(unsigned(time_quantum) < proc_li.front().burst_time){       // if burst time is longer than the quantum
            std::cout << "Running Process " << proc_li.front().name << " for " << time_quantum << " time units" << std::endl;
            elapsed_time += time_quantum;               // only record passage of the time quantum
            times.at(proc_li.front().id).at(1) += time_quantum;    //record the passage of 1 time_quantum in the i'th runtime
            proc_li.front().burst_time -= time_quantum;            //decrease the burst time by 1 time_quantum
            if(proc_li.front().burst_time > 0) proc_li.push_back(proc_li.front());     //push the PCB to the back of the queue if it still has bursttime remaining
        }else { //if the burst_time is less than the time_quantum
            std::cout << "Running Process " << proc_li.front().name << " for " << proc_li.front().burst_time << " time units" << std::endl;
            elapsed_time += proc_li.front().burst_time;    //record passage of remaining burst time
            times.at(proc_li.front().id).at(1) += proc_li.front().burst_time;    //record passage of remaining bursttime into the i'th runtime
            proc_li.front().burst_time = 0; //proc is done, make bursttime 0
            times.at(proc_li.front().id).at(0) = elapsed_time;
        }
        proc_li.pop_front();          // remove highest priority process from list
    }
}
