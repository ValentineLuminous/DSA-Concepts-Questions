/*
LC Link : https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/description/
Given a positive integer n, return the number of the integers in the range [0, n] whose binary representations do not contain consecutive ones.

Example 1:

Input: n = 5
Output: 5
Explanation:
Here are the non-negative integers <= 5 with their corresponding binary representations:
0 : 0
1 : 1
2 : 10
3 : 11
4 : 100
5 : 101
Among them, only integer 3 disobeys the rule (two consecutive ones) and the other 5 satisfy the rule. 

Intuition was quite simple we just need to convert the integer into its binary representation string and try to make numbers less than that
with no consecutive ones which is a baic digit dp problem. :)
*/



class Solution {
public:
    int dp[32][3][2];
    int solve(int index, int prev, bool tight, string &s){
        if(index>=s.length()){
            return 1;
        }

        if(dp[index][prev+1][tight]!=-1) return dp[index][prev+1][tight];
        int start = 0;
        int end = (tight==true) ? s[index]-'0' : 1;

        int ans = 0;

        for(int digit = start;digit<=end;digit++){
            if(digit==1 && prev==1) continue;

            ans+=solve(index+1, digit, (tight && digit==end),s);
        }
        return dp[index][prev+1][tight] = ans;
    }
    int findIntegers(int n) {
        string s = "";
        memset(dp,-1,sizeof(dp));
        for(int i=31;i>=0;i--){
            if(n & (1<<i)){
                s+='1';
            }
            else{
                if(s.length()>0) s+='0';
            }
        }
        return solve(0,-1,true,s);
    }
};
