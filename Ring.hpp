#include <iostream>
#include "Ring.h"

    //***** Copy Assignment Op, Move Assignment Op, Checking operator*****
    template  <typename Key, typename Info>
    BiRing<Key,Info>& BiRing<Key,Info>::operator=(const BiRing<Key,Info>& rhs){
        if(this == &rhs) {return *this;}
        clear();
        const_iterator it;
        it = rhs.cbegin();
        do{
            push_back(it -> key, it -> info);
            ++it;
        }while(it != rhs.cbegin());
        return *this;
    }

    template  <typename Key, typename Info>
    BiRing<Key,Info>& BiRing<Key,Info>::operator=(BiRing<Key,Info>&& rhs){
        clear();
        any = rhs.any;
        NodeCount = rhs.NodeCount;
        rhs.any = nullptr;
        rhs.NodeCount = 0;
        return *this;
    }

    template  <typename Key, typename Info>
    bool BiRing<Key,Info>::operator==(const BiRing<Key,Info>& rhs) const{
        if(any == nullptr && rhs.any == nullptr) {return true;}
        if(NodeCount != rhs.NodeCount) {return false;}

        const_iterator it;
        it = cbegin();
        const_iterator it2;
        it = rhs.cbegin(); 
        do{
            if(it -> key != it2 -> key || it -> info != it2 -> info) {return false;}
            ++it;
            ++it2;
        } while(it != cbegin());
        return true;        
    }  

    template  <typename Key, typename Info>
    bool BiRing<Key,Info>::operator!=(const BiRing<Key,Info>& rhs) const{
        return !(*this == rhs);
    }

    template<typename Key, typename Info>
    BiRing<Key,Info> BiRing<Key,Info>::operator+(const BiRing<Key,Info> &rhs) const{
        BiRing<Key,Info> result;
        if(!(is_key_unique()) || !(rhs.is_key_unique())) {std::cout<<"The key in this ring is not unique !"<<std::endl; return result;}
        result = *this;
        auto temp = rhs.cbegin();
        do { 
            auto temp2 = result.location(temp->key);
            if(temp2.node != nullptr){
                temp2->info += temp->info;
            } else {
                result.push_back(temp->key,temp->info);
            }
            ++temp;
        } while(temp != rhs.cbegin());
    return result;
    }

    //***** Iterator properties************************************************************************
    template  <typename Key, typename Info>
    typename BiRing<Key,Info>::iterator BiRing<Key,Info>::push_front(const Key& key, const Info& info){
        iterator it;
        Node* newnode = new Node(key,info,nullptr,nullptr);
        if(empty()) {it.node = any = newnode; any -> prev = any; any -> next = any; NodeCount++; return it;}
        newnode -> prev = any -> prev;
        newnode -> next = any;
        any -> prev -> next = newnode;
        any -> prev = newnode;
        any = newnode;
        NodeCount++;
        it.node = any;
        return it;
    }

    template  <typename Key, typename Info>
    typename BiRing<Key,Info>::iterator BiRing<Key,Info>::push_back(const Key& key, const Info& info){
        iterator it;
        Node* newnode = new Node(key,info,nullptr,nullptr);
        if(empty()) {push_front(key,info); it.node = any; return it;}
        newnode -> prev = any -> prev;
        newnode -> next = any;
        newnode -> prev -> next = newnode;
        newnode -> next -> prev = newnode;
        NodeCount++;
        it.node = any -> prev;
        return it;
    }

    template  <typename Key, typename Info>
    typename BiRing<Key,Info>::iterator BiRing<Key,Info>::pop_front(){
        iterator it;
        if(empty()) {std::cout<<"Ring is empty"<<std::endl; it.node = nullptr; return it;}
        it = (*this).begin();
        it = (*this).erase(it);
        return it;
    }

    template  <typename Key, typename Info>
    typename BiRing<Key,Info>::iterator BiRing<Key,Info>::pop_back(){
        iterator it;
        if(empty()) {std::cout<<"Ring is empty"<<std::endl; it.node = nullptr; return it;}
        it.node = any -> prev;
        it = (*this).erase(it);
        return it;
    }

    template  <typename Key, typename Info>
    typename BiRing<Key,Info>::iterator BiRing<Key,Info>::insert(const Key& key, const Info& info, iterator& beforeThis){
        if(empty()) {push_front(key,info); beforeThis.node = any; return begin();}

        Node* newnode = new Node(key,info,beforeThis.node,beforeThis.node->prev);
        beforeThis.node->prev->next = newnode;
        beforeThis.node->prev = newnode;
        NodeCount++;
        iterator it;
        it.node = newnode;
        return it;
    }

    template  <typename Key, typename Info>
    typename BiRing<Key,Info>::iterator BiRing<Key,Info>::erase(const iterator& pos){
        iterator it = begin();
        if(pos.node == nullptr) {std::cout<<"Nothing to delete"<<std::endl; return it;}
        if(NodeCount == 1) {delete pos.node; any = nullptr; NodeCount--; return it;}
        if(pos.node == any) {any = any -> next;}
        pos.node -> prev -> next = pos.node -> next;
        pos.node -> next -> prev = pos.node -> prev;
        it.node = pos.node -> next;
        delete pos.node;
        NodeCount--;
        return it;
    }
    
    template<typename Key,typename Info>
    typename BiRing<Key,Info>::iterator BiRing<Key,Info>::location(const Key& key) const{
        iterator it;
        it.node = nullptr;
        if(empty()) return it;

        it = cbegin();
        for(int i = 0; i<size(); i++){
            if(it -> key == key) {
                return it;
            }
            ++it;
        }
        it.node = nullptr;
        return it;
    }  

    template  <typename Key, typename Info>
    typename BiRing<Key,Info>::iterator BiRing<Key,Info>::begin(){
        iterator it;
        it.node = any;
        return it;
    }

    template  <typename Key, typename Info>
    typename BiRing<Key,Info>::iterator BiRing<Key,Info>::end(){
        iterator it;
        it.node = any -> prev;
        return it;
    }    

    template  <typename Key, typename Info>
    typename BiRing<Key, Info>::const_iterator BiRing<Key, Info>::cbegin() const{
        const_iterator it;
        it.node = any;
        return it;
    }

    template  <typename Key, typename Info>
    typename BiRing<Key,Info>::const_iterator BiRing<Key,Info>::cend() const{
        const_iterator it;
        it.node = any -> prev;
        return it;
    }     

    //***** Other methods*******************************************************************
    template<typename Key,typename Info>
    void BiRing<Key,Info>::clear(){
        if(empty()) {return;}

        iterator it = (*this).begin();
        iterator it2 = it;

        for(int i = 0; i<NodeCount; i++) {
            it2 = it;
            ++it;
            (*this).erase(it2);
        }
        NodeCount = 0;
        any = nullptr;
    }

    template<typename Key,typename Info>
    bool BiRing<Key,Info>::empty() const{
        return NodeCount == 0;
    }

    template<typename Key,typename Info>
    bool BiRing<Key,Info>::doesExist(const Key& key, const Info& info) const{
        if(empty()) return false;

        const_iterator it = (*this).cbegin();
        for(int i = 0; i<NodeCount; i++){
            if(it -> key == key && it -> info == info) {
                return true;
            }
            ++it;
        }
        return false;
    }  

    template<typename Key,typename Info>
    int BiRing<Key,Info>::size() const{
        return NodeCount;
    }

    template<typename Key,typename Info>
    void BiRing<Key,Info>::print() const{
        if(empty()) {std::cout<<"Ring is empty"<<std::endl; return;}

        const_iterator it = (*this).cbegin();
        std::cout<<"----Data in the ring----"<<std::endl;
        for(int i = 0; i<NodeCount; i++){
            std::cout<<"Key: " << it -> key << " | Info: " << it -> info << std::endl;
            ++it;
        }
        std::cout<<"----End of the ring --- Key:"<<it -> key<<" -- Info:"<<it -> info<<std::endl;
    }

    template<typename Key,typename Info>
    bool BiRing<Key,Info>::is_key_unique() const{
        const_iterator it = cbegin();
        const_iterator it2 = it;
        ++it2;
        for(int i = 0; i < size(); i++){
            for(int j = 1; j < size(); j++){
                if(it -> key == it2 -> key){return false;}
                ++it2;
            }
            ++it;
            it2 = it;
            ++it2;
        }
        return true;
    }   