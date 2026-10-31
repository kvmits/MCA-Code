//Program to find the sum of two numbers in the following in different functions.
//a) with argument and with return 
//b) with argument and no return 
//c) without argument and with return 
//d) without argument and no return
//It should be menu driven program.

#include <stdio.h>

int sum_1(int a, int b) {
    return a + b;
}

void sum_2(int a, int b) {
    printf("Sum (with argument and no return): %d\n", a + b);
}

int sum_3() {
    int a, b;
    printf("Enter two numbers (without argument and with return): ");
    scanf("%d %d", &a, &b);
    printf("Sum (without argument and with return): %d\n", a + b);
    return a + b;
}

void sum_4() {
    int a, b;
    printf("Enter two numbers (without argument and no return): ");
    scanf("%d %d", &a, &b);
    printf("Sum: %d\n", a + b);
    return 0; 
}

int main() {
    int ch, num1, num2, result;
    do {
        printf("\nMenu:\n");
        printf("1. Sum with argument and return\n");
        printf("2. Sum with argument and no return\n");
        printf("3. Sum without argument and return\n");
        printf("4. Sum without argument and no return\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter two numbers: ");
                scanf("%d %d", &num1, &num2);
                result = sum_1(num1, num2);
                printf("Sum (with argument and return): %d\n", result);
                break;
            case 2:
                printf("Enter two numbers: ");
                scanf("%d %d", &num1, &num2);
                sum_2(num1, num2);
                break;
            case 3:
                sum_3();
                break;
            case 4:
                sum_4();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (ch != 5);
    return 0;
}

/*Algorithm

main():
    1.Start
    2.Declare variables ch, num1, num2, result
    3.Display Choices
    4.Read choice from user
        if choice is 1: call sum_1() with arguments and return the result
        if choice is 2: call sum_2(num1, num2) with arguments and no return
        if choice is 3: call sum_3() without arguments and return the result
        if choice is 4: call sum_4(num1, num2) without arguments and no return
    5.Repeat steps 3 and 4 until user chooses to exit
    6.Stop

sum_1(int a, int b):
    1.Start
    2.Return the sum of a and b
    3.Stop

sum_2(int a, int b):
    1.Start
    2.Print the sum of a and b
    3.Stop

sum_3():
    1.Start 
    2.Read two numbers from user
    3.Print the sum of the two numbers
    4.Return the sum
    5.Stop

sum_4():
    1.Start
    2.Read two numbers from user
    3.Print the sum of the two numbers
    4.Stop
*/

/*
Output:

Menu:
1. Sum with argument and return
2. Sum with argument and no return
3. Sum without argument and return
4. Sum without argument and no return
5. Exit
Enter your choice: 1
Enter two numbers: 10
20
Sum (with argument and return): 30

Menu:
1. Sum with argument and return
2. Sum with argument and no return
3. Sum without argument and return
4. Sum without argument and no return
5. Exit
Enter your choice: 2
Enter two numbers: 20
30
Sum (with argument and no return): 50

Menu:
1. Sum with argument and return
2. Sum with argument and no return
3. Sum without argument and return
4. Sum without argument and no return
5. Exit
Enter your choice: 5
Exiting...

*/