#include<stdio.h>
typedef struct{
	int x,y,z,c;
}T;
T dp[16][16][16][16];
T win={0,0,-3,1};
T lose={0,0,-3,-1};
T init={-1,-1,-1,0};
T imp={0,0,-3,0};
int t;
int max(int a,int b){return a>b?a:b;}
int sft(int x,int z){
	int p;
	if(z>=0)p=(x<<z)&15;
	if(z<0)p=(x>>(-z))&15;
	return p;
}
int calc(int x,int y,int z){
	int p=sft(x,z);
	int ans=p^y;
	return ans;
}
int dfs(bool bt,int x,int m[2],int e[2],bool used[16][16][16][16]){
	int i,j,k;
	if(used[m[0]][m[1]][e[0]][e[1]])return -1;
	if(dp[m[0]][m[1]][e[0]][e[1]].x!=-1)return dp[m[0]][m[1]][e[0]][e[1]].c;
	if(x>1000){
		dp[m[0]][m[1]][e[0]][e[1]]=imp;
		return 0;
	}
	int data[2][2][7];
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			for(k=-3;k<=3;k++){
				data[i][j][k+3]=-1;
				int nm[2]={m[0],m[1]};
				int ne[2]={e[0],e[1]};
				if(bt){
					if(m[i]==15||e[j]==15)continue;
					int p=calc(m[i],e[j],k);
					if(ne[j]==p)continue;
					ne[j]=p;
					used[m[0]][m[1]][e[0]][e[1]]=true;
					data[i][j][k+3]=dfs(false,x+1,nm,ne,used);
					used[m[0]][m[1]][e[0]][e[1]]=false;
				}
				else{
					if(e[i]==15||m[j]==15)continue;
					int p=calc(e[i],m[j],k);
					if(nm[j]==p)continue;
					nm[j]=p;
					used[m[0]][m[1]][e[0]][e[1]]=true;
					data[i][j][k+3]=dfs(true,x+1,nm,ne,used);
					used[m[0]][m[1]][e[0]][e[1]]=false;
				}
				if(data[i][j][k+3]==1){
					T te={i,j,k,1};
					dp[m[0]][m[1]][e[0]][e[1]]=te;
				}
			}
		}
	}
	if(dp[m[0]][m[1]][e[0]][e[1]].c==1)return 1;
	for(i=0;i<2;i++)for(j=0;j<2;j++)for(k=0;k<7;k++){
		if(data[i][j][k]==0){
			T te={i,j,k,0};
			dp[m[0]][m[1]][e[0]][e[1]]=te;
			return 0;
		}
	}
	T te={0,0,-3,-1};
	dp[m[0]][m[1]][e[0]][e[1]]=te;
	return -1;
}
int main(){
	int i,j,k,l;
	int my[2]={8,1},en[2]={1,8};
	bool used[16][16][16][16];
	for(i=0;i<16;i++)for(j=0;j<16;j++)for(k=0;k<16;k++)for(l=0;l<16;l++){
		dp[i][j][k][l]=init;
		used[i][j][k][l]=false;
	}
	for(i=0;i<16;i++)for(j=0;j<16;j++)dp[i][j][15][15]=win;
	for(i=0;i<16;i++)for(j=0;j<16;j++)dp[15][15][i][j]=lose;
	dfs(true,0,my,en,used);
	while(1){
	scanf("%d",&t);
	for(i=0;i<4;i++){int x;scanf("%d",&x);my[0]|=x<<i;}
	for(i=0;i<4;i++){int x;scanf("%d",&x);my[1]|=x<<i;}
	for(i=0;i<4;i++){int x;scanf("%d",&x);en[0]|=x<<i;}
	for(i=0;i<4;i++){int x;scanf("%d",&x);en[1]|=x<<i;}
	int x=dp[my[0]][my[1]][en[0]][en[1]].x;
	int y=dp[my[0]][my[1]][en[0]][en[1]].y;
	int z=dp[my[0]][my[1]][en[0]][en[1]].z;	
	printf("%d %d %d\n",x,y,z);
	fflush(stdout);
	}
}