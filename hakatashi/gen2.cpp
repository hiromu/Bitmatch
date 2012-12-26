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
	FILE *file,*write;
	int cond[65536],temp[65536],fin,now;
	unsigned short int move[65536];
	int num;

	file=fopen("node.txt","r");
	write=fopen("move2.txt","w");

	for (int i=0;i<65536;i++) {
		fscanf(file,"%d %d", &cond[i], &temp[i]);
	}

	for (int i=0;i<65536;i++) {
		if (cond[i]==0) {
			bool flag=true;
			for (int me=0;me<2 && flag;me++) {
				if (!IsKilled(i,me,0)) for (int you=0;you<2 && flag;you++) {
					if (!IsKilled(i,you,1)) for (int shift=-3;shift<=3 && flag;shift++) {
						fin=doxor(i,me,you,shift,false);
						now = ((fin & 0xFF00) >> 8) + ((fin & 0x00FF) << 8);
						if (cond[now]==0) {
							move[i]=fin & 0xFF;
							flag=false;
						}
					}
				}
			}
			if (flag) move[i]=0;
		} else {
			move[i]=temp[i] & 0xFF;
		}
		fprintf(write,"%02X,",move[i]);
	}
	
	fclose(file);
	fclose(write);

	return 0;
}