// C program for implementation of FCFS 
// scheduling 
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//function to validate if input has character.
int haschar(char chararr[], int len){
    int haschar = 0;
    int i = 0;

    while (len > 0 && isspace(chararr[len - 1])){
        len--;     // strip trailing newline or other white space
    }

    if (len > 0)
    {
        haschar = 0;
        for (i = 0; i < len; ++i)
        {
            if (!isdigit(chararr[i]))
            {
                haschar = 1;
                break;
            }
        }
    }

    return haschar;
}

// Function to find the waiting time for all 
// processes = array contain process id
// n = 	number of element in the array
// waitingTime = array to store wait time 
// burstTime = array to store bursting time 
void findWaitingTime(int processes[], int n, 
						int burstTime[], int waitingTime[]) 
{ 
	// waiting time for first process is 0 
	waitingTime[0] = 0; 
	
	// calculating waiting time (burstime + previous waiting time)
	// for loop doesnt start from 
	for (int i = 0; i < n ; i++ ) 
		waitingTime[i+1] = burstTime[i] + waitingTime[i] ; 
} 
	
// Function to calculate turn around time 
void findTurnAroundTime( int processes[], int n, 
				int burstTime[], int waitingTime[], int TurnAroundTime[]) 
{ 
	// calculating turnaround time by adding 
	// burstTime[i] + waitingTime[i] 
	for (int i = 0; i < n ; i++) 
	 TurnAroundTime[i] = burstTime[i] + waitingTime[i]; 
} 
	
//Function to calculate average time 
void findAverageTime( int processes[], int n, int burstTime[]) 
{ 
	int waitingTime[n], TurnAroundTime[n], totalWaitingTime = 0, totalTurnAroundTime = 0; 
	
	//Function to find waiting time of all processes 
	findWaitingTime(processes, n, burstTime, waitingTime); 
	
	//Function to find turn around time for all processes 
	findTurnAroundTime(processes, n, burstTime, waitingTime, TurnAroundTime); 
	
	//Display processes along with all details 
	printf("Processes | Burst time | Waiting time | Turn around time\n"); 
	
	// Calculate total waiting time and total turn 
	// around time 
	for (int i=0; i<n; i++) 
	{ 
		totalWaitingTime = totalWaitingTime + waitingTime[i]; 
		totalTurnAroundTime = totalTurnAroundTime + TurnAroundTime[i]; 
		printf(" %d ",(i+1)); 
		printf("	   %d ", burstTime[i] ); 
		printf("	        %d",waitingTime[i] ); 
		printf("	 	%d\n", TurnAroundTime[i] ); 
	} 
	float s = (float)totalWaitingTime / (float)n; 
	float t = (float)totalTurnAroundTime / (float)n; 
	printf("Average waiting time = %.2f",s); 
	printf("\n"); 
	printf("Average turn around time = %.2f ",t); 
} 
	
// Driver code 
int main() 
{ 
	int num_processes = 0, i = 0;
	char chrarr1[10], chrarr2[10];

	printf("Set number of processes.\n");
    gets(chrarr1);

    while(atoi(chrarr1) <= 0 || haschar(chrarr1, strlen(chrarr1)) ){
    	printf("Number of processes must be positive and cannot contain character, please enter again.\n");
    	printf("Number of processes: \n");
    	gets(chrarr1);
    }

    num_processes = atoi(chrarr1);

	int processes[num_processes];
	int burst_time[num_processes];

	for(i = 0; i < num_processes; i++)
	{
		printf("Set burst times for process %d .\n",i+1);
        gets(chrarr2);

        while(atoi(chrarr2) <= 0 || haschar(chrarr2, strlen(chrarr2))){
            printf("Burst time must be positive and cannot contain character, please enter again.\n");
        	printf("Set burst times for processes %d .\n",i+1);
        	gets(chrarr2);
        }
        burst_time[i] = atoi(chrarr2);
	}
	findAverageTime(processes, num_processes , burst_time); 
	return 0; 
} 
