#include <cstdio>
#define read() ({int x,c,f=1;while((c=getchar())<48||57<c)if(c=='-')f=-1;for(x=c^48;47<(c=getchar())&&c<58;x=x*10+(c^48));x*f; })
inline int random()
{
    static unsigned hold = 1;
    return ((hold = hold * 214013u + 2531011u) & 0x7fffffffl);
}
struct Node
{
    Node *ch[2]; // 左右子树
    int r, v;    // 优先级，值
    int cnt, s;
    Node(int _v) : v(_v), cnt(1), s(1), r(random()) { ch[0] = ch[1] = 0; }
    void maintain()
    {
        s = cnt;
        if (ch[0])
            s += ch[0]->s;
        if (ch[1])
            s += ch[1]->s;
    }
} *rt = NULL;
inline void rotate(Node *&o, int d) // 0是左旋
{
    Node *k = o->ch[d ^ 1];
    o->ch[d ^ 1] = k->ch[d];
    k->ch[d] = o;
    o->maintain(), k->maintain();
    o = k;
}
// 在以o 为根的子树中插入键值x，修改o
void insert(Node *&o, int x)
{
    if (!o)
        o = new Node(x);
    else if (x == o->v)
        o->s++, o->cnt++;
    else
    {
        int d = (o->v < x); // 左0
        insert(o->ch[d], x);
        if (o->ch[d]->r < o->r)
            rotate(o, d ^ 1);
        o->maintain();
    }
}
void remove(Node *&o, int x)
{
    if (x != o->v)
        remove(o->ch[x > o->v], x), o->maintain();
    else if (o->cnt > 1)
        o->cnt--, o->s--;
    else if (!o->ch[0] && !o->ch[1])
        delete o, o = NULL;
    else if (o->ch[0] && o->ch[1])
    {
        int d = (o->ch[0]->r < o->ch[1]->r);
        rotate(o, d);
        remove(o->ch[d], x);
        o->maintain();
    }
    else
    {
        Node *k = o;
        o = o->ch[!!o->ch[1]];
        delete k;
    }
}
int rank(Node *o, int x)
{
    if (x < o->v)
        return o->ch[0] ? rank(o->ch[0], x) : 1;
    int ls = o->ch[0] ? o->ch[0]->s : 0;
    if (x == o->v)
        return ls + 1;
    else
        return o->ch[1] ? ls + o->cnt + rank(o->ch[1], x) : o->cnt + 1;
}
int kth(Node *o, int k)
{
    // if (o == NULL || k <= 0 || k > o->s)return 0;
    int ls = o->ch[0] ? o->ch[0]->s : 0;
    if (k <= ls)
        return kth(o->ch[0], k);
    else if (k <= ls + o->cnt)
        return o->v;
    else
        return kth(o->ch[1], k - ls - o->cnt);
}
int prev(Node *o, int x)
{
    static int prev_t;
    if (x <= o->v)
        return o->ch[0] ? prev(o->ch[0], x) : x;
    prev_t = o->v;
    if (o->ch[1])
        prev(o->ch[1], x);
    return prev_t;
}
int next(Node *o, int x)
{
    static int next_t;
    if (x >= o->v)
        return o->ch[1] ? next(o->ch[1], x) : x;
    next_t = o->v;
    if (o->ch[0])
        next(o->ch[0], x);
    return next_t;
}

int main()
{
    for (int n = read(); n--;)
        switch (read())
        {
        case 1:
            insert(rt, read());
            break;
        case 2:
            remove(rt, read());
            break;
        case 3:
            printf("%d\n", rank(rt, read()));
            break;
        case 4:
            printf("%d\n", kth(rt, read()));
            break;
        case 5:
            printf("%d\n", prev(rt, read()));
            break;
        case 6:
            printf("%d\n", next(rt, read()));
            break;
        }
    return 0;
}
