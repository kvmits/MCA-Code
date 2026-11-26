// Set 17.4 - Single-source shortest paths using Dijkstra's algorithm.

#include <stdio.h>

#define MAX_VERTICES 20
#define INFINITY_VALUE (1LL << 60)

void print_path(const int parent[], int vertex)
{
    if (parent[vertex] != -1) {
        print_path(parent, parent[vertex]);
        printf(" -> ");
    }
    printf("%d", vertex + 1);
}

int main(void)
{
    int graph[MAX_VERTICES][MAX_VERTICES];
    long long distance[MAX_VERTICES];
    int parent[MAX_VERTICES], visited[MAX_VERTICES] = {0};
    int count, start;

    printf("Enter number of vertices (1-%d): ", MAX_VERTICES);
    if (scanf("%d", &count) != 1 || count < 1 || count > MAX_VERTICES) {
        printf("Invalid number of vertices.\n");
        return 1;
    }
    printf("Enter the %d x %d weight matrix (0 for no edge):\n", count, count);
    for (int row = 0; row < count; row++) {
        for (int column = 0; column < count; column++) {
            if (scanf("%d", &graph[row][column]) != 1 || graph[row][column] < 0) {
                printf("Invalid weight. Dijkstra's algorithm requires non-negative weights.\n");
                return 1;
            }
        }
    }
    printf("Enter source vertex (1-%d): ", count);
    if (scanf("%d", &start) != 1 || start < 1 || start > count) {
        printf("Invalid source vertex.\n");
        return 1;
    }

    for (int vertex = 0; vertex < count; vertex++) {
        distance[vertex] = INFINITY_VALUE;
        parent[vertex] = -1;
    }
    distance[start - 1] = 0;

    for (int step = 0; step < count; step++) {
        int current = -1;
        for (int vertex = 0; vertex < count; vertex++) {
            if (!visited[vertex] &&
                (current == -1 || distance[vertex] < distance[current])) {
                current = vertex;
            }
        }
        if (current == -1 || distance[current] == INFINITY_VALUE) {
            break;
        }
        visited[current] = 1;
        for (int neighbor = 0; neighbor < count; neighbor++) {
            if (graph[current][neighbor] > 0 && !visited[neighbor] &&
                distance[current] + graph[current][neighbor] < distance[neighbor]) {
                distance[neighbor] = distance[current] + graph[current][neighbor];
                parent[neighbor] = current;
            }
        }
    }

    printf("Vertex  Distance  Path\n");
    for (int vertex = 0; vertex < count; vertex++) {
        printf("%6d  ", vertex + 1);
        if (distance[vertex] == INFINITY_VALUE) {
            printf("unreachable  -\n");
        } else {
            printf("%8lld  ", distance[vertex]);
            print_path(parent, vertex);
            printf("\n");
        }
    }
    return 0;
}

/*Algorithm
DIJKSTRA(graph, count, source)
    FOR vertex <- 0 TO count - 1
        distance[vertex] <- INFINITY
        parent[vertex] <- NIL
        visited[vertex] <- false
    source <- source - 1
    distance[source] <- 0

    FOR step <- 0 TO count - 1
        current <- NIL
        FOR vertex <- 0 TO count - 1
            IF NOT visited[vertex] AND
               (current = NIL OR distance[vertex] < distance[current]) THEN
                current <- vertex
        IF current = NIL OR distance[current] = INFINITY THEN BREAK
        visited[current] <- true
        FOR neighbor <- 0 TO count - 1
            IF graph[current][neighbor] > 0 AND NOT visited[neighbor] THEN
                candidate <- distance[current] + graph[current][neighbor]
                IF candidate < distance[neighbor] THEN
                    distance[neighbor] <- candidate
                    parent[neighbor] <- current

    FOR vertex <- 0 TO count - 1
        IF distance[vertex] = INFINITY THEN
            PRINT vertex + 1, "unreachable"
        ELSE
            PRINT vertex + 1, distance[vertex]
            PRINT_PATH(parent, vertex)

PRINT_PATH(parent, vertex)
    IF parent[vertex] != NIL THEN
        PRINT_PATH(parent, parent[vertex])
        PRINT " -> "
    PRINT vertex + 1
*/

/*Output:
Enter number of vertices (1-20): 5
Enter the 5 x 5 weight matrix (0 for no edge):
0 10 3 0 0
10 0 1 2 0
3 1 0 8 2
0 2 8 0 7
0 0 2 7 0
Enter source vertex (1-5): 1
Vertex  Distance  Path
     1         0  1
     2         4  1 -> 3 -> 2
     3         3  1 -> 3
     4         6  1 -> 3 -> 2 -> 4
     5         5  1 -> 3 -> 5
*/
