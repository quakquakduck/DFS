#include<bits/stdc++.h>
using namespace std;

int case_i; // 第幾筆測資
int matrix[14][14]; //盤面

int r[14][14], c[14][14], a[5][5][14]; 

/*
r[row][n] 每一列的n出現次數。
c[col][n] 每一行的n出現次數。
a[][][n] 每一個九宮格的n出現次數。
每次操作後這些變數會被插入bset
若出現2以上的數值變代表此作法無解。
*/
set<int> bset; //判斷illegal

int type; 
int ways;//計算方法數

// situation[type]
string situation[5] = {"", "Illegal", "Unique", "Ambiguous", "Impossible"};


bool not_used(int row, int col, int n){ // 判斷數字是否被填過
    return !r[row][n] and !c[col][n] and !a[row/3][col/3][n];
}

void set_reset(){ // 重製bset，並重新填入0與1
    bset.clear();
    bset.insert(1);
    bset.insert(0);
}

void plus_fc(int row, int col, int n){ // 填入
    if (n > 0){
        // 三個出現次數的變數都加1
        r[row][n]++;
        c[col][n]++;
        a[row/3][col/3][n]++;
        matrix[row][col] = n;

        // 將次數記錄進bset
        bset.insert(r[row][n]);
        bset.insert(c[col][n]);
        bset.insert(a[row/3][col/3][n]);
    }
    return;
}

void minus_fc(int row, int col, int n){ // 消除
    // 三個出現次數的變數都減1
    r[row][n]--;
    c[col][n]--;
    a[row/3][col/3][n]--;
    matrix[row][col] = 0;
    // 重製
    set_reset();
    return;
}

void dfs(int row, int col){

    if (type){
        return;
    }
    
    if (row == 9){ // 最底層
        ways++;
        if (ways >= 2){ // 檢測ambiquous
            type = 3;
        }
        return;
    }

    if (!matrix[row][col]){ // 判斷是否為空格
        for (int k = 1 ; k <= 9 ; k++){
             
            if (type){ // 檢測ambiguous
                return;
            }

            if (not_used(row, col, k)){
                
                plus_fc(row, col, k); // 出現次數增加
                
                if (col == 8){ // 進入下一列
                    dfs(row+1, 0);
                }
                else { // 同一列，進入下一行
                    dfs(row, col+1);
                }

                minus_fc(row, col, k); // 出現次數減少
                
            }
        }
        
    }
    else { // 否則繼續往下搜
        if (col == 8){
            dfs(row+1, 0);
        }
        else {
            dfs(row, col+1);
        }        
    }
}


int main(){

    while (true){
        
        case_i++;

        // memset
        for (int j = 0 ; j < 14 ; j++){
            for (int i = 0 ; i < 14 ; i++){
                r[j][i] = 0;
                c[j][i] = 0;
            }
        }
        for (int j = 0 ; j < 5 ; j++){
            for (int i = 0 ; i < 5 ; i++){
                for (int k = 0 ; k < 14 ; k++){
                    a[j][i][k] = 0;
                }
            }
        }
        type = 0;
        ways = 0;
        set_reset();


        // 輸入
        for (int j = 0 ; j < 9 ; j++){
            for (int i = 0 ; i < 9 ; i++){
                cin >> matrix[j][i];
                plus_fc(j, i, matrix[j][i]);

                // 判斷是否為Illegal
                if (bset.count(2)){
                    type = 1;
                }
            }
        }

        // 若非Illegal，則開始DFS
        if (!type){
            dfs(0, 0);
        }

        
        if (!type){ // 方法數<2
            if (ways){ // Unique
                type = 2;
            }
            else { // Impossible
                type = 4;
            }
        }
        
        cout << "Case " << case_i << ": " << situation[type] << ".\n";
    }
    return 0;
}
