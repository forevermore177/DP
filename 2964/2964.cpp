/*
假设关掉的灯为[l,r]（不可能经过不关，因此必为区间），那么人的位置有两种状态：
dp[l][r][0]代表现在在l处，dp[l][r][1]代表现在在r处
则dp[l][r][0]=min(dp[l+1][r][0]+耗费,dp[l+1][r][1]+耗费)
dp[l][r][1]=min(dp[l][r-1][0]+耗费,dp[l][r-1][1]+耗费)
同时l,r应从初始st开始分别向左右扩张，故可以改记c-l,c+r
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = 1e18;
struct lamp{
    int pos;
    int W;
};
int main(){
    int n, c; 
    lamp arr[2010];
    int presum[2010];
    vector<vector<ll>> dp_l(2010, vector<ll>(2010));
    vector<vector<ll>> dp_r(2010, vector<ll>(2010));
    cin >> n >> c;
    c -= 1; // 1-based!
    for (int I = 0; I < n; I++){
        cin >> arr[I].pos >> arr[I].W;
        if (I == 0) presum[I] = arr[I].W;
        else presum[I] = presum[I-1] + arr[I].W;
    }
    dp_l[0][0] = dp_r[0][0] = 0;
    for (int lens = 1; lens < n; lens++){
        int maxleft = min(c, lens);
        int minleft = max(0, c + lens - (n-1));
        for (int left = minleft; left <= maxleft; left++){
            int right = lens - left;
            ll ans1,ans2,ans3,ans4;
            if (left == 0) dp_l[left][right] = INF;
            else{
                ans1 = dp_l[left-1][right] + (arr[c-(left-1)].pos - arr[c-left].pos) * (presum[c-left] + presum[n-1]-presum[c+right]);
                ans2 = dp_r[left-1][right] + (arr[c+right].pos - arr[c-left].pos) * (presum[c-left] + presum[n-1]-presum[c+right]);
                dp_l[left][right] = min(ans1, ans2);
            }
            if (right == 0) dp_r[left][right] = INF;
            else{
                ll temp;
                if (c==left) temp = 0;
                else temp = presum[c-left-1];
                ans3 = dp_l[left][right-1] + (arr[c+right].pos - arr[c-left].pos) * (temp + presum[n-1]-presum[c+right-1]);
                ans4 = dp_r[left][right-1] + (arr[c+right].pos - arr[c+right-1].pos) * (temp + presum[n-1]-presum[c+right-1]);
                dp_r[left][right] = min(ans3, ans4);
            }
        }
    }
    cout << min(dp_l[c][n-1-c],dp_r[c][n-1-c]);
}