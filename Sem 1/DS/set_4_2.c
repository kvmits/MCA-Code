//Program to check weather given square matrix is symmetric
#include <stdio.h>

int main() {
    int mat[10][10], n, i, j, flag = 1;
    printf("Enter the size of the square matrix: ");
    scanf("%d", &n);
    printf("Enter the elements of the matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (mat[i][j] != mat[j][i]) {
                flag = 0;
                break;
            }
        }
        if (!flag) {
            break;
        }
    }
    if (flag) {
        printf("The matrix is symmetric.\n");
    } else {
        printf("The matrix is not symmetric.\n");
    }
    return 0;
}

/*Algorithm
main():
    Start
    Declare mat[10][10], n, i, j, flag = 1
    Read n
    Read elements of the matrix
    for i = 0 to n-1
        for j = 0 to n-1
            if mat[i][j] != mat[j][i]
                flag = 0
                break
        if flag == 0
            break
    if flag == 1
        Print "Symmetric"
    else
        Print "Not Symmetric"
    Stop

*/


/*Output

Enter the size of the square matrix: 3
Enter the elements of the matrix:
1 2 3 4 5 6 7 8 9
The matrix is not symmetric.

Enter the size of the square matrix: 3
Enter the elements of the matrix:
1 2 4 2 3 5 4 5 6
The matrix is symmetric.
*/