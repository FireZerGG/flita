#include <stdio.h>
#include <stdlib.h>

int check_connect(int *visited, int V)
{
    for (int i = 0; i < V; ++i) {
        if (visited[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    int V = 0; // vertex num
    int E = 0; // edge num

    // char buf[10000] = {0};
    // scanf("%10000s", buf);

    if (argc > 2) {
        FILE *input = fopen(argv[1], "r");
        FILE *output = fopen(argv[2], "w+");
        if (!input || !output) {
            printf("Can't open file\n");
            return 1;
        }

        int graph[1000][1000] = {{0}};
        char vertex[1000][1000] = {{0}}; // char *vertex[1000]

        while (fscanf(input, "%10000s", vertex[V]) == 1) {
            char c = 0;
            E = 0;
            while ((c = fgetc(input)) != '\n' && c != EOF) {
                if (c != ' ') {
                    if (c != '0' && c != '1') {
                        printf("Incorrect input\n");
                        fclose(input);
                        fclose(output);
                        return 2;
                    }
                    graph[V][E] = c - '0';
                    E++;
                }
            }
            V++;
        }

        int visited[1000] = {0};
        visited[0] = 1;
        fprintf(output, "graph {\n");
        for (int i = 0; i < E; ++i) {
            int start_idx = -1;
            int finish_idx = -1;
            for (int j = 0; j < V; ++j) {
                if (graph[j][i] == 1) {
                    if (start_idx == -1) {
                        start_idx = j;
                    } else if (finish_idx == -1) {
                        finish_idx = j;
                        j = V;
                    }
                }
            }
            if (start_idx != -1) {
                if (finish_idx != -1) {
                    if (visited[start_idx] == 1) {
                        visited[finish_idx] = 1;
                    } else if (visited[finish_idx] == 1) {
                        visited[start_idx] = 1;
                    }
                    fprintf(output, "\t%s -- %s;\n", vertex[start_idx], vertex[finish_idx]);
                } else {
                    fprintf(output, "\t%s -- %s;\n", vertex[start_idx], vertex[start_idx]);
                }
            }
        }
        for (int i = 0; i < V; ++i) {
            int sum = 0;
            for (int j = 0; j < E; ++j) {
                sum += graph[i][j];
            }
            if (sum == 0) {
                fprintf(output, "\t%s;\n", vertex[i]);
            }
        }
        fprintf(output, "}");
        int flag = check_connect(visited, V);
        if (flag) {
            printf("Graph is connected\n");
        } else {
            printf("Graph is not connected\n");
        }

        fclose(input);
        fclose(output);
        system("dot -Tpng graph.gv -o graph.png");
        system("eog graph.png"); // eog will not work on windows, use just system("graph.png");
    } else {
        printf("No file\n");
        return 3;
    }
    return 0;
}