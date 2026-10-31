//Read n numbers, dynamically allocate an integer array using malloc(),find and display their sum and average, then release the memory.

#include <stdio.h>

int main() {
    int n, i;
    float sum = 0.0, avg;
    int *arr;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    printf("Enter %d numbers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    avg = sum / n;
    printf("Sum: %.2f\n", sum);
    printf("Average: %.2f\n", avg);
    free(arr);
    return 0;
}
/*Algorithm
main():
    Start
    Declare n, i, sum = 0.0, avg
    Declare pointer arr
    Read n
    Allocate memory for arr using malloc
    If arr is NULL
        Exit
    Read n numbers into arr
    for i = 0 to n - 1
        sum += arr[i]
    avg = sum / n
    print sum and average
    Free memory
    Stop
*/
/*Output:
Enter the number of elements: 5
Enter 5 numbers:
10
20
30
40
50
Sum: 150.00
Average: 30.00
*/