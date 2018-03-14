
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#ifndef BST_h
#define BST_h
using namespace std;

class BST{

//*****************************************************************************************
//basic storage element
public:
    struct Node{
        string word;
        int count;
        Node* left = NULL;
        Node* right = NULL;
    };
    
//*****************************************************************************************
//constructor and destructor
    BST(){root = NULL;}
    //destructor
    ~BST(){
        destroy(root);
    }
    void destroy(Node* root){
        if(root){
            if(root->left)  destroy(root->left);
            if(root->right) destroy(root->right);
            delete root;
        }
    }
    
//*****************************************************************************************
    //insert and its tow hleper function;
    void insert(string W){
        root = insert_(root, W);
    }
    
    Node* insert_(Node* root, string W){
        if(!root){
            root = new Node;
            root->word = W;
            root->count = 1;
            return root;
        }
        else{
            if(root->word == W)
                root->count++;
            if(root->word.compare(W) < 0)
                root->right = insert_(root->right, W);
            if(root->word.compare(W) > 0)
                root->left = insert_(root->left, W);
            return root;
        }
    }
//*****************************************************************************************
    //search and its helper fucntion
    bool search(string W){
        if( search_(root, W) != NULL){
            //cout<<"BST: The word "<<W<<" with count "<<search_(root, W)->count<<endl;
            return true;
        }
        else{
            return false;
        }
    }
    Node* search_(Node* root, string W){
        if(!root){
            return NULL;
        }
        else{
            if(root->word.compare(W) == 0)
                return root;
            if(root->word.compare(W) < 0)
                return search_(root->right, W);
            if(root->word.compare(W) > 0)
                return search_(root->left, W);
            return NULL;
        }
    }
//*****************************************************************************************
    //delete
    Node* deleteNode(string W){
        Node* temp = search_(root, W);
        if(temp == NULL)
            return root;
        if( temp->count > 1){
            (temp->count)--;
            return root;
        }
        else{
            return deleteNode_(root, W);
        }
    }
    Node* deleteNode_(Node* root, string W){
        if(!root){
            return NULL;
        }
        if(W > root->word ){
            root->right = deleteNode_(root->right, W);
        }
        else if( W < root->word ){
            root->left = deleteNode_(root->left, W);
        }
        else{
            if(root->left && root->right){
                Node* cursor = root->right;
                while(cursor -> left){
                    cursor = cursor -> left;
                }
                string temp = cursor -> word;
                root->word = cursor -> word;
                root->count = cursor -> count;
                root->right = deleteNode_(root->right, temp);
            }
            else if(root->left && !root->right){
                Node* temp = root->left;
                delete root;
                return temp;
            }
            else if(root->right && !root->left){
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else{
                delete root;
                root = NULL;
            }
        }
        return root;
    }
//*****************************************************************************************
    //sort
    vector<string> sort(){
        vector<string> result;
        inorder(root, result);
        return result;
    }
    void inorder(Node* root, vector<string>& result){
        if(root){
            if(root->left)
                inorder(root->left, result);
            result.push_back(root->word);
            if(root->right)
                inorder(root->right, result);
        }
    }
    
//*****************************************************************************************
    void outputall(ofstream& outfile){
        _outputall(root, outfile);
    }
    
    void _outputall(Node* root,ofstream& outfile){
        if(root){
            if(root->left)
                _outputall(root->left,outfile);
            outfile << root->word;
            outfile << endl;
            if(root->right)
                _outputall(root->right,outfile);
        }
    }
//*****************************************************************************************
    //range search TreeTraversal
    void rangesearch(string LB,string UP){
        int count = 0;
        rangesearch_(root, LB, UP,count);
        //cout<<count<<endl;
    }
    void rangesearch_(Node* root, string LB, string UP, int& count){
        if(root){
            if(root->left)
                rangesearch_(root->left,LB,UP,count);
            if(root->word >= LB && root->word <= UP){
                count++;
                cout<<root->word;
                cout<<endl;
            }
            if(root->right)
                rangesearch_(root->right, LB, UP, count);
        }
    }
    
    
private:
    Node* root;
};

#endif /* BST_h */
