#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

struct Attack{
  Attack(int s = 1, int m = 1, int y = 0){
    shi = s;
    me = m;
    you = y;
  }
  int shi, me, you;
};

int conditions[1 << 4][1 << 4][1 << 4][1 << 4][2];// 0:undefined 1:I win 2:I lose
Attack attack[1 << 4][1 << 4][1 << 4][1 << 4][2];
int shift(int x, int y){
  if(y > 0)return (x << y) & (15);
  else return (x >> -y) & (15);
}


int dfs(int m1, int m2, int y1, int y2, int z){
  if(conditions[m1][m2][y1][y2][z] != 0)return conditions[m1][m2][y1][y2][z];
  int res = 3, tmp;
  Attack loopa, wina;
  bool loop = false;
  conditions[m1][m2][y1][y2][z] = 3;
  for(int i = -3;i <= 3;i++){
    if(z == 0){
      if(m1 != 15 && y1 != 15){
   	tmp = dfs(m1, m2, y1 | shift(m1,i), y2, 1);
   	if(tmp == 3){
   	  loop = true;
   	  loopa.shi = i;
   	  loopa.me = 1;
   	  loopa.you = 1;
   	}
   	if(tmp == 1){
   	  wina.shi = i;
   	  wina.me = 1;
   	  wina.you = 1;
   	  res = 1;
   	  break;
   	}
   	if(tmp == 2)res = 2;
      }
      if(m1 != 15 && y2 != 15){
   	tmp = dfs(m1, m2, y1, y2 | shift(m1, i), 1);
   	if(tmp == 3){
   	  loop = true;
   	  loopa.shi = i;
   	  loopa.me = 1;
   	  loopa.you = 2;
   	}
   	if(tmp == 1){
   	  wina.shi = i;
   	  wina.me = 1;
   	  wina.you = 2;
   	  res = 1;
   	  break;
   	}
   	if(tmp == 2)res = 2;
      }
      if(m2 != 15 && y1 != 15){
   	tmp = dfs(m1, m2, y1 | shift(m2, i), y2, 1);
   	if(tmp == 3){
   	  loop = true;
   	  loopa.shi = i;
   	  loopa.me = 2;
   	  loopa.you = 1;
   	}
   	if(tmp == 1){
   	  wina.shi = i;
   	  wina.me = 2;
   	  wina.you = 1;
   	  res = 1;
   	  break;
   	}
   	if(tmp == 2)res = 2;
      }
      if(m2 != 15 && y2 != 15){
   	tmp = dfs(m1, m2, y1, y2 | shift(m2, i), 1);
   	if(tmp == 3){
   	  loop = true;
   	  loopa.shi = i;
   	  loopa.me = 2;
   	  loopa.you = 2;
   	}
   	if(tmp == 1){
   	  wina.shi = i;
   	  wina.me = 2;
   	  wina.you = 2;
   	  res = 1;
   	  break;
   	}
   	if(tmp == 2)res = 2;
      }
    }	  
    if(z == 1){
      if(m1 != 15 && y1 != 15){
   	tmp = dfs(m1 | shift(y1, i), m2, y1, y2, 0);
   	if(tmp == 3){
   	  loop = true;
   	  loopa.shi = i;
   	  loopa.me = 1;
   	  loopa.you = 1;
   	}
   	if(tmp == 2){
   	  wina.shi = i;
   	  wina.me = 1;
   	  wina.you = 1;
   	  res = 2;
   	  break;
   	}
   	if(tmp == 1)res = 1;
      }
      if(m1 != 15 && y2 != 15){
   	tmp = dfs(m1 | shift(y2, i), m2, y1, y2, 0);
   	if(tmp == 3){
   	  loop = true;
   	  loopa.shi = i;
   	  loopa.me = 1;
   	  loopa.you = 2;
   	}
   	if(tmp == 2){
   	  wina.shi = i;
   	  wina.me = 1;
   	  wina.you = 2;
   	  res = 2;
   	  break;
   	}
   	if(tmp == 1)res = 1;
      }
      if(m2 != 15 && y1 != 15){
   	tmp = dfs(m1, m2 | shift(y1, i), y1, y2, 0);
   	if(tmp == 3){
   	  loop = true;
   	  loopa.shi = i;
   	  loopa.me = 2;
   	  loopa.you = 1;
   	}
   	if(tmp == 2){
   	  wina.shi = i;
   	  wina.me = 2;
   	  wina.you = 1;
	  res = 2;
	  break;
	}
	if(tmp == 1)res = 1;
      }
      if(m2 != 15 && y2 != 15){
	tmp = dfs(m1, m2 | shift(y2, i), y1, y2, 0);
	if(tmp == 3){
	  loop = true;
	  loopa.shi = i;
	  loopa.me = 2;
	  loopa.you = 2;
	}
	if(tmp == 2){
	  wina.shi = i;
	  wina.me = 2;
	  wina.you = 2;
	  res = 2;
	  break;
	}
	if(tmp == 1)res = 1;
      }
    }
  }
  if(z+1 == res | !loop){
    attack[m1][m2][y1][y2][z] = wina;
    return conditions[m1][m2][y1][y2][z] = res;
  }
  else{
    attack[m1][m2][y1][y2][z] = loopa;
    return conditions[m1][m2][y1][y2][z] = 3;  
  }
}

void output_ans(int m1, int m2, int y1, int y2, int z){
  if(conditions[m1][m2][y1][y2][z] == 0){
    dfs(m1, m2, y1, y2, z);
  }
  Attack tmp = attack[m1][m2][y1][y2][z];
  cout << tmp.me - 1 << ' ' << !(tmp.you - 1) << ' ' << -tmp.shi << endl;
}

int turn, baby, medicine, middle, finger, m1, m2, y1, y2;

int main(){
  for(int i = 0; i < 16;i++){
    for(int j = 0;j < 16;j++){
      if(i == 15 && j == 15)continue;
      conditions[i][j][15][15][1] = 1;
      conditions[15][15][i][j][0] = 2;
    }
  }
  while(cin){
    cin >> turn;
    cin >> baby >> medicine >> middle >> finger;
    m1 = baby * 8 + medicine * 4 + middle * 2 + finger;
    cin >> baby >> medicine >> middle >> finger;
    m2 = baby * 8 + medicine * 4 + middle * 2 + finger;
    cin >> baby >> medicine >> middle >> finger;
    y2 = baby * 8 + medicine * 4 + middle * 2 + finger;
    cin >> baby >> medicine >> middle >> finger;
    y1 = baby * 8 + medicine * 4 + middle * 2 + finger;
    output_ans(m1, m2, y1, y2, 0);
    cout.flush();
  }
}
