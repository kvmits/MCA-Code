//Write a menu-driven C program to perform addition, subtraction, and multiplication of two matrices using a menu-based selection mechanism.

#include <stdio.h>

int main() {
    int mat1[10][10], mat2[10][10], result[10][10];
    int r1, c1, r2, c2, i, j, k, ch;
    printf("Enter rows and columns for first matrix: ");
    scanf("%d %d", &r1, &c1);
    printf("Enter rows and columns for second matrix: ");
    scanf("%d %d", &r2, &c2);
    if (r1 != r2 || c1 != c2) {
        printf("Matrices must have the same dimensions.\n");
        return 0;
    }
    printf("Enter elements of first matrix:\n");
    for (i = 0; i < r1; i++)
        for (j = 0; j < c1; j++)
            scanf("%d", &mat1[i][j]);
    printf("Enter elements of second matrix:\n");
    for (i = 0; i < r2; i++)
        for (j = 0; j < c2; j++)
            scanf("%d", &mat2[i][j]);

    do {
        printf("\nMenu:\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                for (i = 0; i < r1; i++)
                    for (j = 0; j < c1; j++)
                        result[i][j] = mat1[i][j] + mat2[i][j];
                printf("Result of addition:\n");
                for (i = 0; i < r1; i++) {
                    for (j = 0; j < c1; j++)
                        printf("%d ", result[i][j]);
                    printf("\n");
                }
                break;
            case 2:
                for (i = 0; i < r1; i++)
                    for (j = 0; j < c1; j++)
                        result[i][j] = mat1[i][j] - mat2[i][j];

                printf("Result of subtraction:\n");
                for (i = 0; i < r1; i++) {
                    for (j = 0; j < c1; j++)
                        printf("%d ", result[i][j]);
                    printf("\n");
                }
                break;
            case 3:
                for (i = 0; i < r1; i++) {
                    for (j = 0; j < c2; j++) {
                        result[i][j] = 0;
                        for (k = 0; k < c1; k++) {
                            result[i][j] += mat1[i][k] * mat2[k][j];
                        }
                    }
                }
                printf("Result of multiplication:\n");
                for (i = 0; i < r1; i++) {
                    for (j = 0; j < c2; j++)
                        printf("%d ", result[i][j]);
                    printf("\n");
                }
                break;
            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (ch != 4);
    return 0;
}

/*Algorithm
main():
    Start
    Declare mat1[10][10], mat2[10][10], result[10][10], r1, c1, r2, c2, i, j, k, ch
    Read mat1 and mat2 dimensions
    If r1 != r2 or c1 != c2
        exit with error
    Read values for mat1 and mat2
    Do
        Display Menu
        Read choice
        Switch(ch)
            Case 1:
                for i = 0; i < r1; i++
                    for j = 0; j < c1; j++
                        result[i][j] = mat1[i][j] + mat2[i][j]
                print result matrix
                Break
            Case 2:
                for i = 0; i < r1; i++
                    for j = 0; j < c1; j++
                        result[i][j] = mat1[i][j] - mat2[i][j]
                print result matrix
                Break
            Case 3:
                for i = 0; i < r1; i++
                    for j = 0; j < c2; j++
                        result[i][j] = 0
                        for k = 0; k < c1; k++
                            result[i][j] += mat1[i][k] * mat2[k][j]
                print result matrix
                Break
            Case 4:
                break
            Default:
                print invalid choice and exit
    While choice != 4
    Stop
*/

/*Output:

Enter rows and columns for first matrix: 2
2
Enter rows and columns for second matrix: 2
2
Enter elements of first matrix:
1 2 3 4
Enter elements of second matrix:
4 3 2 1
Menu:
1. Addition
2. Subtraction
3. Multiplication
4. Exit
Enter your choice: 1
Result of addition:
5 5
5 5
Menu:
1. Addition
2. Subtraction
3. Multiplication
4. Exit
Enter your choice: 2
Result of subtraction:
-3 -1
1 3
Menu:
1. Addition
2. Subtraction
3. Multiplication
4. Exit
Enter your choice: 3
Result of multiplication:
8 5
20 13
Menu:
1. Addition
2. Subtraction
3. Multiplication
4. Exit
Enter your choice: 4
Exiting...

*/