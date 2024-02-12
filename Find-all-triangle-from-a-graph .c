#include <stdio.h>

struct Node {
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};

// Global variable
int total_adj_path = 0, adj_arr[1000][2];

// Function to add a node to the graph
int addNode(struct Node *p, int nid, int count) {
    total_adj_path++;
    int i = 0, ncount = count;

    // Check if the node with the given id already exists
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid) {
            break;
        }
    }

    // If not found, add a new node
    if (i == count) {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }

    return ncount;
}

// Function to add an adjacent node with a cost to a given node
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count) {
    int i = 0, index;

    // Finding the node with the given id
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid1) {
            int c = p[i].adjcount;

            // Add the adjacent node and its cost
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c + 1;

            break;
        }
    }
}

// Function to check if a node is already present in the list
int added(int *list, int lcount, int nid) {
    int i = 0;
    for (i = 0; i < lcount; i++) {
        if (list[i] == nid) {
            return 1;
        }
    }
    return 0;
}

// Recursive function to find paths from start to end node in the graph
void findpath(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount) {
    int index = 0, i = 0;

    // Checking if the list contains the end node
    if (list[lcount - 1] == end) {
        int tcost = 0;

        for (i = 0; i < lcount; i++) {
            tcost += clist[i];
        }

        return;
    }

    // Finding the index of the start node in the graph
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == start) {
            index = i;
            break;
        }
    }

    // Explore adjacent nodes and recursively find paths
    for (i = 0; i < p[index].adjcount; i++) {
        int a = added(list, lcount, p[index].adjs[i]);
        if (a == 0) {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            findpath(p, count, p[index].adjs[i], end, list, clist, lcount);

            lcount--;
        }
    }
}

// Function to find triangular paths in the graph
void find_triangle(struct Node *nodes, int n_adj) {
    printf("\n");

    for (int i = 0; i < n_adj; i++) {
        for (int j = i + 1; j < n_adj; j++) {
            if (adj_arr[j][0] == adj_arr[i][0]) {
                for (int k = i + 1; k < n_adj; k++) {
                    if (adj_arr[j][1] == adj_arr[k][0]) {
                        if (adj_arr[k][1] == adj_arr[i][1])
                            printf("%d %d %d\n", adj_arr[i][0], adj_arr[i][1], adj_arr[k][0]);
                    } else if (adj_arr[j][1] == adj_arr[k][1]) {
                        if (adj_arr[k][0] == adj_arr[i][1])
                            printf("%d %d %d\n", adj_arr[i][0], adj_arr[i][1], adj_arr[k][1]);
                    }
                }
            } else if (adj_arr[j][1] == adj_arr[i][0]) {
                for (int k = i + 1; k < n_adj; k++) {
                    if (adj_arr[j][0] == adj_arr[k][0]) {
                        if (adj_arr[k][1] == adj_arr[i][1])
                            printf("%d %d %d\n", adj_arr[i][0], adj_arr[i][1], adj_arr[k][0]);
                    } else if (adj_arr[j][0] == adj_arr[k][1]) {
                        if (adj_arr[k][0] == adj_arr[i][1])
                            printf("%d %d %d\n", adj_arr[i][0], adj_arr[i][1], adj_arr[k][1]);
                    }
                }
            }
        }
    }
}

int main() {
    struct Node nodes[50];
    int nodecount = 0;
    int n1 = 0, n2 = 0, c = 0;

    // Input nodes and edges of the graph
    for (int i = 0;; i++) {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);

        adj_arr[i][0] = n1;
        adj_arr[i][1] = n2;

        // Break the loop if input is -9
        if (n1 == -9 || n2 == -9 || c == -9) {
            break;
        }

        // Add nodes and edges to the graph
        nodecount = addNode(&nodes[0], n1, nodecount);
        nodecount = addNode(&nodes[0], n2, nodecount);

        addAdjacent(&nodes[0], n1, n2, c, nodecount);
        addAdjacent(&nodes[0], n2, n1, c, nodecount);
    }

    int start, end;
    int list[50], clist[50], lcount = 0;

    // Input start and end nodes
    printf("start, end ? ");
    scanf("%d %d", &start, &end);
    list[0] = start;
    clist[0] = 0;
    lcount = 1;

    // Find and print paths
    findpath(nodes, nodecount, start, end, list, clist, lcount);

    // Calculate the total number of adjacent paths
    total_adj_path /= 2;

    printf("\nTriangular paths are: ");
    // Find and print triangular paths
    find_triangle(nodes, total_adj_path);

    return 0;
}
