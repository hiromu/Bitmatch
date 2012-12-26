#include<stdio.h>
int t;
int my[2]={0,0},en[2]={0,0};
int min(int a,int b){return a<b?a:b;}
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
int dfs(bool bt,int x,int m[2],int e[2]){
	int i,j,k;
	if(x>=t+4||x>1000){
		int p=0;
		if(m[0]==15)p-=3;
		if(m[1]==15)p-=3;
		if(e[0]==15)p+=8;
		if(e[1]==15)p+=8;
		return p;
	}
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			for(k=-3;k<=3;k++){
				if(bt){
					if(m[i]==15||e[j]==15)continue;
					int p=calc(m[i],e[j],k);
					int nm[2]={m[0],m[1]};
					int ne[2]={e[0],e[1]};
					if(p==ne[j])continue;
					if(p==15)return 20+x-t;
				}
				else{
					if(e[i]==15||m[j]==15)continue;
					int p=calc(e[i],m[j],k);
					int nm[2]={m[0],m[1]};
					int ne[2]={e[0],e[1]};
					if(p==nm[j])continue;
					nm[j]=p;
					if(p==15)return -20;
				}
			}
		}
	}
	int a;
	if(bt)a=-20;
	else a=20;
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			for(k=-3;k<=3;k++){
				if(bt){
					if(m[i]==15||e[j]==15)continue;
					int p=calc(m[i],e[j],k);
					int nm[2]={m[0],m[1]};
					int ne[2]={e[0],e[1]};
					if(p==ne[j])continue;
					ne[j]=p;
					a=max(a,dfs(false,x+1,nm,ne));
				}
				else{
					if(e[i]==15||m[j]==15)continue;
					int p=calc(e[i],m[j],k);
					int nm[2]={m[0],m[1]};
					int ne[2]={e[0],e[1]};
					if(p==nm[j])continue;
					nm[j]=p;
					a=min(a,dfs(true,x+1,nm,ne));
				}
			}
		}
	}
	return a;
}
int main(){
	int i,j,k;
	while(1){
start:	
	scanf("%d",&t);
	my[0]=0;my[1]=0;
	en[0]=0;en[1]=0;
	for(i=0;i<4;i++){int x;scanf("%d",&x);my[0]+=x<<i;}
	for(i=0;i<4;i++){int x;scanf("%d",&x);my[1]+=x<<i;}
	for(i=0;i<4;i++){int x;scanf("%d",&x);en[0]+=x<<i;}
	for(i=0;i<4;i++){int x;scanf("%d",&x);en[1]+=x<<i;}
	int x=0,y=0,z=-3;
	int d[2][2][7];
	int mx=0;
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			for(k=-3;k<=3;k++){
				d[i][j][k]=-100;
				if(my[i]==15||en[j]==15)continue;
				int nm[2]={my[0],my[1]};
				int ne[2]={en[0],en[1]};
				int q=calc(my[i],en[j],k);
				if(q==ne[j])continue;
				if(q==15){
					printf("%d %d %d\n",i,j,k);
					fflush(stdout);
					goto start;
				}
				ne[j]=q;
				d[i][j][k+3]=dfs(false,t+1,nm,ne);
				if(d[x][y][z+3]<d[i][j][k+3]){
					x=i;y=j;z=k;
					mx=0;
					for(int l=0;l<4;l++){mx+=(ne[0]>>l)&1;}
					for(int l=0;l<4;l++){mx+=(ne[1]>>l)&1;}
				}
				else if(d[x][y][z+3]==d[i][j][k+3]){
					int yn=0;
					for(int l=0;l<4;l++){yn+=(ne[0]>>l)&1;}
					for(int l=0;l<4;l++){yn+=(ne[1]>>l)&1;}
					if(yn>mx){
						x=i;y=j;z=k;
						mx=yn;
					}
				}
			}
		}
	}
	printf("%d %d %d\n",x,y,z);
	fflush(stdout);
	}
}