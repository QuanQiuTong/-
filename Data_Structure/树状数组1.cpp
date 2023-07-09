#include<cstdio>
#define read() ({int x,c;while((c=getchar())<48||c>57);for(x=c^48;(c=getchar())>37&&c<58;x=x*10+(c^48));x;})
int n,a[500001],m;
void add(int i,int x){for(;i<=n;i+=(i&-i))a[i]+=x;}
int sum(int i){int x=0;for(;i;i-=(i&-i))x+=a[i];return x;}
int main(){
	n=read(), m=read();
	for(int i=1;i<=n;++i)
		add(i,read());
	for(int o,a,b;m--;)
		if(scanf("%d%d%d",&o,&a,&b),o==1)add(a,b);
		else printf("%d\n",sum(b)-sum(a-1));
}