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

    //Main code
    AvlTree(){
        BinaryTree<AvlNode<T> >();
        _updater = (AvlNode<T>**) malloc(sizeof(AvlNode<T>*) * 50);
        _navigator = (int*) malloc(sizeof(int) * 50);
    }

    //Clean the tree when destroyed
    ~AvlTree(){
        free(_updater);
        free(_navigator);

        AvlNode<T>* pivot = this->_root;

        if(pivot == NULL)
            return;

        queue<AvlNode<T>*> pipe;
        pipe.push(pivot);

        while(true){
            if(pipe.size() == 0)
                return;

            pivot = pipe.front();
            pipe.pop();
            if(pivot->LeftChild() != NULL)
                pipe.push(pivot->LeftChild());

            if(pivot->RightChild() != NULL)
                pipe.push(pivot->RightChild());

            delete pivot;
        }
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

    //Insert the point, repair the tree, then update the balance code
    void Insert(T key){
        if(this->_root == NULL){
            AvlNode<T>* new_node = new AvlNode<T>(key);
            this->_root = new_node;
            return;
        }

        int path_len = insertTrace(key);

        repairTree(path_len);
    }

    //Return the predecessor of key
    T Query(T key){
        T result = NULL;
        AvlNode<T>* pivot = this->_root;
        while(true){
            if(pivot==NULL)
                return result;
            else{
                T node_value = pivot->GetValue();
                if(key == node_value)
                    return node_value;
                else if(node_value > key){
                    pivot = pivot->LeftChild();
                } else{
                    result = node_value;
                    pivot = pivot->RightChild();
                }
            }
        }
    }

private:
    /*
     * Only handle when root is not null. Insert the new key and reture
     * the length of the trace path
     *
     * Trace to the leaf that we going to insert the node and record the
     * child heights in the path.
     *
     *
     * return value is the height of the path
     */
    int insertTrace(T key){
        AvlNode<T>* pivot = this->_root;
        int height = 0;

        _updater[height]=pivot;

        while(true){
            T node_value=pivot->GetValue();

                if(key > node_value){
                    AvlNode<T>* right_node = pivot->RightChild();
                    if(right_node==NULL){
                        AvlNode<T>* new_node = new AvlNode<T>(key);
                        pivot->SetRight(new_node);
                        _updater[height + 1] = new_node;
                        _navigator[height] = right_navi;
                        height+=2;
                        break;
                    }else {
                        _updater[height+1] = right_node;
                        _navigator[height] = right_navi;
                        pivot = right_node;
                        ++height;
                    }
                } else{
                    AvlNode<T>* left_node = pivot->LeftChild();
                    if(left_node == NULL){
                        AvlNode<T>* new_node = new AvlNode<T>(key);
                        pivot->SetLeft(new_node);
                        _updater[height + 1] = new_node;
                        _navigator[height] = left_navi;
                        height+=2;
                        break;
                    }else {
                        _updater[height+1] = left_node;
                        _navigator[height] = left_navi;
                        pivot = left_node;
                        ++height;
                    }
                }
        }

        return height;
    }

    /*
     * all the rotation function will rotate the tree and update the balance
     * in the real nodes
     */
    inline void rotationRR(int pivot){


        AvlNode<T>* A = _updater[pivot];
        AvlNode<T>* B = _updater[pivot + 1];
        AvlNode<T>* Y = B->LeftChild();

        B->SetLeft(A);
        B->SetCode(0);


        A->SetRight(Y);
        A->SetCode(0);

        if(pivot == 0){
            this->SetRoot(B);
        } else {
            if(_navigator[pivot-1] == right_navi)
                _updater[pivot-1]->SetRight(B);
            else
                _updater[pivot-1]->SetLeft(B);
        }

    }

    inline void rotationRL(int pivot){

        AvlNode<T>* A = _updater[pivot];
        AvlNode<T>* B = _updater[pivot + 1];
        AvlNode<T>* C = _updater[pivot + 2];
        AvlNode<T>* Y = C->LeftChild();
        AvlNode<T>* W = C->RightChild();
        int C_code = C->GetCode();

        C->SetLeft(A);
        C->SetRight(B);
        C->SetCode(0);
        A->SetRight(Y);
        B->SetLeft(W);
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
            if(_navigator[pivot-1] == right_navi)
                _updater[pivot-1]->SetRight(C);
            else
                _updater[pivot-1]->SetLeft(C);
        }
    }

    inline void rotationLR(int pivot){

        AvlNode<T>* A = _updater[pivot];
        AvlNode<T>* B = _updater[pivot + 1];
        AvlNode<T>* C = _updater[pivot + 2];
        AvlNode<T>* W = C->LeftChild();
        AvlNode<T>* Y = C->RightChild();
        int C_code = C->GetCode();

        C->SetLeft(B);
        C->SetRight(A);
        C->SetCode(0);

        A->SetLeft(Y);

        B->SetRight(W);
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
            if(_navigator[pivot-1] == right_navi)
                _updater[pivot-1]->SetRight(C);
            else
                _updater[pivot-1]->SetLeft(C);
        }
    }

    inline void rotationLL(int pivot){

        AvlNode<T>* A = _updater[pivot];
        AvlNode<T>* B = _updater[pivot + 1];

        AvlNode<T>* Y = B->RightChild();

        B->SetRight(A);
        B->SetCode(0);

        A->SetLeft(Y);
        A->SetCode(0);

        if(pivot == 0){
            this->SetRoot(B);
        } else {
            if(_navigator[pivot-1] == right_navi)
                _updater[pivot-1]->SetRight(B);
            else
                _updater[pivot-1]->SetLeft(B);
        }
    }

    /*
     * Repairt the tree after a insertion, two step
     * 1. repair the balance code along the path
     *    if the status returned is 0, no need to repair
     *    more. if -1, 1, repair more. if -2, 2, directly
     *    rotation and repair finished.
     */
    void repairTree(int len){

        int pivot = len - 2;
        int status;

        while(pivot >= 0) {
            status = _updater[pivot]->RepairCode(_navigator[pivot]);
            if (status == 0) {
                return;
            } else if (status == -1 || status == 1) {
                --pivot;
            } else {
                if (_navigator[pivot] == right_navi) {
                    if (_navigator[pivot + 1] == right_navi) {
                        rotationRR(pivot);
                    } else {
                        rotationRL(pivot);
                    }
                } else {
                    if (_navigator[pivot + 1] == right_navi) {
                        rotationLR(pivot);
                    } else {
                        rotationLL(pivot);
                    }
                }
                return;
            }
        }
    }

    AvlNode<T>** _updater;
    int* _navigator;

};
