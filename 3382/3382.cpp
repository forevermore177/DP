#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main(){
    int n, M, N, t;
    cin >> n >> M >> N >>t;
    if (t == 0) N = 0;
    vector<vector<int>> dp(M+1,vector<int>(N+1,0));
    for (int i = 0; i < n; i++){
        int cur_w,cur_v;
        cin >> cur_w >>cur_v;
        for (int x = M; x >= 0; x--){
            for (int y = N; y >= 0; y--){
                int maxv = dp[x][y];
                if (y >= cur_w) maxv = max(maxv, dp[x][y-cur_w]+cur_v);
                if (x >= cur_w) maxv = max(maxv, dp[x-cur_w][y]+cur_v);
                dp[x][y] = maxv;
            }
        }
    }
    cout << dp[M][N];
}