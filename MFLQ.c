#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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

// Function to find the waiting time for all
// processes
void findWaitingTime(int processes[], int n,
             int bt[], int wt[], int quantum,int prt[])
{
    // Make a copy of burst times bt[] to store remaining
    // burst times.
    int rem_bt[n],j,counter,check;
    for (int i = 0 ; i < n ; i++)
        rem_bt[i] =  bt[i];

    int t = 0; // Current time

    // Keep traversing processes
    // until all of them are done.
    while (1)
    {
        int done = 1;

        // Traverse all processes one by one repeatedly
        for (int i = 0 ; i < n; i++)
        {
            // If burst time of a process is greater than 0
            // If priority is 1(not demoted)
            // then only need to process further
            if (rem_bt[i] > 0 && prt[i] == 1)
            {
                done = 0; // There is a pending process

                if (rem_bt[i] > quantum)
                {
                    // Increase the value of t i.e. shows
                    // how much time a process has been processed
                    t += quantum;

                    // Decrease the burst_time of current process
                    // by quantum
                    rem_bt[i] -= quantum;



                    //after allocated time quantum, process is demoted to queue 2
                    printf("process %d demoted to queue 2(FCFS).\n", i+1);
                    prt[i] = 2;
                }

                // If burst time is smaller than or equal to
                // quantum. Last cycle for this process
                else
                {
                    // Increase the value of t i.e. shows
                    // how much time a process has been processed
                    t = t + rem_bt[i];

                    // Waiting time is current time minus time
                    // used by this process
                    wt[i] = t - bt[i];

                    // As the process gets fully executed
                    // make its remaining burst time = 0
                    rem_bt[i] = 0;
                }
            }


            //FCFS
            //remaining processes are scheduled using first come first serve schedular.
            else if (rem_bt[i] > 0 && prt[i] == 2)
            {
                done = 0;
                // Increase the value of t i.e. shows
                // how much time a process has been processed
                t = t + rem_bt[i];

                // Waiting time is current time minus time
                // used by this process
                wt[i] = t - bt[i];

                // As the process gets fully executed
                // make its remaining burst time = 0
                rem_bt[i] = 0;
            }
        }
        if (done == 1){
          break;
        }
    }
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n,
                        int bt[], int wt[], int tat[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}

// Function to calculate average time
void findavgTime(int processes[], int n, int bt[],
                                     int quantum,int prt[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Function to find waiting time of all processes
    findWaitingTime(processes, n, bt, wt, quantum,prt);

    // Function to find turn around time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat);

    // Display processes along with all details
    printf("Processes, Burst time, Waiting time, Turn around time, Priority Level\n");

    // Calculate total waiting time and total turn
    // around time
    for (int i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("    %d \t\t%d\t   %d\t\t %d\t\t    %d\n",i+1,bt[i],wt[i],tat[i],prt[i]);
    }

    printf("Time quantum = %d\n",quantum);
    printf("Average waiting time = %.2f",(float)total_wt / (float)n);
    printf("\nAverage turn around time = %.2f\n\n",(float)total_tat / (float)n);
}

// Driver code
int main()
{

    int num_processes, i,quantum, process_priority;
    char chrarr1[10], chrarr2[10], chrarr3[10];

    // get user desired number of process and time quantum
    printf("Set number of processes.\n");
    gets(chrarr1);

    printf("Set time quantum.\n");
    gets(chrarr2);

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
    int priorities[num_processes];

    for (i=0; i < num_processes; i++)
    {
        // printf("Set burst times for processes %d .\n",i+1);
        // scanf("%d",&burst_time[i]);
        printf("Set burst times for process %d .\n",i+1);
        gets(chrarr3);

        //make sure burst time more than 0 and does not have character
        while(atoi(chrarr3) <= 0 || haschar(chrarr3, strlen(chrarr3))){
            printf("Burst time must be positive and cannot contain character, please enter again.\n");
            printf("Set burst times for processe %d .\n",i+1);
            gets(chrarr3);
        }
        burst_time[i] = atoi(chrarr3);

        // if(burst_time[i] <= quantum){
        //     priorities[i] = 1;
        // }else if(burst_time[i] > quantum){
        //     priorities[i] = 2;
        // }
    }

    for (i=0; i < num_processes; i++)
    {
        priorities[i] = 1;
        printf("process %d queued in queue 1(RR).\n",i+1);
    }

    findavgTime(processes, n, burst_time, quantum, priorities);

    return 0;
}
