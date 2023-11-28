#include <stdio.h>

int main() {
    int m, n, position, k, l;
    int a = 0, b = 0, page_fault = 0;

    int total_frames;
    printf("----------------------------------------------------------\n");
    printf("Enter the number of frames: ");
    scanf("%d", &total_frames);
    printf("----------------------------------------------------------\n");
    int frames[total_frames];
    int temp[total_frames];

    int total_pages;
    printf("Enter the total number of pages: ");
    scanf("%d", &total_pages);
    printf("----------------------------------------------------------\n");
    int pages[total_pages];
    printf("Enter the page reference sequence: ");
    for (n = 0; n < total_pages; n++) {
        scanf("%d", &pages[n]);
    }

    for (m = 0; m < total_frames; m++) {
        frames[m] = -1;
    }
    printf("----------------------------------------------------------\n");
    for (n = 0; n < total_pages; n++) {
        printf("%d: ", pages[n]);
        a = 0, b = 0;
        for (m = 0; m < total_frames; m++) {
            if (frames[m] == pages[n]) {
                a = 1;
                b = 1;
                break;
            }
        }
        if (a == 0) {
            for (m = 0; m < total_frames; m++) {
                if (frames[m] == -1) {
                    frames[m] = pages[n];
                    b = 1;
                    page_fault++;
                    break;
                }
            }
        }
        if (b == 0) {
            for (m = 0; m < total_frames; m++) {
                temp[m] = 0;
            }
            for (k = n - 1, l = 1; l <= total_frames - 1; l++, k--) {
                for (m = 0; m < total_frames; m++) {
                    if (frames[m] == pages[k]) {
                        temp[m] = 1;
                    }
                }
            }
            for (m = 0; m < total_frames; m++) {
                if (temp[m] == 0)
                    position = m;
            }
            frames[position] = pages[n];
            page_fault++;
        }

        for (m = 0; m < total_frames; m++) {
            printf("%d\t", frames[m]);
        }
        printf("\n");
    }
    printf("----------------------------------------------------------\n");
    printf("LRU Page Faults: %d\n", page_fault);
    printf("----------------------------------------------------------\n");

    return 0;
}
