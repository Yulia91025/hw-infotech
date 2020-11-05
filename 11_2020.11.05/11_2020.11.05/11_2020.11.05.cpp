#include <iostream>
using namespace std;

int rec(int l, int r, int* a, int k) {
    if (l >= r) {
        return a[l];
    }

    int m = (l + r) / 2;
    int p = a[m];

    int pi = l;
    for (int i = l; i < r; i++) {
        if (a[i] < p) {
            pi++;
        }
    }
    if (pi == k) {
        return p;
    }

    int i = l;
    int j = r - 1;
    while (i < j) {
        while (a[i] < p) i++;
        while (a[j] > p) j--;
        if (i < j) {
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    }

    if (k < pi) {
        return rec(l, pi, a, k);
    }
    else {
        return rec(pi + 1, r, a, k);
    }
}

int p(int n, int* a, int k) {
    return rec(0, n, a, k);
}


int main() {
    int k, n;
    cin >> k >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cout << p(n, a, k - 1);
}