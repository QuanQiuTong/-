#include <stdio.h>
typedef long long ll;
typedef const int ct;
#define N 400005
int n, L, R;
ll sum[N], k, lz[N];
#define read() ({long long x,f=1,c;while((c=getchar())<48||c>57)if(c=='-')f=-1;for(x=c^48;(c=getchar())>47&&c<58;)x=x*10+(c^48);x*f; })
#define ls i << 1
#define rs i << 1 | 1
#define mid (l + r >> 1)
#define pu sum[i] = sum[ls] + sum[rs]
#define pd                                \
    {                                     \
        sum[ls] += (mid - l + 1) * lz[i]; \
        sum[rs] += (r - mid) * lz[i];     \
        lz[ls] += lz[i];                  \
        lz[rs] += lz[i];                  \
        lz[i] = 0;                        \
    }
void bld(ct i, ct l, ct r)
{
    // printf("*%d %d %d\n",i,l,r);
    if (l == r)
    {
        sum[i] = read();
        return;
    }
    bld(ls, l, mid);
    bld(rs, mid + 1, r);
    pu;
}
void add(ct i, ct l, ct r)
{
    if (R < l || r < L)
        return;
    if (L <= l && r <= R)
    {
        sum[i] += (r - l + 1) * k;
        lz[i] += k;
        return;
    }
    if (lz[i])
        pd;
    if (L <= mid)
        add(ls, l, mid);
    if (mid < R)
        add(rs, mid + 1, r);
    pu;
}
ll qry(ct i, ct l, ct r)
{
    if (R < l || r < L)
        return 0;
    if (L <= l && r <= R)
        return sum[i];
    if (lz[i])
        pd;
    ll ret = (L <= mid ? qry(ls, l, mid) : 0);
    if (mid < R)
        ret += qry(rs, mid + 1, r);
    pu;
    return ret;
}
int main()
{
    int m, f;
    n = read();
    m = read();
    bld(1, 1, n);
    while (m--)
    {
        f = read();
        L = read();
        R = read();
        if (f == 1)
            k = read(), add(1, 1, n);
        else
            printf("%lld\n", qry(1, 1, n));
    }
    return 0;
}
