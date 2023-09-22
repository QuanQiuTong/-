// 刘汝佳
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

struct Node {
  Node* ch[2];
  int s, flip, v;
  int cmp(int k) const {
    int d = k - ch[0]->s;
    if (d == 1) return -1;
    return d <= 0 ? 0 : 1;
  }
  void maintain() { s = ch[0]->s + ch[1]->s + 1; }
  void pushdown() {
    if (flip) {
      flip = 0;
      swap(ch[0], ch[1]);
      ch[0]->flip = !ch[0]->flip;
      ch[1]->flip = !ch[1]->flip;
    }
  }
};

Node* null = new Node();

void rotate(Node*& o, int d) {
  Node* k = o->ch[d ^ 1];
  o->ch[d ^ 1] = k->ch[d];
  k->ch[d] = o;
  o->maintain();
  k->maintain();
  o = k;
}

void splay(Node*& o, int k) {  // 找到序列的左数第k个元素并伸展到根结点
  o->pushdown();
  int d = o->cmp(k);  // 看看第k个元素在整个树中的位置
  if (d == 1) k -= o->ch[0]->s + 1;  // 第k个元素在o的右子树中
  if (d == -1) return;               // 已经在根上了
  Node* p = o->ch[d];                // 第k个元素所在的子树
  p->pushdown();
  int d2 = p->cmp(k);  // 第k个元素是在p的左子树?→d2
  int k2 = (d2 == 0 ? k : k - p->ch[0]->s - 1);  // 在树中的排名
  if (d2 != -1) {          // 不是子树的根，伸展到p
    splay(p->ch[d2], k2);  // 伸展到p的子树根，下面旋转到p
    if (d == d2)
      rotate(o, d ^ 1);  // 一条直线
    else
      rotate(o->ch[d], d);  // 不是一条直线
  }
  rotate(o, d ^ 1);  // 从p旋转到o
}

// 合并left和right。假定left的所有元素比right小。注意right可以是null，但left不可以
Node* merge(Node* left, Node* right) {
  splay(left, left->s);
  left->ch[1] = right;
  left->maintain();
  return left;
}

// 把o的前k小结点放在left里，其他的放在right里。1<=k<=o->s。当k=o->s时，right=null
void split(Node* o, int k, Node*& left, Node*& right) {
  splay(o, k);
  left = o;
  right = o->ch[1];
  o->ch[1] = null;
  left->maintain();
}

const int NN = 100000 + 10;
struct SplaySequence {
  int n;
  Node seq[NN];
  Node* root;

  Node* build(int sz) {
    if (!sz) return null;
    Node* L = build(sz / 2);
    Node* o = &seq[++n];
    o->v = n;  // 节点编号
    o->ch[0] = L;
    o->ch[1] = build(sz - sz / 2 - 1);
    o->flip = o->s = 0;
    o->maintain();
    return o;
  }

  void init(int sz) { n = 0, null->s = 0, root = build(sz); }
};

vector<int> ans;
void print(Node* o) {
  if (o == null) return;
  o->pushdown();
  print(o->ch[0]);
  ans.push_back(o->v);
  print(o->ch[1]);
}

void debug(Node* o) {
  if (o == null) return;
  o->pushdown();
  debug(o->ch[0]);
  printf("%d ", o->v - 1);
  debug(o->ch[1]);
}

SplaySequence ss;
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  ss.init(n + 1);  // 最前面有一个虚拟结点
  for (int i = 0, a, b; i < m; i++) {
    scanf("%d%d", &a, &b);
    Node *left, *mid, *right, *o;
    split(ss.root, a, left, o);  // 如无虚拟结点，a将改成a-1，违反split的限制
    split(o, b - a + 1, mid, right);
    mid->flip ^= 1;
    ss.root = merge(merge(left, mid), right);
  }

  print(ss.root);
  for (size_t i = 1; i < ans.size(); i++)
    printf("%d ", ans[i] - 1);  // 节点编号减1才是本题的元素值

  return 0;
}
