#include "utils.h"

int get_num_of_digits(int x) {
    x = x < 0 ? -x : x;
    int cnt = 0;
    while (x > 0) {
        x /= 10;
        ++cnt;
    }
    return cnt;
}

void print_adj_matrix(int num_of_nodes, int **adjacency_matrix) {
    int max_width_of_node_id = get_num_of_digits(num_of_nodes);
    printf("\n-------- adjacency matrix of the graph --------\n");
    printf("%*c   ", max_width_of_node_id,
           ' '); // whitespace before the IDs for columns
    // ID for columns
    for (int i = 0; i < num_of_nodes; ++i) {
        printf("%*d ", max_width_of_node_id, i + 1);
    }
    printf("\n");
    printf("%*c___", max_width_of_node_id, '_');
    for (int i = 0; i < num_of_nodes; ++i) {
        printf("%*c_", max_width_of_node_id, '_');
    }
    printf("\n");
    for (int i = 0; i < num_of_nodes; ++i) {
        printf("%*d | ", max_width_of_node_id, i + 1); // ID for the row
        for (int j = 0; j < num_of_nodes; ++j) {
            printf("%*d ", max_width_of_node_id, adjacency_matrix[i][j]);
        }
        printf("\n");
    }
}

void print_adj_list(int num_of_nodes, node_t *adjacency_list) {
    int max_width_of_node_id = get_num_of_digits(num_of_nodes);
    printf("\n-------- adjacency list of the graph --------\n");
    for (int i = 0; i < num_of_nodes; ++i) {
        printf("[node %*d]: ", max_width_of_node_id, i + 1);
        node_t *ptr_curr_node = &(adjacency_list[i]);
        while (1) {
            if (ptr_curr_node == NULL) {
                printf("x\n");
                break;
            }
            printf("%*d -> ", max_width_of_node_id, ptr_curr_node->id);
            ptr_curr_node = ptr_curr_node->next;
        }
    }
    printf("");
}

int **read_as_adj_matrix(int num_of_nodes) {
    // dynamically create a two dimentional array as adjacency matrix
    int **adjacency_matrix = (int **)calloc(num_of_nodes, sizeof(int *));
    for (int i = 0; i < num_of_nodes; ++i)
        adjacency_matrix[i] = (int *)calloc(num_of_nodes, sizeof(int));

    int max_width_of_node_id = get_num_of_digits(num_of_nodes);
    printf("Input the IDs of all adjacent node to the following nodes "
           "(seperated with space).\n");
    for (int i = 0; i < num_of_nodes; ++i) {
        printf("[node %*d]: ", max_width_of_node_id, i + 1);

        // read in a line of numbers seperated by space
        // e.g. "2 3 7\n"
        // reference: https://blog.csdn.net/BUPTSCSLJ/article/details/51023494
        int adj_node_id;
        while (1) {
            scanf("%d", &adj_node_id);
            // validate the inputted node ID (from 1~n and not equal to itself)
            if (adj_node_id < 1 || adj_node_id > num_of_nodes ||
                adj_node_id == i + 1) {
                printf("Illegal node ID\n");
                getchar();
                getchar();
                exit(-1);
            }
            adjacency_matrix[i][adj_node_id - 1] =
                adjacency_matrix[adj_node_id - 1][i] = 1;
            if (getchar() == '\n')
                break;
        }
    }

    return adjacency_matrix;
}

node_t *read_as_adj_lists(int num_of_nodes) {
    // index of adj_list = node ID - 1
    node_t *adj_list = malloc(sizeof(node_t) * num_of_nodes);

    int max_width_of_node_id = get_num_of_digits(num_of_nodes);
    printf("Input the IDs of all adjacent node to the following nodes "
           "(seperated with space).\n");
    for (int i = 0; i < num_of_nodes; ++i) {
        printf("[node %*d]: ", max_width_of_node_id, i + 1);

        // read in a line of adjacency node IDs seperated by space
        // e.g. "2 3 7\n"
        // reference: https://blog.csdn.net/BUPTSCSLJ/article/details/51023494
        int adj_node_id;
        node_t *ptr_curr_node = &(adj_list[i]);
        int is_first = 0;
        while (1) {
            scanf("%d", &adj_node_id);
            // validate the inputted node ID (from 1~n and not equal to itself)
            if (adj_node_id < 1 || adj_node_id > num_of_nodes ||
                adj_node_id == i + 1) {
                printf("Illegal node ID\n");
                getchar();
                getchar();
                exit(-1);
            }

            if (is_first == 0) {
                ptr_curr_node->id = adj_node_id;
                ptr_curr_node->next = NULL;
                is_first = 1;
            } else {
                // temporary variables in loop normally have fixed address, so
                // we need to dynamycally allocate memory
                node_t *next_node = (node_t *)malloc(sizeof(node_t));
                next_node->id = adj_node_id;
                next_node->next = NULL;
                ptr_curr_node->next = next_node;
            }

            if (getchar() == '\n') // read in whiltespace or newline
                break;
        }
    }

    return adj_list;
}
