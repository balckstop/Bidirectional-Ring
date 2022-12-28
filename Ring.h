#ifndef _RING_H_
#define _RING_H_

template<typename Key,typename Info>
class BiRing{
    public:
        struct KeyInfoPair{
            Key key;
            Info info;
            KeyInfoPair() : key(), info() {};
            KeyInfoPair(Key newKey, Info newInfo) : key(newKey), info(newInfo) {};
        };
    private:    
        struct Node{
            KeyInfoPair Key_Info;
            Node* next;
            Node* prev;
            Node() : Key_Info(KeyInfoPair()), next(nullptr), prev(nullptr) {};
            Node(Key newKey, Info newInfo, Node* node, Node* prevNode) 
                : Key_Info(KeyInfoPair(newKey,newInfo)), next(node), prev(prevNode) {};
        }; 
        Node* any;
        int NodeCount; 

    public:
    //***** Class for traversal*****
    class iterator;
    class const_iterator;

    //***** Default Constructor, Destructor, Copy Constructor, Move Constructor*****
    BiRing() : any(nullptr), NodeCount(0) {};
    ~BiRing() {clear();}
    BiRing(const BiRing& rhs) : any(nullptr) {*this = rhs;}
    BiRing(BiRing&& rhs) : any(nullptr) {*this = rhs;}

    //***** Copy Assignment Op, Move Assignment Op, Checking operator*****
    BiRing<Key,Info>& operator=(const BiRing<Key,Info>& rhs);
    BiRing<Key,Info>& operator=(BiRing<Key,Info>&& rhs);
    bool operator==(const BiRing<Key,Info>& rhs) const;
    bool operator!=(const BiRing<Key,Info>& rhs) const;
    BiRing<Key,Info> operator+(const BiRing<Key,Info>& rhs) const;

    //***** Iterator properties*****
    iterator push_front(const Key& key, const Info& info);
    iterator push_back(const Key& key, const Info& info);
    iterator pop_front();
    iterator pop_back();
    iterator insert(const Key& key, const Info& info, iterator& beforeThis);
    iterator erase(const iterator& pos);
    iterator location(const Key& key) const;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

    //***** Other methods***** 
    void clear();
    bool empty() const;
    bool doesExist(const Key& key, const Info& info) const;    
    int size() const;
    void print() const;
    bool is_key_unique() const;
};
#include "Ring.hpp"
#include "iterators.h"
#endif

