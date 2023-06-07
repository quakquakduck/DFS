#include<bits/stdc++.h>
using namespace std;

pair<double, double> cor[10];
int n;
int a = 0;


int ans_idx[10], idx[10];
bool used[10];
double ans_len[10], len[10];
long double l;
long double m = 1e9;

double r(pair<double, double> a, pair<double, double> b){
    return sqrt(pow(a.first-b.first, 2)+pow(a.second-b.second, 2));
}


void dfs(int depth, int top){
    
    if (depth == n){
        if (l < m){
            for (int i = 0 ; i < n ; i++){
                m = l;
                ans_len[i] = len[i];
                ans_idx[i] = idx[i];
            }
        }
        return;
    }
    if (l >= m){
        return;
    }
    if (depth == 0){
        for (int i = 0 ; i < n ; i++){
            idx[depth] = i;
            used[i] = 1;
            dfs(depth+1, i);
            used[i] = 0;    
        }
    }
    else {
        for (int i = 0 ; i < n ; i++){
            if (!used[i]){
                idx[depth] = i;
                used[i] = 1;
                len[depth] = r(cor[i], cor[top]);
                l += len[depth];
                dfs(depth+1, i);
                used[i] = 0;
                l -= len[depth];
            }
        }
    }
    
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    while (cin >> n){
        if (n == 0){
            return 0;
        }
        m = 1e9;
        a++;
        for (int i = 0 ; i < n ; i++){
            cin >> cor[i].first >> cor[i].second;
        }
        dfs(0, 0);
        cout << "**********************************************************\nNetwork #" << a << '\n';
        for (int i = 1 ; i < n ; i++){
            cout << "Cable requirement to connect (" << cor[ans_idx[i-1]].first << "," << cor[ans_idx[i-1]].second << ") to (" << cor[ans_idx[i]].first << "," << cor[ans_idx[i]].second << ") is " << fixed << setprecision(2) << ans_len[i]+16 << " feet.\n";
        }
        cout << fixed << setprecision(2) << "Number of feet of cable required is " << fixed << setprecision(2) << m+16*(n-1) << ".\n";
    }

}
