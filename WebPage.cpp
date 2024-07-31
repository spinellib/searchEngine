//WebPage.cpp
//Bruno Spinelli

#include "WebPage.h"
#include <iostream>
#include <fstream>
#include <set>
#include <list>
#include <string>
#include <regex>

using namespace std;

WebPage::WebPage(string fPath, string content)
{
  totalDensityScore = 0;
  backLinkScore = 0;
  filePath = fPath;
  fullContent = content;

  outLinks = extractLinksFromHTML(fullContent);

  findBody();
  findTitle();
  findDescription();
  contentLength = countLength();
}

WebPage::~WebPage()
{

}

// function to parse an HTML file and extract links to local files
list<string> WebPage::extractLinksFromHTML(const string& fileContent) 
{
    list<string> links;
    // regular expression to match href attributes in anchor tags
    regex linkRegex("<a\\s+[^>]*href\\s*=\\s*['\"]([^'\"]+)['\"][^>]*>");
    smatch match;

    // search for links in the HTML content
    string::const_iterator start = fileContent.cbegin();
    while (regex_search(start, fileContent.cend(), match, linkRegex)) 
    {
        if (match.size() > 1) 
        {
            links.push_back(match[1].str());
        }
        start = match.suffix().first;
    }

    return links;
}

//goes through fullContent and finds the body of the HTML file
//stores the body in a string
void WebPage::findBody()
{
  string tempBody;
  string::size_type start = fullContent.find("<body>");
  string::size_type end = fullContent.find("</body>");
  tempBody = fullContent.substr(start, end);
  body = tempBody;
}

//finds the title of the HTML file
//stores the title in a string
void WebPage::findTitle()
{
  string tempTitle;
  string::size_type start = fullContent.find("<title>");
  string::size_type end = fullContent.find("</title>");
  tempTitle = fullContent.substr(start, end);
  title = tempTitle;
}

//finds the description of the HTML file
//stores the description in a string
void WebPage::findDescription()
{
  string tempDescription;
  string::size_type start = fullContent.find("<meta name=\"description\" content=\"");
  string::size_type end = fullContent.find("\" />");
  tempDescription = fullContent.substr(start, end);
  description = tempDescription;
}

//counts the number of words in fullContent
int WebPage::countLength()
{
  string tempContent = fullContent;
  int count = 0;
  string::size_type start = tempContent.find_first_not_of(" \t\n");
  string::size_type end = tempContent.find_first_of(" \t\n", start);
  while(start != string::npos)
  {
    count++;
    start = tempContent.find_first_not_of(" \t\n", end);
    end = tempContent.find_first_of(" \t\n", start);
  }
  return count;
}

//counts the number of times a word appears in the body of the HTML file
//stores the amount of times as an int
void WebPage::countWord(string word)
{
  string tempBody = body;
  string tempWord = " " + word + " ";

  int count = 0;
  for(int i = 0; i < tempBody.length(); i++)
  {
    if(tempBody.substr(i, tempWord.length()) == tempWord)
    {
      count++;
    }
  }

  wordCount = count;

  cout << count << endl;

  //also generates the density of the word
  density = double(wordCount) / double(contentLength);
}

void WebPage::findSnippet()
{

}
