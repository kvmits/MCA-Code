//Program to sort an integer array

#include <stdio.h>

int main() {
    int arr[50], n, i, j, temp;
    printf("Enter the Array Size: ");
    scanf("%d", &n);
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("Sorted Array:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

/*Algorithm
main():
    Start
    Declare variables arr[50], n, i, j, temp
    Read n
    Read n elements into arr
    for i = 0; i < n - 1; i++
        for j = 0; j < n - i - 1; j++
            If arr[j] > arr[j+1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
    display sorted array
    Stop
*/
/*
Output:
Enter the Array Size: 4
Enter 4 elements:
3 
1 
4 
1
Sorted Array:
1 1 3 4
*/