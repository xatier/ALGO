#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    int s;
    int e;
    int w;
} Edge;

typedef struct {
    int v;
    int e;
    Edge edge[MAX];
} graph;

void make_G1(graph *G) {
    G->e = 14;
    G->v = 9;

    G->edge[0].s = 'a'; G->edge[0].e = 'b'; G->edge[0].w =  10;
    G->edge[1].s = 'a'; G->edge[1].e = 'c'; G->edge[1].w =  12;
    G->edge[2].s = 'b'; G->edge[2].e = 'c'; G->edge[2].w =  9;
    G->edge[3].s = 'b'; G->edge[3].e = 'd'; G->edge[3].w =  8;
    G->edge[4].s = 'c'; G->edge[4].e = 'e'; G->edge[4].w =  3;
    G->edge[5].s = 'd'; G->edge[5].e = 'e'; G->edge[5].w =  7;
    G->edge[6].s = 'c'; G->edge[6].e = 'f'; G->edge[6].w =  1;
    G->edge[7].s = 'e'; G->edge[7].e = 'f'; G->edge[7].w =  3;
    G->edge[8].s = 'd'; G->edge[8].e = 'h'; G->edge[8].w =  5;
    G->edge[9].s = 'f'; G->edge[9].e = 'h'; G->edge[9].w =  6;
    G->edge[10].s ='d'; G->edge[10].e ='g'; G->edge[10].w = 8;
    G->edge[11].s ='g'; G->edge[11].e ='h'; G->edge[11].w = 9;
    G->edge[12].s ='g'; G->edge[12].e ='i'; G->edge[12].w = 2;
    G->edge[13].s ='h'; G->edge[13].e ='i'; G->edge[13].w = 11;
}

void make_G2(graph *G) {
    G->e = 14;
    G->v = 9;

    G->edge[0].s = 'a'; G->edge[0].e = 'b'; G->edge[0].w =  4;
    G->edge[1].s = 'b'; G->edge[1].e = 'c'; G->edge[1].w =  8;
    G->edge[2].s = 'a'; G->edge[2].e = 'h'; G->edge[2].w =  8;
    G->edge[3].s = 'b'; G->edge[3].e = 'h'; G->edge[3].w =  11;
    G->edge[4].s = 'h'; G->edge[4].e = 'i'; G->edge[4].w =  7;
    G->edge[5].s = 'i'; G->edge[5].e = 'c'; G->edge[5].w =  2;
    G->edge[6].s = 'i'; G->edge[6].e = 'g'; G->edge[6].w =  6;
    G->edge[7].s = 'c'; G->edge[7].e = 'f'; G->edge[7].w =  4;
    G->edge[8].s = 'g'; G->edge[8].e = 'f'; G->edge[8].w =  2;
    G->edge[9].s = 'c'; G->edge[9].e = 'd'; G->edge[9].w =  7;
    G->edge[10].s ='d'; G->edge[10].e ='f'; G->edge[10].w = 14;
    G->edge[11].s ='f'; G->edge[11].e ='e'; G->edge[11].w = 10;
    G->edge[12].s ='d'; G->edge[12].e ='d'; G->edge[12].w = 9;
    G->edge[13].s ='h'; G->edge[13].e ='g'; G->edge[13].w = 1;

}

int cmp (const void *a, const void *b) {
    return ((Edge *)a)->w > ((Edge *)b)->w;
}

void kruskal (graph G) {
    int visited[MAX];
    int i, j;
    int ct = 0;
    int m1, m2;

    for (i = 0; i < G.v; i++)
        visited[i] = i;

    qsort(G.edge, G.e, sizeof(Edge), cmp);


    for (i = 0; i < G.e; i++) {
        // two nodes of an edge
        m1 = visited[G.edge[i].s - 'a'];
        m2 = visited[G.edge[i].e - 'a'];
        if (m1 != m2) {
            // go through
            for (j = 0; j < G.e; j++) {
                if (visited[j] == m1)
                    visited[j] = m2;
            }
            ct++;
            printf("(%c,%c) ", G.edge[i].s, G.edge[i].e);
            if (ct == G.v - 1)
                break;
        }
    }
    puts("");
}


int main(void) {
    graph G1, G2;
    puts ("Kruskal's algorithm for graph in lecture");
    make_G1(&G1);
    kruskal(G1);

    puts ("Kruskal's algorithm for graph in book");
    make_G2(&G2);
    kruskal(G2);
    return 0;
}
