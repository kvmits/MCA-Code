//program to implement linear search and binary search

#include <stdio.h>

int main() {
    int arr[50], n, i, key, ch, flag = 0;
    printf("Enter the Array Size: ");
    scanf("%d", &n);
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter the element to search: ");
    scanf("%d", &key);
    printf("Choose search method:\n");
    printf("1. Linear Search\n");
    printf("2. Binary Search\n");
    printf("Enter your choice: ");
    scanf("%d", &ch);
    switch (ch) {
        case 1:{
            for (i = 0; i < n; i++) {
                if (arr[i] == key) {
                    printf("Element %d found at index %d.\n", key, i);
                    flag = 1;
                    break;
                }
            }
            break;
        }
        case 2:{
            int low = 0, high, mid;
            high = n - 1;
            while (low <= high) {
                mid = (low + high) / 2;
                if (arr[mid] == key) {
                    printf("Element %d found at index %d.\n", key, mid);
                    flag = 1;
                    break;
                } else if (arr[mid] < key) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            break;
        }
        default:
            printf("Invalid choice!\n");
            return 0;
    }
    if (flag) {
        printf("Element %d found in the array.\n", key);
    } else {
        printf("Element %d not found in the array.\n", key);
    }
    return 0;
}


/*Algorithm

main():
    Start
    Declare arr(50), n, i, key, ch, flag = 0
    Read n
    Read n elements into arr
    Read key
    Display search method menu
    Read ch
    Switch(ch)
        Case 1:
            for i = 0 to n-1
                if arr[i] == key
                    print index and set flag = 1
                    break
            break
        Case 2:
            low = 0, high = n - 1
            while low <= high
                mid = (low + high) / 2
                if arr[mid] == key
                    print index and set flag = 1
                    break
                else if arr[mid] < key
                    low = mid + 1
                else
                    high = mid - 1
            break
        Default:
            print invalid choice and exit
    if flag == 1
        found
    else
        not found
    Stop

*/

/*Output:

Enter the Array Size: 3
Enter 3 elements:
1
2
3
Enter the element to search: 2
Choose search method:
1. Linear Search
2. Binary Search
Enter your choice: 1
Element 2 found at index 1.
Element 2 found in the array.

Enter the Array Size: 3
Enter 3 elements:
1
2
3
Enter the element to search: 2
Choose search method:
1. Linear Search
2. Binary Search
Enter your choice: 2
Element 2 found at index 1.
Element 2 found in the array.

*/