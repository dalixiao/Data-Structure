// insert delete 
//  Avl Tree.h
//  AVL Tree
//
//  Created by dali on 2/25/18.
//  Copyright © 2018 dali. All rights reserved.
#include <iostream>
#include <algorithm>
#include <cassert>
#include <fstream>
#ifndef Avl_Tree_h
#define Avl_Tree_h

template <class T>
class AVLTree{
public:
//----------------------------------------------------------------------------------------------------------------------------------------------------
    struct Node{
        Node(){ element = 0; height = 0; count = 0; left = nullptr; right = nullptr;}
        Node(T E, int H , int C, Node* L, Node* R){
            element = E;
            height = H;
            count = C;
            left = L;
            right = R;
        }
        T element;
        int height;
        int count;
        Node* left;
        Node* right;
    };
 //----------------------------------------------------------------------------------------------------------------------------------------------------
    AVLTree(){ root = NULL;}
    ~AVLTree(){ destroy(root); }
    void destroy(Node* root){
        if(root){
            if(root->left)
                destroy(root->left);
            if(root->right)
                destroy(root->right);
            delete root;
        }
    }
    
//----------------------------------------------------------------------------------------------------------------------------------------------------
//Left Rotation and Right rotation     //左旋和右旋不会改变root高度
    Node* ClockWiseRotate(Node* root){
        Node* Aright = root->left->right;
        Node* NewRoot = root->left;
        root->left = Aright;
        NewRoot -> right = root;
        root->height =  max(getHeight(root->left),getHeight(root->right))+1;
        NewRoot->height =  max(getHeight(NewRoot->left),getHeight(NewRoot->right))+1;
        return NewRoot;
    }
    Node* CounterClockWiseRotate(Node* root){
        Node* Bleft = root->right->left;   //B1
        Node* NewRoot = root->right;
        root->right = Bleft;
        NewRoot -> left = root;
        root->height =  max(getHeight(root->left),getHeight(root->right))+1;
        NewRoot->height =  max(getHeight(NewRoot->left),getHeight(NewRoot->right))+1;
        return NewRoot;
    }
    Node* DoubleRotateLR(Node* root){
        //assert(root->left->right);
        root->left = CounterClockWiseRotate(root->left);
        return ClockWiseRotate(root);
    }
    Node* DoubleRotateRL(Node* root){
        assert(root->right->left);
        root->right = ClockWiseRotate(root->right);
        return CounterClockWiseRotate(root);
        
        
    }
//----------------------------------------------------------------------------------------------------------------------------------------------------
    void rangesearch(T LB, T UB){
        rangesearch_(LB,UB,root);
    }
    void rangesearch_(T LB, T UB, Node* root){
        if(root){
        if(root->left)
            rangesearch_(LB,UB,root->left);
        if(root->element >= LB && root->element <= UB)
            cout<<root->element<<endl;
        if(root->right)
            rangesearch_(LB,UB,root->right);
        }
    }
    void Traversal(Node* root){
        if(root){
        if(root->left)
            Traversal(root->left);
        cout<<root->element<<"     "<<root->count<<endl;
        if(root->right)
            Traversal(root->right);
        }
    }
    void outputall(ofstream& OUT){
        outputall_(OUT, root);
    }
    void outputall_(ofstream& OUT, Node* root){
        if(root){
        if(root->left)
            outputall_(OUT,root->left);
        OUT << root->element << "\n";
        if(root->right)
            outputall_(OUT,root->right);
        }
    }
//----------------------------------------------------------------------------------------------------------------------------------------------------
    bool search(T e){
        return search_(e, root);
    }
    
    bool search_(T e, Node* root){
        if(root == NULL)
            return false;
        else{
            if( e == root->element )
                return true;
            else if( e < root->element )
                return search_(e, root->left);
            else
                return search_(e, root->right);
        }
    }
//----------------------------------------------------------------------------------------------------------------------------------------------------


    void insert(T e){
        root = insert_(e,root);
    }
    
    Node* insert_(T e, Node* root){
        if(root == nullptr){
            T E = e;
            int one = 1;
            Node* Nullptr = NULL;
            return new Node(E, one, one, Nullptr, Nullptr);
        }
        else{
            if(e == root->element){
                root->count++;
            }
            else if(e < root->element){
                root->left = insert_(e, root->left);
            }
            else if(e > root->element){
                root->right = insert_(e, root->right);
            }
           
            if(abs( getHeight(root->left)-getHeight(root->right) ) == 2){     //删了一个叶节点， 每次进行return之前 都要检查一遍是否平衡
                int CASE = whichCase(root);
                if(CASE == 1)
                    return ClockWiseRotate(root);
                else if(CASE == 2)
                    return DoubleRotateLR(root);
                else if(CASE == 3)
                    return CounterClockWiseRotate(root);
                else
                    return DoubleRotateRL(root);
            }
            root->height = max(getHeight(root->left),getHeight(root->right))+1;
            return root;
        }
    }
//----------------------------------------------------------------------------------------------------------------------------------------------------
    void remove(T e){
        root = remove_(e,root);
    }
    
    Node* remove_(T e, Node* root){
        if(root == NULL)
            return NULL;
        if( e < root->element)
            root->left = remove_(e, root->left);
        else if( e > root->element)
            root->right = remove_(e, root->right);
        else{          // e == root->element
            root->count--;
            if(root->count >= 1)
                return root;
            
            if( !root->left && !root->right){
                delete root;
                return NULL;
            }
            else if( (root->left != NULL) ^ (root->right != NULL) ){
                if(root->left){
                    Node* temp = root->left;
                    delete root;
                    root = temp;
                }
                else if(root->right){
                    Node* temp = root->right;
                    delete root;
                    root = temp;
                }
            }
            else{      //it is a internal node
                Node* pre = findSuccessor(root);
                root->element = pre->element;
                root->right = remove_(root->element, root->right);
            }
        }
        if(abs( getHeight(root->left)-getHeight(root->right) ) == 2){     //删了一个叶节点， 每次进行return之前 都要检查一遍是否平衡
            int CASE = whichCase(root);
            if(CASE == 1)
                return ClockWiseRotate(root);
            else if(CASE == 2)
                return DoubleRotateLR(root);
            else if(CASE == 3)
                return CounterClockWiseRotate(root);
            else
                return DoubleRotateRL(root);
        }
        root->height = max(getHeight(root->left),getHeight(root->right))+1;
        return root;
    }
//----------------------------------------------------------------------------------------------------------------------------------------------------
//Some helper function
    int getHeight(Node* root){
        if(root == NULL)
            return 0;
        else
            return root->height;
    }
    
    Node* findSuccessor(Node* root){      //return NULL if it has no predecessor
        Node* temp = NULL;
        if(root->right){
            temp = root->right;
            while(1){
                if(temp->left == NULL)
                    break;
                else
                    temp = temp->left;
            }
        }
        return temp;
    }
    void updateheight(Node* root){
        root->height = max(getHeight(root->left),getHeight(root->right))+1;
    }
    int whichCase(Node* root){       //used in AVL deletion. Determine the which action to be performed wiwh root  1: LL   2: LR   3:RR    4: RL
        if( getHeight(root->left) > getHeight(root->right) ){   //L    //不存在等于的情况， 因为调用这个函数了， 肯定左右不平衡
            if( getHeight(root->left->left) >= getHeight(root->left->right) )
                return 1;
            else
                return 2;
        }
        else{        //R
            if( getHeight(root->right->right) >= getHeight(root->right->left) )
                return 3;                                  //RR
            else
                return 4;                                   //RL
        }
        
    }
//----------------------------------------------------------------------------------------------------------------------------------------------------
    
//----------------------------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------------------------------

    Node* root;
};

#endif /* Avl_Tree_h */
