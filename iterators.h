#ifndef _ITERATORS_H_
#define _ITERATORS_H_
#include "Ring.h"

template<typename Key, typename Info>
class BiRing<Key,Info>::iterator{
    friend class BiRing;

    private:
    Node* node;
    iterator(const const_iterator& rhs);

    public:
    iterator();

    KeyInfoPair& operator*() const; 
    KeyInfoPair* operator->() const;
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    bool operator==(const iterator& rhs) const;
    bool operator!=(const iterator& rhs) const;   
};

template<typename Key, typename Info>
class BiRing<Key,Info>::const_iterator{
    friend class BiRing;

    private:
    Node* node;

    public:
    const_iterator();
    const_iterator(const iterator& rhs);

    const KeyInfoPair& operator*();
    const KeyInfoPair* operator->();
    const_iterator& operator++();
    const_iterator operator++(int);
    const_iterator& operator--();
    const_iterator operator--(int);
    bool operator==(const const_iterator& rhs) const;
    bool operator!=(const const_iterator& rhs) const;    

};

#include"iterators.hpp"
#endif