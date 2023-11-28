#include <stdio.h>
#include <stdlib.h>

struct node
{
    int process, AT, BT, CT, WT, TAT, priority, vis;
};
struct link
{
    struct node data;
    struct link *next;
};
struct link *head = NULL;
void insert(struct node t)
{
    struct link *temp = head;
    struct link *newnode = (struct link *)malloc(sizeof(struct link));
    newnode->data = t;
    newnode->next = NULL;
    if (head == NULL)
    {
        head = newnode;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newnode;
    }
}
void Delete(int p)
{
    struct link *temp = head, *prevnode = head;
    while (temp->data.process != p)
    {
        prevnode = temp;
        temp = temp->next;
    }
    if (temp == head)
    {
        head = head->next;
        free(temp);
    }
    else
    {
        prevnode->next = temp->next;
        free(temp);
    }
}
void priorityBased(struct node arr[], int n)
{
    struct node ganttChart[n];
    struct link *temp, *minPrio;
    int done = 0, t = 0;
    float totalWT = 0, totalTAT = 0;
    printf("Solution: \n");
	printf("\n-------------------------------------------------------------------\n");
    printf("PID\tAT\tBT\tPriority\tCT\tWT\tTAT\n\n");
    while (done != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (arr[i].AT <= t && arr[i].vis == 0)
            {
                insert(arr[i]);
                arr[i].vis = 1;
            }
        }
        temp = head, minPrio = head;
        while (temp != NULL)
        {
            if (temp->data.priority < minPrio->data.priority)
            {
                minPrio = temp;
            }
            temp = temp->next;
        }
        temp = minPrio;
        if (temp != NULL)
        {
            t = t + temp->data.BT;
            temp->data.CT = t;
            printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", temp->data.process, temp->data.AT, temp->data.BT, temp->data.priority, temp->data.CT, temp->data.CT - temp->data.AT - temp->data.BT, temp->data.CT - temp->data.AT);
            totalWT = totalWT + temp->data.CT - temp->data.AT - temp->data.BT;
            totalTAT = totalTAT + temp->data.CT - temp->data.AT;
            ganttChart[done].process = temp->data.process;
            ganttChart[done].CT = t;
            Delete(temp->data.process);
            done++;
        }
        else
        {
            t++;
        }
    }
    printf("\n-------------------------------------------------------------------\n");
    printf("Gantt Chart: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", ganttChart[i].process);
    }
    printf("\n-------------------------------------------------------------------\n");
    printf("Average WT: %.2f", totalWT / n);
    printf("\nAverage TAT: %.2f", totalTAT / n);
    printf("\n-------------------------------------------------------------------\n");
}
int main()
{
    int n;
    printf("\n-----------------------Prority(Non-Preemptive)--------------------------\n");
    printf("Enter no. of process: ");
    scanf("%d", &n);
    printf("\n-------------------------------------------------------------------\n");
    struct node arr[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter process id: ");
        scanf("%d", &arr[i].process);
        printf("Arrival time of process[%d] : ", arr[i].process);
        scanf("%d", &arr[i].AT);
        printf("Burst time of process[%d] : ", arr[i].process);
        scanf("%d", &arr[i].BT);
        printf("Priority of process[%d] : ", arr[i].process);
        scanf("%d", &arr[i].priority);
        arr[i].vis = 0;
        printf("\n-------------------------------------------------------------------\n");
    }
    printf("\n");

    priorityBased(arr, n);
}
