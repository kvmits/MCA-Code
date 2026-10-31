//Write a Program to merge two arrays

#include <stdio.h>

int main() {
    int a1[50], a2[50], result[100];
    int n1, n2, i, j, k;
    printf("First Array Size: ");
    scanf("%d", &n1);
    printf("Enter %d elements for the first array:\n", n1);
    for (i = 0; i < n1; i++) {
        scanf("%d", &a1[i]);
    }
    printf("Second Array Size: ");
    scanf("%d", &n2);
    printf("Enter %d elements for the second array:\n", n2);
    for (i = 0; i < n2; i++) {
        scanf("%d", &a2[i]);
    }
    for (i = 0; i < n1; i++) {
        result[i] = a1[i];
    }
    for (j = 0; j < n2; j++) {
        result[n1 + j] = a2[j];
    }
    printf("Merged Array:\n");
    for (k = 0; k < n1 + n2; k++) {
        printf("%d ", result[k]);
    }
    printf("\n");
    return 0;
}

/*Algorithm
main():
    Start
    Declare arrays a1[50], a2[50], result[100]
    Declare variables n1, n2, i, j, k
    Read array n1
    Read array n2
    for i = 0 to n1 - 1
        result[i] = a1[i]
    for j = 0 to n2 - 1
        result[n1 + j] = a2[j]
    print result[]
    Stop
*/

/*Output:
First Array Size: 3
Enter 3 elements for the first array:
1
2
3
Second Array Size: 2
Enter 2 elements for the second array:
4
5
Merged Array:
1 2 3 4 5
*/  