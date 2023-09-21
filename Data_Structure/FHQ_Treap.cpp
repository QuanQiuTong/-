//https://paste.ubuntu.com/p/bwpzbrf6HG/


#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<algorithm>

#define read() ({int x,c,f=1;while((c=getchar())<48||57<c)if(c=='-')f=-1;for(x=c^48;47<(c=getchar())&&c<58;)x=x*10+(c^48);x*f;})

const int MAXN(1e5+10);
int n,m;
int ch[MAXN][2],val[MAXN],siz[MAXN],rnd[MAXN];
int tot,rt,x,y,z;
bool tag[MAXN];
inline int New(int v)
{
	val[++tot]=v;
	siz[tot]=1;
	rnd[tot]=rand();
	tag[tot]=false;
	return tot;
}
inline void push_up(int u){siz[u]=siz[ch[u][0]]+siz[ch[u][1]]+1;}
inline void push_down(int u)
{
	tag[u]=false;
	std::swap(ch[u][0],ch[u][1]);
	tag[ch[u][0]]^=1;
	tag[ch[u][1]]^=1; 
}
inline void split(int u,int k,int&x,int&y)
{
	if(!u) x=y=0;
	else 
	{
		if(tag[u]) push_down(u);
		if(siz[ch[u][0]]<k) x=u,split(ch[u][1],k-siz[ch[u][0]]-1,ch[u][1],y);
		else y=u,split(ch[u][0],k,x,ch[u][0]);
		push_up(u);
	}
}
inline int unite(int x,int y)
{
	if(!x||!y) return x+y;
	if(rnd[x]<rnd[y])
	{
		if(tag[x]) push_down(x);
		ch[x][1]=unite(ch[x][1],y);
		push_up(x);
		return x;
	}
	else 
	{
		if(tag[y]) push_down(y);
		ch[y][0]=unite(x,ch[y][0]);
		push_up(y);
		return y;
	}
}
inline void ins(int v)
{
	split(rt,v,x,y);
	rt=unite(unite(x,New(v)),y);
}
inline void rev(int l,int r)
{
	split(rt,l-1,x,y);
	split(y,r-l+1,y,z);
	tag[y]^=1;
	rt=unite(unite(x,z),y);
}
inline void dfs(int u)
{
	if(!u) return;
	if(tag[u]) push_down(u);
	dfs(ch[u][0]);
	printf("%d ",val[u]);
	dfs(ch[u][1]);
}
int main()
{
	srand(time(0));
	n=read(),m=read();
	for(int i=1;i<=n;i++) ins(i);
	while(m--)
	{
		int l=read(),r=read();
		rev(l,r);
	}
	dfs(rt);
	return 0;
}