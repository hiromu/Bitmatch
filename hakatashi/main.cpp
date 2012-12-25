#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define WIN 10000
#define LOSE -10000

typedef struct {
	bool me,you;
	int shift;
} manu_t;

manu_t search(bool *fin1, bool *fin2, bool *fin3, bool *fin4, int turn, int *value) {
	manu_t manu,tempm,root[128];
	bool temp[4][4];
	bool sfted[10];
	int value_t[128];
	int count;
	bool tflag[4];
	
	if (fin1[0] && fin1[1] && fin1[2] && fin1[3]) tflag[0]=true; else tflag[0]=false;
	if (fin2[0] && fin2[1] && fin2[2] && fin2[3]) tflag[1]=true; else tflag[1]=false;
	if (fin3[0] && fin3[1] && fin3[2] && fin3[3]) tflag[2]=true; else tflag[2]=false;
	if (fin4[0] && fin4[1] && fin4[2] && fin4[3]) tflag[3]=true; else tflag[3]=false;
	
	if (turn%2==0) {
		int max=LOSE;
		count=0;
		for (int i=0;i<4;i++) {
			temp[0][i]=fin1[i];
			temp[1][i]=fin2[i];
		}
		for (int i=0;i<2;i++) {
			if (!tflag[i]) for (int j=0;j<2;j++) {
				if (!tflag[2+j]) {
					if (!j) {
						for (int k=0;k<4;k++) {
							temp[3][i]=fin4[i];
						}
					} else {
						for (int k=0;k<4;k++) {
							temp[2][i]=fin3[i];
						}
					}
					for (int k=-3;k<=3;k++) {
						for (int l=0;l<10;l++) {
							sfted[l]=false;
						}
						if (!i) {
							for (int l=0;l<4;l++) {
								sfted[3+l+k]=fin1[l];
							}
						} else {
							for (int l=0;l<4;l++) {
								sfted[3+l+k]=fin2[l];
							}
						}
						for (int l=0;l<4;l++) {
							if (sfted[3+l]) {
								if (!j) {
									temp[2][l]=!fin3[l];
								} else {
									temp[3][l]=!fin4[l];
								}
							} else {
								if (!j) {
									temp[2][l]=fin3[l];
								} else {
									temp[3][l]=fin4[l];
								}
							}
						}
						bool flag=true;
						for (int l=0;l<4;l++) {
							if (!temp[2][l]) {
								flag=false;
								break;
							}
						}
						for (int l=0;l<4;l++) {
							if (!temp[3][l]) {
								flag=false;
								break;
							}
						}
						if (flag) {
							value_t[count]=WIN*(4-turn);
							if (turn==0) {
								turn+=0;
							}
						} else {
							search(temp[0],temp[1],temp[2],temp[3],turn+1,&value_t[count]);
						}
						root[count].me=(bool)i;
						root[count].you=(bool)j;
						root[count].shift=k;
						count++;
					}
				}
			}
		}
		for (int i=0;i<count;i++) {
			if (value_t[i]>max || i==0) {
				max=value_t[i];
				manu.me=root[i].me;
				manu.you=root[i].you;
				manu.shift=root[i].shift;
			}
		}
		*value=max;
	} else {
		int min=WIN;
		count=0;
		for (int i=0;i<4;i++) {
			temp[2][i]=fin3[i];
			temp[3][i]=fin4[i];
		}
		for (int i=0;i<2;i++) {
			if (!tflag[2+i]) for (int j=0;j<2;j++) {
				if (!tflag[j]) {
					if (!j) {
						for (int k=0;k<4;k++) {
							temp[1][i]=fin2[i];
						}
					} else {
						for (int k=0;k<4;k++) {
							temp[0][i]=fin1[i];
						}
					}
					for (int k=-3;k<=3;k++) {
						for (int l=0;l<10;l++) {
							sfted[l]=false;
						}
						if (!i) {
							for (int l=0;l<4;l++) {
								sfted[3+l+k]=fin3[l];
							}
						} else {
							for (int l=0;l<4;l++) {
								sfted[3+l+k]=fin4[l];
							}
						}
						for (int l=0;l<4;l++) {
							if (sfted[3+l]) {
								if (!j) {
									temp[0][l]=!fin1[l];
								} else {
									temp[1][l]=!fin2[l];
								}
							} else {
								if (!j) {
									temp[0][l]=fin1[l];
								} else {
									temp[1][l]=fin2[l];
								}
							}
						}
						bool flag=true;
						for (int l=0;l<4;l++) {
							if (!temp[0][l]) {
								flag=false;
								break;
							}
						}
						for (int l=0;l<4;l++) {
							if (!temp[1][l]) {
								flag=false;
								break;
							}
						}
						if (flag) {
							value_t[count]=LOSE*(4-turn);
						} else if (turn==3) {
							bool kill[4];
							value_t[count]=0;
							for (int l=0;l<4;l++) kill[l]=false;
							if (temp[0][0] && temp[0][1] && temp[0][2] && temp[0][3]) kill[0]=true;
							if (temp[1][0] && temp[1][1] && temp[1][2] && temp[1][3]) kill[1]=true;
							if (temp[2][0] && temp[2][1] && temp[2][2] && temp[2][3]) kill[2]=true;
							if (temp[3][0] && temp[3][1] && temp[3][2] && temp[3][3]) kill[3]=true;
							if (kill[0] || kill[1]) value_t[count]-=100;
							if (kill[2] || kill[3]) value_t[count]+=100;
							for (int l=0;l<4;l++) {
								for (int m=0;m<2;m++) {
									for (int n=2;n<4;n++) {
										if (!kill[m] && !kill[n]) {
											if (temp[m][l]==temp[n][l]) value_t[count]-=10;
											else value_t[count]+=10;
										}
									}
								}
							}
						} else {
							if (!flag) {
								search(temp[0],temp[1],temp[2],temp[3],turn+1,&value_t[count]);
							}
						}
						root[count].me=(bool)i;
						root[count].you=(bool)j;
						root[count].shift=k;
						count++;
					}
				}
			}
		}
		for (int i=0;i<count;i++) {
			if (value_t[i]<min || i==0) {
				min=value_t[i];
				manu.me=root[i].me;
				manu.you=root[i].you;
				manu.shift=root[i].shift;
			}
		}
		*value=min;
	}
	
	return manu;
}

int main() {
	int turn,temp;
	bool fin[4][4];
	manu_t ans;
	int value;
	
	while(1) {
		scanf("%d", &turn);
		for (int i=0;i<4;i++) {
			for (int j=0;j<4;j++) {
				scanf("%d", &temp);
				if (temp) fin[i][j]=true;
				else fin[i][j]=false;
			}
		}

		if (fin[2][0]
			&& fin[2][1]
			&& fin[2][2]
			&& fin[2][3]
			&& !fin[3][0]
			&& !fin[3][1]
			&& !fin[3][2]
			&& !fin[3][3]) {
				if (fin[0][0] && fin[0][1] && fin[0][2] && fin[0][3]) {
					printf("1 1 0\n");
				} else {
					printf("0 1 0\n");
				}
		} else if (!fin[2][0]
			&& !fin[2][1]
			&& !fin[2][2]
			&& !fin[2][3]
			&& fin[3][0]
			&& fin[3][1]
			&& fin[3][2]
			&& fin[3][3]) {
				if (fin[0][0] && fin[0][1] && fin[0][2] && fin[0][3]) {
					printf("1 0 0\n");
				} else {
					printf("0 0 0\n");
				}
		} else {
		
			ans = search( fin[0], fin[1], fin[2], fin[3], 0, &value);
		
			printf("%d %d %d\n", ans.me?1:0, ans.you?1:0, ans.shift);
		}
		
		fflush(stdout);
	}
	
	return 0;
}
