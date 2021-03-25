# KeyValueParserFromFile
One header file add parser functions for you project to extract data from file to containers

# Use
To use call ParseFileToVector() function and make template specialization
depending on the types to be guessed from file. It is also possible to choose two separators - 
'assigment separator', connect key and value in pair and 'separator' to split next key-value pair.
Default separators are respectively '=' for assigment separator and next line tag '\n' for separator

```cpp
ParseFileToVector<KeyType, ValueType>("YourFile.txt",'AssigmentSeparator','Separator')
```

Function returns in this case vector of pairs. For now avaible only string and int pair
```cpp 
std::vector<std::pair<std::string,int>>
```

More types soon.
