// Set 17.1 - BFS and DFS on a connected undirected graph.

#include <stdio.h>

#define MAX_VERTICES 20

void breadth_first_search(int graph[MAX_VERTICES][MAX_VERTICES], int count, int start)
{
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;
    printf("BFS: ");
    while (front < rear) {
        int vertex = queue[front++];
        printf("%d ", vertex + 1);
        for (int neighbor = 0; neighbor < count; neighbor++) {
            if (graph[vertex][neighbor] && !visited[neighbor]) {
                visited[neighbor] = 1;
                queue[rear++] = neighbor;
            }
        }
    }
    printf("\n");
}

void depth_first_search(int graph[MAX_VERTICES][MAX_VERTICES], int count,
                        int vertex, int visited[MAX_VERTICES])
{
    visited[vertex] = 1;
    printf("%d ", vertex + 1);
    for (int neighbor = 0; neighbor < count; neighbor++) {
        if (graph[vertex][neighbor] && !visited[neighbor]) {
            depth_first_search(graph, count, neighbor, visited);
        }
    }
}

int main(void)
{
    int graph[MAX_VERTICES][MAX_VERTICES] = {{0}};
    int count, start;

    printf("Enter number of vertices (1-%d): ", MAX_VERTICES);
    if (scanf("%d", &count) != 1 || count < 1 || count > MAX_VERTICES) {
        printf("Invalid number of vertices.\n");
        return 1;
    }
    printf("Enter the %d x %d adjacency matrix (0 or 1):\n", count, count);
    for (int row = 0; row < count; row++) {
        for (int column = 0; column < count; column++) {
            if (scanf("%d", &graph[row][column]) != 1 ||
                (graph[row][column] != 0 && graph[row][column] != 1)) {
                printf("Invalid adjacency matrix.\n");
                return 1;
            }
        }
    }
    printf("Enter starting vertex (1-%d): ", count);
    if (scanf("%d", &start) != 1 || start < 1 || start > count) {
        printf("Invalid starting vertex.\n");
        return 1;
    }

    breadth_first_search(graph, count, start - 1);
    int visited[MAX_VERTICES] = {0};
    printf("DFS: ");
    depth_first_search(graph, count, start - 1, visited);
    printf("\n");
    return 0;
}

/*Algorithm
BFS(graph, count, start)
    visited[0..count-1] <- false
    CREATE empty queue
    visited[start] <- true
    ENQUEUE(start)
    WHILE queue is not empty
        vertex <- DEQUEUE()
        PRINT vertex
        FOR each neighbor from 0 to count - 1
            IF graph[vertex][neighbor] = 1 AND NOT visited[neighbor] THEN
                visited[neighbor] <- true
                ENQUEUE(neighbor)

DFS(graph, vertex)
    visited[vertex] <- true
    PRINT vertex
    FOR each neighbor from 0 to count - 1
        IF graph[vertex][neighbor] = 1 AND NOT visited[neighbor] THEN
            DFS(graph, neighbor)

MAIN
    READ count and adjacency matrix
    READ start vertex
    BFS(graph, count, start)
    RESET visited
    DFS(graph, start)
*/

/*Output:
Enter number of vertices (1-20): 5
Enter the 5 x 5 adjacency matrix (0 or 1):
0 1 1 0 0
1 0 0 1 1
1 0 0 0 1
0 1 0 0 0
0 1 1 0 0
Enter starting vertex (1-5): 1
BFS: 1 2 3 4 5
DFS: 1 2 4 5 3
*/
