#include <iostream>
#include <fstream> 
#include <string>
#include <vector>

struct Line {
  int number, type, degree; // type: 0->header, ... degree: 1->h1, 2->h2, ...
  std::string text;  
};

struct Article {
  std::vector<Line> lines;
  std::vector<std::string> imageSources;
}; 

std::vector<std::string> getMD(std::string path){
    std::string File, line; 
    std::ifstream md(path);
    std::vector<std::string> lines;
    while (getline (md, line)) {
      lines.push_back(line + '\n');
      // File = File + line + '\n';
    }
    md.close();   
    return lines;
}

Article MDProcessor(std::vector<std::string> file, std::string outputFileName){
  Article article;
  std::vector<Line> linesOfArticle;
  std::ofstream outfile (outputFileName);
  outfile << "<!DOCTYPE html><html><head><title>Pardus grafik arayüzle kurulum</title><meta charset=\"UTF-8\"><link rel=\"shortcut icon\" href=\"pardus-icon.png\" type=\"image/x-icon\" /><link rel=\"stylesheet\" href=\"../Styles/style.css\"><link rel=\"stylesheet\" href=\"../Styles/article-style.css\"><link rel=\"stylesheet\" href=\"../Styles/global.css\"></head><body>" << std::endl;
  for(unsigned long ind=0; ind<=file.size()-1; ind++){
    Line line;
    line.text = file[ind];
    // Headers
    if(ind == 0){
      outfile << "<center><h1>" << file[ind] << "</h1></center>";  
      continue;
    }
    if (file[ind].find("#") != std::string::npos) {
      int index=0;
      while(true){
        if(file[ind].substr(index,file[ind].length()-index).find("#") == std::string::npos){
          break;
        }
        index++;
      }
      line.degree=index;
      outfile << "<h" << index+1 << ">" << file[ind].substr(line.degree+1,file[ind].length()) << "</h" << index+1 << ">";  
    }else if(file[ind].find("![") != std::string::npos){
      std::string ResimUzantisi;
      if(file[ind].find(".png") != std::string::npos){
        ResimUzantisi = ".png";
      }else if(file[ind].find(".jpg") != std::string::npos){
        ResimUzantisi = ".jpg";
      }
      std::string imageTitle = file[ind].substr(2,file[ind].find("]")-2);
      std::string imagePath = file[ind].substr(file[ind].find("$")+1, file[ind].length());
      outfile << "<img src=\"" << imagePath << "\">" << std::endl;
    }else if(file[ind].find("[") != std::string::npos){
      std::string linkTitle = file[ind].substr(1,file[ind].find("]")-1);
      std::string linkPath = file[ind].substr(file[ind].find("$")+1, file[ind].length());
      outfile << "<p>"  << "<a href=\"" << linkPath << "\">" << linkTitle << "</a></p>" << std::endl;
    }
    else{
      outfile << "<p class=\"article-text\">" << file[ind] << "<p>";
    }
  }
  outfile << "</body></html>" << std::endl;
  outfile.close();
  return article;
}
std::vector<std::string>& Arguments()
{
    static std::vector<std::string> arguments;
    return arguments;
}
int main(int argc, char* argv[])
{
  for (int i = 0; i < argc; ++i)
  {
      Arguments().push_back(argv[i]);
  }
  std::string MDPath = Arguments()[1];
  std::string HTMLPath = Arguments()[2];
  MDProcessor(getMD(MDPath),HTMLPath);
  return 0;
}
