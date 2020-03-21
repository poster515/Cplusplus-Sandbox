From Hackerrank challenge. Input looks like the following:

<tag1 value = "HelloWorld">
<tag2 name = "Name1">
</tag2>
</tag1>

And queries to a markup file like this are as follows:

tag1~value  
tag1.tag2~name

main.cpp outputs the correct attributes for each tag. There is no memory management yet but this trie structure was a proof of concept. 
