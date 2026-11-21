/*
为了避免处理复杂的边界情况，采取1-based方式，并补充定义0的边界情况
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
using ll = unsigned int;
const ll MOD = 100000000;

int main(){
    string a, b;
    cin >> a >> b;
    int n = a.size();
    int m = b.size();
    a.resize(a.size()-1);
    b.resize(b.size()-1);
    a = "." + a;
    b = "." + b;
    vector<vector<ll>> dp(n, vector<ll>(m));
    vector<vector<ll>> cnt(n, vector<ll>(m));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++){
        cnt[i][0] = 1;
    }
    for (int i = 1; i < m; i++){
        cnt[0][i] = 1;
    }
    for (int i = 1; i < n; i++){
        for (int j = 1; j < m; j++){
            if (a[i] == b[j]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
                cnt[i][j] = cnt[i-1][j-1];
                // AA&A
                if (dp[i][j] == dp[i-1][j]) cnt[i][j] = (cnt[i][j] + cnt[i-1][j])%MOD;
                if (dp[i][j] == dp[i][j-1]) cnt[i][j] = (cnt[i][j] + cnt[i][j-1])%MOD;
            }
            else {
                dp[i][j] = max(dp[i][j - 1],dp[i-1][j]);
                if (dp[i][j-1] == dp[i-1][j]){
                    cnt[i][j] = 0;
                    if (dp[i-1][j-1] == dp[i][j]) cnt[i][j] = (cnt[i-1][j] + cnt[i][j-1] + MOD - cnt[i-1][j-1])%MOD;
                    else cnt[i][j] = (cnt[i-1][j] + cnt[i][j-1])%MOD;
                }
                else{
                    if (dp[i][j-1]>dp[i-1][j]) cnt[i][j] = cnt[i][j-1];
                    else cnt[i][j] = cnt[i-1][j];
                }      
            }
        }
    }
    cout << dp[n-1][m-1] << '\n' << cnt[n-1][m-1];
}