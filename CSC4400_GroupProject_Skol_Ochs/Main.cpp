//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  Main.cpp          ASSIGNMENT #:  2            Grade: _________              *
//*                                                                                                   *
//*   PROGRAM AUTHOR:     _______________________          _________________________                  *
//*                           Brendan Ochs           &         Micaiah Skolnick                       *
//*                                                                                                   *
//*   COURSE #:  CSC 4060 11                            DUE DATE:  May 5, 2017                        *
//*                                                                                                   *
//*****************************************************************************************************
//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS:                 NEED TO FILL THIS IN ******************************************************** *
//*                                                                                                   *
//*   USER DEFINED                                                                                    *
//*    MODULES     : newPage - Prints a blank line for each blank space left on the page              *
//*                  Footer - Prints a footer to signify end of program output                        *
//*                  Header - Prints a header to signify start of program output                      *
//*                  getData - Data from the input file is read into the program                      *
//*                  main - Variables are declared, functions are called, and headers are printed     *
//*                  processData - Read each Op code character and perform the subsequent action.     *
//*                                                                                                   *
//*****************************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <string>
#include <sstream>
#include <math.h>
#include "Variables.h"
using namespace std;
//*****************************************************************************************************
void newPage(ofstream&dataOUT) {
        //File Name: Main.cpp
        //Primary: Micaiah Skolnick / Contributing Brendan Ochs
        //Date last revised: 05/12/17
        //Inserts line ends until the end of page is reached
	while (lineCount < LINESPERPAGE) {
		dataOUT << endl;
		lineCount++;
	}
	lineCount = 0; // Reset the line count to 0 for next page.
}
//*************************************  FUNCTION HEADER  *********************************************
void Header(ofstream &Outfile)
{       //File Name: Main.cpp
        //Primary: Micaiah Skolnick / Contributing Brendan Ochs
        //Date last revised: 05/03/17
		//Task - Prints the output preamble
		//Returns - Nothing
	Outfile << setw(35) << "Brendan Ochs & Micaiah Skolnick";
	Outfile << setw(17) << "CSC 40600";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(27) << "Spring 2017";
	Outfile << setw(30) << "Assignment #2" << endl;
	Outfile << setw(35) << "---------------------------------- - ";
	Outfile << setw(35) << "---------------------------------- - " << endl << endl;
	lineCount += 4;
	return;
}
//************************************* END OF FUNCTION HEADER  ***************************************
//*************************************  FUNCTION FOOTER  *********************************************
void Footer(ofstream &Outfile) {
		//File Name: Main.cpp
		//Primary: Micaiah Skolnick / Contributing Brendan Ochs
		//Date last revised: 05/03/17
        // Task - Prints the output salutation
        // Returns - Nothing
	Outfile << setw(35) << "-------------------------------- - " << endl;
	Outfile << setw(35) << " | END OF PROGRAM OUTPUT | " << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	lineCount += 4;
	return;
}
//*****************************************************************************************************
void computeStats() {
		//File Name: Main.cpp
		//Primary: Micaiah Skolnick / Contributing Brendan Ochs
		//Date last revised: 05/05/17
		// Task - Calculates all of the processing statistics
		// Returns - Nothing
	float totLTQwait=0, totSTQwait=0, totIOQwait=0, totCPUwait=0;
	for (int i = 0; i < job_count; i++) {
		totLTQwait += statList[i].ltqWait;
		totSTQwait += statList[i].stqWait;
		totIOQwait += statList[i].ioWait;
		totCPUwait += statList[i].cpuWait;
	}

	avgLTQwait = (float) totLTQwait / job_count;
	avgSTQwait = (float) totSTQwait / job_count;
	avgIOQwait = (float) totIOQwait / job_count;
	avgCPUwait = (float) totCPUwait / job_count;

	systemThroughput = (float)(job_count / system_clock) * 1000;
	cpuUtilization = (float)((system_clock-totCPUwait) / system_clock) * 100;

		//Calculations for extra credit one:
	for (int i = 0; i < job_count; i++) {
		interArrivals.sum += statList[i].interArrival;//add to the total of inter-arrival time
		jobLengths.sum += statList[i].length; //Add to the total of job lengths
		ioBursts.count += statList[i].IOburstCount; //Add to the IO burst count
		cpuBursts.count = ioBursts.count; //IO burst count and CPU burst count are the same thing
		for (int z = 0; z < statList[i].IOburstCount; z++) { //For each CPU burst
			cpuBursts.sum += statList[i].CPUBurst[z]; //Add this cpu burst to the total
			ioBursts.sum += statList[i].IOBurstLength; //Add to the total IO burst length
		}	
	}
	interArrivals.count = job_count; //set the counts for interarrivals and job lengths
	jobLengths.count = job_count;
		//Compute the averages for each bonus stat
	interArrivals.AVG = interArrivals.sum / interArrivals.count;
	jobLengths.AVG = jobLengths.sum / jobLengths.count;
	ioBursts.AVG = ioBursts.sum / ioBursts.count;
	cpuBursts.AVG = cpuBursts.sum / cpuBursts.count;
	//Sum all of the squares from the mean as first step of variance
	for (int i = 0; i < job_count; i++) {
		interArrivals.variance += (statList[i].interArrival
			- interArrivals.AVG)*(statList[i].interArrival - interArrivals.AVG);
		jobLengths.variance += (statList[i].length
			- jobLengths.AVG)*(statList[i].length - jobLengths.AVG);
		for (int z = 0; z < statList[i].IOburstCount; z++) { //For each CPU burst
			ioBursts.variance += (statList[i].IOBurstLength
				- ioBursts.AVG)*(statList[i].IOBurstLength - ioBursts.AVG);
			cpuBursts.variance += (statList[i].CPUBurst[z]
				- cpuBursts.AVG)*(statList[i].CPUBurst[z] - cpuBursts.AVG);
		}
	}
	interArrivals.variance /= interArrivals.count; //Compute last step of variance
	interArrivals.SD = sqrt(interArrivals.variance); //Calculate Standard Deviation
	jobLengths.variance /= jobLengths.count; //Compute last step of variance
	jobLengths.SD = sqrt(jobLengths.variance); //Calculate Standard Deviation
	ioBursts.variance /= ioBursts.count; //Compute last step of variance
	ioBursts.SD = sqrt(ioBursts.variance); //Calculate Standard Deviation
	cpuBursts.variance /= cpuBursts.count; //Compute last step of variance
	cpuBursts.SD = sqrt(cpuBursts.variance); //Calculate Standard Deviation
}
void printSummaryReport(ofstream &dataOUT) {
		//File Name: Main.cpp
		//Primary: Micaiah Skolnick / Contributing Brendan Ochs
		//Date last revised: 05/05/17
		// Task - Prints a summary of the statistics gathered for the chosen algorithm
		// Returns - Nothing
	dataOUT << "   Authors:                   Brendan Ochs and Micaiah Skolnick" << endl;
	dataOUT << "   Date Completed:                             May 05, 2017" << endl;
	dataOUT << "   Algorithm used:                First in first out (FIFO)" << endl; 
	dataOUT << "   Number of jobs processed:                      " << fixed<< setprecision(2) <<
		right << setw (9) << job_count << endl;
	dataOUT << "   Total time to complete the simulation:         " << fixed << setprecision(2) <<
		right << setw(9) << system_clock << endl;
    dataOUT << "   Total system time spent in context switching:  " << fixed << setprecision(2) <<
    right << setw(9) << contextSwitchTime << endl;
	dataOUT << "   CPU utilization rate:                          " << fixed << setprecision(2) <<
		right << setw(9) << cpuUtilization << endl;
    dataOUT << "   Average Response Time for all jobs:            " << fixed << setprecision(2) <<
    right << setw(9) << avgResponseTime << endl;
	dataOUT << "   Average Turnaround Time for all jobs:          " << fixed << setprecision(2) <<
        right << setw(9) << avgTurnAroundTime << endl;
	dataOUT << "   System Throughput per 1000 clock ticks:        " << fixed << setprecision(2) <<
		right << setw(9) << fixed <<
		setprecision(2) << systemThroughput << endl;
	dataOUT << "   Average LTQ wait time for all jobs:            " << fixed << setprecision(2) <<
		right << setw(9) << avgLTQwait << endl;
	dataOUT << "   Average STQ wait time for all jobs:            " << fixed << setprecision(2) <<
		right << setw(9) << avgSTQwait << endl;
	dataOUT << "   Average IOQ wait time for all jobs:            " << fixed << setprecision(2) <<
		right << setw(9) << avgIOQwait << endl << endl;

		//Print statistics for extra credit one
	dataOUT << "EXTRA CREDIT ONE:" << endl;
	dataOUT << "   Average of all inter arrival times:            " << fixed << setprecision(2) <<
		right << setw(9) << interArrivals.AVG << endl;
	dataOUT << "   Variance of all inter arrival times:           " << fixed << setprecision(2) <<
		right << setw(9) << interArrivals.variance << endl;
	dataOUT << "   Standard deviation of all inter arrival times: " << fixed << setprecision(2) <<
		right << setw(9) << interArrivals.SD << endl;
	dataOUT << "   Average of all job lengths:                    " << fixed << setprecision(2) <<
		right << setw(9) << jobLengths.AVG << endl;
	dataOUT << "   Variance of all job lengths:                   " << fixed << setprecision(2) <<
		right << setw(9) << jobLengths.variance << endl;
	dataOUT << "   Standard deviation of all job lengths:         " << fixed << setprecision(2) <<
		right << setw(9) << jobLengths.SD << endl;
	dataOUT << "   Average of all I/O bursts:                     " << fixed << setprecision(2) <<
		right << setw(9) << ioBursts.AVG << endl;
	dataOUT << "   Variance of all I/O bursts:                    " << fixed << setprecision(2) <<
		right << setw(9) << ioBursts.variance << endl;
	dataOUT << "   Standard deviation of all I/O bursts:          " << fixed << setprecision(2) <<
		right << setw(9) << ioBursts.SD << endl;
	dataOUT << "   Average of all CPU bursts:                     " << fixed << setprecision(2) <<
		right << setw(9) << cpuBursts.AVG << endl;
	dataOUT << "   Variance of all CPU bursts:                    " << fixed << setprecision(2) <<
		right << setw(9) << cpuBursts.variance << endl;
	dataOUT << "   Standard deviation of all CPU bursts:          " << fixed << setprecision(2) <<
		right << setw(9) << cpuBursts.SD << endl;

}
//************************************* END OF FUNCTION FOOTER  ***************************************
void getData() {
		//File Name: Main.cpp
		//Primary: Micaiah Skolnick / Contributing Brendan Ochs
		//Date last revised: 05/05/17
		// Task - Reads all of the data from input file into a job array
		// Returns - Nothing
	int i = 0, newJob = 0, burstLength = 0;
	dataIN >> ws >> newJob; // Seed read first job number
	while (newJob > 0) { //Read in jobs until the last negative value is reached
		jList[i].number = newJob;
		dataIN >> jList[i].length;
		dataIN >> jList[i].interArrival;
		dataIN >> jList[i].IOBurstLength;
		dataIN >> burstLength; //Seed read the first burst length
		int j = 0;
		while (burstLength > 0) {
			jList[i].CPUBurst[j]= burstLength;
			dataIN >> burstLength; // Read in the next burst length
			j++; //Increment the burst count
		}
		jList[i].IOburstCount = j; // Set the number of bursts to the number of loops
		
		i++; // Increment the job counter
		if (burstLength < 0) { //Burst length < 0 is sentinel
							   //Copy the job list into a list from which values will not be deleted
			for (int z = 0; z < i; z++) {
				statList[z] = jList[z];
			}
			jobcount = i;
			return; //Exit the function if a burst length of -1 is reached
		}
		dataIN >> ws >> newJob;
	}	
}
//*****************************************************************************************************
void  deleteJobFromQueue(jobType oldQueue[], int jobIndex, int &length){
		//File Name: Main.cpp
		//Primary: Micaiah Skolnick / Contributing Brendan Ochs
		//Date last revised: 05/05/17
		// Task    - delete a job from a queue
		// Returns - Nothing
	if (length == 1) { //If there is only one job in the Q, move it to the front
		oldQueue[0] = oldQueue[1];
	}
	for (int i = jobIndex; i < length-1; i++) { //delete job from queue
		oldQueue[i] = oldQueue[i + 1];
	}
	length--; //Decrement the Q length
	jobType newJob;
	oldQueue[length] = newJob; //Replace the job at the end of the Q with a new job

}
//*****************************************************************************************************
void addJobToQueue(jobType newQueue[], jobType newJob, int &length){
		//File Name: Main.cpp
		//Primary: Micaiah Skolnick / Contributing Brendan Ochs
		//Date last revised: 05/05/17 
		// Receives- old job, new job, and Q length
		// Task    - add a new job to the end of a queue
		// Returns - Nothing
	newQueue[length] = newJob;
	length++;
}
void addThenDelete(jobType newQueue[],int &newLength,jobType oldQueue[],int &oldLength, int jobIndex) {
		// Receives- Q from which job is going and coming, Q lengths, and job number
		// Task    - Add a new job to one queue and delete it from the other
		// Returns - Nothing
	addJobToQueue(newQueue, oldQueue[jobIndex], newLength);
	deleteJobFromQueue(oldQueue, jobIndex, oldLength);
}
//*****************************************************************************************************
void addJobToSystem() {
		//File Name: Main.cpp
		//Primary: Micaiah Skolnick / Contributing Brendan Ochs
		//Date last revised: 05/05/17
		// Receives � Nothing
		// Task - If job has arrived, adds it to the system
		// Returns - A bool to indicate whether a job was added to the system	
	job_timer++; //Increment job timer
	if (jList[0].interArrival == job_timer) { //If a job has arrived
		job_flag = true; //Signal LTQ of job arrival
		statList[jList[0].number-1].arrivalTime = system_clock;  //Record time of arrival
		job_timer = 0; //Reset job_timer to zero
		job_count++; //Increment count (Total number of jobs ran)
		more_jobs++; //Increment more_jobs (Number of jobs in the system)
		return; //If a job was added, return true
	}
}
//*****************************************************************************************************
void manageLTQ() {
		//File Name: Main.cpp
		//Primary: Micaiah Skolnick / Contributing Brendan Ochs
		//Date last revised: 05/05/17	
		// Receives � Nothing
		// Task - Manages the Long Term Q
		// Returns - Nothing		
	if (!ltq_empty) { //If the LTQ is not empty
			//Increment the wait counters for all processes in the queue.
		for (int i = 0; i < ltqCount; i++) {
			statList[LTQ[i].number-1].ltqWait++;
		}
	}
	if (job_flag && !ltq_full) { //If there is a job to enter, and the ltq is not full
		addThenDelete(LTQ, ltqCount, jList, jobcount, 0);//put the incoming job(s) in the queue
		job_flag = false;//set job_flag to false
		ltq_empty = false; //set ltq_empty to false
	}
	if (ltqCount == MAXALLOWEDINLTQ) //If the ltq que is full then set ltq_full to true
	{
		ltq_full = true;
	}
}
//*****************************************************************************************************
void manageSTQ() {
		//File Name: Main.cpp
		//Primary: Micaiah Skolnick / Contributing Brendan Ochs
		//Date last revised: 05/05/17
		// Receives � Nothing
        // Task - Manages the Short Term Q
        // Returns - Nothing
    if (!stq_empty){ //If stq is not empty
			//increment wait counters for all processes in the queue
		for (int i = 0; i < stqCount; i++) {
			statList[STQ[i].number-1].stqWait++;
		}
    }
	if (io_complete_flag)           //if io_complete_flag is true
	{
		io_complete_flag = false;   //reset io_complete_flag to false
		io_device_flag = true;      //set io_device_flag to true
		if (finished_flag)          //if finished flag is true
		{
			more_jobs--;            //decrement more jobs (remove job from system)
			finished_flag = false;
			//collect data
		}
		else if (!stq_full)         //if STQ is not full
		{
			addThenDelete(STQ, stqCount, IOQ, ioqCount, 0); //place process in the stq
			device = 0; //set device = 0
			if (stqCount == MAXALLOWEDINSTQ) { //If the count = the max allowed
				stq_full = true;
			}
		}
	}
    if(stqCount < MAXALLOWEDINSTQ-1 && !ltq_empty) //if stq is not full, and ltq is not empty
    {
		addThenDelete(STQ, stqCount, LTQ, ltqCount, 0);	//move process from LTQ to STQ
        stq_empty = false; //Set STQ empty to false to indicate that there is now a process in STQ
		if (ltqCount == 0){ //If the LTQ is empty, indicate it
            ltq_empty = true;
            ltq_full = false;
        }
        if (stqCount == MAXALLOWEDINSTQ) { //If the stq is full, indicate it
            stq_full = true;
        }
    }
}
//*****************************************************************************************************
void manageCPU() {
		//File Name: Main.cpp
		//Primary: Brendan Ochs / Contributing Micaiah Skolnick
		//Date last revised: 05/04/17
        //Receives � Nothing
        //Task - Manages the CPU
        //Returns - Nothing    
    if (suspend_flag) //if suspend_flag is true
	{
        suspend_timer--; //decrement suspend timer
        if(suspend_timer == 0) //if suspend_timer is 0
        {
            interrupt_flag = false; //set interrupt_flag to false
            suspend_flag = false; //set suspend_flag to false
        }
        else if (temp == process) //A process is in CPU when interrupt occurred
        {
			statList[process].cpuWait++;//increment CPU wait counter
            stop_flag = true;   //set stop_flag to true
        }
    }
    if (!stop_flag)  //if stop_flag is false
    {
        if(interrupt_flag)                      //if interrupt_flag is true
        {
            if(suspend_timer == 0)              //if suspend_timer equals 0
            {
                if(cpu > 0)                     //if cpu is greater than 0
                {
                    temp = cpu;                 //set temp equal to cpu
                    cpu = 0;                    //set cpu equal to 0
                }
                suspend_timer = 3;              //set suspend_timer equal to 3
                suspend_flag = true;           //set suspend timer to true
            }
        }
        else
        {
			if (cpu == process) //if cpu equals process
			{
				process_timer++;                    //increment process_timer
				if (process_timer == STQ[0].CPUBurst[0]) //if processtimer equals cpu burst length
				{
					for (int i = 0; i < STQ[0].IOburstCount; i++) { //Delete the cpu burst from list
						STQ[0].CPUBurst[i] = STQ[0].CPUBurst[i+1];
					}
					cpu_complete_flag = true;       //set cpu_complete_flag to true
					process_timer = 0;              //set process_timer equal to 0
				}
			}
            else{
				if(temp == process)         //if temp equals process
				{
					cpu = process;          //cpu equals process
					statList[process].cpuWait++;//increment CPU wait counter
					temp = 0;               //set temp equal to 0
				}
				else
				{
					if(!stq_empty && cpu_ready_flag) //if stq_empty false and cpu_ready_flag true
					{
                        contextSwitchTime = contextSwitchTime+2; // add context switch time
						process = STQ[0].number; //set process equal to the head of the STQ
						cpu = process;      //set cpu equal to process
						deleteJobFromQueue(STQ, 0, stqCount); //delete job from queue
						stq_full = false;   //set stq_full to false
						if(stqCount==0) //if STQ is now empty
						{
							stq_empty = true;    //set stq_empty to true							
						}
						cpu_ready_flag = false;  //set cpu_ready_flag to false
						process_timer = 0;       //set process_timer equal to 0
					}
				}                
            }
        }
    }
    stop_flag = false; //set stop_flag equal to false
}
//*****************************************************************************************************
void manageIOQ() {
		//File Name: Main.cpp
		//Primary: Brendan Ochs / Contributing Micaiah Skolnick
		//Date last revised: 05/04/17
        // Receives � Nothing
        // Task - Manages the Input Output Q
        // Returns - Nothing    
	if (!ioq_empty)                      //if ioq_empty is false
	{
		for (int i = 0; i < ioqCount; i++){//increment IOQ wait counter for all processes in the queue
			statList[IOQ[i].number-1].ioWait++; //Increment the io wait counter in the statistic list
		}
	}        
	if (cpu_complete_flag) {               //if cpu_complete_flag is true
		if (!ioq_full)                   //if ioq_full is false
		{
			addThenDelete(IOQ, ioqCount, STQ, stqCount, 0); //add the process to the tail of the queue
			cpu = 0;                    //set cpu equal to 0
			ioq_empty = false;          //set ioq_empty to false
			cpu_ready_flag = true;      //set cpu ready flag to true
			if (ioqCount == MAXALLOWEDINIOQ)   //if the queue is full
			{
				ioq_full = true;        //set ioq_full equal to true				
			}
			cpu_complete_flag = false;  //set cpu_complete_flag to false
		}
	}
}
//*****************************************************************************************************
void manageIODevice() {
		//File Name: Main.cpp
		//Primary: Brendan Ochs / Contributing Micaiah Skolnick
		//Date last revised: 05/05/17
        // Receives � Nothing
        // Task - Manages the IO device
        // Returns - Nothing   
    if (!interrupt_flag)                        //if interrupt_flag equal to false
    {
        if (device == ioprocess)               //if device is equal to ioprocess
        {
            io_timer++; //Increment the IO timer
            if (io_timer == IOQ[0].IOBurstLength)//If io timer is equal to IOBurst LENGTH
            {
                io_complete_flag = true; //set io_complete_flag to true
                device = 0; //set device equal to 0
				if (IOQ[0].CPUBurst[0] > 0)//if the next cpu burst length is <> 0
				{
					interrupt_flag = true; //set interrupt_flag to true
				}          
				else {
					finished_flag = true; //set finished flag to true
				}
            }
        }
        else{
            if (!ioq_empty && io_device_flag)   //if ioq_empty is false and iodevice flag is true
			{
				ioprocess = IOQ[0].number; //set ioprocess equal to head of the IOQ
                device = process; //set device equal to process
				deleteJobFromQueue(IOQ, 0, ioqCount); //delete job from the queue
                if(ioqCount == 0) //if the IOQ is now empty
				{
					ioq_empty = true; //set ioq_empty to true
				}
				io_timer = 0; //set io_timer equal to 0
				io_device_flag = false; //set io_device_flag to false
            }
        }
    }
}

//*****************************************************************************************************

void turnAroundClock()
{
            //File Name: Main.cpp
            //Primary: Micaiah Skolnick / Contributing Brendan Ochs
            //Date last revised: 05/04/17
            // Receives-  LTQcount, STQcount, IOQcount
            // Task    - increment all clocks while in the system
            // Returns - turnAroundTime
    
    avgTurnAroundTime += ltqCount;
    avgTurnAroundTime += stqCount;
    avgTurnAroundTime += ioqCount;
    avgTurnAroundTime += currentJob;
    
}
//*****************************************************************************************************

void responceTime()
{
            //File Name: Main.cpp
            //Primary: Micaiah Skolnick / Contributing Brendan Ochs
            //Date last revised: 05/04/17
            // Receives-  ltqcount, stqcount, ioqcount, avgResponce time
            // Task    - add up reponce times
            // Returns - total responce time
    
    avgResponseTime += ltqCount;
    avgResponseTime += stqCount;
    
}
//*****************************************************************************************************
int main() {
		//File Name: Main.cpp
		//Primary: Micaiah Skolnick / Contributing Brendan Ochs
		//Date last revised: 05/04/17
        // Receives � Nothing
        // Task - Call each necessary function of the program in order
        // Returns - Nothing
	getData(); //Retrieve data from input file
	addJobToSystem(); //Get a job into the system
    totalJobs = jobcount;
	while (jList[0].number!=-999){ // While jobs to process
        
		manageLTQ(); //manage the Long Term Q
		manageSTQ(); //manage the short term Q
		manageCPU(); //manage the CPU
		manageIOQ(); //manage the IO Queue
		manageIODevice(); //manage the IO device
		addJobToSystem(); //Get a job into the system
		system_clock++; //Increment the clock
        turnAroundClock();  // add time to turnaround and get turn avg turn around
        responceTime();     // add time to responce time
	}
    avgTurnAroundTime = avgTurnAroundTime/totalJobs; //calculate avg turn around time
    avgResponseTime = avgResponseTime/totalJobs; //calculate avg responce time
	computeStats(); //Compute all of the statistical data
	Header(dataOUT5); //Print a data header
	printSummaryReport(dataOUT5); //Print a report of stat. data
	Footer(dataOUT5); //Print footer. 
	dataIN.close(); //Close input data file. 
	dataOUT5.close(); //Close output data file.
	return 0;
}
