#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

void itob(int value, bool *fin) {
	if (value & 0x8000) fin[0]=true; else fin[0]=false;
	if (value & 0x4000) fin[1]=true; else fin[1]=false;
	if (value & 0x2000) fin[2]=true; else fin[2]=false;
	if (value & 0x1000) fin[3]=true; else fin[3]=false;
	if (value & 0x0800) fin[4]=true; else fin[4]=false;
	if (value & 0x0400) fin[5]=true; else fin[5]=false;
	if (value & 0x0200) fin[6]=true; else fin[6]=false;
	if (value & 0x0100) fin[7]=true; else fin[7]=false;
	if (value & 0x0080) fin[8]=true; else fin[8]=false;
	if (value & 0x0040) fin[9]=true; else fin[9]=false;
	if (value & 0x0020) fin[10]=true; else fin[10]=false;
	if (value & 0x0010) fin[11]=true; else fin[11]=false;
	if (value & 0x0008) fin[12]=true; else fin[12]=false;
	if (value & 0x0004) fin[13]=true; else fin[13]=false;
	if (value & 0x0002) fin[14]=true; else fin[14]=false;
	if (value & 0x0001) fin[15]=true; else fin[15]=false;

	return;
}

int btoi(bool *fin) {
	int value=0;
	if (fin[0])  value+=0x8000;
	if (fin[1])  value+=0x4000;
	if (fin[2])  value+=0x2000;
	if (fin[3])  value+=0x1000;
	if (fin[4])  value+=0x0800;
	if (fin[5])  value+=0x0400;
	if (fin[6])  value+=0x0200;
	if (fin[7])  value+=0x0100;
	if (fin[8])  value+=0x0080;
	if (fin[9])  value+=0x0040;
	if (fin[10]) value+=0x0020;
	if (fin[11]) value+=0x0010;
	if (fin[12]) value+=0x0008;
	if (fin[13]) value+=0x0004;
	if (fin[14]) value+=0x0002;
	if (fin[15]) value+=0x0001;

	return value;
}

//turn false:Ž©•ª‚©‚ç‘ŠŽè true:‘ŠŽè‚©‚çŽ©•ª
int doxor(int fin_int, bool from, bool to, int shift, bool turn) {
	int tohand,fromhand;
	bool shifted[4],dest[16],fin[16];

	itob(fin_int,fin);

	if (!turn) {
		tohand=to?3:2;
		fromhand=from?1:0;
	} else {
		tohand=to?1:0;
		fromhand=from?3:2;
	}

	for (int i=0;i<4;i++) {
		if (i!=tohand) {
			for (int j=0;j<4;j++) dest[i*4+j]=fin[i*4+j];
		} else {
			for (int j=0;j<4;j++) shifted[j]=false;
			for (int j=0;j<4;j++) if (0<=j+shift && j+shift<4) shifted[j+shift]=fin[fromhand*4+j];
			for (int j=0;j<4;j++) dest[tohand*4+j] = fin[tohand*4+j] ^ shifted[j];
		}
	}

	return btoi(dest);
}

//turn 0:Ž©•ª 1:‘ŠŽè
bool IsKilled(int fin_int, int hand, int turn) {
	int handnum;
	bool fin[16];
	itob(fin_int,fin);

	if (turn==0) {
		handnum=hand?1:0;
	} else {
		handnum=hand?3:2;
	}

	for (int i=0;i<4;i++) if (!fin[handnum*4+i]) return false;

	return true;
}

int main() {
	FILE *file,*file2;
	//int list[65536][28];
	char node[65536][2];
	int temp;
	unsigned short int move[65536][2];
	std::vector<unsigned short int> list[65536][2];

	//file=fopen("list.txt","w");
	//file2=fopen("node.txt","w");

	for (int turn=0;turn<2;turn++) {
		for (int fin=0;fin<65536;fin++) {
			list[fin][turn].clear();
			for (int from=0;from<2;from++) {
				for (int to=0;to<2;to++) {
					if (!IsKilled(fin,from,turn) && !IsKilled(fin,to,turn?0:1)) {
						for (int shift=-3;shift<=3;shift++) {
							temp=doxor(fin,(bool)from,(bool)to,shift,(bool)turn);
							std::vector<unsigned short int>::iterator it = std::find(list[fin][turn].begin(),list[fin][turn].end(),temp);
							if (it == list[fin][turn].end()) list[fin][turn].push_back(temp);
						}
					}
				}
			}
			for ( std::vector<unsigned short int>::iterator it = list[fin][turn].begin() ; it!=list[fin][turn].end() ; ++it ) {
				if (it!=list[fin][turn].begin()) ;//printf(" ");
				//printf("%d",*it);
			}
			//printf("\n");
		}
	}

	memset(node,0,sizeof(node));
	memset(move,0,sizeof(move));

	for (int i=0;i<65536;i++) {
		if (IsKilled(i,0,0) && IsKilled(i,1,0)) {
			node[i][0]=2;
			node[i][1]=2;
		} else if (IsKilled(i,0,1) && IsKilled(i,1,1)) {
			node[i][0]=1;
			node[i][1]=1;
		}
	}
	
	for (int i=0;i<500;i++) {
		bool noflag=true;
		for (int fin=0;fin<65536;fin++) {
			if (node[fin][0]==0) {
				bool tsumi=true;
				for ( std::vector<unsigned short int>::iterator it = list[fin][0].begin() ; it!=list[fin][0].end() ; ++it ) {
					if (node[*it][1] == 1) {
						node[fin][0] = 1;
						move[fin][0] = *it;
						noflag=false;
						break;
					}
				}
			}
			if (node[fin][1]==0) {
				bool tsumi=true;
				for ( std::vector<unsigned short int>::iterator it = list[fin][1].begin() ; it!=list[fin][1].end() ; ++it ) {
					if (tsumi) {
						if (node[*it][0] != 1) {
							tsumi=false;
						}
					}
				}
				if (tsumi && node[fin][1]==0) {
					node[fin][1]=1;
					move[fin][1]=list[fin][1][0];
					noflag=false;
				}
			}
		}
		if (noflag) {
			//printf("%d\n",i);
			break;
		}
	}

	for (int fl=2;fl<100;fl++) {
		int win,total;
		for (int fin=0;fin<65536;fin++) {
			if (node[fin][1]==0) {
				bool tsumi=true;
				win=0;
				total=0;
				for ( std::vector<unsigned short int>::iterator it = list[fin][1].begin() ; it!=list[fin][1].end() ; ++it ) {
					if (node[*it][0]<fl && node[*it][0]!=0) {
						win++;
					}
					total++;
				}
				if ((win>5 && total-win==1) || (double)win/(double)total>=0.9) {
					node[fin][1]=fl;
					for ( std::vector<unsigned short int>::iterator it = list[fin][1].begin() ; it!=list[fin][1].end() ; ++it ) {
						if (node[*it][0]<fl && node[*it][0]!=0) {
							move[fin][1]=*it;
							break;
						}
					}
				}
			}
		}
		for (int fin=0;fin<65536;fin++) {
			if (node[fin][0]==0) {
				bool tsumi=true;
				for ( std::vector<unsigned short int>::iterator it = list[fin][0].begin() ; it!=list[fin][0].end() ; ++it ) {
					if (node[*it][1] == fl) {
						node[fin][0] = fl;
						move[fin][0]=*it;
						break;
					}
				}
			}
		}
	}

	for (int i=0;i<15000;i++) {
		printf("%04x",move[i][0]);
	}

	//puts("end");

	//fclose(file);
	//fclose(file2);

	return 0;
}