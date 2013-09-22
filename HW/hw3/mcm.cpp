#include <iostream>
#include <vector>
#include <map>

static std::vector<std::string> stack;
static std::map<std::string, int> output;

void pop(const std::vector< std::vector<int> >& s, int i, int j) {
    if (i == j) {
        std::cout << "A" << i;
    }
    else {
        std::cout << "(";
        pop(s, i, s[i][j]);
        pop(s, s[i][j]+1, j);
        std::cout << ")";
    }
}

void mcm(const std::vector<int>& p) {
    int n = p.size()-1;
    std::cout << n << std::endl;
    // s[1..n][1..n]
    std::vector< std::vector<int> >s(n+1, std::vector<int>(n+1));
    // m[1..n][1..n]
    std::vector< std::vector<int> >m(n+1, std::vector<int>(n+1));

    for (int i = 1; i <= n; i++)
        m[i][i] = 0;

    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n-l+1; i++) {
            int j = i+l-1;
            m[i][j] = 1<<30;
            for (int k = i; k <= j-1; k++) {
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    std::cout << m[1][n] << " scalar multiplications" << std::endl;
    pop(s, 1, n);
    std::cout << "\n";
}

void testing_mcm (const std::vector<int>& p) {
    static int test=0;
    std::cout << "Test " << ++test << "...\n";
    mcm(p);
    std::cout << std::endl;
}

int main (void) {
    testing_mcm({30, 35, 15, 5, 10, 20, 25});
    testing_mcm({3, 3, 3, 3, 3});
    testing_mcm({2, 2, 3, 2, 2, 3, 3, 2});
    return 0;
}
