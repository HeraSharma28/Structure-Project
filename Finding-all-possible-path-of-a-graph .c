
/*Finding-all-possible-path-of-a-graph*/

#include <stdio.h>

// Define the Node structure to represent a graph node
struct Node {
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};

// Global variables
int num_visa, a_index_c = 0;
int index_list[1000], arr1[1000][50];

// Function to add a node to the graph
int addNode(struct Node *p, int nid, int count) {
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

    // Find the node with the given id
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
void findpath(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount, int *visa) {
    int index = 0, i = 0, arr[1000], pathNode_c = 0;

    // Check if the list contains the end node
    if (list[lcount - 1] == end) {
        printf("\n");

        // Print the path and calculate total cost
        int tcost = 0;
        for (i = 0; i < lcount; i++) {
            printf("%d ", list[i]);
            pathNode_c++;
            arr[i] = list[i];
            tcost += clist[i];
        }

        int compare_c = 0;

        // Check if the path contains at most num_visa visa nodes
        if (pathNode_c - 1 <= num_visa) {
            for (int i = 1; i < pathNode_c; i++) {
                for (int j = 0; j < num_visa; j++) {
                    if (arr[i] == visa[j])
                        compare_c++;
                }
            }
        }

        // If the path is valid, store it in the arr1 array
        if (compare_c == pathNode_c - 1) {
            int indx_c = 0;
            for (int i = 0; i < pathNode_c; i++) {
                indx_c++;
                arr1[a_index_c][i] = arr[i];
            }
            index_list[a_index_c] = indx_c;
            a_index_c++;
        }
        return;
    }

    // Find the index of the start node in the graph
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

            findpath(p, count, p[index].adjs[i], end, list, clist, lcount, visa);
            lcount--;
        }
    }
}

// Main function
int main() {
    struct Node nodes[50];
    int nodecount = 0;
    int n1 = 0, n2 = 0, c = 0;

    // Input nodes and edges of the graph
    while (1) {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);

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

    // Input start and end nodes
    printf("start, end ? ");
    scanf("%d %d", &start, &end);

    // Initialize arrays for path and cost
    int list[50], clist[50], lcount = 0;
    list[0] = start;
    clist[0] = 0;
    lcount = 1;

    // Input the number of visa nodes and the visa nodes
    printf("Number of Visa: ");
    scanf("%d", &num_visa);
    printf("Put Visa Node: ");
    int visa[num_visa];

    for (int i = 0; i < num_visa; i++)
        scanf("%d", &visa[i]);

    // Find and print paths satisfying the conditions
    findpath(nodes, nodecount, start, end, list, clist, lcount, visa);
    printf("\n\n");

    // Print stored paths
    for (int k = 0; k < a_index_c; k++) {
        for (int l = 0; l < index_list[k]; l++) {
            printf("%d ", arr1[k][l]);
        }
        printf("\n");
    }

    return 0;
}
