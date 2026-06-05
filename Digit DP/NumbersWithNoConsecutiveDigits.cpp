/*
How to deal with digit dp problems it is difficult but not impossible so let's do it in step by step process -

1. First generally in the questions it is mention that you need to find numbers in the range [a, b] with numbers
    following certain conditions like no consecutive digits should be same.(we are taking this no consecutive equal digit example)

2. We cannot directly find all the numbers in the range [a, b] we will first find all the numbers in the range [0,a-1] and range [0,b]
    then we'll subtract the answers from those two ranges

3. Why we are doing this because while generating numbers it will be difficult for us to handle the generated number must lie 
    in the range we can handle the part where the generated number should be less than the upper limit (b).

4. Now for solving this we need four things 1. ind( the current index of the digit in the number where are we standing). 
    2. prev (if required what last digit we have picked ) 3. tight( it is a state which will tell whether we can freely put any digit
    from 0 to 9 or we have some sort of restriction ove there so that number should not be graeter than the upperlimit)
    Example - 324567 for ind = 0 digit = 3 we cannot put any digit from 0 to 9 at that index because digit greater than zero will make it 
    out of range so tight is one we can only choose from 0 to 3. Now let's say if we choose 2 at index 0 then at index 1 we can
    choose any number between [0, 9] means tight is zero choosing any digit will not make the number out of range.
    and value of tight will be decide by this logic if the currently we are tight (1) and we also choose the last digit like upper limit 2 then 
    the tight will be 1 for next index otherwise zero

5. Now we need one more thing which is necessary to handle which isLeadingZero state let's say we have choose zero as starting digit then 
    that digit will not be counted beacuse leading digit is zero for example - if i choose first index as zero "0" and move to the next index
    then my logic will say i can't choose zero one more time on index 1 because at zeroth index it is zero but that's not the case it is a leading zero so that
    will not matter so we have to deal with this part and for this we are using this state.
    And  the value of this state should follow this logic (if leading zero are true and we are agian choosing zero then it will be pass as true
    otherwise if we choose any other value and leading zero is true or false can be anything then isleading zero will be false.) 

6. After this all things remain same just the question demands can change but the core lagic remains same like no consecutive digit, all smaller digit
    ,etc.
*/

#include<bits/stdc++.h>
using namespace std;
class Solution  {

public:

    int dp[15][11][2][2];    
    long long solve(int index, int prev, bool tight, bool isLeadZero, string &num){
        if(index>=num.length()) return 1; //we have reached the last index that means one number is generated with satified conditions

        if(dp[index][prev+1][tight][isLeadZero]!=-1) return dp[index][prev+1][tight][isLeadZero];
        int lowerBound = 0;
        int upperBound = (tight==true) ? num[index]-'0' : 9;

        long long ans = 0;

        for(int digit = lowerBound; digit<=upperBound; digit++){
            if(digit==prev && isLeadZero==false) continue;

            ans+= solve(index+1, digit, (tight && digit==upperBound), (isLeadZero && digit==0), num);
        }
        return dp[index][prev+1][tight][isLeadZero] = ans;
    }

    long long digitDp(long long a, long long b){
        string temp1 = to_string(a-1);
        string temp2 = to_string(b);

        memset(dp,-1,sizeof(dp));
        long long right = solve(0,-1,1,1,temp2);

        memset(dp,-1,sizeof(dp));
        long long left = solve(0,-1,1,1,temp1);

        return right - left;
    }
};
int main(){

    long long  a, b;
    cin>>a>>b;

    Solution sol;

    cout<<sol.digitDp(a,b)<<endl;

    return 0;
}
