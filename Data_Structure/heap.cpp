#include <cstdio>
#include <cassert>
#define read() ({int x,c,f=1;while((c=getchar())<48||57<c)if(c=='-')f=-1;for(x=c^48;47<(c=getchar())&&c<58;x=x*10+(c^48));x*f; })
template <typename T>
class max_heap
{
    T heap[1000006];
    size_t sz;

public:
    max_heap() : sz(0) {}
    size_t size() const { return sz; }
    void push(const T &x)
    {
        size_t cur = ++sz;
        while (cur != 1 && heap[cur / 2] < x)
            heap[cur] = heap[cur / 2], cur /= 2;
        heap[cur] = x;
    }
    void pop()
    {
        assert(sz);
        heap[1].~T();
        T las = heap[sz--];
        size_t cur = 1, son = 2;
        while (son <= sz)
        {
            if (son < sz && heap[son] < heap[son + 1])
                son++;
            if (!(las < heap[son]))
                break;
            heap[cur] = heap[son], cur = son, son <<= 1;
        }
        heap[cur] = las;
    }
    T top() const { return heap[1]; }
};

struct gint
{
    int x;
    gint() = default;
    gint(int _x) : x(_x) {}
    bool operator<(gint rhs) const { return x > rhs.x; }
};

max_heap<gint> h;

#if 0

int main()
{
    for (int n = read(); n--;)
        if (int op = read(); op == 1)
            h.push(read());
        else if (op == 2)
            printf("%d\n", h.top());
        else
            h.pop();
}

#elif 0

int main()
{
    int n = read();
    for (int i = n; i--;)
        h.push(read());
    for (int i = n; i--;)
        printf("%d%c", h.top(), " \n"[!i]), h.pop();
}

#endif
