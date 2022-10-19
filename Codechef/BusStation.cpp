#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define F first
#define S second

const int MAXN = 1e6 + 100;
const ll INF = 1e18;

int m, n, a[5][MAXN], sec[MAXN];
ll d[MAXN], seg[MAXN<<2], lz[MAXN<<2];
pii dis[MAXN];

bool cmp(int u, int v){return a[0][u] < a[0][v];}

void shift(int v){
	if (!lz[v]) return;

	seg[v<<1] += lz[v];
	lz[v<<1] += lz[v];
	seg[v<<1^1] += lz[v];
	lz[v<<1^1] += lz[v];
	lz[v] = 0;
}

ll getMin(int v, int b, int e, int l, int r){
	if (l <= b && e <= r) return seg[v];
	if (r <= b || e <= l) return INF;

	int mid = b + e >> 1;
	shift(v);
	return min(getMin(v<<1, b, mid, l, r), getMin(v<<1^1, mid, e, l, r));
}

void upd(int v, int b, int e, int l, int r, int val){
	if (l <= b && e <= r){
		seg[v] += val;
		lz[v] += val;
		return;
	}
	if (r <= b || e <= l) return;

	int mid = b + e >> 1;
	shift(v);
	upd(v<<1, b, mid, l, r, val);
	upd(v<<1^1, mid, e, l, r, val);
	seg[v] = min(seg[v<<1], seg[v<<1^1]);
}

void updPos(int v, int b, int e, int pos, ll val){
	if (e - b == 1){
		seg[v] = val;
		return;
	}

	int mid = b + e >> 1;
	shift(v);
	if (pos < mid)
		updPos(v<<1, b, mid, pos, val);
	else
		updPos(v<<1^1, mid, e, pos, val);
	seg[v] = min(seg[v<<1], seg[v<<1^1]);
}

int ppos[MAXN];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int te;	cin >> te;
	while (te--){
		cin >> m;
		for (int i = 0; i < m; i++) {
			cin >> a[0][i];
			a[1][i] = a[3][i] = 5;
			a[2][i] = a[4][i] = 0;
		}

		cin >> n;
		for (int w = 0; w < 5; w++)
			for (int i = 0; i < n; i++)
				cin >> a[w][i+m];

		iota(sec, sec + n + m, 0);
		sort(sec, sec + n + m, cmp);
		for (int i = 0; i < n+m; i++) ppos[sec[i]] = i;

		int sz = 0;
		for (int i = m; i < n+m; i++){
			int lo = 0, hi = n+m+1, x = a[0][i] + a[3][i];
			while (hi-lo>1){
				int mid = hi+lo>>1;
				if (a[0][sec[mid-1]] < x)
					lo = mid;
				else
					hi = mid;
			}
			dis[sz++] = {hi, i};
		}
		sort(dis, dis + sz);

		memset(d, 63, sizeof(d));
		fill(seg, seg+4*(n+m+1)+5, INF);
		d[0] = 0;
		updPos(1, 0, n+m+1, 0, 0);

		int l = 0, r = 1, lst = -1, pt = 0;
		for (int i = 0; i < n+m; i++){
			int v = sec[i];
			if (v < m){
				if (~lst)
					l = lst+1, r = i+1;
				lst = i;
			}
			else {
				int lo = 0, hi = i+1, x = a[0][v] - a[1][v];
				while (hi-lo>1){
					int mid = hi+lo>>1;
					if (a[0][sec[mid-1]] <= x)
						lo = mid;
					else
						hi = mid;
				}
				upd(1, 0, n+m+1, lo+1, i+1, a[2][v]);
			}

			while (pt < sz && dis[pt].F == i+1){
				int u = dis[pt++].S;
				int pos = ppos[u];
				upd(1, 0, n+m+1, 0, pos+1, a[4][u]);
			}

			if (~lst)
				d[i+1] = getMin(1, 0, n+m+1, l, r);
			updPos(1, 0, n+m+1, i+1, d[i+1]);
		}
		cout << d[n+m] << "\n";
	}
	return 0;
}
