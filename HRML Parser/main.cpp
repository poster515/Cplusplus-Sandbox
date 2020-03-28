/*
 * HRMLparser.cpp
 *
 *  Created on: Mar 21, 2020
 *      Author: Jpost
 */

#include <cmath>
#include <cstdio>
#include <iterator>
#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
#include "trie.h"
#include "parser.h"

int main() {
    int num_lines_src_code;
    int num_lines_queries;
    cin >> num_lines_src_code;
    cin >> num_lines_queries;

    vector<string> src_code;
    vector<string> queries;

    for (int i = 0; i < num_lines_src_code; i++){
        string temp_line, line;
        cin >> temp_line;
        line = temp_line;
        while (temp_line.find(">") == string::npos){
            cin >> temp_line;
            line = line + " " + temp_line;
        }
        src_code.push_back(line);
    }

    for (int i = 0; i < num_lines_queries; i++){
        string query;
        cin >> query;
        queries.push_back(query);
    }

    TrieNodeBldr * trie_root = new TrieNodeBldr();
    TrieNode * current_node = trie_root->getRootAddress();

    for (int i = 0; i < num_lines_src_code; i++){

        string tag = HRML_tag_parser(src_code[i]);    // grab the HRML tag
        // cout << "tag in line is: " << tag << endl;
        if (tagEnd(src_code[i])){

            // return to parent node
            if (current_node->getMyTagName() == "root") { // if we're at the root
                // should never get here but ya know whatever
                continue;
            } else {
                // cout << "going back up tree from node " << current_node->getMyTagName();
                current_node = current_node->getParentAddress(); //could be "root" now FYI
                // cout << " to node " << current_node->getMyTagName() << endl;
                continue; // don't need to do anything else, just go back to parent
            }
        } else {
            // cout << "making new TrieNode with tag " << tag;
            // cout << " at current node " << current_node->getMyTagName() << endl;
            current_node = current_node->addAndReturnNewNode(tag); //add and jump to new node
            current_node->addAttributes(HRML_attr_parser(tag, src_code[i]));
        }
    }

    for (int i = 0; i < num_lines_queries; i++){

        string query = queries[i];
        // cout << "query[" << i << "] = " << query << endl;
        vector<string> query_tags = queryTagParser(queries[i]);
        // cout << "tags in query:" << endl;
        // for_each(query_tags.begin(), query_tags.end(), [](string &s){cout<<s<<endl;});
        current_node = trie_root->getRootAddress(); //now at "root" Trie Node
        bool found_tag = false;
        for (unsigned int i = 0; i < query_tags.size(); i++){
            unordered_map<string, TrieNode *> next_tags = current_node->getNextTags();
            // cout<<"looking for tag "<<query_tags[i]<<" from node "<<current_node->getMyTagName()<<endl;
            if (next_tags.find(query_tags[i]) != next_tags.end()) { //query_tags[i] in next_tags
                current_node = next_tags[query_tags[i]];
                found_tag = true;
                continue;
            } else {
                // cout<<"no tag "<<query_tags[i]<<" from node "<<current_node->getMyTagName()<<endl;
                found_tag = false;
                break;
            }
        }
        if (found_tag) {
            string attr = queryAttrParser(query);
            unordered_map<string, string> attrs = current_node->getAttributes();
            if (attrs.find(attr) != attrs.end()){
                cout << attrs.at(attr) << endl; // attr is in attrs
            } else {
                cout << "Not Found!" << endl;
            }
        } else {
            cout << "Not Found!" << endl; //prints when the tag doesn't exist
        }
    }
    return 0;
}


