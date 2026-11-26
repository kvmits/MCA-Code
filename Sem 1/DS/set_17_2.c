// Set 17.2 - Prim's algorithm for a minimum cost spanning tree.

#include <stdio.h>

#define MAX_VERTICES 20
#define INFINITY_VALUE 1000000000

int main(void)
{
    int graph[MAX_VERTICES][MAX_VERTICES];
    int key[MAX_VERTICES], parent[MAX_VERTICES], selected[MAX_VERTICES] = {0};
    int count, start, total_cost = 0;

    printf("Enter number of vertices (1-%d): ", MAX_VERTICES);
    if (scanf("%d", &count) != 1 || count < 1 || count > MAX_VERTICES) {
        printf("Invalid number of vertices.\n");
        return 1;
    }
    printf("Enter the %d x %d weight matrix (0 for no edge):\n", count, count);
    for (int row = 0; row < count; row++) {
        for (int column = 0; column < count; column++) {
            if (scanf("%d", &graph[row][column]) != 1) {
                printf("Invalid edge weight.\n");
                return 1;
            }
        }
    }
    printf("Enter starting vertex (1-%d): ", count);
    if (scanf("%d", &start) != 1 || start < 1 || start > count) {
        printf("Invalid starting vertex.\n");
        return 1;
    }

    for (int vertex = 0; vertex < count; vertex++) {
        key[vertex] = INFINITY_VALUE;
        parent[vertex] = -1;
    }
    key[start - 1] = 0;

    for (int step = 0; step < count; step++) {
        int current = -1;
        for (int vertex = 0; vertex < count; vertex++) {
            if (!selected[vertex] &&
                (current == -1 || key[vertex] < key[current])) {
                current = vertex;
            }
        }
        if (current == -1 || key[current] == INFINITY_VALUE) {
            printf("Graph is disconnected; spanning tree does not exist.\n");
            return 0;
        }
        selected[current] = 1;
        for (int neighbor = 0; neighbor < count; neighbor++) {
            if (graph[current][neighbor] != 0 && !selected[neighbor] &&
                graph[current][neighbor] < key[neighbor]) {
                key[neighbor] = graph[current][neighbor];
                parent[neighbor] = current;
            }
        }
    }

    printf("Edges in the minimum spanning tree:\n");
    for (int vertex = 0; vertex < count; vertex++) {
        if (parent[vertex] != -1) {
            printf("%d - %d : %d\n", parent[vertex] + 1, vertex + 1, key[vertex]);
            total_cost += key[vertex];
        }
    }
    printf("Minimum cost: %d\n", total_cost);
    return 0;
}

/*Algorithm
PRIM(graph, count, start)
    FOR vertex <- 0 TO count - 1
        key[vertex] <- INFINITY
        parent[vertex] <- NIL
        selected[vertex] <- false
    start <- start - 1
    key[start] <- 0

    FOR step <- 0 TO count - 1
        current <- NIL
        FOR vertex <- 0 TO count - 1
            IF NOT selected[vertex] AND
               (current = NIL OR key[vertex] < key[current]) THEN
                current <- vertex
        IF current = NIL OR key[current] = INFINITY THEN
            RETURN DISCONNECTED
        selected[current] <- true
        FOR neighbor <- 0 TO count - 1
            IF graph[current][neighbor] != 0 AND NOT selected[neighbor] AND
               graph[current][neighbor] < key[neighbor] THEN
                key[neighbor] <- graph[current][neighbor]
                parent[neighbor] <- current

    total_cost <- 0
    FOR vertex <- 0 TO count - 1
        IF parent[vertex] != NIL THEN
            PRINT parent[vertex] + 1, vertex + 1, key[vertex]
            total_cost <- total_cost + key[vertex]
    PRINT total_cost
*/

/*Output:
Enter number of vertices (1-20): 5
Enter the 5 x 5 weight matrix (0 for no edge):
0 2 0 6 0
2 0 3 8 5
0 3 0 0 7
6 8 0 0 9
0 5 7 9 0
Enter starting vertex (1-5): 1
Edges in the minimum spanning tree:
1 - 2 : 2
2 - 3 : 3
1 - 4 : 6
2 - 5 : 5
Minimum cost: 16
*/
