#include <stdio.h>

int sumMN(int m, int n);
void pyramid(int n);
int main() {
    // int m, n;
    // scanf("%d %d", &m, &n);
    // printf("sum = %d\n", sumMN(m, n));
    pyramid(5);
    return 0;
}
int sumMN(int m, int n){
    int sum = 0;
    for (int a = m; a < n + 1; ++a) {
        sum += a;
    }
    
    return sum;
}

void pyramid(int n)  {
    int a = 1;
    
    for( ; a < n + 1 ; ++a) {
        int b = 0;
        int space = 0;
        for (; space < n-a; ++space) {
            printf(" ");
        }
        for (; b< a; ++b){
            printf("%d", a);
        }
        printf("\n");
    }
}