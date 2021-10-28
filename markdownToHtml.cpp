#include <iostream>
#include <fstream> 
#include <string>
#include <cstdio>
#include <vector>

void getMD(std::string path){
    std::vector<std::string> Program = {};
    std::string line; 
    std::ifstream md(path);
    
    while (getline (md, line)) {
      Program[Program.size()] = line;
      std::cout << line << std::endl;
    }

    md.close();   
}

int main(){
  std::vector<std::string> prog;
  prog = getMD("deneme.md");
  std::cout << prog.size() << std::endl;
  return 0;
}
