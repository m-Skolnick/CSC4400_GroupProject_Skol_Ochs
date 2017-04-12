//*****************************************************************************************************

//This file is used only to declare global variables so they are all in one location


int MAXLINECOUNT = 50;
int lineCount;
struct jobType {
	int number, length, arrival, IOBurst, CPUBurstLength[10], IOburstCount;

};
jobType jList[101];



//*****************************************************************************************************