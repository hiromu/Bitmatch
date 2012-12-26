#include <stdio.h>

int main() {
	FILE *read,*write;
	char buff[300000];

	read=fopen("dat.txt","r");
	write=fopen("temp.txt","w");

	fgets(buff,300000,read);
	for (int i=0;i<65536;i++) {
		unsigned char temp=0;
		if ('0'<=buff[i*4+2] && buff[i*4+2]<='9') temp+=(buff[i*4+2]-'0')*16;
		if ('a'<=buff[i*4+2] && buff[i*4+2]<='f') temp+=(buff[i*4+2]-'a'+10)*16;
		if ('0'<=buff[i*4+3] && buff[i*4+3]<='9') temp+=(buff[i*4+3]-'0');
		if ('a'<=buff[i*4+3] && buff[i*4+3]<='f') temp+=(buff[i*4+3]-'a'+10);
		fprintf(write,"%d ",temp);
	}

	fclose(read);
	fclose(write);

	return 0;
}