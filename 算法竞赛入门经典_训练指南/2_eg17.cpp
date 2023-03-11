// #pragma GCC optimize(2)
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read()
{
    int x, ch, f = 1;
    while ((ch = getchar()) < 48 || 57 < ch)
        if (ch == '-')
            f = -1;
    for (x = ch ^ 48; 47 < (ch = getchar()) && ch < 58; x = x * 10 + (ch ^ 48))
        ;
    return x * f;
}
const int N = 1e6 + 2;
int primes[N], prime_cnt;
void sieve()
{
    int &cnt = prime_cnt, *p = primes - 1; // 需要翻译i

    static bool v[N];
    cnt = 2, p[1] = 2, p[2] = 3;
    for (int i = 5, ff = 1, j; i <= N; ff ^= 1, i += 1 + ff << 1)
    {
        if (!v[i])
            p[++cnt] = i;
        for (j = 3; j <= cnt && p[j] * i <= N; ++j)
        {
            v[p[j] * i] = 1;
            if (i % p[j] == 0)
                break;
        }
    }
}
double dp(int x)
{
    static bool vis[N];
    static double f[N];
    if (x == 1)
        return 0.0; // 边界
    if (vis[x])
        return f[x]; // 记忆化
    vis[x] = 1;
    double &ans = f[x];
    int g = 0, p = 0; // 累加g(x)和p(x)
    ans = 0;
    for (int i = 0; i < prime_cnt && primes[i] <= x; i++)
    {
        p++;
        if (x % primes[i] == 0)
        {
            g++;
            ans += dp(x / primes[i]);
        }
    }
    ans = (ans + p) / g;
    return ans;
}
int main()
{
    sieve();

    for (int t = read(), i = 0; ++i <= t;)
        printf("Case %d: %.10lf\n", i, dp(read()));
    return 0;
}