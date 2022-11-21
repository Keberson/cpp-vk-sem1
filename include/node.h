#ifndef INCLUDE_NODE_H_
#define INCLUDE_NODE_H_

template<typename T>
struct Node {
    T _val;
    Node *_next;
    Node *_prev;
};

#endif  // INCLUDE_NODE_H_
