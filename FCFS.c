
#include<stdio.h>

int main() {
    int n;
    int AT[20] ={0}, BT[20] = {0}, CT[20] = {0}, WT[20] = {0}, TAT[20] = {0}, process[20];
    float totalWT = 0, totalTAT = 0;
    printf("--------------------------------------------------\n");
    printf("Enter the number of processes: ");
    scanf("%d",&n);

    for(int i=0; i<n; i++){
        printf("--------------------------------------------------\n");
        printf("Enter Arrival and Burst Time of Process[%d]: ", i+1);
        scanf("%d %d", &AT[i], &BT[i]);
        process[i] = i+1;   // Storing process IDs
    }
	
	// Sorting based on arrival time using bubble sort
    printf("\n--------------------------------------------------\n");
    for(int i=0; i<n; i++){
        for(int j=0; j < n - i - 1; j++){ 
            if(AT[j] > AT[j+1]){
                int temp = AT[j];
                AT[j] = AT[j+1];
                AT[j+1] = temp;

                temp = BT[j];
                BT[j] = BT[j+1];
                BT[j+1] = temp;

                temp = process[j];
                process[j] = process[j+1];
                process[j+1] = temp;
            }
        }
    }
    
    int completionTime = 0; // Track the current time
    for(int i=0; i<n; i++){
        if(completionTime < AT[i]){
            completionTime = AT[i]; // If there is an idle state, update the current time
        }
        completionTime += BT[i];
        CT[i] = completionTime;
    }

    for(int i=0; i<n; i++){
        TAT[i] = CT[i] - AT[i];
        totalTAT += TAT[i];
    }

    for(int i=0; i<n; i++){
        WT[i] = TAT[i] - BT[i];
        totalWT += WT[i];
    }
    
    printf("Table: \n");
    printf("--------------------------------------------------\n");
    printf("Pid\tAT\tBT\tWT\tTAT\tWT\n\n");
    for(int i=0; i<n; i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", process[i], AT[i], BT[i], CT[i], TAT[i], WT[i]);
    }
    
    float avg_WT = totalWT/n;
    float avg_TAT = totalTAT/n;
    printf("--------------------------------------------------\n");
    printf("\nAverage Turn Around Time = %.2f\n", avg_TAT);
    printf("Average Waiting Time = %.2f\n", avg_WT);
    printf("--------------------------------------------------\n");

}

