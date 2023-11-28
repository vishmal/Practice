#include <stdio.h>
#define max 10

int main() {
    int n, TQ, count = 0, temp, sq = 0, PID[max], AT[max], BT[max], REM_BT[max], WT[max], TAT[max];
    int TotalWT = 0, TotalTAT = 0;
    printf("\n----------------------------Round Robin-----------------------------\n");
    printf("Enter the number of Process: ");
    scanf("%d", &n);
    printf("\n-------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("Enter process id: ");
        scanf("%d", &PID[i]);
        printf("Arrival time of process[%d]: ", i + 1);
        scanf("%d", &AT[i]);
        printf("Burst time of process[%d]: ", i + 1);
        scanf("%d", &BT[i]);
        REM_BT[i] = BT[i];
        printf("\n-------------------------------------------------------------------\n");
    }
    printf("Enter the Time Quantum: ");
    scanf("%d", &TQ);
    printf("\n-------------------------------------------------------------------\n");
    while (1) {
        int allComplete = 1; 
        for (int i = 0; i < n; i++) {
            temp = TQ;
            if (REM_BT[i] == 0){
                count++;
              continue;
            }

            if (REM_BT[i] > TQ) {
                REM_BT[i] -= TQ;
            } else {
                temp = REM_BT[i];
                REM_BT[i] = 0;
            }
            sq += temp;
            TAT[i] = sq;
            allComplete = 0;
        }

        if (allComplete) {
            break;
        }
    }

    printf("Solution: \n");
	printf("\n-------------------------------------------------------------------\n");
    printf("\nPID\t AT\t BT\t TAT\t WT\n\n");
    for (int i = 0; i < n; i++) {
        TAT[i] = TAT[i] - AT[i]; 
        WT[i] = TAT[i] - BT[i];  
        TotalWT += WT[i];
        TotalTAT += TAT[i];
        printf("%d\t %d\t %d\t %d\t %d\n", PID[i], AT[i], BT[i], TAT[i], WT[i]);
    }
    printf("\n-------------------------------------------------------------------\n");
    printf("Average Waiting time is %.2f\n", (float)TotalWT / n);
    printf("Average Turn Around Time is %.2f\n", (float)TotalTAT / n);
    printf("\n-------------------------------------------------------------------\n");

    return 0; 
}
