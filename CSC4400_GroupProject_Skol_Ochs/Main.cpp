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
#include "Variables.h"
using namespace std;
//*****************************************************************************************************
void newPage(ofstream&dataOUT) {
        // Receives � the output file
        // Task - Insert blank lines to fill the rest of the current page
        // Returns - Nothing
        //Insert line ends until the end of page is reached
	while (lineCount < LINESPERPAGE) {
		dataOUT << endl;
		lineCount++;
	}
	lineCount = 0; // Reset the line count to 0 for next page.
}
//*************************************  FUNCTION HEADER  *********************************************
void Header(ofstream &Outfile)
{       // Receives � the output file
		// Task - Prints the output preamble
		// Returns - Nothing
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
        // Receives � the output file
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
	// Receives � Nothing
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

}
void printSummaryReport(ofstream &dataOUT) {
		// Receives � Nothing
		// Task - Prints a summary of the statistics gathered for the chosen algorithm
		// Returns - Nothing
	dataOUT << "   Authors: Brendan Ochs and Micaiah Skolnick" << endl;
	dataOUT << "   Algorithm used:                                First in first out (FIFO)" << endl; 
	dataOUT << "   Number of jobs processed:                      " << job_count << endl;
	dataOUT << "   Total time to complete the simulation:         " << system_clock << endl;
	dataOUT << "   Total system time spent in context switching:  ?????" << endl;
	dataOUT << "   CPU utilization rate:                          " << cpuUtilization << endl;
	dataOUT << "   Average Response Time for all jobs:            ?????" << endl;
	dataOUT << "   Average Turnaround Time for all jobs:          ?????" << endl;
	dataOUT << "   System Throughput per 1000 clock ticks:        " << systemThroughput << endl;
	dataOUT << "   Average LTQ wait time for all jobs:            " << avgLTQwait << endl;
	dataOUT << "   Average STQ wait time for all jobs:            " << avgSTQwait << endl;
	dataOUT << "   Average IOQ wait time for all jobs:            " << avgIOQwait << endl;
	lineCount += 11; //Increment the line count for each printed line

}
//************************************* END OF FUNCTION FOOTER  ***************************************
void getData() {
		// Receives � Nothing
		// Task - Reads all of the data from input file into a job array
		// Returns - Nothing
	int i = 0, newJob = 0, burstLength = 0;
	dataIN >> ws >> newJob; // Seed read first job number
	while (newJob > 0) { //Read in jobs until the last negative value is reached
		jList[i].number = newJob;
		dataIN >> jList[i].length;
		dataIN >> jList[i].interArrival;
		dataIN >> jList[i].IOBurst;
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
		// Receives- Job from which queue is coming, job number, length of que
		// Task    - delete a job from the queue
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
        // Receives � Nothing
        // Task - Manages the CPU
        // Returns - Nothing    
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
                    temp = cpu;                 //set temp equal to 0
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
					//I set this to the first CPU Burst but I don't think it's right ************************************
				{
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
        // Receives � Nothing
        // Task - Manages the IO device
        // Returns - Nothing   
    if (!interrupt_flag)                        //if interrupt_flag equal to false
    {
        if (device == ioprocess)               //if device is equal to ioprocess
        {
            io_timer++; //Increment the IO timer
            if (io_timer == IOQ[0].currentIOBurst)//If io timer is equal to IOBurst LENGTH
            {
                io_complete_flag = true; //set io_complete_flag to true
                device = 0; //set device equal to 0
				if (IOQ[0].CPUBurst[io_timer + 1] > 0)//if the next cpu burst length is <> 0
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
				ioprocess = 0; //set ioprocess equal to head of the IOQ
                device = process; //set device equal to process
				deleteJobFromQueue(IOQ, 0, ioqCount);	//delete job from the queue
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
void removeFinished() {
        // Receives � Nothing
        // Task - Removes finished processes
        // Returns - Nothing

}

//*****************************************************************************************************




//*****************************************************************************************************

void takeJobOutOfSystem()
{
        // Receives--------------------------
        // Task    - take job out of the sytem
        // Returns --------------------------
}

//*****************************************************************************************************


//*****************************************************************************************************

void processData()
{
        // Receives--------------------------
        // Task    - process the data
        // Returns --------------------------
}

//*****************************************************************************************************
int main() {
        // Receives � Nothing
        // Task - Call each necessary function of the program in order
        // Returns - Nothing
	//Header(dataOUT);// Print data header.

	/*1.  Initialize variables
		**   	2.  Read in all processes from the input file.
		**   	3.  Enter the first process into the system.
		4.  Increment the clock
		5.  While(jobs are being processed)
		**       	4.1  Manage the LTQ
		**       	4.2  Manage the STQ
		**       	4.3  Manage the CPU
		**       	4.4  Manage the I / O Queue
		**       	4.5  Manage the I / O Device
		**       	4.6  Remove finished jobs
		4.7  Increment the clock
		**       	4.8  Check for incoming processes
		**   	6.  Process the accumulated data.
	*/	
	//dataOUT << "test output" << endl;
	getData(); //Retrieve data from input file

	addJobToSystem(); //Get a job into the system

	while (jList[0].number!=-999 || !ltq_empty || !stq_empty || !ioq_empty) { //While jobs to process
		manageLTQ(); //manage the Long Term Q
		manageSTQ(); //manage the short term Q
		manageCPU(); //manage the CPU
		manageIOQ(); //manage the IO Queue
		manageIODevice(); //manage the IO device
		removeFinished(); //remove finished jobs
		addJobToSystem(); //Get a job into the system
		system_clock++; //Increment the clock
	}
	computeStats(); //Compute all of the statistical data
	printSummaryReport(dataOUT5); //Print a report of stat. data
	Footer(dataOUT5); //Print footer. 
	dataIN.close(); //Close input data file. 
	dataOUT5.close(); //Close output data file.


	return 0;
}
