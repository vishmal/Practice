#include <stdio.h>

int main() {
    int AT[10], BT[10], temp[10];
    int i, smallest, count = 0, j, n;
    double WT = 0, TAT = 0, end;
    float averageWT, averageTAT;
    printf("\n-----------------------------SRTF---------------------------------\n");
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("\n-------------------------------------------------------------------\n");
    printf("Enter Arrival time and Burst times for each process\n");
    for (i = 0; i < n; i++) {
        printf("\n-------------------------------------------------------------------\n");
        printf("\nArrival time of process[%d]: ", i + 1);
        scanf("%d", &AT[i]);
        printf("Burst time of process[%d]: ", i + 1);
        scanf("%d", &BT[i]);
        temp[i] = BT[i];
    }
    printf("\n-------------------------------------------------------------------\n");
    BT[9] = 99;

    for (j = 0; count != n; j++) {
        smallest = 9;
        for (i = 0; i < n; i++) {
            if (AT[i] <= j && BT[i] < BT[smallest] && BT[i] > 0) {
                smallest = i;
            }
        }
        BT[smallest]--;
        if (BT[smallest] == 0) {
            count++;
            end = j + 1;
            WT = WT + end - AT[smallest] - temp[smallest];
            TAT = TAT + end - AT[smallest];
        }
    }
    
    printf("Solution: \n");
	printf("\n-------------------------------------------------------------------\n");
    printf("\nPID\t\tAT\t\tBT\t\tTAT\t\tWT\n\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%.2f\t\t%.2f\n", i + 1, AT[i], temp[i], end - AT[i], end - AT[i] - temp[i]);
    }
    printf("\n-------------------------------------------------------------------\n");
    printf("\nAverage Waiting Time: %.2f\n", WT/n);
    printf("Average Turnaround Time: %.2f\n", TAT/n);
    printf("\n-------------------------------------------------------------------\n");
    return 0;

}
