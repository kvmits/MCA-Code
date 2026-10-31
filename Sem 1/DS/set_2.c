//Menu Driven Program to perform following array operations:
//a) Insert an element to a perticular location
//b) Delete an element from a perticular location
//c) Traverse



int main() {
    int arr[50], n, ch, i, pos, element;

    printf("Enter the Array Size: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    do {
        printf("\nMenu:\n");
        printf("1. Insert an element at a particular location\n");
        printf("2. Delete an element from a particular location\n");
        printf("3. Traverse the array\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter the position to insert (0 to %d): ", n);
                scanf("%d", &pos);
                if (pos < 0 || pos > n) {
                    printf("Invalid position!\n");
                    break;
                }
                printf("Enter the element to insert: ");
                scanf("%d", &element);
                for (i = n; i > pos; i--) {
                    arr[i] = arr[i - 1];
                }
                arr[pos] = element;
                n++;
                break;

            case 2:
                printf("Enter the position to delete (0 to %d): ", n - 1);
                scanf("%d", &pos);
                if (pos < 0 || pos >= n) {
                    printf("Invalid position!\n");
                    break;
                }
                for (i = pos; i < n - 1; i++) {
                    arr[i] = arr[i + 1];
                }
                n--;
                break;

            case 3:
                printf("Array elements are:\n");
                for (i = 0; i < n; i++) {
                    printf("%d ", arr[i]);
                }
                printf("\n");
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (ch != 4);
    return 0;
}

/*Algorithm

main():
    Start
    Declare arr(50), n, ch, i, pos, element
    Read n
    Read n elements into arr
    Do
        Read ch
        Switch(ch)
            Case 1:
                Read pos
                if pos < 0 || pos > n
                    break
                Read element
                for i = n; i > pos; i--
                    arr[i] = arr[i - 1]
                increment n
                Break
            Case 2:
                Read pos
                if pos < 0 || pos > n
                    break
                for i = pos; i < n - 1; i++
                    arr[i] = arr[i + 1]
                Decrement n
                Break
            Case 3:
                Print all array elements
                Break
            Case 4:
                break
            Default:
                invalid choice
    While ch != 4
    Stop

*/

/*Output:

Enter the Array Size: 3
Enter 3 elements:
2
3
4
Menu:
1. Insert an element at a particular location
2. Delete an element from a particular location
3. Traverse the array
4. Exit
Enter your choice: 1
Enter the position to insert (0 to 3): 2
Enter the element to insert: 5
Menu:
1. Insert an element at a particular location
2. Delete an element from a particular location
3. Traverse the array
4. Exit
Enter your choice: 2
Enter the position to delete (0 to 3): 2
Menu:
1. Insert an element at a particular location
2. Delete an element from a particular location
3. Traverse the array
4. Exit
Enter your choice: 3
Array elements are:
2 3 4 
Menu:
1. Insert an element at a particular location
2. Delete an element from a particular location
3. Traverse the array
4. Exit
Enter your choice: 4
Exiting...

*/