/*
 * parser.h
 *
 *  Created on: Mar 21, 2020
 *      Author: Jpost
 */

#include <string>
#include <unordered_map>

using namespace std;

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


    // <tag1 value = "HelloWorld">
    unsigned int tag_front = line.find_first_not_of(" ", 1 + tag.length());
    unsigned int tag_back = line.find_first_of(" ", tag_front); //next non-space character
    // cout << "tag_front = " << tag_front << " and tag_back = " << tag_back << endl;
    while (tag_front < line.length() - 1 ){ //subtract one from length() to ignore ">" character

        string temp_name("");
        string temp_val("");
        for(unsigned int i = tag_front; i < tag_back; i++){ temp_name.push_back(line[i]); }

        tag_front = line.find_first_of("\"", tag_back); //
        tag_back = line.find_first_of("\"", tag_front + 1);

        for(unsigned int i = tag_front + 1; i < tag_back; i++){ temp_val.push_back(line[i]); }

        tag_front = line.find_first_not_of(" ", tag_back + 1); //next non-space character
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

string HRML_tag_parser(string line){
    string tag; // all tags are <tag1 adfads...> or </tag1>
    unsigned int tag_back = line.find_first_of(" ");
    unsigned int end_tag = line.find_first_of(">");

    if (!tagEnd(line)){
        if (tag_back < end_tag){
            for (unsigned int i = 1; i < tag_back; i++){ tag.push_back(line[i]); }
        } else {
            for (unsigned int i = 1; i < end_tag; i++){ tag.push_back(line[i]); }
        }

    } else {
        for (unsigned int i = 2; i < line.find(">"); i++){ tag.push_back(line[i]); }
    }

    return tag;
}

vector<string> queryTagParser(string query){
    //query = tag1.tag2~name
    vector<string> query_tags;
    string temp_tag;

    unsigned int tag_front = 0; //first non-space character i.e., tag name
    unsigned int tag_back = query.find_first_of(".", tag_front); //next period character
    unsigned int end_tag = query.find_first_of("~"); //next tilda character

    while (tag_back < end_tag) {
        temp_tag = "";
        for (unsigned int i = tag_front; i < tag_back; i++) { temp_tag.push_back(query[i]); }
        query_tags.push_back(temp_tag);

        tag_front = tag_back + 1; //
        tag_back = query.find_first_of(".", tag_front); //

    }
    //grab last possible tag in query
    temp_tag = "";
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


