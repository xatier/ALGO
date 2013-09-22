#include <iostream>
#include <cstdio>


#ifdef R
void isort (int *a, int n) {
    for (int j = 1; j < n; j++) {
        int key = a[j], i = j-1;
        int l = 0, h = j-1, m;
        while (l < h ) {
            m = (l+h)/2;
            if (key < a[m])
                h = m - 1;
            else if (key > a[m])
                l = m + 1;
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
#else
void isort (int *a, int n) {
    for (int j = 1; j < n; j++) {
        int key = a[j], i = j-1;
        while (i >= 0 && a[i] > key) {
            a[i+1] = a[i];
            i--;
        }
        a[i+1] = key;
    }
}
#endif

int main (void) {
    int *a = new int[k];
    for (int i = 0; i < k; i++)
        a[i] = k-i;
    isort(a, k);
    for (int i = 0; i < k; i++)
        std::cout << a[i] << " ";
}
