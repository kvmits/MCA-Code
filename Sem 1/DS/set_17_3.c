// Set 17.3 - Kruskal's algorithm for a minimum cost spanning tree.

#include <stdio.h>

#define MAX_VERTICES 20
#define MAX_EDGES 190

struct edge {
    int from;
    int to;
    int weight;
};

int find_root(int parent[], int vertex)
{
    if (parent[vertex] != vertex) {
        parent[vertex] = find_root(parent, parent[vertex]);
    }
    return parent[vertex];
}

int main(void)
{
    struct edge edges[MAX_EDGES];
    int parent[MAX_VERTICES], rank[MAX_VERTICES] = {0};
    int count, edge_count, total_cost = 0, selected_count = 0;

    printf("Enter number of vertices (1-%d): ", MAX_VERTICES);
    if (scanf("%d", &count) != 1 || count < 1 || count > MAX_VERTICES) {
        printf("Invalid number of vertices.\n");
        return 1;
    }
    printf("Enter number of edges (0-%d): ", MAX_EDGES);
    if (scanf("%d", &edge_count) != 1 || edge_count < 0 || edge_count > MAX_EDGES) {
        printf("Invalid number of edges.\n");
        return 1;
    }
    for (int index = 0; index < edge_count; index++) {
        printf("Enter edge %d (from to weight): ", index + 1);
        if (scanf("%d %d %d", &edges[index].from, &edges[index].to,
                  &edges[index].weight) != 3 ||
            edges[index].from < 1 || edges[index].from > count ||
            edges[index].to < 1 || edges[index].to > count) {
            printf("Invalid edge.\n");
            return 1;
        }
        edges[index].from--;
        edges[index].to--;
    }

    for (int index = 0; index < count; index++) {
        parent[index] = index;
    }
    for (int index = 1; index < edge_count; index++) {
        struct edge current = edges[index];
        int position = index - 1;
        while (position >= 0 && edges[position].weight > current.weight) {
            edges[position + 1] = edges[position];
            position--;
        }
        edges[position + 1] = current;
    }

    printf("Edges in the minimum spanning tree:\n");
    for (int index = 0; index < edge_count && selected_count < count - 1; index++) {
        int first_root = find_root(parent, edges[index].from);
        int second_root = find_root(parent, edges[index].to);
        if (first_root != second_root) {
            if (rank[first_root] < rank[second_root]) {
                parent[first_root] = second_root;
            } else if (rank[first_root] > rank[second_root]) {
                parent[second_root] = first_root;
            } else {
                parent[second_root] = first_root;
                rank[first_root]++;
            }
            printf("%d - %d : %d\n", edges[index].from + 1,
                   edges[index].to + 1, edges[index].weight);
            total_cost += edges[index].weight;
            selected_count++;
        }
    }

    if (selected_count != count - 1) {
        printf("Graph is disconnected; spanning tree does not exist.\n");
    } else {
        printf("Minimum cost: %d\n", total_cost);
    }
    return 0;
}

/*Algorithm
FIND_ROOT(parent, vertex)
    IF parent[vertex] != vertex THEN
        parent[vertex] <- FIND_ROOT(parent, parent[vertex])
    RETURN parent[vertex]

KRUSKAL(count, edges, edge_count)
    FOR vertex <- 0 TO count - 1
        parent[vertex] <- vertex
        rank[vertex] <- 0

    SORT edges[0..edge_count-1] BY weight ascending
    selected_count <- 0
    total_cost <- 0

    FOR index <- 0 TO edge_count - 1
        first_root <- FIND_ROOT(parent, edges[index].from)
        second_root <- FIND_ROOT(parent, edges[index].to)
        IF first_root != second_root THEN
            IF rank[first_root] < rank[second_root] THEN
                parent[first_root] <- second_root
            ELSE IF rank[first_root] > rank[second_root] THEN
                parent[second_root] <- first_root
            ELSE
                parent[second_root] <- first_root
                rank[first_root] <- rank[first_root] + 1
            PRINT edges[index]
            total_cost <- total_cost + edges[index].weight
            selected_count <- selected_count + 1
        IF selected_count = count - 1 THEN BREAK

    IF selected_count != count - 1 THEN
        PRINT "DISCONNECTED"
    ELSE
        PRINT total_cost
*/

/*Output:
Enter number of vertices (1-20): 5
Enter number of edges (0-190): 7
Enter edge 1 (from to weight): 1 2 2
Enter edge 2 (from to weight): 1 4 6
Enter edge 3 (from to weight): 2 3 3
Enter edge 4 (from to weight): 2 4 8
Enter edge 5 (from to weight): 2 5 5
Enter edge 6 (from to weight): 3 5 7
Enter edge 7 (from to weight): 4 5 9
Edges in the minimum spanning tree:
1 - 2 : 2
2 - 3 : 3
2 - 5 : 5
1 - 4 : 6
Minimum cost: 16
*/
