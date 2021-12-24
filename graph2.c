#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

int check_connect(int *visited, int V)
{
    for (int i = 0; i < V; ++i) {
        if (visited[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int count_vertexes_by_degree(int **graph, int degree, int v)
{
    if (!graph || (v < 2 && degree > 0) || degree >= v) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < v; ++i) {
        int degree_i = 0;
        for (int j = 0; j < v; ++j) {
            if (i != j && graph[i][j] != 0) {
                degree_i++;
            }
        }
        if (degree_i == degree) {
            count++;
        }
    }
    return count;
}

int main(int argc, char *argv[])
{
    int V = 0; // vertex num
    int E = 0; // edge num
    if (argc > 1) {
        FILE *input = fopen(argv[1], "r");
        if (!input) {
            printf("Can't open file\n");
            return 1;
        }

        int **graph = calloc(MAX_SIZE, sizeof(int *));
        char **vertex = calloc(MAX_SIZE, sizeof(char *));

        int degree = 0;
        if (scanf("%d", &degree) != 1) {
            printf("Can't read degree\n");
            fclose(input);
            return 2;
        }
        vertex[V] = calloc(MAX_SIZE, sizeof(char));
        while (fscanf(input, "%1000s", vertex[V]) == 1) {
            char c = 0;
            E = 0;
            graph[V] = calloc(MAX_SIZE, sizeof(int));
            while ((c = fgetc(input)) != '\n' && c != EOF) {
                if (c != ' ' && c != '\r') {
                    if (c != '0' && c != '1') {
                        printf("Incorrect edge input\n");
                        fclose(input);
                        return 3;
                    }
                    graph[V][E] = c - '0';
                    E++;
                }
            }
            V++;
            vertex[V] = calloc(MAX_SIZE, sizeof(char));
        }
        int count = 0;
        count = count_vertexes_by_degree(graph, degree, V);
        printf("Number of vertexes with given degree(%d): %d\n", degree, count);

        for (int i = 0; i < V; ++i) {
            free(vertex[i]);
            free(graph[i]);
        }
        free(vertex[V]);
        free(vertex);
        free(graph);
        fclose(input);
    }
    return 0;
}