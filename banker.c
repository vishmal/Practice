#include <stdio.h>

int main() {
    int n, m, i, j, k;
    printf("\n-------------------------------------------------------------------\n");
    printf("Enter the Number of process: ");
    scanf("%d", &n);
    printf("\n-------------------------------------------------------------------\n");
    printf("Enter the Number of Resources: ");
    scanf("%d", &m);
    printf("\n-------------------------------------------------------------------\n");
    int alloc[n][m];
    int max[n][m];
    
    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("\n-------------------------------------------------------------------\n");
    printf("Enter the Maximum Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    printf("\n-------------------------------------------------------------------\n");
    int avail[m];
    printf("Enter the Available Resources: ");
    for (j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }
    printf("\n-------------------------------------------------------------------\n");
    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++) {
        f[k] = 0; //if process complete then value will be 1
    }

    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int y = 0;
    for (k = 0; k < 5; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) { //checking need of each process
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    int flag = 1;

    for (int i = 0; i < n; i++) {
        if (f[i] == 0) {
            flag = 0;
            printf("The following system is not safe\n");
            break;
        }
    }
    if (flag == 1) {
        printf("Following is the SAFE Sequence\n");
        printf("\n-------------------------------------------------------------------\n");
        for (i = 0; i < n - 1; i++)
            printf(" P%d ->", ans[i]);
            printf(" P%d", ans[n - 1]);
    }
    printf("\n-------------------------------------------------------------------\n");
    return 0;
}
