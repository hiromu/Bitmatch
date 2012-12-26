# Bitmatch Battle System

## Input

[ターン数(0-Indexed)]  
[自分の左手小指] [自分の左手薬指] [自分の左手中指] [自分の左手人さし指]  
[自分の右手人さし指] [自分の右手中指] [自分の右手薬指] [自分の右手小指]  
[相手の左手人さし指] [相手の左手中指] [相手の左手薬指] [相手の左手小指]  
[相手の右手小指] [相手の右手薬指] [相手の右手中指] [相手の右手人さし指]  

## Output

[自分の手(左手:0, 右手:1)] [相手の手(左手:0, 右手:1)] [シフト数(-3 ~ 3)]  

## Sample Input

    0
    0 0 1 1
    1 0 0 0
    1 0 0 0
    0 0 0 1

このInputから自分が後攻であることが分かります。  

## Sample Output

    0 1 -1

Sample Inputに対しこういった出力を行うと、手は以下のような状態になります。  

    0 0 1 1
    1 0 0 0
    1 0 0 0
    0 1 1 1

## Warning

Inputごとにプロセスを終了しないようにしてください。  
相手が負けた場合、もしくはターン数上限に達した場合(引き分けた場合)は、KILLシグナルが送られます。  

