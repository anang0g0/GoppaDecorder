#include <stdio.h>
//using namespace std;

long long modinv(long long a, long long m) {
    long long b = m, u = 1, v = 0,tmp;
    while (b) {
        printf("b=%lld\n",b);
        long long t = a / b;
        printf("t=%lld\n",t);
        a -= t * b;
         tmp=a;
         a=b;
         b=tmp;
        u -= t * v; 
        tmp=u;
        u=v;
        v=tmp;
    }
    u %= m; 
    if (u < 0) u += m;
    return u;
}

int main() {
    // mod. 13 での逆元を求めてみる
    for (int i = 1; i < 13; ++i) {
        printf("%d 's inv; %lld\n", i,modinv(i, 13));
    }
}