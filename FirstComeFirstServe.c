// C program for implementation of FCFS 
// scheduling 
#include<stdio.h>
#include <ctype.h> 
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
	int numberOfProcesses,i,varForWhileLoop;

	input:
	printf("Please enter number of processes:" );
	scanf("%d",&numberOfProcesses);
	printf("%d\n",numberOfProcesses );
	int processes[numberOfProcesses];
	int burst_time[numberOfProcesses];

	for(i = 0; i < numberOfProcesses; i++)
	{
		printf("Please enter burst time for process id number %d \n",i + 1 );
		scanf("%d",&burst_time[i]);			
	}
	findAverageTime(processes, numberOfProcesses , burst_time); 
	return 0; 

} 
