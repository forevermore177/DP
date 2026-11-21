#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    int n;
    cin >> n;
    int arr[110];
    int dp_up[110], dp_down[110];
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        dp_up[i] = 1;
        dp_down[i] = 1;
    }
    //注意初始化时每个dp_up[i]=1
    for (int i = 0; i < n; i++){
        int temp_ans = -1;
        for (int j = 0; j < i; j++){
            if (arr[j] < arr[i]){
                temp_ans = max(temp_ans, dp_up[j]);
            }
        }
        dp_up[i] = max(dp_up[i], temp_ans + 1);
    }
    for (int i = n-1; i >= 0; i--){
        int temp_ans = -1;
        for (int j = n - 1; j > i; j--){
            if (arr[j] < arr[i]){
                temp_ans = max(temp_ans, dp_down[j]);
            }
        }
        dp_down[i] = max(dp_down[i], temp_ans + 1);
    }
    int maxstu = -1;
    for (int i = 0; i < n; i++){
        maxstu = max(maxstu,dp_up[i]+dp_down[i]-1);
    }
    cout << n-maxstu;
}