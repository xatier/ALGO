#include <iostream>


#ifdef R
void merge (int *a, int l, int m, int h) {
    static int b[n];
    int i = l, j = m+1, k = l;
    for (i = l; i <= h; i++)
        b[i] = a[i];
    while (i <= m && j <= h)
        if (b[i] < b[j]) a[k++] = b[i++];
        else a[k++] = b[j++];
    while (i <= m)  a[k++] = b[i++];
    while (j <= h)  a[k++] = b[j++];
}
#else
void merge (int *a, int l, int m, int h) {
    static int b[n];
    int i = l, j = m+1, k = l;
    while (i <= m && j <= h)
        if (a[i] < a[j]) b[k++] = a[i++];
        else b[k++] = a[j++];
    i = l;
    while (i <= m)  b[k++] = a[i++];
    while (j <= h)  b[k++] = a[j++];
    for (i = l; i <= h; i++)
        a[i] = b[i];
}
#endif

void msort(int *a, int l, int h) {
    if (l < h) {
        int m = (l+h) / 2;
        msort(a, l, m);
        msort(a, m+1, h);
        merge(a, l, m, h);
    }
}

int main (void) {
    int *a = new int[n];
    msort(a, 0, n-1);
}
