#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//function prototype to validate if input has character.
int haschar(char chararr[], int sizearr);

// Function to find the waiting time for all 
// processes = array contain process id
// n =  number of element in the array
// waitingTime = array to store wait time 
// burstTime = array to store bursting time
void findWaitingTime(int processes[], int n, 
             int burstTime[], int waitingTime[], int quantum) 
{ 
    // Make a copy of burst times burstTime[] to store remaining 
    // burst times. 
    int remainingBurstTime[n]; 
    for (int i = 0 ; i < n ; i++) 
        remainingBurstTime[i] =  burstTime[i]; 
  
    int t = 0; // Current time 
  
    // Keep traversing processes in round robin manner 
    // until all of them are not done. 
    while (1) 
    { 
        int done = 1; 
  
        // Traverse all processes one by one repeatedly 
        for (int i = 0 ; i < n; i++) 
        { 
            // If burst time of a process is greater than 0 
            // then only need to process further 
            if (remainingBurstTime[i] > 0) 
            { 
                done = 0; // There is a pending process 
  
                if (remainingBurstTime[i] > quantum) 
                { 
                    // Increase the value of t i.e. shows 
                    // how much time a process has been processed 
                    t += quantum; 
  
                    // Decrease the burst_time of current process 
                    // by quantum 
                    remainingBurstTime[i] -= quantum; 
                } 
  
                // If burst time is smaller than or equal to 
                // quantum. Last cycle for this process 
                else
                { 
                    // Increase the value of t i.e. shows 
                    // how much time a process has been processed 
                    t = t + remainingBurstTime[i]; 
  
                    // Waiting time is current time minus time 
                    // used by this process 
                    waitingTime[i] = t - burstTime[i]; 
  
                    // As the process gets fully executed 
                    // make its remaining burst time = 0 
                    remainingBurstTime[i] = 0; 
                } 
            } 
        } 
  
        // If all processes are done 
        if (done == 1) 
          break; 
    } 
} 
  
// Function to calculate turn around time 
void findTurnAroundTime(int processes[], int n, 
                        int burstTime[], int waitingTime[], int turnAroundTime[]) 
{ 
    // calculating turnaround time by adding 
    // burstTime[i] + waitingTime[i] 
    for (int i = 0; i < n ; i++) 
        turnAroundTime[i] = burstTime[i] + waitingTime[i]; 
} 
  
// Function to calculate average time 
void findavgTime(int processes[], int n, int burstTime[], 
                                     int quantum) 
{ 
    int waitingTime[n], turnAroundTime[n], totalWaitingTime = 0, totalTurnAroundTime = 0; 
  
    // Function to find waiting time of all processes 
    findWaitingTime(processes, n, burstTime, waitingTime, quantum); 
  
    // Function to find turn around time for all processes 
    findTurnAroundTime(processes, n, burstTime, waitingTime, turnAroundTime); 
  
    // Display processes along with all details 
    printf("Processes, Burst time, Waiting time, Turn around time\n");
  
    // Calculate total waiting time and total turn 
    // around time 
    for (int i=0; i<n; i++) 
    { 
        totalWaitingTime = totalWaitingTime + waitingTime[i]; 
        totalTurnAroundTime = totalTurnAroundTime + turnAroundTime[i]; 
        printf(" %d \t\t %d\t %d\t\t %d\n",i+1,burstTime[i],waitingTime[i],turnAroundTime[i]);
    } 
  
    printf("Time quantum = %d\n",quantum);
    printf("Average waiting time = %.2f",(float)totalWaitingTime / (float)n);
    printf("\nAverage turn around time = %.2f",(float)totalWaitingTime / (float)n);
} 
  
// Driver code 
int main()
{ 
    int num_processes, i, quantum = 0;
    char chrarr1[10], chrarr2[10], chrarr3[10];

    // get user desired number of process and time quantum
    printf("Set number of processes.\n");
    gets(chrarr1);
    
    printf("Set time quantum.\n");
    gets(chrarr2);

    //input output error handling
    //make sure num of process and quantum more than 0 and inputs does not contain character
    //atoi converts string to int
    while(atoi(chrarr1) <= 0 || atoi(chrarr2) <= 0 || haschar(chrarr1, strlen(chrarr1)) || haschar(chrarr2, strlen(chrarr2))){
        printf("Number of processes and time quantum must be positive and cannot contain character, please enter again.\n");
        printf("Number of processes: \n");
        gets(chrarr1);
        printf("Time quantum: \n");
        gets(chrarr2);
    }

    //convert string into int
    num_processes = atoi(chrarr1);
    quantum = atoi(chrarr2);

    int processes[num_processes]; 

    //get number of element in the array
    int n = sizeof processes / sizeof processes[0];  
  
    // Burst time of all processes 
    int burst_time[num_processes];

    for (i=0; i < num_processes; i++)
    {
        printf("Set burst times for process %d .\n",i+1);
        gets(chrarr3);

        //make sure burst time more than 0 and does not have character
        while(atoi(chrarr3) <= 0 || haschar(chrarr3, strlen(chrarr3))){
            printf("Burst time must be positive and cannot contain character, please enter again.\n");
            printf("Set burst times for processe %d .\n",i+1);
            gets(chrarr3);
        }
        burst_time[i] = atoi(chrarr3);
    }

    findavgTime(processes, n, burst_time, quantum); 
    return 0; 
} 

//validates of input has character
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