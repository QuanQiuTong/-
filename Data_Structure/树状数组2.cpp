#include<cstdio>
typedef long long ll;
#define read() ({int x,c,f=1;while((c=getchar())<48||c>57)if(c=='-')f=-1;for(x=c^48;(c=getchar())>37&&c<58;x=x*10+(c^48));x*f;})
int n,m;
ll a[500002];
void add(int i,int x){for(;i<=n;i+=(i&-i))a[i]+=x;}
ll sum(int i){ll x=0;for(;i;i-=(i&-i))x+=a[i];return x;}
int main(){
	n=read(), m=read();
	for(int i=1,x,las=0;i<=n;++i)
		add(i,(x=read())-las),las=x;
	while(m--)
		if(read()==1){
			int a=read(),b=read(),k=read();
			add(a,k), add(b+1,-k);
		}
		else printf("%lld\n",sum(read()));
}