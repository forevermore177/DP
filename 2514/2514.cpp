/*
对于区间[l,r]，设最后删除的是牌k，则最后一次贡献应当是a[l-1]*a[k]*a[r+1]
故不妨在原数组首尾补1，dp[l][r]定义为l、r保留不删的最大贡献值
dp[l][r]=max(dp[l][k]+a[l]a[k]a[r]+dp[k][r])
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;
int main(){
    int n;
    cin >> n;
    vector<int>a(n+2);
    a[0] = a[n+1] = 1;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    int N = n+2;
    vector<vector<ll>>dp(N,vector<ll>(N));
    for (int lens = 0; lens < N; lens++){
        for (int left = 0; left +lens <= N-1; left++){
            int right = left + lens;
            if (right <= left + 1) dp[left][right] = 0;
            else{
                ll times = a[left] * a[right];
                ll tempmax = dp[left][left+1] + a[left+1] * times + dp[left+1][right];
                for (int i = left + 2; i < right; i++){
                    ll cur = dp[left][i] + dp[i][right] + a[i] * times;
                    tempmax = max(tempmax, cur);
                }
                dp[left][right] = tempmax;
            }
        }
    }
    cout << dp[0][N - 1];
}