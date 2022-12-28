#include "Ring.h"
#include "iterators.h"
#include <iostream>
#include <string>
#include <vector>


template<typename Key,typename Info>
BiRing<Key,Info> filter(const BiRing<Key,Info>& source, bool(predicate)(const Key& key)){
    BiRing<Key,Info> result;
    typename BiRing<Key,Info>::const_iterator it;
    it = source.cbegin();
    for(int i = 0; i<source.size(); i++){
        if(predicate(it->key)){
            result.push_back(it->key,it->info);
        }
        ++it;
    }
    return result;
}

template<typename Key,typename Info>
BiRing<Key,Info> join(const BiRing<Key,Info>& first, const BiRing<Key,Info>& second){
    BiRing<Key,Info> result;
    result = first + second;
    return result;
}   

template<typename Key,typename Info>
BiRing<Key,Info> shuffle(const BiRing<Key,Info>& first, unsigned int fromFirst, const BiRing<Key,Info>& second, unsigned int fromSecond, unsigned int repeat){
    BiRing<Key,Info> result;
    if(first.empty() || second.empty()) {return result;}

    typename BiRing<Key,Info>::const_iterator it_first;
    it_first = first.cbegin();
    typename BiRing<Key,Info>::const_iterator it_second;
    it_second = second.cbegin();
    
    for(unsigned int r = 0; r < repeat; r++){
        for(unsigned int f = 0; f < fromFirst; f++){
            result.push_back(it_first->key,it_first->info);
            ++it_first;
        }
        for(unsigned int s = 0; s < fromSecond; s++){
            result.push_back(it_second->key,it_second->info);
            ++it_second;
        }
    }
    return result;
}

int main(){
    // BiRing<int, int> ring;
    // BiRing<int, int>::iterator it;
    // std::cout << "INSERTION, PRINT, EMPTY" << std::endl;
    // std::cout << "Is this ring empty ? " << ring.empty() <<std::endl;
    // ring.insert(3, 4, it);
    // ring.insert(2, 3, it);
    // ring.insert(6, 4, it);
    // ring.insert(10, 8, it);
    // ring.print();

    // std::cout<<std::endl;
    // std::cout << "SIZE, DOES_EXIST, CLEAR" << std::endl;
    // std::cout << "The length of the ring is " << ring.size() << std::endl;
    // std::cout << "Does this node exist ? " << ring.doesExist(3, 4) <<std::endl;
    // ring.clear();
    // std::cout << "The length of the ring is " << ring.size() << std::endl;

    // std::cout<<std::endl;
    // BiRing<int, std::string> ring_two;
    // BiRing<int, std::string>::iterator it_two;
    // std::cout << "PUSH_BACK, PUSH_FRONT, POP_BACK, POP_FRONT" << std::endl;
    // ring_two.push_back(3, "Apple");
    // ring_two.push_back(4, "Orange");
    // ring_two.print();
    // ring_two.push_front(1, "Orange");
    // ring_two.push_front(2, "Grapes");
    // ring_two.print();
    // ring_two.pop_back();
    // ring_two.pop_front();
    // ring_two.print();

    // std::cout<<std::endl;
    // BiRing<int, std::string> ring_three;
    // BiRing<int, std::string>::iterator it_three;
    // BiRing<int, std::string>::const_iterator it_four; 
    // std::cout << "ERASE, BEGIN, CBEGIN, END, CEND" << std::endl;
    // ring_three.push_back(20,"Hasan Minhaj");
    // ring_three.push_back(21,"Audrey Hepburn");
    // ring_three.push_back(22,"Meryl Streep");
    // ring_three.push_back(23,"Denzel Washington");
    // it_three = ring_three.begin();
    // std::cout<< "Key: "<<it_three->key << " Info: "<<it_three->info<<std::endl;
    // it_three = ring_three.end();
    // std::cout<< "Key: "<<it_three->key << " Info: "<<it_three->info<<std::endl;
    // it_four = ring_three.cbegin();
    // std::cout<< "Key: "<<it_four->key << " Info: "<<it_four->info<<std::endl;
    // it_four = ring_three.cend();
    // std::cout<< "Key: "<<it_four->key << " Info: "<<it_four->info<<std::endl;
    // ring_three.erase(it_three);
    // ring_three.print();

    // std::cout<<std::endl;
    // std::cout << "ASSIGNMENT OPERATOR" << std::endl;
    // BiRing<int, int> ring_four;
    // BiRing<int, int>::iterator it_five;
    // ring_four.push_front(3,3);
    // ring_four.push_front(4,5);
    // ring_four.push_front(5,6);
    // BiRing<int, int> ring_five;
    // ring_five.push_front(5,4);
    // ring_five.push_front(5,9);
    // ring_five = ring_four;
    // ring_five.print();

    // std::cout<<std::endl;
    // std::cout << "SHUFFLE" << std::endl;
    // BiRing<int, int> shuffleFirst;
    // shuffleFirst.push_back(3,1);
    // shuffleFirst.push_back(4,1);
    // shuffleFirst.push_back(5,1);
    // shuffleFirst.push_back(6,1);
    // shuffleFirst.push_back(7,1);
    // shuffleFirst.push_back(8,1);
    // shuffleFirst.push_back(9,1);
    // shuffleFirst.push_back(10,1);
    // BiRing<int, int> shuffleSecond;
    // shuffleSecond.push_back(20,2);
    // shuffleSecond.push_back(21,2);
    // shuffleSecond.push_back(22,2);
    // BiRing<int,int> result = shuffle(shuffleFirst,4,shuffleSecond,2,5);
    // result.print();

    // std::cout<<std::endl;
    // std::cout<<"OPERATOR +"<<std::endl;
    // BiRing<std::string, int> joinFirst;
    // joinFirst.push_back("eins",3);
    // joinFirst.push_back("zwei",2);
    // joinFirst.push_back("drei",2);
    // joinFirst.push_back("zwei",2); 
    // BiRing<std::string, int> joinSecond; 
    // joinSecond.push_back("eins",2);
    // joinSecond.push_back("zwei",1);
    // BiRing<std::string,int> resultJoin = joinFirst + joinSecond;
    // resultJoin.print();

    // std::cout<<std::endl;
    // std::cout<<"JOIN"<<std::endl;
    // BiRing<std::string, int> joinFirst;
    // joinFirst.push_back("eins",3);
    // joinFirst.push_back("zwei",2);
    // joinFirst.push_back("drei",2);
    // joinFirst.push_back("vier",2); 
    // BiRing<std::string, int> joinSecond; 
    // joinSecond.push_back("eins",2);
    // joinSecond.push_back("zwei",1);
    // BiRing<std::string,int> resultJoin = join(joinFirst,joinSecond);
    // resultJoin.print();

    // BiRing<std::string,int> filter_source;
    // filter_source.push_back("uno",1);
    // filter_source.push_back("due",2);
    // filter_source.push_back("tre",3);
    // filter_source.push_back("quatro",4);
    // filter_source.push_back("cinque",5);
    // BiRing<std::string,int> result_filter;
    // result_filter = filter<std::string,int>(filter_source, [](const std::string& str)->bool{return str.size() > 3;});
    // result_filter.print();

}
