/*
The implementaion of Trie is very simple and can be done in many ways i have used an array of Trie iteself we can use a map also to implement
a trie. Also 90% of time this trie implementaion and logic works perfectly fine but in some cases where memory constraints are so tight that this 
implementaion can give tle so we need to remove the space after iterating or code ends and we can use this by the deconstructor we are using 
although it is not required but in some cases where memory constraints are so high we need use this to avoid MLE
*/

class Trie {
public:
    Trie *node[26];
    bool isEnd;

    Trie() {
        for(int i=0;i<26;i++) node[i] = NULL;
        isEnd = false;
    }

    ~Trie(){
        for(int i=0;i<26;i++){
            if(node[i]!=NULL){
                delete node[i];
                node[i]==NULL;
            }
        }
    }
    
    void insert(string word) {
        Trie *root = this;
        for(auto it: word){
            int index = it-'a';

            if(root->node[index]==NULL){
                root->node[index] = new Trie();
            }
            root = root->node[index];
        }
        root->isEnd = true;
    }
    
    bool search(string word) {
        Trie *root = this;

        for(auto it: word){
            int index = it-'a';

            if(root->node[index]==NULL){
                return false;
            }
            root = root->node[index];
        }

        return root->isEnd;
    }
    
    bool startsWith(string word) {
        Trie *root = this;

        for(auto it: word){
            int index = it-'a';

            if(root->node[index]==NULL){
                return false;
            }
            root = root->node[index];
        }
        
        return true;
    }
};

