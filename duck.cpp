#include<bits/stdc++.h>
using namespace std;

int matrix[14][14];

bool r[14][14], c[14][14], a[5][5][14]; // r/c[pos][num], a[r/3][c/3][num]
bool e;

void dfs(int row, int col){

    if (row == 9){
        e = 1;
        return;
    }

    if (!matrix[row][col]){
        for (int k = 1 ; k <= 9 ; k++){
            //判斷最後一格是否已填
            if (e == 1){
                return;
            }
            
            if (!r[row][k] and !c[col][k] and !a[row/3][col/3][k]){
                r[row][k] = 1;
                c[col][k] = 1;
                a[row/3][col/3][k] = 1;
                matrix[row][col] = k;
                
                if (col == 8){
                    dfs(row+1, 0);
                }
                else {
                    dfs(row, col+1);
                }
                r[row][k] = 0;
                c[col][k] = 0;
                a[row/3][col/3][k] = 0;
                
                if (e == 1){ //判斷最後一格是否已填
                    return;
                }
                
                matrix[row][col] = 0;
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

    for (int j = 0 ; j < 9 ; j++){
        for (int i = 0 ; i < 9 ; i++){
            cin >> matrix[j][i];
            r[j][matrix[j][i]] = 1;
            c[i][matrix[j][i]] = 1;
            a[j/3][i/3][matrix[j][i]] = 1;
        }
    }
    
    dfs(0, 0);
    
    for (int j = 0 ; j < 9 ; j++){
        for (int i = 0 ; i < 9 ; i++){
            cout << matrix[j][i] << " \n" [i == 8];
        }
    }   
    
    return 0;
}