
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
using namespace std;
template <typename T> void read(T &t) {
	t=0; char ch=getchar(); int f=1;
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	do { (t*=10)+=ch-'0'; ch=getchar(); } while ('0'<=ch&&ch<='9'); t*=f;
}
template <typename T> void write(T t) {
	if (t<0) { putchar('-'); write(-t); return; }
	if (t>9) write(t/10);
	putchar('0'+t%10);
}
template <typename T> void writeln(T t) { write(t); puts(""); }
#define MP make_pair
typedef long long ll;
const ll mod=2500000001LL;
const int INF=0x7f7f7f7f;
int T,n,m,K,x[1010],y[1010];
int lsh[1010],N,lsh2[1010],N2;
int lst[50010],dis[50010];
ll sum[100010];
int id[1010];
bool cmp(int a,int b) { return y[a]<y[b]; }
void add(int l,int r) {
	if (l>r) swap(l,r);
	sum[l]++,sum[r+1]--;

}
ll ksm(ll x,ll y) {
	ll res=1; while (y) { if (y&1) res=res*x%mod; x=x*x%mod; y>>=1; } return res;
}
void update(int &x,int y) { if (x>y) x=y; }
int main() {

	read(T);
	while (T--) {
		read(n),read(m),read(K);
		N=0;
		for (int i=1;i<=K;i++) read(x[i]),read(y[i]),lsh[++N]=x[i],lsh2[++N2]=y[i];
		sort(lsh+1,lsh+N+1),N=unique(lsh+1,lsh+N+1)-lsh-1;
		sort(lsh2+1,lsh2+N2+1),N2=unique(lsh2+1,lsh2+N2+1)-lsh2-1;
		if ((ll)N*m>=(ll)N2*n) {
			swap(n,m);
			for (int i=1;i<=K;i++) swap(x[i],y[i]);
			N=N2;
			for (int i=1;i<=N;i++) lsh[i]=lsh2[i];
		}
		for (int i=1;i<=K;i++) id[i]=i;
		sort(id+1,id+K+1,cmp);
		for (int i=0;i<=n+m;i++) sum[i]=0;
		for (int j=1;j<=m;j++) dis[j]=INF;
		lsh[N+1]=n+1;
		int A,d1,d2,L,R,bd;
		for (int i=1;i<=N;i++) {
			L=lsh[i-1]+1,R=lsh[i]-1;
			int pos=K+1,mn=INF;
			for (int j=m;j>=1;j--) {
				while (pos>1&&y[id[pos-1]]>=j) {
					pos--;
					update(mn,y[id[pos]]+abs(x[id[pos]]-lsh[i]));
				}
				dis[j]=mn-j;
			}
			pos=0,mn=INF;
			A=R-L+1;
			for (int j=1;j<=m;j++) {
				while (pos<K&&y[id[pos+1]]<=j) {
					pos++;
					update(mn,-y[id[pos]]+abs(x[id[pos]]-lsh[i]));
				}
				if (dis[j]>mn+j) dis[j]=mn+j;
				if (L<=R) {
					if (i==1) add(dis[j]+lsh[1]-1,dis[j]+1);
					else {
						d1=lst[j];
						d2=dis[j];
						bd=min(A,(d2-d1+A+1)/2);
						if (bd>=1) {
							add(d1+1,d1+bd);
							if (bd<A) add(d2+1,d2+A-bd);
						} else add(d2+1,d2+A);
					}
				}
				if (i==N&&lsh[i]!=n) add(dis[j]+n-lsh[N],dis[j]+1);
				sum[dis[j]]++,sum[dis[j]+1]--;
				lst[j]=dis[j],dis[j]=INF;
			}
		}
		
		
		for (int i=1;i<=n+m;i++) sum[i]+=sum[i-1];
		
		for (int i=1;i<=n+m;i++) sum[i]+=sum[i-1];
		ll fz=1,fm=1;
		for (int i=0;i<=n+m-3;i++) {
			sum[i]%=mod;
			fz=fz*((sum[i]-i+mod)%mod)%mod;
			fm=fm*(((ll)n*m-i)%mod)%mod;
		}
		printf("%lld\n",fz*ksm(fm,mod-2)%mod);
	}
	return 0;
}

