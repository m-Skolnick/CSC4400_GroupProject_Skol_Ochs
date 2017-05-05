//*****************************************************************************************************

//This file is used only to declare global variables so they are all in one location

#ifndef VARIABLES_H
#define VARIABLES_H
using namespace std;

struct jobType {
	int number=-999, length, interArrival, IOBurstLength, CPUBurst[25], IOburstCount;
	int arrivalTime; //Holds the time at which the job entered the system
	int exitTime; //Holds the time at which the job exited the system
	int ltqWait, stqWait, ioWait, cpuWait; //Wait counters for each queue
};

//Variables added by Micaiah
int lineCount = 0; //Intialize the line counter to 0
const int LINESPERPAGE = 54; //Set the max number of lines which fit on a page
const int MAXJOBNUMBER = 150; //Set the maximum number of jobs to 150
const int MAXALLOWEDINLTQ = 60; //Set the max num of jobs allowed in long term Q to 60
const int MAXALLOWEDINSTQ = 30;
const int MAXALLOWEDINIOQ = 30;

int jobcount = 0;  //keeps track of how many jobs are actually read in to jList[maxjobnumber].
int currentJob = 0;//keeps track of which job is currently in the system
int system_clock = 0; //Keeps track of the system time
int ltqCount = 0; //Keeps track of the number of jobs in the LTQ
int stqCount = 0; //Keeps track of the number of jobs in the STQ
int ioqCount = 0; //Keeps track of the number of jobs in the IOQ

//stats variables
int contextSwitchTime = 0; //total time spent context switching
float cpuUtilization = 0.0;
float avgResponseTime = 0.0; //avg responce time for all jobs
float avgTurnAroundTime = 0.0;  //avg turn aroung time for all jobs
float systemThroughput = 0.0;   //system throughput per 1000 clock ticks
float avgLTQwait = 0.0;     //average LTQ wait time
float avgSTQwait = 0.0;     //average STQ wait time
float avgIOQwait = 0.0;     //average IOQ wait time
float avgCPUwait = 0.0;     //average CPU wait time
float cpuBurstCount = 0.0; //Holds a count of all of the cpu bursts
struct bonusStatType {
	float total = 0, count = 0, AVG = 0, variance = 0, SD = 0;
};
bonusStatType interArrivals, jobLengths, ioBursts, cpuBursts;




jobType jList[MAXJOBNUMBER]; //Declare and initialize the list of jobs
jobType statList[MAXJOBNUMBER]; //Declare and initialize the list of jobs
jobType STQ[MAXALLOWEDINSTQ]; //Declare and initialize list of jobs for short term Q
jobType LTQ[MAXALLOWEDINLTQ]; //Declare and initialize list of jobs for long term Q
jobType IOQ[MAXALLOWEDINIOQ]; //Declare and initialize list of jobs for I/O Queue
ifstream dataIN("Data_in.txt"); //Open the file containing data.
ofstream dataOUT5("dataOUT5.txt"); //Create and open the file to write data to.

//Variables given by Dr. Vandyke

int io_timer = 0; // Indicates the current I / O burst 
int job_timer = 0; // Keeps track of the time between job arrivals 
int more_jobs = 0; // Keeps track of the # of jobs in system 
int process_timer = 0; // Keeps track of the current CPU burst 
int suspend_timer = 0; // Keeps track of current interrupt time 
bool cpu_ready_flag = true; //Signals that the CPU is available
bool cpu_complete_flag = false; //Signals the completion of a CPU burst
bool finished_flag = false; //Signals that a JOB is finished
bool interrupt_flag = false; //Signals that an interrupt is in progress
bool io_complete_flag = false; //Signals the completion of an I / O burst
bool io_device_flag = true; //Signals that the I / O device is available
bool job_flag = false; //Signals that a job has arrived
bool stop_flag = false; //Signals to stop CPU job processing
bool suspend_flag = false; //Signals context switch to handle interrupt

int cpu = 0; //integer to indicate which job has the CPU.            
float job_count = 0; // keeps track of the number of processes ran 
int device = 0; // integer to signal which process is in the I / O device
int process = 1; //integer to indicate the process entering the CPU      
int ioprocess = 1; //integer to indicate the process entering the I / O device
int temp = 0; // integer to indicate which process is suspended 
bool ioq_full = false; //Signals that the I / O Queue is full
bool ioq_empty = true; //Signals that the I / O Queue is empty
bool ltq_empty = true; //Signals that the Long Term Queue is empty
bool ltq_full = false; //Signals that the Long Term Queue is full
bool stq_empty = true; //Signals that the Short Term Queue is empty
bool stq_full = false; //Signals that the Short term Queue is full

#endif
//*****************************************************************************************************
