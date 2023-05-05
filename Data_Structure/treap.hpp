#pragma once
template <typename T>
class Treap
{
    static inline long random()
    {
        static unsigned hold = 1;
        return ((hold = hold * 214013u + 2531011u) & 0x7fffffffl);
    }
    struct Node
    {
        Node *ch[2]; // 左右子树,
        T v;
        int r, cnt, s; // priority, count, size of subtree
        Node(T _v) : v(_v), cnt(1), s(1), r(random()) { ch[0] = ch[1] = 0; }
        void maintain()
        {
            s = cnt;
            if (ch[0])
                s += ch[0]->s;
            if (ch[1])
                s += ch[1]->s;
        }
    } *rt = NULL;
    static inline void rotate(Node *&o, int d) // 0是左旋
    {
        Node *k = o->ch[d ^ 1];
        o->ch[d ^ 1] = k->ch[d];
        k->ch[d] = o;
        o->maintain(), k->maintain();
        o = k;
    }
    // 在以o 为根的子树中插入键值x，修改o
    static void _insert(Node *&o, T x)
    {
        if (o == NULL)
            o = new Node(x);
        else if (x == o->v)
            o->s++, o->cnt++;
        else
        {
            int d = (o->v < x); // 左0
            _insert(o->ch[d], x);
            if (o->ch[d]->r < o->r)
                rotate(o, d ^ 1);
            o->maintain();
        }
    }
    static void _remove(Node *&o, T x)
    {
        if (x != o->v)
            _remove(o->ch[x > o->v], x), o->maintain();
        else if (o->cnt > 1)
            o->cnt--, o->s--;
        else if (!o->ch[0] && !o->ch[1])
            delete o, o = NULL;
        else if (o->ch[0] && o->ch[1])
        {
            int d = (o->ch[0]->r < o->ch[1]->r);
            rotate(o, d);
            _remove(o->ch[d], x);
            o->maintain();
        }
        else
        {
            Node *k = o;
            o = o->ch[!!o->ch[1]];
            delete k;
        }
    }
    static int _rank(Node *o, T x)
    {
        if (x < o->v)
            return o->ch[0] ? _rank(o->ch[0], x) : 1;
        int ls = o->ch[0] ? o->ch[0]->s : 0;
        if (x == o->v)
            return ls + 1;
        else
            return o->ch[1] ? ls + o->cnt + _rank(o->ch[1], x) : o->cnt + 1;
    }
    static T _kth(Node *o, int k)
    {
        int ls = o->ch[0] ? o->ch[0]->s : 0;
        if (k <= ls)
            return _kth(o->ch[0], k);
        else if (k <= ls + o->cnt)
            return o->v;
        else
            return _kth(o->ch[1], k - ls - o->cnt);
    }
    static T _prev(Node *o, T x)
    {
        static T prev_t;
        if (x <= o->v)
            return o->ch[0] ? _prev(o->ch[0], x) : x;
        prev_t = o->v;
        if (o->ch[1])
            _prev(o->ch[1], x);
        return prev_t;
    }
    static T _next(Node *o, T x)
    {
        static T next_t;
        if (x >= o->v)
            return o->ch[1] ? _next(o->ch[1], x) : x;
        next_t = o->v;
        if (o->ch[0])
            _next(o->ch[0], x);
        return next_t;
    }

public:
    void insert(T val) { _insert(rt, val); }
    void remove(T val) { _remove(rt, val); }
    T prev(T val) const { return _prev(rt, val); }
    T next(T val) const { return _next(rt, val); }
    int rank(T val) const { return _rank(rt, val); }
    T kth(int rank) const
    {
        if (rt == NULL || rank <= 0 || rank > rt->s)
            throw;
        return _kth(rt, rank);
    }
};

#if LOCAL || ONLINE_JUDGE
#include <cstdio>
#define read() ({int x,c,f=1;while((c=getchar())<48||57<c)if(c=='-')f=-1;for(x=c^48;47<(c=getchar())&&c<58;x=x*10+(c^48));x*f; })
Treap<int> t;
int main()
{
    for (int n = read(); n--;)
        switch (read())
        {
        case 1:
            t.insert(read());
            break;
        case 2:
            t.remove(read());
            break;
        case 3:
            printf("%d\n", t.rank(read()));
            break;
        case 4:
            printf("%d\n", t.kth(read()));
            break;
        case 5:
            printf("%d\n", t.prev(read()));
            break;
        case 6:
            printf("%d\n", t.next(read()));
            break;
        }
    return 0;
}
#endif
