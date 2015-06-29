#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<vector>

using namespace std;

#define MAXN 4*26*50000
#define N 100000001

int nodecount=2,Q1,Q2;
vector<int>lf(MAXN),r(MAXN),T(MAXN),L(MAXN);

inline int Left(int v) {
	if (lf[v]==0)
		lf[v]=nodecount++;
	
	return lf[v];
	
}

inline int Right (int v) {
	if (r[v]==0)
		r[v]=nodecount++;
	
	return r[v];
}

void Update(int node,int s,int e,int i,int j,int val) {
	int mid=(s+e)/2;


	if (s==i&&e==j) {
		L[node]+=val;
		T[node]+=(e-s+1)*val;
		return;
	}
	
	if (L[node]!=0) {
		Update(Left(node),s,mid,s,mid,L[node]);
		Update(Right(node),mid+1,e,mid+1,e,L[node]);
		L[node]=0;
	}

	if (j<=mid)
		Update(Left(node),s,mid,i,j,val);
	else
	if (i>mid)
		Update(Right(node),mid+1,e,i,j,val);
	else {
		Update(Left(node),s,mid,i,mid,val);
		Update(Right(node),mid+1,e,mid+1,j,val);
	}
}

int Query(int node,int s,int e,int i,int j) {
	int mid=(s+e)/2;
	
	if (i==s&&j==e) {
		return T[node];
	}
	
	if (L[node]) {
		Update(Left(node),s,mid,s,mid,L[node]);
		Update(Right(node),mid+1,e,mid+1,e,L[node]);
		L[node]=0;
	}
	
	if (j<=mid) 
		return Query(Left(node),s,mid,i,j);
	else
	if (i>mid)
		return Query(Right(node),mid+1,e,i,j);
}



void Solve(int test) {
	scanf("%d %d",&Q1,&Q2);
	
	printf("Case %d:\n",test);
	
	for (int i=1;i<=Q1;i++) {
		int x1,y1;
		scanf("%d %d",&x1,&y1);
		x1++;
		y1++;
		Update(1,1,N,x1,y1,1);
	}
	
	for (int i=1;i<=Q2;i++) {
		int p;
		scanf("%d",&p);
		printf("%d\n",Query(1,1,N,p+1,p+1));
	}
}

void Init() {
	for (int i=1;i<=nodecount;i++) {
		lf[i]=0;
		r[i]=0;
		T[i]=0;
		L[i]=0;
	}
}

int main () {
	//freopen("segment.in","r",stdin);
	//freopen("segment.out","w",stdout);
	
	int t;
	scanf("%d",&t);
	
	for (int i=1;i<=t;i++) {
		Solve(i);
		Init();
	}
	return 0;
}
