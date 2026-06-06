/*
Given an array of digits which is sorted in non-decreasing order. You can write numbers using each digits[i] as many times as we want. For example, if digits = ['1','3','5'], we may write numbers such as '13', '551', and '1351315'.

Return the number of positive integers that can be generated that are less than or equal to a given integer n.

 

Example 1:

Input: digits = ["1","3","5","7"], n = 100
Output: 20
Explanation: 
The 20 numbers that can be written are:
1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.
*/


class Solution {
public:
    int dp[10][2][2];
    int solve(int index, bool tight, bool leadZero, vector<string> &digits, string &s){
        if(index>=s.length()){
            return 1;
        }

        if(dp[index][tight][leadZero]!=-1) return dp[index][tight][leadZero];

        int end = (tight) ? s[index]-'0' : 9;

        int ans = 0;

        for(int i=0;i<digits.size();i++){
            int digit = digits[i][0]-'0';

            if(tight){
                if(digit<=end){
                    if(digit==0 && !leadZero) continue;
                    ans+=solve(index+1, (tight && digit>=end),(leadZero && digit==0), digits, s);
                }
            }
            else{
                if(digit==0 && !leadZero) continue;
                ans+=solve(index+1, false,(leadZero && digit==0), digits, s);
            }
            
        }
        return dp[index][tight][leadZero] = ans;
    }
    int atMostNGivenDigitSet(vector<string>& digits, int n) {

        string num = to_string(n);
        memset(dp, -1, sizeof(dp));
        digits.insert(digits.begin(),"0");
        return solve(0,true,true,digits,num) - 1;
    }
};
