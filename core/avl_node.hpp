//
// Created by Oruqimaru on 18/7/2020.
//
#pragma once

#include "binary_node.hpp"
#include <string>
#include <utility>

using std::pair;
using std::string;
//using std::to_string;

template <class T>
class AvlNode : public BinaryNode<T, AvlNode<T> >{
public:
    #define right_navi 1
    #define left_navi 0

    AvlNode(int value):BinaryNode<int, AvlNode>(value), _balance_code(0){
    }

    ~AvlNode(){

    }

    /*
     * status code: 0: no need to repair
     *              1: need to repair
     *              2: need to rotation
     */
    inline int RepairCode(int navi){
        int old_code = _balance_code;
        if(navi == right_navi){
            _balance_code--;
        } else{
            _balance_code++;
        }
        return _balance_code;
    }

    inline void SetCode(int code){
        _balance_code=code;
    }

    inline int GetCode(){
        return _balance_code;
    }

//    string ToString(){
//        string result="{";
//
//        int left_v = -1;
//        int right_v = -1;
//        if(this->LeftChild() != NULL)
//            left_v = this->LeftChild()->GetValue();
//
//        if(this->RightChild() != NULL)
//            right_v = this->RightChild()->GetValue();
//
//        return result + to_string(left_v) + " " + to_string(this->GetValue()) + " " + to_string(right_v) + "}" +to_string(_balance_code);
//    }
private:
    int _balance_code;
};
