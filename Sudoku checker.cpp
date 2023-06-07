#include<bits/stdc++.h>
using namespace std;

int case_i;
int matrix[14][14];
set<int> bset;
int r[14][14], c[14][14], a[5][5][14];

int type;
int ways;

int st_r, st_c;

string situation[5] = {"", "Illegal", "Unique", "Ambiguous", "Impossible"};


bool not_used(int row, int col, int n){
    return !r[row][n] and !c[col][n] and !a[row/3][col/3][n];
}

void set_reset(){
    bset.clear();
    bset.insert(1);
    bset.insert(0);
}

void plus_fc(int row, int col, int n){ // 填入
    if (n > 0){
        r[row][n]++;
        c[col][n]++;
        a[row/3][col/3][n]++;
        matrix[row][col] = n;
        bset.insert(r[row][n]);
        bset.insert(c[col][n]);
        bset.insert(a[row/3][col/3][n]);
    }
    return;
}

void minus_fc(int row, int col, int n){ // 消除
    
    r[row][n]--;
    c[col][n]--;
    a[row/3][col/3][n]--;
    matrix[row][col] = 0;
    set_reset();
    return;
}

void dfs(int row, int col){

    if (type){
        return;
    }
    
    if (row == 9){
        ways++;
        if (ways >= 2){
            type = 3;
        }
        return;
    }

    if (!matrix[row][col]){
        for (int k = 1 ; k <= 9 ; k++){
             
            if (type){
                return;
            }

            if (not_used(row, col, k)){
                
                plus_fc(row, col, k);
                
                if (col == 8){
                    dfs(row+1, 0);
                }
                else {
                    dfs(row, col+1);
                }

                minus_fc(row, col, k);
                
            }
        }
        
    }
    else {
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

        // 初始化
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
        st_r = -1;
        st_c = -1;
        set_reset();


        // 輸入
        for (int j = 0 ; j < 9 ; j++){
            for (int i = 0 ; i < 9 ; i++){
                if (st_r == -1 and matrix[j][i]){
                    st_r = j;
                    st_c = i;
                }
                cin >> matrix[j][i];
                plus_fc(j, i, matrix[j][i]);
                if (bset.count(2)){
                    type = 1;
                }
            }
        }


        if (!type){
            dfs(0, 0);
        }

        
        if (!type){
            if (ways){
                type = 2;
            }
            else {
                type = 4;
            }
        }
        
        cout << "Case " << case_i << ": " << situation[type] << ".\n";
    }
    return 0;
}
