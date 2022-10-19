#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ui unsigned int
#define ull unsigned long long
#define db long double
#define pii pair<int,ll>
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define vi vector<int>
#define vii vector<vi>
#define lb lower_bound
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,b,a) for(int i=(b);i>=(a);--i)
#define rep0(i,a,b) for(int i=(a);i<(b);++i)
#define fore(i,a) for(int i=0;i<a.size();++i)
#define ls x<<1,l,m
#define rs x<<1|1,m+1,r
#define gc() getchar()
inline int rd()
{
	int x=0;char c=gc();while(!isdigit(c))c=gc();
	while(isdigit(c))x=x*10+c-48,c=gc();return x;
}
const int N=1005,L=1e7; 
int n,m,mid,ff,e[N][N],c[N],vis[N],p[N],rk[N],cnt[N],ans[N];vi g[N];
inline bool cmp(int x,int y)
{
	if(c[x]!=c[y])return c[x]<c[y];
	if(c[x])return g[x].size()<g[y].size();
	return g[x].size()>g[y].size();
}
void dfs(int x)
{
	for(int y:g[x])
	{
		if(vis[y])ff|=c[x]==c[y];
		else c[y]=c[x]^2,vis[y]=1,dfs(y);
	}
}
void sol()
{
	memset(e,0,sizeof(e));
	memset(c,0,sizeof(c));
	memset(vis,0,sizeof(vis));
	n=rd();m=rd();ff=0;mid=0;
	rep(i,1,n)g[i].clear();
	rep(i,1,m){int u=rd(),v=rd();e[u][v]=e[v][u]=1;g[u].pb(v);g[v].pb(u);}
	rep(i,1,n)if(g[i].size()==2&&e[g[i][0]][g[i][1]]){mid=i;break;}
	c[mid]=1;vis[mid]=1;
	rep(i,1,n)if(!vis[i]){c[i]=0;vis[i]=1;dfs(i);}
	if(ff){puts("No");return;}
	rep(i,1,n)p[i]=i;
	sort(p+1,p+n+1,cmp);
	int sl=0,sm=mid!=0,sr=0;
	rep(i,1,n)rk[p[i]]=i;
	rep(i,1,n)sl+=c[i]==0,sr+=c[i]==2;
	rep(i,sl+sm+1,n)
	{
		int mx=0,x=p[i];
		for(int y:g[x])mx=max(mx,rk[y]);
		cnt[i]=mx;ff|=mx!=g[x].size();
	}
	if(ff){puts("No");return;}
	puts("Yes");
	int pl=1,pr=1,ps=1;
	if(sm)
	{
		while(pl<=sl||pr<=sr-1)
		{
			if(pl>sl)ans[p[sl+sm+pr]]=L+ps,pr++,ps++; 
			else if(pr>sr-1)ans[p[pl]]=ps,pl++,ps++;
			else if(cnt[sl+sm+pr]>=pl)ans[p[pl]]=ps,pl++,ps++;
			else ans[p[sl+sm+pr]]=L+ps,pr++,ps++; 
		}
		ans[mid]=L+1;
		ans[p[n]]=2*L+1;
	}
	else
	{
		while(pl<=sl||pr<=sr)
		{
			if(pl>sl)ans[p[sl+sm+pr]]=L+ps,pr++,ps++; 
			else if(pr>sr)ans[p[pl]]=ps,pl++,ps++;
			else if(cnt[sl+sm+pr]>=pl)ans[p[pl]]=ps,pl++,ps++;
			else ans[p[sl+sm+pr]]=L+ps,pr++,ps++; 
		}
	}
	printf("%d ",2*L);
	rep(i,1,n)printf("%d ",ans[i]);puts("");
}
int main(){int T=rd();while(T--)sol();return 0;}
