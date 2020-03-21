#include <cmath>
#include <cstdio>
#include <iterator>
#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

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
        void addAttributes(vector<vector<string>> attrs){
            /* [
                    [attr_name1, attr_name2, ...],
                    [attr_val1,  attr_val2,  ...]
                ]                                       */
            for (int i =0; i < attrs[0].size(); i++){
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
        TrieNodeBldr(){}

        ~TrieNodeBldr(){
            delete root;
        }

        void addRoot(string t_name){
            root = new TrieNode(t_name, nullptr);
        }
        TrieNode * getRootAddress(){
            return root;
        }
};

string HRML_tag_parser(string line){
    string tag; // all tags are "<tag1 adfads...>"
    for (unsigned int i = 1; i < line.find(" "); i++){ tag.push_back(line[i]); }
    return tag;
}

vector<vector<string>> HRML_attr_parser(string tag, string line){
    //inputs: tag name and line of source code e.g., <tag1 value = "HelloWorld">
    //outputs: vector of two vectors: 1 for attribute names and 1 for attribute values
    /*
        [
            [attr_name1, attr_name2, ...],
            [attr_val1,  attr_val2,  ...]
        ]
    */
    vector<string> attr_names;
    vector<string> attr_values;

    string temp_name;
    string temp_val;
    // <tag1 value = "HelloWorld">
    unsigned int tag_front = line.find_first_not_of(" ", 1 + tag.length()); //first non-space character i.e., tag name
    unsigned int tag_back = line.find_first_of(" ", tag_front); //next non-space character

    while (tag_front < line.length()){
        //
        for(unsigned int i = tag_front; i < tag_back; i++){ temp_name.push_back(line[i]); }

        cout << "found attribute name: '" << temp_name << "'" <<endl; //going to assume attribute name must have a value

        tag_front = line.find_first_not_of("= ", tag_back); //
        tag_back = line.find_first_of(" ", tag_front); //next non-space character

        //DEBUG - tag_front works, need to handle ">" character behind closing quote for tag_back
        cout << "tag front = " << tag_front << " , tag_back = " << tag_back << endl;

        for(unsigned int i = tag_front + 1; i < tag_back - 1; i++){ temp_val.push_back(line[i]); }

        cout << "found attribute value: '" << temp_name << "'" << endl;

        tag_front = line.find_first_not_of(" ", tag_back); //first non-space character
        tag_back = line.find_first_of(" ", tag_front); //next non-space character

        // now push back newly found attribute name and corresponding value into vectors
        attr_names.push_back(temp_name);
        attr_values.push_back(temp_val);
    }
    vector<vector<string>> attrs;
    attrs.push_back(attr_names);
    attrs.push_back(attr_values);
    return attrs;
}

bool tagEnd(string line){ //returns true if '/' in src code line
    string delimiter ("/");
    return (line.find(delimiter) != string::npos);
}

vector<string> queryTagParser(string query){
    //query = tag1.tag2~name
    vector<string> query_tags;
    string temp_tag;

    unsigned int tag_front = 0; //first non-space character i.e., tag name
    unsigned int tag_back = query.find_first_of(".", tag_front); //next period character
    unsigned int end_tag = query.find_first_of("~"); //next tilda character

    while (tag_back < end_tag) {

        for (unsigned int i = tag_front; i < tag_back; i++) { temp_tag.push_back(query[i]); }
        query_tags.push_back(temp_tag);

        tag_front = tag_back + 1; //
        tag_back = query.find_first_of(".", tag_front); //

    }
    //grab last possible tag in query
    for (unsigned int i = tag_front; i < end_tag; i++) { temp_tag.push_back(query[i]); }
    query_tags.push_back(temp_tag);

    return query_tags;
}

string queryAttrParser(string query){
    string attribute;
    unsigned int start_attr = query.find_first_of("~"); //next tilda character
    for (unsigned int i = start_attr+1; i < query.length(); i++) { attribute.push_back(query[i]); }
    return attribute;
}

int main() {
    int num_lines_src_code;
    int num_lines_queries;
    cin >> num_lines_src_code;
    cin >> num_lines_queries;

    vector<string> src_code;
    vector<string> queries;

    TrieNodeBldr trie_root;
    TrieNode * current_node;

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
    //DEBUG
    for_each(src_code.begin(), src_code.end(), [](string &s){ cout << s << endl;});

    for (int i = 0; i < num_lines_queries; i++){
        string query;
        cin >> query;
        queries.push_back(query);
    }
    //DEBUG
    for_each(queries.begin(), queries.end(), [](string &s){ cout << s << endl;});

    for (int i = 0; i < num_lines_src_code; i++){

        string tag = HRML_tag_parser(src_code[i]);    // grab the HRML tag

        if (tagEnd(src_code[i])){
            // return to parent node
            if (current_node->getParentAddress() == nullptr) { // if we're at the root
                // not sure what to do if we're at the root
                cout << "can't go up, at root node" << endl;
                break;
            } else {
                cout << "going back up trie" << endl;
                current_node = current_node->getParentAddress();
                continue; // don't need to do anything else, just go back to parent
            }
        }

        if (trie_root.getRootAddress() == nullptr){ // if trie isn't built
            cout << "establishing new root node" << endl;
            trie_root.addRoot(tag);                // now add it to the root node
            cout << "root tag is: " << trie_root.getRootAddress()->getMyTagName() << endl;
            current_node = trie_root.getRootAddress(); // then go to the new node
            current_node->addAttributes(HRML_attr_parser(tag, src_code[i]));

        } else if (tag != current_node->getMyTagName()){
            // then we have a new tag, need to create new trie node
            cout << "found new tag, adding new trie node" << endl;
            // create new node and jump to it
            current_node = current_node->addAndReturnNewNode(tag);
            // now add attributes to it
            current_node->addAttributes(HRML_attr_parser(tag, src_code[i]));
        }
    }

    for (int i = 0; i < num_lines_queries; i++){
        // grab ith query from list
        vector<string> query_tags = queryTagParser(queries[i]);

        // reset current_node to root of trie structure
        current_node = trie_root.getRootAddress();

        for (unsigned int i = 0; i < query_tags.size(); i++){

            if(query_tags[i] == current_node->getMyTagName()){

                if (i < (query_tags.size()-1)){
                    // good, but we've got to continue looking for tags
                    unordered_map<string,TrieNode*>next_tags=current_node->getNextTags();

                    if (next_tags.find(query_tags[i+1]) != next_tags.end()){
                        // then the next tag is in the dictionary
                        current_node = next_tags.at(query_tags[i+1]);
                        continue;
                    }
                } else {
                    // now we just need to look for attributes
                    string attr = queryAttrParser(queries[i]);
                    unordered_map<string,string>attrs = current_node->getAttributes();
                    if (attrs.find(attr) != attrs.end()){
                        // then the attribute is in the dictionary
                        cout << attrs.at(attr);
                        continue;
                    } else {
                        cout << "Not Found!" << endl;
                        continue;
                    }
                }

            } else {
                cout << "Not Found!" << endl;
                continue;
            }
        }
    }

    return 0;
}
