/*
 * trie.cpp
 *
 *  Created on: Mar 28, 2020
 *      Author: Jpost
 */
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "trie.h"

using namespace std;

#ifndef TRIE_CPP_
#define TRIE_CPP_

TrieNode::~TrieNode(){
	cout << "entering destructor" << endl;
	delete_nodes(this);
}

void TrieNode::delete_nodes(TrieNode * node){
	if (!node->next_tags.empty()){
		for (auto it = node->next_tags.begin(); it != node->next_tags.end(); ++it ){
			delete_nodes(it->second);
			delete it->second;
			node->next_tags.erase(it);
		}
	}
}
#endif /* TRIE_CPP_ */
