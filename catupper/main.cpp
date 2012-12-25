#include<stdio.h>
int t;
int my[2]={0,0},en[2]={0,0};
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
	if(m[0]==15&&m[1]==15)return -1;
	if(e[0]==15&&e[1]==15)return 10;
	if(x>=t+4||x>1000){
		int p=0;
		if(m[0]!=15)p++;
		if(m[1]!=15)p++;
		if(e[0]==15)p++;
		if(e[1]==15)p++;
		return p;
	}
	int a=-1;
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			for(k=-3;k<=3;k++){
				if(bt){
					if(m[i]==15||e[j]==15)continue;
					int p=calc(m[i],e[j],k);
					int nm[2]={m[0],m[1]};
					int ne[2]={e[0],e[1]};
					if(ne[j]==p)continue;
					ne[j]=p;
					a=max(a,dfs(false,x+1,nm,ne));
				}
				else{
					if(e[i]==15||m[j]==15)continue;
					int p=calc(e[i],m[j],k);
					int nm[2]={m[0],m[1]};
					int ne[2]={e[0],e[1]};
					if(nm[j]==p)continue;
					nm[j]=p;
					a=max(a,dfs(true,x+1,nm,ne));
				}
			}
		}
	}
	return a;
}
int main(){
	int i,j,k;
	while(1){
	scanf("%d",&t);
	for(i=0;i<4;i++){int x;scanf("%d",&x);my[0]|=x<<i;}
	for(i=0;i<4;i++){int x;scanf("%d",&x);my[1]|=x<<i;}
	for(i=0;i<4;i++){int x;scanf("%d",&x);en[0]|=x<<i;}
	for(i=0;i<4;i++){int x;scanf("%d",&x);en[1]|=x<<i;}
	int ans=-1;
	int x=0,y=0,z=-3;
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			for(k=-3;k<=3;k++){
				if(my[i]==15||en[j]==15)continue;
				int nm[2]={my[0],my[1]};
				int ne[2]={en[0],en[1]};
				int q=calc(my[i],en[j],k);
				if(q==ne[j])continue;
				ne[j]=q;
				int p=dfs(false,t+1,nm,ne);
				if(ans<p){
					ans=p;
					x=i;
					y=j;
					z=k;
				}
			}
		}
	}
	printf("%d %d %d\n",x,y,z);
	fflush(stdout);
	}
}