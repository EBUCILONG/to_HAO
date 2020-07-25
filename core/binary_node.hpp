//
// Created by Oruqimaru on 18/7/2020.
//
#pragma once

#include <cstddef>

template <class T, class NodeT>
class BinaryNode {
public:
    BinaryNode(T value):_value(value),_parent(NULL),_left_child(NULL),_right_child(NULL){
    }

    void SetLeft(NodeT* node){
        _left_child = node;
    }

    void SetRight(NodeT* node){
        _right_child = node;
    }

    T GetValue() const{
        return _value;
    }

    NodeT* LeftChild() {
        return _left_child;
    }

    NodeT* RightChild() {
        return _right_child;
    }

    NodeT* Parent() {
        return _parent;
    }

protected:
    T _value;
//private:
    NodeT *_parent;
    NodeT *_left_child;
    NodeT *_right_child;
};
