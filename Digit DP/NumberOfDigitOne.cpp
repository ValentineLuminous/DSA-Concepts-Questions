/*
LC Link - https://leetcode.com/problems/number-of-digit-one/description/

Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.

Example 1:

Input: n = 13
Output: 6
*/

// Memoized Solution
class Solution {
public:
    pair<int, int> dp[12][3];
    pair<int, int> solve(int index, bool tight,  string &num){
        if(index>=num.size()){
            return {0,1};
        }

        if(dp[index][tight]!=make_pair(-1, -1)) return dp[index][tight];
        int start = 0;
        int end = (tight == true) ? num[index]-'0' : 9;

        int total = 0, ones = 0;
        for(int digit=start;digit<=end;digit++){
            pair<int, int> child = solve(index+1, (tight&& digit==end), num);

            ones+=(digit==1) ? child.first + child.second : child.first;
            total+=child.second;
        }

        return dp[index][tight] = make_pair(ones, total);
    }
    int countDigitOne(int n) {
        string num = to_string(n);

        for(int i=0;i<12;i++){
            for(int j=0;j<3;j++){
                dp[i][j] = make_pair(-1, -1);
            }
        }

        int ans = solve(0,true,num).first;

        return ans;
    }
};


// Tabulated One without recursion
class Solution {
public:
    pair<int, int> dp[12][3];
    int countDigitOne(int N) {
        string num = to_string(N);

        int n = num.size();


        for(int i=0;i<n+1;i++){
            for(int j=0;j<3;j++){
                dp[i][j] = make_pair(0, 1);
            }
        }
        
        for(int index = n-1;index>=0;index--){
            for(int tight = 1;tight>=0;tight--){
                int start = 0;
                int end = (tight == true) ? num[index]-'0' : 9;

                long long total = 0, ones = 0;
                for(int digit=start;digit<=end;digit++){
                    pair<int, int> child = dp[index+1][tight&& digit==end];

                    ones+=(digit==1) ? child.first + child.second : child.first;
                    total+=child.second;
                }

                dp[index][tight] = make_pair(ones, total);
            }
        }
        return dp[0][1].first;
    }
};
