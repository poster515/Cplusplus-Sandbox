/*
 * trie.h
 *
 *  Created on: Mar 21, 2020
 *      Author: Jpost
 */

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

#ifndef TRIE_H_
#define TRIE_H_

class TrieNode{
    private:
        string tag_name;
        unordered_map<string, string> attributes;
        unordered_map<string, TrieNode *> next_tags;
        TrieNode * parent_tag = nullptr;

    public:
        TrieNode(string tagName, TrieNode * parent){
            tag_name = tagName;
            parent_tag = parent;
        }
        ~TrieNode(){

        }
        void addAttributes(vector<vector<string>> attrs){
            /* [
                    [attr_name1, attr_name2, ...],
                    [attr_val1,  attr_val2,  ...]
                ]                                       */
            for (unsigned int i =0; i < attrs[0].size(); i++){
                attributes[attrs[0][i]] = attrs[1][i];
            }
        }
        TrieNode * addAndReturnNewNode(string t_name){
            TrieNode * temp_ptr = new TrieNode(t_name, this); // create new Node
            next_tags[t_name] = temp_ptr;      // link to current node
            return temp_ptr;
        }
        TrieNode * getParentAddress(){
            return parent_tag;
        }
        string getMyTagName(){
            return tag_name;
        }
        unordered_map<string, TrieNode *> getNextTags(){
            return next_tags;
        }
        unordered_map<string, string> getAttributes(){
            return attributes;
        }
};

class TrieNodeBldr {
    private:
        TrieNode * root = nullptr;
    public:
        TrieNodeBldr(){
            root = new TrieNode("root", nullptr);
        }
        ~TrieNodeBldr(){}

        TrieNode * getRootAddress(){
            return root;
        }
};


#endif /* TRIE_H_ */
