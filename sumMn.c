#include <stdio.h>

int sumMN(int m, int n) {
    int sum = 0;
    for (int a = m; a < n + 1; ++a) {
        sum += a;
    }
    return sum;
}
int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    printf("sum = %d\n", sumMN(m, n));
    return 0
}