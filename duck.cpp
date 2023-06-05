#include<bits/stdc++.h>
using namespace std;

int pos[19][19]; //棋盤
int n;
long long int ans;

bool xpy[38], xmy[38], used[19];
/* 
計算攻擊範圍，不能同行、同列
bool used 為 x 座標, depth 為 y 座標。

↘方向：當目前座標為 (x,y) 下一行為 (x+1, y+1)，
座標相減時，變動量會互相抵銷，可知同一斜線上 x-y 不變。
↙方向：當目前座標為 (x,y) 下一行為 (x-1, y+1)，
座標相加時，變動量會互相抵銷，可知同一斜線上 x+y 不變。

*/


void dfs(int depth){ // dfs 實作

    if (depth == n){
        ans++;
        return;
    }


    for (int i = 0 ; i < n ; i++){
        if (!xpy[i+depth] and !xmy[i-depth+n] and !used[i]){ // i-depth+n 避免負整數
            
            xpy[i+depth] = 1;
            xmy[i-depth+n] = 1;
            used[i] = 1;

            dfs(depth+1);
            
            xpy[i+depth] = 0;
            xmy[i-depth+n] = 0;
            used[i] = 0;
        }    
    }
    return;
}

int main(){
    while (cin >> n){
        ans = 0;
        dfs(0);
        cout << ans << "\n";
    }
    return 0;
}
