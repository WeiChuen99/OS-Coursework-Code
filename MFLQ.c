#include <stdio.h>

// Function to find the waiting time for all
// processes
void findWaitingTime(int processes[], int n,
             int bt[], int wt[], int quantum,int prt[])
{
    // Make a copy of burst times bt[] to store remaining
    // burst times.
    int rem_bt[n],j;
    for (int i = 0 ; i < n ; i++)
        rem_bt[i] =  bt[i];

    int t = 0; // Current time

    // Keep traversing processes in round robin manner
    // until all of them are not done.
    while (1)
    {
        int done = 1;

        // Traverse all processes one by one repeatedly
        for (int i = 0 ; i < n; i++)
        {

            //printf("%d",i);
            // If burst time of a process is greater than 0
            // then only need to process further
            if (rem_bt[i] > 0)
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
                    if(rem_bt[i] > 0 && prt[i] == 1 ){
                        prt[i] += 1;
                    }

                    else{
                            //printf("entered");
                        quantum = rem_bt[i];
                    }

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
            //Second queue will have more quantum time allocated

            /*if(rem_bt[i] <= 5){
            prt[i] = 1;
            }else if(rem_bt[i] > 5 && rem_bt[i] <= 10 ){
                prt[i] = 2;
            }
            else
                prt[i] = 3;*/
        }

        quantum = quantum * 2;
       // printf("entered!");
        // If all processes are done
        if (done == 1)
          break;
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

    printf("Average waiting time = %.2f",(float)total_wt / (float)n);
    printf("\nAverage turn around time = %.2f\n\n",(float)total_wt / (float)n);
}

// Driver code
int main()
{

    int num_processes, i,process_priority;
    // process id's
    printf("Set number of processes.\n");
    scanf("%d",&num_processes);


    int processes[num_processes];
    int n = sizeof processes / sizeof processes[0];

    // Burst time of all processes
    int burst_time[num_processes];
    int priorities[num_processes];

    for (i=0; i < num_processes; i++)
    {
        printf("Set burst times for processes %d .\n",i+1);
        scanf("%d",&burst_time[i]);
        if(burst_time[i] <= 5){
            priorities[i] = 1;
        }else if(burst_time[i] > 5){
            priorities[i] = 2;
        }
    }

    // Time quantum
    int quantum = 2;

    findavgTime(processes, n, burst_time, quantum,priorities);

    return 0;
}
