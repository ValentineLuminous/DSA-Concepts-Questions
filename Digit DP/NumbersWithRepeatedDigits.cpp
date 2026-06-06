/*
LC Link : https://leetcode.com/problems/numbers-with-repeated-digits/description/
Given an integer n, return the number of positive integers in the range [1, n] that have at least one repeated digit.

Example 1:

Input: n = 20
Output: 1
Explanation: The only positive number (<= 20) with at least 1 repeated digit is 11.

*/



class Solution {
public:
    int dp[11][2][2][2][1030];
    int solve(int index, bool tight, bool isZero, bool repeat, int bit, string num){
        if(index>=num.size()){
            if(repeat) return 1;
            return 0;
        }

        if(dp[index][tight][isZero][repeat][bit]!=-1) return dp[index][tight][isZero][repeat][bit];
        int start = 0;
        int end = (tight==true) ? num[index]-'0' : 9;

        int ans = 0;

        for(int digit=start; digit<=end;digit++){
            if(isZero && digit==0){
                ans+=solve(index+1, (tight && digit==end), true,false, bit, num);
            }
            else{
                bool isDigitUsed = (bit & (1<<digit));

                ans += solve(index + 1,(tight && digit == end),false,(repeat || isDigitUsed),(bit | (1 << digit)),num);
            }
        }
        return dp[index][tight][isZero][repeat][bit] = ans;
    }
    int numDupDigitsAtMostN(int N) {
        string num = to_string(N);

        int n = num.length();

        memset(dp,-1, sizeof(dp));

        return solve(0,true,true,false, 0,num);

    }
};
