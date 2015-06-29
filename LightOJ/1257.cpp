#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXN 30009
#define pii pair<int,int>
#define mp make_pair
#define f first
#define s second

int N;
vector<pii>con[MAXN],t[MAXN];
int sub[MAXN],diam[MAXN];

int Run1(int root,int father) {
	sub[root]=0;
	for (int i=0;i<t[root].size();++i) {
		if (t[root][i].f!=father) {
			con[root].push_back(mp(t[root][i].f,t[root][i].s));
			sub[root]=max(sub[root],t[root][i].s+Run1(t[root][i].f,root));
		}
	}
	return sub[root];
}

void Run2(int root,int back) {
	diam[root]=back+sub[root];
	int v1=0,v2=0;
	int w1=0,w2=0;
	for (int i=0;i<con[root].size();++i) {
		if (sub[con[root][i].f]+con[root][i].s > w1) {
			w1=sub[con[root][i].f]+con[root][i].s;
			v1=con[root][i].f;
		}
	}
	for (int i=0;i<con[root].size();++i) {
		if (sub[con[root][i].f]+con[root][i].s > w2 && con[root][i].f!=v1) {
			w2=sub[con[root][i].f]+con[root][i].s;
			v2=con[root][i].f;
		}
	}
	for (int i=0;i<con[root].size();++i) {
		int w=con[root][i].s;
		if (con[root][i].f==v1) {
			Run2(con[root][i].f,max(back+w,w2+w));
		}
		else
			Run2(con[root][i].f,max(back+w,w1+w));
	}
}

void Read() {
	scanf("%d",&N);
	for (int i=1;i<N;i++) {
		int x,y,w;
		scanf("%d %d %d",&x,&y,&w);
		x++;
		y++;
		t[x].push_back(mp(y,w));
		t[y].push_back(mp(x,w));
	}
}

void Solve(int kase) {
	printf("Case %d:\n",kase);
	for (int i=1;i<=N;i++)
		printf("%d\n",max(diam[i]-sub[i],sub[i]));
}

void Init() {
	for (int i=1;i<=N;i++) {
		con[i].clear();
		t[i].clear();
		diam[i]=0;
		sub[i]=0;
	}
}

int main () {
	int t;
	scanf("%d",&t);
	int p=1;
	while (t--) {
		Read();
		Run1(1,0);
		Run2(1,0);
		Solve(p);
		Init();
		p++;
	}
	
	return 0;
}
