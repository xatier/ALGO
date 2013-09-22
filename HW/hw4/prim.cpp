#include <iostream>
#include <cstdio>
#include <queue>

struct node {
    char p;
    char me;
    int key;
};

bool operator < (const struct node &a, const struct node &b) {
    return a.key > b.key;
}

class myq : public std::priority_queue<struct node> {
public:
    // is me in the q?
    bool find (char me) {
        struct node n;
        std::vector<struct node> tmp;
        while (!this->empty()) {
            n = this->top();
            if (n.me == me) {
                // restore
                for (auto &x : tmp) {
                    this->push(x);
                }
                return 1;
            }
            tmp.push_back(n);
            this->pop();
        }
        for (auto &x : tmp) {
            this->push(x);
        }
        return 0;
    }

    // get key
    int key (char me) {
        struct node n;
        std::vector<struct node> tmp;
        while (!this->empty()) {
            n = this->top();
            if (n.me == me) {
                for (auto &x : tmp) {
                    this->push(x);
                }
                return n.key;
            }
            tmp.push_back(n);
            this->pop();
        }
        for (auto &x : tmp) {
            this->push(x);
        }
        return -1;
    }

    // set key
    void decrease_key (char me, int key) {
        struct node n;
        std::vector<struct node> tmp;
        while (!this->empty()) {
            n = this->top();
            if (n.me == me) {
                this->pop();
                n.key = key;
                this->push(n);
                for (auto &x : tmp) {
                    this->push(x);
                }
                return;
            }
            tmp.push_back(n);
            this->pop();
        }
    }

    // set p value
    void setp (char me, char p) {
        struct node n;
        std::vector<struct node> tmp;
        while (!this->empty()) {
            n = this->top();
            if (n.me == me) {
                this->pop();
                n.p = p;
                this->push(n);
                for (auto &x : tmp) {
                    this->push(x);
                }
                return;
            }
            tmp.push_back(n);
            this->pop();
        }
    }

};


void prim (int (&G)[9][9]) {
    myq q, out;
    struct node n;

    for (int i = 1; i < 9; i++) {
        n.key = 999;     // inf
        n.p = 0;         // null
        n.me = 'a' + i;
        q.push(n);
    }

    n.key = 0;     // r.key = 0
    n.p = 0;       // null
    n.me = 'a';    // start from a
    q.push(n);

    while (!q.empty()) {
        n = q.top();
        q.pop();
        out.push(n);
        for (int i = 0; i < 9; i++) {
            if (G[n.me-'a'][i] != 999) {   // for each v in G.add[u]
                if (q.find(i+'a') && G[n.me-'a'][i] < q.key(i+'a')) {
                    q.setp(i+'a', n.me);
                    q.decrease_key(i+'a', G[n.me-'a'][i]);
                }
            }
        }
    }

    out.pop();
    while (!out.empty()) {
        n = out.top();
        std::cout << "(" << n.me << ", " << n.p << ") ";
        out.pop();
    }
    std::cout << std::endl;
}


int main (void) {

    int G1[9][9];
    int G2[9][9];

    std::cout << "Prim's algorithm for graph in lecture\n";
    // clear G1 & G2
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            G2[i][j] = G1[i][j] = 999;
        }
    }

    // adj matrix
    G1[0][1] = G1[1][0] = 10;
    G1[0][2] = G1[2][0] = 12;
    G1[1][2] = G1[2][1] = 9;
    G1[1][3] = G1[3][1] = 8;
    G1[2][4] = G1[4][2] = 3;
    G1[3][4] = G1[4][3] = 7;
    G1[2][5] = G1[5][2] = 1;
    G1[4][5] = G1[5][4] = 3;
    G1[3][7] = G1[7][3] = 5;
    G1[5][7] = G1[7][5] = 6;
    G1[3][6] = G1[6][3] = 8;
    G1[6][7] = G1[7][6] = 9;
    G1[6][8] = G1[8][6] = 2;
    G1[7][8] = G1[8][7] = 11;


    prim(G1);


    // G2
    std::cout << "Prim's algorithm for graph in book\n";

    // adj matrix
    G2[0][1] = G2[1][0] = 4;
    G2[0][7] = G2[7][0] = 8;
    G2[1][7] = G2[7][1] = 11;
    G2[1][2] = G2[2][1] = 8;
    G2[7][8] = G2[8][7] = 7;
    G2[2][8] = G2[8][2] = 2;
    G2[6][7] = G2[7][6] = 1;
    G2[6][8] = G2[8][6] = 6;
    G2[2][5] = G2[5][2] = 4;
    G2[5][6] = G2[6][5] = 2;
    G2[2][3] = G2[3][2] = 7;
    G2[3][4] = G2[4][3] = 9;
    G2[3][5] = G2[5][3] = 14;
    G2[3][4] = G2[4][3] = 10;

    prim(G2);

    return 0;
}
