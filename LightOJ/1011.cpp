#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <string.h>

using namespace std;

#define MAXN 17
#define POWER 133000

int dp[MAXN][POWER],A[MAXN][MAXN],N;

void Read() {
	scanf("%d",&N);
	for (int i=1;i<=N;i++) {
		for (int j=1;j<=N;j++) {
			scanf("%d",&A[i][j]);
		}
	}
}

void Solve(int kase) {
	
	for (int i=1;i<=N;i++)
		dp[1][(1<<(i-1))]=A[1][i];
	
	for (int i=1;i<(1<<N);i++) {
		int p=0,val=i;
		int Log[N];
		for (int j=N-1;j>=0;j--) {
			if (val>=(1<<j)) {
				p++;
				Log[j]=1;
				val-=(1<<j);
			}
			else
				Log[j]=0;
		}
		for (int j=0;j<N;j++)
			if (!Log[j])
				dp[p+1][i+(1<<j)]=max(dp[p+1][i+(1<<j)],dp[p][i]+A[p+1][j+1]);
	}
	
	printf("Case %d: %d\n",kase,dp[N][(1<<N)-1]);
}

void Init() {
	memset(dp,0,sizeof dp);
}

int main () {
	//freopen("in.in","r",stdin);
	
	int t;
	scanf("%d",&t);
	
	for (int kase=1;kase<=t;kase++) {
		Read();
		Solve(kase);
		Init();
	}
}
