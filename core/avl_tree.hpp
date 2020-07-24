//
// Created by Oruqimaru on 18/7/2020.
//

#pragma once

#include "binary_tree.hpp"
#include "avl_node.hpp"
#include <iostream>
#include <queue>
#include <vector>
#include <stdlib.h>

using namespace std;

template <class T>
class AvlTree : BinaryTree<AvlNode<T> >{
public:
#define right_navi 1
#define left_navi 0

    //DEBUG: for debug use
    clock_t trace_time;
    int repair_time;
//    int** path_height_L;
//    int** path_height_R;
    int** path_height;
    AvlNode<T>** updater;
    int* navigator;
    int* path_key;


    //Main code
    AvlTree():repair_time(0), trace_time(0){
        BinaryTree<AvlNode<T> >();
//        path_height_L = (int**) malloc(sizeof(int*) * 50);
//        path_height_R = (int**) malloc(sizeof(int*) * 50);
        path_height = (int**) malloc(sizeof(int*) * 50);
        updater = (AvlNode<T>**) malloc(sizeof(AvlNode<T>*) * 50);
        navigator = (int*) malloc(sizeof(int) * 50);
        path_key = (int*) malloc(sizeof(int) * 50);
    }

    //TODO: clean the tree when destroyed
    ~AvlTree(){

    }

//    void ShowTree(){
//        AvlNode<T>* pivot = this->_root;
//
//        queue<AvlNode<T>*> pipe;
//        pipe.push(pivot);
//        if(pivot == NULL)
//            return;
//        while(true){
//            if(pipe.size() == 0)
//                return;
//
//            pivot = pipe.front();
//            cout << pivot->ToString() << endl;
//            pipe.pop();
//            if(pivot->LeftChild() != NULL)
//                pipe.push(pivot->LeftChild());
//
//            if(pivot->RightChild() != NULL)
//                pipe.push(pivot->RightChild());
//        }
//    }

//    int GetHeight(){
//        int left = *(this->_root->GetChildHeight());
//        int right = *(this->_root->GetChildHeight()+1);
//        return left > right ? left : right;
//
////        return this->_height;
//    }

    //TODO: insert the point, repair the tree, then update the height
    void Insert(int key){
        if(this->_root == NULL){
            AvlNode<T>* new_node = new AvlNode<T>(key);
            this->_root = new_node;
            return;
        }

        int path_len = insertTrace(key/*, path_heights, navigator, updater*/);

        repairTree(path_len/*, path_heights, navigator, updater*/);
    }

    void Query(int key){

    }

protected:
    /*
     * Only handle when root is not null. Insert the new key and reture a
     * trace vector for repair use
     *
     * Trace to the leaf that we going to insert the node and record the
     * child heights in the path. Using copy constructor to do the insert
     * of the vector. Maybe slow in this part.
     *
     * return value is the height of the path
     */
    int insertTrace(int key/*, vector<pair<int, int> >& path_heights, vector<int>& navigator, vector<AvlNode<T>*>& updater*/){
        AvlNode<T>* pivot = this->_root;
        int height = 0;

        updater[height]=pivot;

        while(true){
            int node_value=pivot->GetValue();

                if(key > node_value){
                    AvlNode<T>* right_node = pivot->RightChild();
                    if(right_node==NULL){
                        AvlNode<T>* new_node = new AvlNode<T>(key);
                        pivot->SetRight(new_node);
                        updater[height + 1] = new_node;
                        navigator[height] = right_navi;
                        height+=2;
                        break;
                    }else {
                        updater[height+1] = right_node;
                        navigator[height] = right_navi;
                        pivot = right_node;
                        ++height;
                    }
                } else{
                    AvlNode<T>* left_node = pivot->LeftChild();
                    if(left_node == NULL){
                        AvlNode<T>* new_node = new AvlNode<T>(key);
                        pivot->SetLeft(new_node);
                        updater[height + 1] = new_node;
                        navigator[height] = left_navi;
                        height+=2;
                        break;
                    }else {
                        updater[height+1] = left_node;
                        navigator[height] = left_navi;
                        pivot = left_node;
                        ++height;
                    }
                }
        }

        return height;
    }

    /*
     * all the rotation function will rotate the tree and update the child
     * heights in the real nodes
     */
    inline void rotationRR(int pivot/*, vector<pair<int, int> >& path_heights, vector<AvlNode<T>*>& updater, vector<int>& navigator*/){


        AvlNode<T>* A = updater[pivot];
        AvlNode<T>* B = updater[pivot + 1];
        AvlNode<T>* Y = B->LeftChild();

        B->SetLeft(A);
//        B->SetChildHeightL(B->GetChildHeight().first + 1);
        B->SetCode(0);


        A->SetRight(Y);
//        A->SetChildHeightR(A->GetChildHeight().second - 2);
        A->SetCode(0);

        if(pivot == 0){
            this->SetRoot(B);
        } else {
            if(navigator[pivot-1] == right_navi)
                updater[pivot-1]->SetRight(B);
            else
                updater[pivot-1]->SetLeft(B);
        }

    }

    inline void rotationRL(int pivot/*, vector<pair<int, int> >& path_heights, vector<AvlNode<T>*>& updater, vector<int>& navigator*/){

        AvlNode<T>* A = updater[pivot];
        AvlNode<T>* B = updater[pivot + 1];
        AvlNode<T>* C = updater[pivot + 2];
        AvlNode<T>* Y = C->LeftChild();
        AvlNode<T>* W = C->RightChild();

        int C_code = C->GetCode();



        C->SetLeft(A);
        C->SetRight(B);
//        C->SetChildHeight(h+1, h+1);
        C->SetCode(0);
        A->SetRight(Y);
//        A->SetChildHeightR(Y_height);
        B->SetLeft(W);
//        B->SetChildHeightL(W_height);
        switch(C_code){
            case 0:
                A->SetCode(0);
                B->SetCode(0);
                break;
            case 1:
                A->SetCode(0);
                B->SetCode(-1);
                break;
            case -1:
                A->SetCode(1);
                B->SetCode(0);
                break;
        }

        if(pivot == 0){
            this->SetRoot(C);
        } else {
            if(navigator[pivot-1] == right_navi)
                updater[pivot-1]->SetRight(C);
            else
                updater[pivot-1]->SetLeft(C);
        }
    }

    inline void rotationLR(int pivot/*, vector<pair<int, int> >& path_heights, vector<AvlNode<T>*>& updater, vector<int>& navigator*/){

        AvlNode<T>* A = updater[pivot];
        AvlNode<T>* B = updater[pivot + 1];
        AvlNode<T>* C = updater[pivot + 2];
        AvlNode<T>* W = C->LeftChild();
        AvlNode<T>* Y = C->RightChild();

        int C_code = C->GetCode();

        C->SetLeft(B);
        C->SetRight(A);
//        C->SetChildHeight(h+1, h+1);
        C->SetCode(0);

        A->SetLeft(Y);
//        A->SetChildHeightL(Y_height);

        B->SetRight(W);
//        B->SetChildHeightR(W_height);
        switch(C_code){
            case 0:
                A->SetCode(0);
                B->SetCode(0);
                break;
            case 1:
                A->SetCode(-1);
                B->SetCode(0);
                break;
            case -1:
                A->SetCode(0);
                B->SetCode(1);
                break;
        }

        if(pivot == 0){
            this->SetRoot(C);
        } else {
            if(navigator[pivot-1] == right_navi)
                updater[pivot-1]->SetRight(C);
            else
                updater[pivot-1]->SetLeft(C);
        }
    }

    inline void rotationLL(int pivot/*, vector<pair<int, int> >& path_heights, vector<AvlNode<T>*>& updater, vector<int>& navigator*/){

        AvlNode<T>* A = updater[pivot];
        AvlNode<T>* B = updater[pivot + 1];

        AvlNode<T>* Y = B->RightChild();

        B->SetRight(A);
//        B->SetChildHeightR(B->GetChildHeight().second + 1);
        B->SetCode(0);

        A->SetLeft(Y);
//        A->SetChildHeightL(A->GetChildHeight().first - 2);
        A->SetCode(0);

        if(pivot == 0){
            this->SetRoot(B);
        } else {
            if(navigator[pivot-1] == right_navi)
                updater[pivot-1]->SetRight(B);
            else
                updater[pivot-1]->SetLeft(B);
        }
    }

    /*
     * Repairt the tree after a insertion, two step
     * 1. Check whether need rotation, if not,
     */
    void repairTree(int len/*, vector<pair<int, int> >& path_heights, vector<int>& navigator, vector<AvlNode<T>*>& updater*/){
//        if(len != updater.size() || len != path_heights.size() || (len - 1) != navigator.size()){
//            cout << "[error#] Unexpected error, length of input vector doesn't suit in repair step!\n" << endl;
//            cout << "input len: " << len << "  " << "path_heights size: " << path_heights.size() << "  navi size: " << navigator.size() << " updater size: " << updater.size() ;
//            assert(0);
//        }

        int pivot = len - 2;


        int status;

        while(pivot >= 0) {
            status = updater[pivot]->RepairCode(navigator[pivot]);
            if (status == 0) {
                return;
            } else if (status == -1 || status == 1) {
                --pivot;
            } else {
                if (navigator[pivot] == right_navi) {
                    if (navigator[pivot + 1] == right_navi) {
                        rotationRR(pivot/*, path_heights, updater, navigator*/);
                    } else {
                        rotationRL(pivot/*, path_heights, updater, navigator*/);
                    }
                } else {
                    if (navigator[pivot + 1] == right_navi) {
                        rotationLR(pivot/*, path_heights, updater, navigator*/);
                    } else {
                        rotationLL(pivot/*, path_heights, updater, navigator*/);
                    }
                }
                return;
            }
        }
    }


private:
};
