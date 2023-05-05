#include<cstdio>
#define read() ({int x,c,f=1;while((c=getchar())<48||57<c)if(c=='-')f=-1;for(x=c^48;47<(c=getchar())&&c<58;x=x*10+(c^48));x*f; })

namespace splay{

constexpr int N = 100005;
int rt, tot, fa[N], ch[N][2], val[N], cnt[N], sz[N];

#define maintain(x) {sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+cnt[x];}

#define get(x) (x==ch[fa[x]][1])

#define clear(x) {ch[x][0]=ch[x][1]=fa[x]=val[x]=sz[x]=cnt[x]=0;}

/** z           z
    |           |
    y           x
   / \         / \
  X      ->       y
 / \             / \
    c           c
*/
inline void rotate(int x) {
	int y=fa[x], z=fa[y], chk=get(x);
	ch[y][chk]=ch[x][chk^1];
	if(ch[x][chk^1])fa[ch[x][chk^1]]=y;
	ch[x][chk^1]=y;
	fa[y]=x;fa[x]=z;
	if(z)ch[z][y==ch[z][1]]=x;
	maintain(x);maintain(y);
}

inline void splay(int x){
    for(int f;f=fa[x];rotate(x))
        if(fa[f])rotate(get(x)==get(f)? f:x);
    rt = x;
}

inline void insert(int k){
	if(!rt){
		val[++tot]=k;
		cnt[rt=tot]++;
		maintain(rt);
		return ;
	}
	for(int cur=rt,f=0;;){
		if(val[cur]==k){
			cnt[cur]++;
			maintain(cur);maintain(f);
			splay(cur);
			return ;
		}
		f=cur;
		cur=ch[cur][val[cur]<k];
		if(!cur){
			val[++tot]=k;
			++cnt[tot];
			ch[fa[tot]=f][val[f]<k]=tot;
			maintain(tot);maintain(f);
			splay(tot);
			return ;
		}
	}
}
inline int rank(int k){
	for(int res=0,cur=rt;;){
		if(k<val[cur])cur=*ch[cur];
		else{
			res+=sz[*ch[cur]];
			if(k==val[cur]){
				splay(cur);
				return res+1;
			}
			res+=cnt[cur];
			cur=ch[cur][1];
		}
	}
}
inline int kth(int k){
	for(int cur=rt;;){
		if(*ch[cur]&&k<=sz[*ch[cur]])cur=*ch[cur];
		else {
			k-=cnt[cur] +sz[*ch[cur]];
			if(k<=0){
				splay(cur);
				return val[cur];
			}
			cur=ch[cur][1];
		}
	}
}

inline int pre() {
	int cur=*ch[rt];
	if(!cur) return cur;
	while(ch[cur][1])cur=ch[cur][1];
	splay(cur);
	return cur;
}
inline int next(){
	int cur=ch[rt][1];
	if(!cur)return cur;
	while(ch[cur][0])cur=ch[cur][0];
	splay(cur);
	return cur;
}
inline void erase(int k){
	for(int cur=rt;;){/*rank(k)*/
		if(k<val[cur])cur=*ch[cur];
		else{
			if(k==val[cur]){
				splay(cur);
				break;
			}
			cur=ch[cur][1];
		}
	}
	if(cnt[rt]>1){
		cnt[rt]--;
		maintain(rt);
		return ;
	}
	if(!ch[rt][0]&&!ch[rt][1]){
		clear(rt);
		rt=0;
		return ;
	}
	int cur=rt;
	if(!ch[rt][0]){
		rt=ch[rt][1];
		fa[rt]=0;
		clear(cur);
	}
	else if(!ch[rt][1]){
		rt=ch[rt][0];
		fa[rt]=0;
		clear(cur);
	}
	else {
		int x=pre();
		fa[ ch[cur][1] ]=x;
		ch[x][1]=ch[cur][1];
		clear(cur);
		maintain(rt);
	}
}
}
using namespace splay;

int main(){
  for (int n = read(), opt, x; n--;)
  {
    opt = read(), x = read();
    if (opt == 1)
	  insert(x);
    else if (opt == 2)
      erase(x);
    else if (opt == 3)
      printf("%d\n", rank(x));
    else if (opt == 4)
      printf("%d\n", kth(x));
    else if (opt == 5)
      insert(x), printf("%d\n", val[pre()]), erase(x);
    else
      insert(x), printf("%d\n", val[next()]), erase(x);
  }
	return 0;
}
