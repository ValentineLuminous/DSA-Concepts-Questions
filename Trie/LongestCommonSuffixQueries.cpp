/*

LC LINK : https://leetcode.com/problems/longest-common-suffix-queries/
Question :
You are given two arrays of strings wordsContainer and wordsQuery.

For each wordsQuery[i], you need to find a string from wordsContainer that has the longest common suffix with wordsQuery[i]. 
If there are two or more strings in wordsContainer that share the longest common suffix, find the string that is the smallest in length. 
If there are two or more such strings that have the same smallest length, find the one that occurred earlier in wordsContainer.

Return an array of integers ans, where ans[i] is the index of the string in wordsContainer that has the longest common suffix 
with wordsQuery[i].

Input: wordsContainer = ["abcdefgh","poiuygh","ghghgh"], wordsQuery = ["gh","acbfgh","acbfegh"]

Output: [2,0,2]

Explanation:

Let's look at each wordsQuery[i] separately:

For wordsQuery[0] = "gh", strings from wordsContainer that share the longest common suffix "gh" are at indices 0, 1, and 2. Among these, the answer is the string at index 2 because it has the shortest length of 6.
For wordsQuery[1] = "acbfgh", only the string at index 0 shares the longest common suffix "fgh". Hence it is the answer, even though the string at index 2 is shorter.
For wordsQuery[2] = "acbfegh", strings from wordsContainer that share the longest common suffix "gh" are at indices 0, 1, and 2. Among these, the answer is the string at index 2 because it has the shortest length of 6.


Approach: This question is very simple  we just need to figure out that for suffix we need to reverse those strings and we can normally use
the longest common prefix approach and in place of reversing because it will cost us O(nlogn) TC we can just iterate on srings from last to first.
And for finding longest common prefix in a query based question we can definitely use a TRIE data structure.

One important thing in this question is that if two strings s1 and s2 share same common suffix then we need to pick the string with the shortest
length and if length of both strings are also same we need to pick the sring which comes first for this we have a small tweek in the code that
with isEnd bool variable we have one int suffix variable also which will account for this like which index string have longest common suffix till now.

*/

#include<bits/stdc++.h>
using namespace std;

class Trie{
private:

    Trie *node[26];
    bool isEnd;
    int suff ;

public:
    Trie(){
        for(int i=0;i<26;i++) node[i] = NULL;
        isEnd = false;
        suff = -1;
    }

    ~Trie(){
        for(int i=0;i<26;i++){
            if(node[i] != NULL){
                delete node[i];
                node[i] = NULL;
            }
        }
    }


    void insert(string &word,int &index, vector<string> &nums){
        Trie *dummy = this;

        // changed here: iterate from end
        for(int j = word.length()-1; j>=0; j--){

            char ch = word[j];
            int ind = ch-'a';

            if(dummy->node[ind]==NULL){
                dummy->node[ind] = new Trie();
                dummy->node[ind]->suff = index;
            }
            else{

                if(word.length()<nums[dummy->node[ind]->suff].length()){
                    dummy->node[ind]->suff = index;
                }
                else if(word.length()==nums[dummy->node[ind]->suff].length()){
                    dummy->node[ind]->suff = min(dummy->node[ind]->suff, index);
                }
            }

            dummy = dummy->node[ind];
        }

        dummy->isEnd = true;
    }

    int search(string &word){
        Trie *dummy = this;

        // changed here: iterate from end
        for(int j = word.length()-1; j>=0; j--){

            char ch = word[j];
            int ind = ch-'a';

            if(dummy->node[ind]==NULL) 
                return dummy->suff;

            dummy = dummy->node[ind];
        }

        return dummy->suff;
    }
};


class Solution {
public:
    vector<int> stringIndices(vector<string>& nums, vector<string>& q) {

        Trie *root = new Trie();

        int mini = INT_MAX;

        for(int i=0;i<nums.size();i++){

            // no copy + no reverse now
            root->insert(nums[i], i, nums);

            if(mini==INT_MAX || nums[mini].length()>nums[i].length()){
                mini = i;
            }
            else if(nums[mini].length() == nums[i].length()){
                mini = min(i, mini);
            }
        }


        vector<int> ans(q.size(), 0);

        for(int i=0;i<q.size();i++){

            // no copy + no reverse now
            int k = root->search(q[i]);

            ans[i] = k==-1 ? mini : k;
        }

        delete root;
        return ans;
    }
};



