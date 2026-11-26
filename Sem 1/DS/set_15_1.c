// Set 15.1 - Create a Max-Heap and Min-Heap from an array.

#include <stdio.h>

#define MAX_SIZE 100

void heapify(int heap[], int size, int root, int is_max_heap)
{
    int selected = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size && (is_max_heap ? heap[left] > heap[selected] : heap[left] < heap[selected])) {
        selected = left;
    }
    if (right < size && (is_max_heap ? heap[right] > heap[selected] : heap[right] < heap[selected])) {
        selected = right;
    }
    if (selected != root) {
        int temporary = heap[root];
        heap[root] = heap[selected];
        heap[selected] = temporary;
        heapify(heap, size, selected, is_max_heap);
    }
}

void build_heap(int heap[], int size, int is_max_heap)
{
    for (int index = size / 2 - 1; index >= 0; index--) {
        heapify(heap, size, index, is_max_heap);
    }
}

void display_heap(const int heap[], int size)
{
    for (int index = 0; index < size; index++) {
        printf("%d ", heap[index]);
    }
    printf("\n");
}

int main(void)
{
    int values[MAX_SIZE], max_heap[MAX_SIZE], min_heap[MAX_SIZE];
    int size;

    printf("Enter number of elements (1-%d): ", MAX_SIZE);
    if (scanf("%d", &size) != 1 || size < 1 || size > MAX_SIZE) {
        printf("Invalid number of elements.\n");
        return 1;
    }

    printf("Enter %d elements: ", size);
    for (int index = 0; index < size; index++) {
        if (scanf("%d", &values[index]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
        max_heap[index] = values[index];
        min_heap[index] = values[index];
    }

    build_heap(max_heap, size, 1);
    build_heap(min_heap, size, 0);

    printf("Max-Heap (level-order): ");
    display_heap(max_heap, size);
    printf("Min-Heap (level-order): ");
    display_heap(min_heap, size);
    return 0;
}

/*Algorithm
HEAPIFY(heap, size, root, is_max_heap)
    selected <- root
    left <- 2 * root + 1
    right <- 2 * root + 2
    IF is_max_heap THEN
        IF left < size AND heap[left] > heap[selected] THEN selected <- left
        IF right < size AND heap[right] > heap[selected] THEN selected <- right
    ELSE
        IF left < size AND heap[left] < heap[selected] THEN selected <- left
        IF right < size AND heap[right] < heap[selected] THEN selected <- right
    END IF
    IF selected != root THEN
        SWAP(heap[root], heap[selected])
        HEAPIFY(heap, size, selected, is_max_heap)
    END IF
END HEAPIFY

BUILD_HEAP(heap, size, is_max_heap)
    FOR index <- size / 2 - 1 DOWNTO 0
        HEAPIFY(heap, size, index, is_max_heap)
    END FOR
END BUILD_HEAP

main():
    read size
    if size < 1 or size > MAX_SIZE then stop
    for index = 0 to size - 1
        read values[index]
        max_heap[index] = values[index]
        min_heap[index] = values[index]
    build_heap(max_heap, size, true)
    build_heap(min_heap, size, false)
    print max_heap
    print min_heap
*/

/*Output:
Enter number of elements (1-100): 6
Enter 6 elements: 4 10 3 5 1 8
Max-Heap (level-order): 10 5 8 4 1 3
Min-Heap (level-order): 1 4 3 5 10 8
*/
