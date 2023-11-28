#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int size;
    printf("Enter the size of request array : ");
    scanf("%d",&size);
    int* arr = (int*)malloc(size * sizeof(int));
    printf("Enter the elements of the request array : \n");
    for(int i=0;i<size;i++){
        scanf("%d",&arr[i]);
    }
    int disk_size;
    printf("Enter the size of disk : ");
    scanf("%d",&disk_size);
    int head;
    printf("Enter the initial head position : ");
    scanf("%d",&head);
    char direction;
    printf("Enter the direction ('l' for left & 'r' for right) : ");
    scanf(" %c",&direction);
    int curr_head,seekCount=0;
    printf("The seek sequence is ");
    if(direction == 'l'){
        for(int i=head;i>=0;i--){
            for(int j=0;j<size;j++){
                if(arr[j] == i){
                    curr_head = arr[j];
                    seekCount+=abs(curr_head-head);
                    head = curr_head;
                    printf("%d ",head);
                    arr[j] = -1;
                }
            }
        }
        for(int i=head;i<disk_size-1;i++){
            for(int j=0;j<size;j++){
                if(arr[j] == i){
                    curr_head = arr[j];
                    seekCount+=abs(curr_head-head);
                    head = curr_head;
                    printf("%d ",head);
                    arr[j] = -1;
                }
            }
        }
    }
    else if(direction == 'r'){
        for(int i=head;i<disk_size-1;i++){
            for(int j=0;j<size;j++){
                if(arr[j] == i){
                    curr_head = arr[j];
                    seekCount+=abs(curr_head-head);
                    head = curr_head;
                    printf("%d ",head);
                    arr[j] = -1;
                }
            }
        }
        for(int i=head;i>=0;i--){
            for(int j=0;j<size;j++){
                if(arr[j] == i){
                    curr_head = arr[j];
                    seekCount+=abs(curr_head-head);
                    head = curr_head;
                    printf("%d ",head);
                    arr[j] = -1;
                }
            }
        }
    }
    printf("\nThe total no. of seek operations is %d",seekCount);
    float seek_length = (float)seekCount/(float)size;
    printf("\nThe average seek length is %f",seek_length);
    return 0;
}