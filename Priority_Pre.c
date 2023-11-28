#include <stdio.h>
#include <stdlib.h>

struct proc
{
    int PID, AT, PT, bt, RBT, WT, TAT, ct;
} ganttChart[100];

int pc = 0;
void addprocess(struct proc arr[], int PID, int AT, int bt, int PT)
{

    arr[pc].PID = PID;
    arr[pc].AT = AT;
    arr[pc].bt = bt;
    arr[pc].RBT = bt;
    arr[pc].PT = PT;
    arr[pc].WT = 0;
    arr[pc].TAT = 0;
    arr[pc].ct = 0;
    pc++;
}
struct Node
{
    struct proc node;
    struct Node *next;
};
struct Node *head = NULL;
struct Node *temp = NULL;
int rare = 0;
void insert(struct proc node)
{
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    newnode->node = node;
    newnode->next = NULL;
    if (head == NULL)
    {
        head = newnode;
    }
    else
    {
        temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newnode;
    }
    rare++;
}
void delete(int PID)
{
    temp = head;
    while (temp != NULL)
    {
        if (temp->node.PID == PID)
        {
            if (temp == head)
            {
                head = head->next;
                free(temp);
                break;
            }
            else if (temp->next == NULL)
            {
                struct Node *temp2 = head;
                struct Node *prev = temp2;
                while (temp2->next != NULL)
                {
                    prev = temp2;
                    temp2 = temp2->next;
                }
                prev->next = NULL;
                free(temp);
                break;
            }
            else
            {
                struct Node *temp2 = head;
                struct Node *prev = temp2;
                while (temp2->node.PID != PID)
                {
                    prev = temp2;
                    temp2 = temp2->next;
                }
                prev->next = temp2->next;
                free(temp);
                break;
            }
        }
        temp = temp->next;
    }
    rare--;
}
struct proc findmin()
{
    struct proc min_array[pc];
    int min_count = 0;
    temp = head;
    struct proc min = head->node;
    while (temp != NULL)
    {
        if (min.PT > temp->node.PT)
        {
            min = temp->node;
        }
        temp = temp->next;
    }
    temp = head;
    while (temp != NULL)
    {
        if (temp->node.PT == min.PT)
        {
            min_array[min_count++] = temp->node;
        }
        temp = temp->next;
    }
    struct proc ans = min_array[0];
    for (int i = 0; i < min_count; i++)
    {
        if (ans.AT > min_array[i].AT)
        {
            ans = min_array[i];
        }
    }
    return ans;
}
int found(int PID)
{
    struct Node *tempnode = head;
    while (tempnode != NULL)
    {
        if (tempnode->node.PID == PID)
        {
            return 0;
        }
        tempnode = tempnode->next;
    }
    return 1;
}
int gpc = 0;
void prioritybased(struct proc arr[])
{
    for (int i = 0; i < pc; i++)
    {
        for (int j = i + 1; j < pc; j++)
        {
            if (arr[j].AT < arr[i].AT)
            {
                struct proc tempnode = arr[j];
                arr[j] = arr[i];
                arr[i] = tempnode;
            }
        }
    }
    int maxAT = arr[pc - 1].AT;
    int ct = arr[0].AT;
    insert(arr[0]);
    while (rare != 0)
    {
        struct proc current = findmin();
        for (int i = 0; i < pc; i++)
        {
            if (arr[i].PID == current.PID && arr[i].RBT != 0)
            {
                if (ct >= maxAT)
                {
                    ct = ct + arr[i].RBT;
                    arr[i].RBT = 0;
                }
                else
                {
                    arr[i].RBT = arr[i].RBT - 1;
                    ct = ct + 1;
                }
            }
        }
        current.ct = ct;
        current.WT = current.ct - (current.AT + current.bt);
        current.TAT = current.bt + current.WT;
        current.RBT = current.RBT - 1;
        ganttChart[gpc++] = current;
        for (int i = 0; i < pc; i++)
        {
            if (arr[i].AT <= ct && arr[i].RBT != 0 && arr[i].PID != current.PID && found(arr[i].PID))
            {
                insert(arr[i]);
            }
        }
        struct Node *temp3 = head;
        delete (current.PID);
        for (int i = 0; i < pc; i++)
        {
            if (arr[i].PID == current.PID && arr[i].RBT != 0)
            {
                insert(arr[i]);
            }
        }
    }
}
int alreadyexist(struct proc processes[], struct proc key, int limit)
{
    for (int i = 0; i < limit; i++)
    {
        if (key.PID == processes[i].PID)
        {
            return 0;
        }
    }
    return 1;
}
void processStATics()
{
    struct proc processes[pc];
    int c = 0;
    int responsetime[pc];
    for (int i = 0; i < pc; i++)
    {
        responsetime[i] = -1;
    }
    int res_count = 0;
    int res_time = 0;
    for (int i = 0; i < gpc; i++)
    {
        if (responsetime[ganttChart[i].PID - 1] == -1)
        {
            responsetime[ganttChart[i].PID - 1] = res_time;
        }
        res_time = ganttChart[i].ct;
    }
    for (int i = gpc - 1; i >= 0; i--)
    {
        if (alreadyexist(processes, ganttChart[i], c))
        {
            processes[c++] = ganttChart[i];
        }
    }
    for (int i = 0; i < pc; i++)
    {
        for (int j = i + 1; j < pc; j++)
        {
            if (processes[j].PID < processes[i].PID)
            {
                struct proc tempnode = processes[j];
                processes[j] = processes[i];
                processes[i] = tempnode;
            }
        }
    }
    printf("\n\nProcess Execution Details \n\n");
    printf("-----------------------------------------------------------\n");
    printf("PID     AT      BT      PT      WT      TAT     CT      RT\n");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < pc; i++)
    {
        printf("%d%8d%8d%8d%9d%8d%8d%8d", processes[i].PID, processes[i].AT, processes[i].bt, processes[i].PT, processes[i].WT, processes[i].TAT, processes[i].ct, responsetime[i]);
        printf("\n");
    }
    printf("----------------------------------------------------------\n");
    int twt = 0;
    int ttAT = 0;
    for (int i = 0; i < pc; i++)
    {
        twt = twt + processes[i].WT;
        ttAT = ttAT + processes[i].TAT;
    }
    float awt = (float)twt / pc;
    float ATAT = (float)ttAT / pc;
    printf("\n\nAverage Waiting Time:  %.1f", awt);
    printf("\n\nAverage Turn Around Time:  %.1f\n\n", ATAT);
    printf("\n\nGanttChart:   ");
    for (int i = 0; i < gpc; i++)
    {
        printf("%d  ", ganttChart[i].PID);
    }
    printf("\n");
}
int main()
{
    printf("\n--------------------------Priority(PREEMPTIVE)-----------------------------\n");
    printf("\nPress 1 to enter Process\nPress 2 for ganttChart && Process Execution Statistics\n");
    int entrycode, option;
    int PID, AT, bt, np, PT;
    printf("\n-------------------------------------------------------------------\n");
    printf("\nEnter the number Of Process : ");
    scanf("%d", &np);
    struct proc arr[np];
    do
    {
        printf("\n-------------------------------------------------------------------\n");
        printf("\n\nEnter option: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            for (int i = 0; i < np; i++)
            {
                printf("\n-------------------------------------------------------------------\n");
                printf("\nEnter Process ID : ");
                scanf("%d", &PID);
                printf("Arrival time of process: ");
                scanf("%d", &AT);
                printf("Burst time of process: ");
                scanf("%d", &bt);
                printf("Priority of process : ");
                scanf("%d", &PT);
                addprocess(arr, PID, AT, bt, PT);
                getchar();
                printf("\n");
                printf("\n-------------------------------------------------------------------\n");
            }
            break;
        case 2:
            printf("\n-------------------------------------------------------------------\n");
            prioritybased(arr);
            processStATics();
            printf("\n-------------------------------------------------------------------\n");
            break;
        default:
            printf("\n-------------------------------------------------------------------\n");
            printf("\nEnter Valid Inputs!!!!!!!!!");
            printf("\n-------------------------------------------------------------------\n");
            break;
        }

        printf("\nWant to Continue or Not(1/0) : ");
        scanf("%d", &entrycode);
        printf("\n-------------------------------------------------------------------\n");

    } while (entrycode != 0);
}
