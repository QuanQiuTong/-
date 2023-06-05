#include <bits/stdc++.h>
using namespace std;
#define read() ({long long x,f=1,c;while((c=getchar())<48||c>57)if(c=='-')f=-1;for(x=c^48;(c=getchar())>47&&c<58;)x=x*10+(c^48);x*f; })
template <typename T, int N>
class SegmentTree
{
    int n, L, R;
    T sum[N], k, lz[N];
#define ls (o << 1)
#define rs (o << 1 | 1)
#define mid (l + r >> 1)
#define pu (sum[o] = sum[ls] + sum[rs])
#define pd                                               \
    do                                                   \
        if (lz[o])                                       \
        {                                                \
            sum[ls] += (mid - l + 1) * lz[o];            \
            sum[rs] += (r - mid) * lz[o];                \
            lz[ls] += lz[o], lz[rs] += lz[o], lz[o] = 0; \
        }                                                \
    while (0)

    void build(int o, int l, int r)
    {
        if (l == r)
            sum[o] = read();
        else
            build(ls, l, mid), build(rs, mid + 1, r), pu;
    }
    void _add(int o, int l, int r)
    {
        if (R < l || r < L)
            return;
        if (L <= l && r <= R)
        {
            sum[o] += (r - l + 1) * k;
            lz[o] += k;
            return;
        }
        pd;
        if (L <= mid)
            _add(ls, l, mid);
        if (mid < R)
            _add(rs, mid + 1, r);
        pu;
    }
    T qry(int o, int l, int r)
    {
        if (R < l || r < L)
            return 0;
        if (L <= l && r <= R)
            return sum[o];
        pd;
        T ret = (L <= mid ? qry(ls, l, mid) : 0) + (mid < R ? qry(rs, mid + 1, r) : 0);
        pu;
        return ret;
    }

public:
    SegmentTree() {}
    SegmentTree(int _n) { init(_n); }
    void init(int _n) { build(1, 1, n = _n); }
    void add(int l, int r, const T &diff) { L = l, R = r, k = diff, _add(1, 1, n); }
    T query(int l, int r) { return (L = l, R = r, qry(1, 1, n)); }
#undef mid
};
SegmentTree<long long, int(4e5)> t;
int main()
{
    int n = read(), _ = read();
    t.init(n);
    for (; _--;)
    {
        if (read() == 1)
        {
            auto l = read(), r = read(), k = read();
            t.add(l, r, k);
        }
        else
        {
            auto l = read(), r = read();
            printf("%lld\n", t.query(l, r));
        }
    }
    return 0;
}
