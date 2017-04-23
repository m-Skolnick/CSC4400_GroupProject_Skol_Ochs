//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  Project2.cpp          ASSIGNMENT #:  2            Grade: _________          *
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
	// Receives – the output file
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
{       // Receives – the output file
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
	// Receives – the output file
	// Task - Prints the output salutation
	// Returns - Nothing
	Outfile << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	Outfile << setw(35) << " | END OF PROGRAM OUTPUT | " << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	lineCount += 4;
	return;
}
//************************************* END OF FUNCTION FOOTER  ***************************************
void getData() {
		// Receives – Nothing
		// Task - Reads all of the data from input file into a job array
		// Returns - Nothing
	int i = 0, newJob = 0, burstLength = 0;
	dataIN >> ws >> newJob; // Seed read first job number
	while (newJob > 0) { //Read in jobs until the last negative value is reached
		jList[i].number = newJob;
		dataIN >> jList[i].length;
		dataIN >> jList[i].arrival;
		dataIN >> jList[i].IOBurst;
		dataIN >> burstLength; //Seed read the first burst length
		int j = 0;
		while (burstLength > 0) {
			jList[i].CPUBurstLength[j]= burstLength;
			dataIN >> burstLength; // Read in the next burst length
			j++; //Increment the burst count
		}
		jList[i].IOburstCount = j; // Set the number of bursts to the number of loops
		if (burstLength < 0) {
			return; //Exit the function if a burst length of -1 is reached
		}
		i++; // Increment the job count
		dataIN >> ws >> newJob;
	}
}
//*****************************************************************************************************
bool addJobToSystem() {
	// Receives – Nothing
	// Task - If job has arrived, adds it to the system
	// Returns - A bool to indicate whether a job was added to the system

	if (jList[currentJob].arrival == job_timer) {
		job_flag = true;
		//Record time of arrival
		job_timer = 0; //Reset job_timer to zero
		job_count++; //Increment count
		more_jobs++; //Increment more_jobs
		return true; //If a job was added, return true
	}
	else {
		return false; //If a job wasn't added, return false
	}
}
//*****************************************************************************************************
void manageLTQ() {
	// Receives – Nothing
	// Task - Manages the Long Term Q
	// Returns - Nothing
	while (job_flag != 0) {//While there are jobs to process (not sure if this is right)
                            // It isnt in the Psuedocode she gave us. But we can cross this
                            // bridge when we get to it.

		if (ltq_empty == false) {
			//Increment the wait counters for all processes in the queue.
		}
		if (job_flag && !ltq_full) {
			//put the incoming job(s) in the queue
			job_flag = false;//set job_flag to false
			ltq_empty = false; //set ltq_empty to false
		}
		//If the ltq que is full then set ltq_full to true
	}
}
//*****************************************************************************************************
void manageSTQ() {
	// Receives – Nothing
	// Task - Manages the Short Term Q
	// Returns - Nothing
    if (!stq_empty)                 //if stq_empty is false
    {
        //increment wait counters for all processes in the que
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
        else if (!stq_full)         //if stq_full is false
        {
            //place process in the stq
            device = 0;//set device = 0
            if(STQ is full)            // This seems weird... but this is what her psuedocode says
            {
                stq_full = true;
                
            }
            
        }
        if(!stq_full && !ltq_empty) //if stq_full is false and ltq_empty is false
        {
            //move process from LTQ to STQ
            stq_empty = false;
            if (LTQ is now empty)
            {
                ltq_empty = true;
                ltq_full = false;
            }
            if (STQ is full)
            {
                stq_full = true;
            }
        }
    }
}
//*****************************************************************************************************
void manageCPU() {
	// Receives – Nothing
	// Task - Manages the CPU
	// Returns - Nothing

}
//*****************************************************************************************************
void manageIOQ() {
	// Receives – Nothing
	// Task - Manages the Input Output Q
	// Returns - Nothing

}
//*****************************************************************************************************
void manageIODevice() {
	// Receives – Nothing
	// Task - Manages the IO device
	// Returns - Nothing

}
//*****************************************************************************************************
void removeFinished() {
	// Receives – Nothing
	// Task - Removes finished processes
	// Returns - Nothing

}
//*****************************************************************************************************
int main() {
	// Receives – Nothing
	// Task - Call each necessary function of the program in order
	// Returns - Nothing		
	Header(dataOUT);// Print data header.

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
	getData(); //Retrieve data from input file
	addJobToSystem(); //Get a job into the system
	//while () { //While jobs are being processed //Not sure how you tell if jobs are being processed
		manageLTQ(); //manage the Long Term Q
		manageSTQ(); //manage the short term Q
		manageCPU(); //manage the CPU
		manageIOQ(); //manage the IO Queue
		manageIODevice(); //manage the IO device
		removeFinished(); //remove finished jobs
	//}
	system_clock++; //Increment the clock


	Footer(dataOUT); //Print footer. 
	dataIN.close(); //Close input data file. 
	dataOUT.close(); //Close output data file.


	return 0;
}
