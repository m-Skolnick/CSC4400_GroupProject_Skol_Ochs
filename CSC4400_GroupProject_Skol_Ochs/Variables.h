//*****************************************************************************************************

//This file is used only to declare global variables so they are all in one location

#ifndef VARIABLES_H
#define VARIABLES_H
using namespace std;

struct jobType {
	int number, length, arrival, IOBurst, CPUBurstLength[10], IOburstCount;

	//Added by Micaiah
	int waitCounter;

};


//Variables added by Micaiah
int lineCount = 0; //Intialize the line counter to 0
const int LINESPERPAGE = 54; //Set the max number of lines which fit on a page
const int MAXJOBNUMBER = 150; //Set the maximum number of jobs to 150
const int MAXALLOWEDINLTQ = 60; //Set the max num of jobs allowed in long term Q to 60
const int MAXALLOWEDINSTQ = 30;
const int MAXALLOWEDINIOQ = 30;

int currentJob = 0;//keeps track of which job is currently in the system
int system_clock = 0; //Keeps track of the system time

jobType jList[MAXJOBNUMBER]; //Declare and initialize the list of jobs
ifstream dataIN("Data_in.txt"); //Open the file containing data.
ofstream dataOUT("dataOUT.txt"); //Create and open the file to write data to.


//Variables given by Dr. Vandyke
int io_timer = 0; // Indicates the current I / O burst 
int job_timer = 0; // Keeps track of the time between job arrivals 
int more_jobs = 0; // Keeps track of the # of jobs in system 
int process_timer = 0; // Keeps track of the current CPU burst 
int suspend_timer = 0; // Keeps track of current interrupt time 
int cpu_ready_flag = true; //Signals that the CPU is available          
int cpu_complete_flag = false; //Signals the completion of a CPU burst      
int finished_flag = false; //Signals that a JOB is finished             
int interrupt_flag = false; //Signals that an interrupt is in progress   
int io_complete_flag = false; //Signals the completion of an I / O burst     
int io_device_flag = true; //Signals that the I / O device is available   
int job_flag = false; //Signals the a job has arrived              
int stop_flag = false; //Signals to stop CPU job processing         
int suspend_flag = false; //Signals context switch to handle interrupt 

int cpu = 0; //integer to indicate which job has the CPU.            
int job_count = 0; // keeps track of the number of processes ran 
int devise = 0; // integer to signal which process is in the I / O device 
int process = 1; //integer to indicate the process entering the CPU      
int ioprocess = 1; //integer to indicate the process entering the I / O device
int temp = 0; // integer to indicate which process is suspended 
int ioq_full = false; //Signals that the I / O Queue is full        
int ioq_empty = true; //Signals that the I / O Queue is empty       
int ltq_empty = true; //Signals that the Long Term Queue is empty 
int ltq_full = false; //Signals that the Long Term Queue is full  
int stq_empty = true; //Signals that the Short Term Queue is empty
int stq_full = false; //Signals that the Short term Queue is full 

#endif
//*****************************************************************************************************