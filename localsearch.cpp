//localsearch.cpp
//bruno spinelli

#include "WebPage.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <set>
#include <algorithm>

using namespace std;

//recursive web crawler function with set
void webCrawler(string filePath, set<string> &visitedPages, list<WebPage> &pages)
{
  //gets the directory of the file
  string currentDir;
  
  //gets the name of the file
  string fileName;

  // suppose URL is "html_files/subdir1/subdir2/file7.html"
  size_t lastSlashPos = filePath.find_last_of('/');
  if (lastSlashPos != std::string::npos) 
  {
    // directory will now be "html_files/subdir1/subdir2/"
    currentDir = filePath.substr(0, lastSlashPos + 1);

    // file will now be "file7.html"
    fileName = filePath.substr(lastSlashPos + 1);
  }

  //adds the current page to the set of visited pages
  visitedPages.insert(filePath);

  //create a new webpage object
  ifstream fileStream(filePath);
  if(fileStream.is_open())
  {
    string fileContent((istreambuf_iterator<char>(fileStream)), istreambuf_iterator<char>());
    WebPage* newPage = new WebPage(filePath, fileContent);

    //get the links from the webpage
    list<string> linksToCheck = newPage->getOutLinks();

    //add the webpage to the list of webpages
    pages.push_back(*newPage);
   
    //iterate through the list of links
    //if the link is not in the set of visited pages, call the web crawler function on that link
    //if the link is in the set of visited pages, do nothing

    for(list<string>::iterator it = linksToCheck.begin(); it != linksToCheck.end(); ++it)
    {
      string tempPath = currentDir;
      string tempDir;
      string tempFile;

      size_t lastSlashPos = (*it).find_last_of('/');
      if(lastSlashPos != std::string::npos)
      {
        tempDir = (*it).substr(0, lastSlashPos + 1);
        tempFile = (*it).substr(lastSlashPos + 1);
      }
      else
      {
        tempFile = (*it);
      }

      //if tempDir has "../" in it, we need to go back one directory for each "../"

      while(tempDir.find("../") != std::string::npos)
      {
        size_t lastSlashPos = tempPath.find_last_of('/');
        if(lastSlashPos != std::string::npos)
        {
          //if the directory is "html_files/subdir1/subdir2/", we want to get "html_files/subdir1/"
          //so we need to remove everything between the last slash and the second to last slash
          tempPath = tempPath.substr(0, lastSlashPos);
          lastSlashPos = tempPath.find_last_of('/');
          if(lastSlashPos != std::string::npos)
          {
            tempPath = tempPath.substr(0, lastSlashPos + 1);
          }
        }
        tempDir = tempDir.substr(3);
      }
      
      tempPath = tempPath + tempDir + tempFile;

      if(visitedPages.find(tempPath) == visitedPages.end())
      {
        webCrawler(tempPath, visitedPages, pages);
      }
    }
    
  }
}

void webCrawlerStart(string filePath, list<WebPage> &pages)
{
  //create a set of strings to keep track of visited pages
  set<string> visitedPages;

  //calls the recursive web crawler function with the set of visited pages
  webCrawler(filePath, visitedPages, pages);

}

//searches through the web pages for the query
void search(list<WebPage> &pages, string query)
{
  int keyNum = 0;
  int keyDenom = 0;

  //iterate through the list of web pages
  for(list<WebPage>::iterator it = pages.begin(); it != pages.end(); ++it)
  {
    it->countWord(query);
    keyNum += it->getWordCount();
    keyDenom += it->getContentLength();
  }

  //calculate the keyword density across all web pages
  double keyDensity = (double)keyNum / (double)keyDenom;

  //calculate the keyword density score for each web page
  for(list<WebPage>::iterator it = pages.begin(); it != pages.end(); ++it)
  {
    double score = (double)it->getWordCount() / ((keyDensity) * (double)it->getContentLength());
    it->setDensityScore(score);

    //adds the density score to the total density score, this is only relevant with multiple keywords
    it->setTotalDensityScore(it->getTotalDensityScore() + score);

    cout << "Page density score: " << it->getTotalDensityScore() << endl;
  }

  cout << "Total density score: " << keyDensity << endl;


}

//calculate the backlink score of each webpage
void makeBacklinkScores(list<WebPage> &pages)
{
  for(list<WebPage>::iterator it = pages.begin(); it != pages.end(); ++it)
  {
    list<string> outgoingLinks = it->getOutLinks();
    double outScore = 1.0/(1.0 + (double)outgoingLinks.size());
    cout << "outLinkScore: " << outScore << endl;

  }
}

//outputs the results to the output file
void outputResults(list<WebPage> webPages, ostream &outputStream)
{
  outputStream << "Matching Documents:" << endl << endl;
}
  

int main(int argc, char * argv[])
{
  list<WebPage> webPages;

  //take the first argument as the file path
  string filePath = argv[1];

  //open a file for output
  ofstream outputFile;
  outputFile.open(argv[2]);

  webCrawlerStart(filePath, webPages);

  std::string query1 = argv[3];
  search(webPages, query1);

  if(argc > 4)
  {
    string query2 = argv[4];
    search(webPages, query2);
  }

  if(argc > 5)
  {
    string query3 = argv[5];
    search(webPages, query3);
  }

  makeBacklinkScores(webPages);

  outputResults(webPages, outputFile);

  return 0;
}
