#include<stdio.h>
typedef long long ll;
#define N 400005
int mid[N],L,R,p;
ll sum[N],k,lz[N],ml[N];
#define read() ({long long x,f=1,c;while((c=getchar())<48||c>57)if(c=='-')f=-1;for(x=c^48;(c=getchar())>47&&c<58;)x=x*10+(c^48);x*f;})
#define ls i<<1
#define rs i<<1|1
#define pu sum[i]=sum[ls]+sum[rs]
#define pd {sum[ls]*=ml[i];sum[ls]%=p;sum[ls]+=(mid[i]-l+1)*lz[i];sum[ls]%=p;\
	sum[rs]*=ml[i];sum[rs]%=p;sum[rs]+=(r-mid[i])*lz[i];sum[rs]%=p;\
	lz[ls]*=ml[i];lz[ls]+=lz[i];lz[ls]%=p;\
	lz[rs]*=ml[i];lz[rs]+=lz[i];lz[rs]%=p;\
	ml[ls]*=ml[i];ml[ls]%=p;ml[rs]*=ml[i];ml[rs]%=p;\
	lz[i]=0;ml[i]=1;}
void bld(int i,int l,int r){
	ml[i]=1;//printf("*%d %d %d\n",i,l,r);
	if(l==r){sum[i]=read();return;}
	bld(ls,l,mid[i]=l+r>>1);
	bld(rs,mid[i]+1,r);
	pu;
}
void add(int i,int l,int r){
	if(R<l||r<L)return ;
	if(L<=l&&r<=R){sum[i]+=(r-l+1)*k;lz[i]+=k;return;}
	if(lz[i]||ml[i]!=1)pd;
	if(L<=mid[i])add(ls,l,mid[i]);
	if(mid[i]<R)add(rs,mid[i]+1,r);
	pu;
}
void mul(int i,int l,int r){
	if(R<l||r<L)return ;
	if(L<=l&&r<=R){sum[i]*=k;sum[i]%=p;lz[i]=(lz[i]*k)%p;ml[i]=(ml[i]*k)%p;return;}
	if(lz[i]||ml[i]!=1)pd;
	if(L<=mid[i])mul(ls,l,mid[i]);
	if(mid[i]<R)mul(rs,mid[i]+1,r);
	pu;
}
ll qry(int i,int l,int r){
	if(R<l||r<L)return 0;
	if(L<=l&&r<=R)return sum[i];
	if(lz[i]||ml[i]!=1)pd;
	ll ret=(L<=mid[i]?qry(ls,l,mid[i]):0);
	if(mid[i]<R)ret+=qry(rs,mid[i]+1,r);
	pu;
	return ret%p;
}
int main(){
	int n,m,f;
	n=read();m=read(),p=read();
	bld(1,1,n);
	while(m--){
		f=read();L=read();R=read();
		if(f==1)k=read(),mul(1,1,n);
		else if(f==2)k=read(),add(1,1,n);
		else printf("%lld\n",qry(1,1,n));
	}
	return 0;
}
