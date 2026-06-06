/*
You are given two numeric strings num1 and num2 and two integers max_sum and min_sum. We denote an integer x to be good if:

num1 <= x <= num2
min_sum <= digit_sum(x) <= max_sum.
Return the number of good integers. Since the answer may be large, return it modulo 109 + 7.

Note that digit_sum(x) denotes the sum of the digits of x.

 

Example 1:

Input: num1 = "1", num2 = "12", min_sum = 1, max_sum = 8
Output: 11
Explanation: There are 11 integers whose sum of digits lies between 1 and 8 are 1,2,3,4,5,6,7,8,10,11, and 12. Thus, we return 11.

*/



class Solution {
public:
    const int mod = 1e9+7;
    int mini, maxi;
    long long dp[25][2][500];
    string subtractOne(string num) {
        int n = num.size();

        int i = n - 1;

        while (i >= 0) {
            if (num[i] > '0') {
                num[i]--;
                break;
            }

            num[i] = '9';
            i--;
        }

        int pos = 0;
        while (pos < num.size() - 1 && num[pos] == '0')
            pos++;

        return num.substr(pos);
    }
    long long solve(int index, bool tight, long long sum, string &num){
        if(index>=num.length()){
            return (sum>=mini && sum<=maxi) ? 1: 0;
        }
        if(sum>maxi) return 0;

        if(dp[index][tight][sum]!=-1) return (dp[index][tight][sum])%mod;

        int start = 0;
        int end = (tight==true) ? num[index]-'0' : 9;

        long long ans = 0;

        for(int digit = start; digit<=end;digit++){

            ans = (ans%mod + solve(index+1,(tight && digit==end), sum+digit,num)%mod)%mod;
        }
        return dp[index][tight][sum] = ans%mod;
    }
    int count(string num1, string num2, int min_sum, int max_sum) {
        
        mini = min_sum;
        maxi = max_sum;

        

        num1 = subtractOne(num1);
        // cout<<num1<<endl;
        memset(dp,-1*1LL, sizeof(dp));
        long long a = (solve(0,true,0*1LL,num1))%mod;

        memset(dp,-1*1LL, sizeof(dp));
        long long b = (solve(0,true,0*1LL,num2))%mod;
        // cout<<a<<" "<<b<<endl;

        return (b - a + mod) % mod;
    }
};
