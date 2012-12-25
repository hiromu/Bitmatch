#include <stdio.h>

int main(void)
{
    int i, j, k, turn, finger[2][2][4];
    while(1) {
        scanf("%d", &turn);
        for(i = 0; i < 2; i++)
            for(j = 0; j < 2; j++)
                for(k = 0; k < 4; k++)
                    scanf("%d", &finger[i][j][k]);
        printf("%d %d %d\n", rand() % 2, rand() % 2, rand() % 4);
        fflush(stdout);
    }
    return 0;
}
