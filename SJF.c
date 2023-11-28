#include <stdio.h>

void sortProcesses(int BT[], int AT[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (AT[j] > AT[j + 1] || (AT[j] == AT[j + 1] && BT[j] > BT[j + 1])) {
                int temp_at = AT[j];
                AT[j] = AT[j + 1];
                AT[j + 1] = temp_at;

                int temp_bt = BT[j];
                BT[j] = BT[j + 1];
                BT[j + 1] = temp_bt;
            }
        }
    }
}

int main() {
    int n;
    printf("\n--------------------------------SJF-----------------------------------\n");
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int BT[n], AT[n];
    printf("\n-------------------------------------------------------------------\n");
    printf("Enter Burst time and arrival time for each process\n");
    for (int i = 0; i < n; i++) {
        printf("\n-------------------------------------------------------------------\n");
        printf("Arrival time of process[%d]: ", i + 1);
        scanf("%d", &AT[i]);
        printf("Burst time of process[%d]: ", i + 1);
        scanf("%d", &BT[i]);
    }
    printf("\n-------------------------------------------------------------------\n");
    sortProcesses(BT, AT, n);

    int WT[n], TAT[n];
    float totalWT = 0, totalTAT = 0;
    WT[0] = 0;

    for (int i = 1; i < n; i++) {
        WT[i] = WT[i - 1] + BT[i - 1];
        totalWT += WT[i];
    }

    for (int i = 0; i < n; i++) {
        TAT[i] = WT[i] + BT[i];
        totalTAT += TAT[i];
    }

    printf("Solution: \n");
	printf("\n-------------------------------------------------------------------\n");
    printf("PID\t\tAT\t\tBT\t\tWT\t\tTAT\t\t\n\n");
    for (int i = 0; i < n; i++) {
        printf(" P%d\t\t%d\t\t%d\t\t %d\t\t %d\n", i + 1, AT[i], BT[i], WT[i], TAT[i]);
    }
    printf("\n-------------------------------------------------------------------\n"); 
    printf("\nAverage TurnAround Time = %.2f", totalTAT / n);
    printf("\nAverage Waiting Time = %.2f", totalWT / n);  
    printf("\n-------------------------------------------------------------------\n");
}
