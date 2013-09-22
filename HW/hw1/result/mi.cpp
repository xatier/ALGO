#include <iostream>


void isort (int *a, int n) {
    for (int j = 1; j < n; j++) {
        int key = a[j], i = j-1;
        int l = 0, h = j-1, m;
        while (l < h ) {
            m = (l+h)/2;
            if (key < a[m])
                h = m-1;
            else if (key > a[m])
                l = m+1;
            else
                break;
        }
        while (i >= l) {
            a[i+1] = a[i];
            i--;
        }
        a[l] = key;
    }
}
void merge (int *a, int l, int m, int h) {
    static int b[N];
    int i = l, j = m+1, k = l;
    for (i = l; i <= h; i++)
        b[i] = a[i];
    i = l;
    while (i <= m && j <= h)
        if (b[i] < b[j]) a[k++] = b[i++];
        else a[k++] = b[j++];
    while (i <= m)  a[k++] = b[i++];
    while (j <= h)  a[k++] = b[j++];
}

void msort(int *a, int l, int h) {
    if (l < h) {
        int m = (l+h) / 2;
        if (h-l < 10)
            isort(a+l, h-l+1);
        else {
            msort(a, l, m);
            msort(a, m+1, h);
            merge(a, l, m, h);
        }
    }
}

int main (void) {
    int *a = new int[N];
//    for (int i = 0; i < N; i++) {
//        a[i] = N-i;
//    }
    msort(a, 0, N-1);
//    for (int i = 0; i < N; i++) {
//        std::cout << a[i] << " ";
//    }
}
