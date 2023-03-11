#include <cstring>
#include <cstdio>
#define LL long long
int m;
struct mat
{
    static const int sz = 16;
    LL a[sz][sz];

    inline mat() { memset(a, 0, sizeof a); }

    inline mat operator-(const mat &T) const
    {
        mat res;
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
            {
                res.a[i][j] = (a[i][j] - T.a[i][j]) % m;
            }
        return res;
    }

    inline mat operator+(const mat &T) const
    {
        mat res;
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
            {
                res.a[i][j] = (a[i][j] + T.a[i][j]) % m;
            }
        return res;
    }

    inline mat operator*(const mat &T) const
    {
        mat res;
        int r;
        for (int i = 0; i < sz; ++i)
            for (int k = 0; k < sz; ++k)
            {
                r = a[i][k];
                for (int j = 0; j < sz; ++j)
                    (res.a[i][j] += T.a[k][j] * r) %= m;
            }
        return res;
    }

    inline mat operator^(LL x) const
    {
        mat res, bas = *this;
        for (int i = 0; i < sz; ++i)
            res.a[i][i] = 1;
        while (x)
        {
            if (x & 1)
                res = res * bas;
            bas = bas * bas;
            x >>= 1;
        }
        return res;
    }
};
int main()
{
    for (int d, n; scanf("%d%d%d", &d, &n, &m), d && n && m;)
    {
        mat A, F;
        for (int i = 0; i < d - 1; ++i)
            A.a[i][i + 1] = 1;
        for (int j = 0; j < d; ++j)
            scanf("%lld", &A.a[d - 1][d - 1 - j]);
        for (int i = 0; i < d; ++i)
            scanf("%lld", &F.a[i][0]);
        printf("%lld\n", ((A ^ (n - d)) * F).a[d - 1][0]);
    }
    return 0;
}
