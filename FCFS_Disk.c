#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int size;
    printf("Enter the size of request array : ");
    scanf("%d",&size);
    int* arr = (int*)malloc(size* sizeof(int));
    printf("Enter the elements of the request array : \n");
    for(int i=0;i<size;i++){
        scanf("%d",&arr[i]);
    }
    int head;
    printf("Enter the initial head position : ");
    scanf("%d",&head);
    int curr_head,distance,seek_ops=0;
    for(int i=0;i<size;i++){
        curr_head = arr[i];
        distance = abs(head-curr_head);
        seek_ops+=distance;
        head = curr_head;
    }
    printf("The total no. of seek operations is %d",seek_ops);
    float seek_length = (float)seek_ops/(float)size;
    printf("\nThe average seek length is %f",seek_length);
    printf("\nThe seek sequence is ");
    for(int i=0;i<size;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}