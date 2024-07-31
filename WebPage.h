//WebPage.h
//Bruno Spinelli

#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <iostream>
#include <string>
#include <set>
#include <list>
#include <regex>

using namespace std;

class WebPage
{
  private:
    string filePath;
    string fullContent;
    string body;
    string title;
    string URL;
    string description;
    string snippet;
    list<string> outLinks;

    double pageRank;
    int contentLength;
    int wordCount;
    double density;
    double densityScore;
    double totalDensityScore;
    double backLinkScore;

  public:
    WebPage(string filePath, string content);
    ~WebPage();

    string getFilePath() const {return filePath;}
    string getFullContent() const {return fullContent;}
    int getContentLength() const {return contentLength;}
    string getTitle() const {return title;}
    string getURL() const {return URL;}
    string getDescription() const {return description;}
    string getBody() const {return body;}
    string getSnippet() const {return snippet;}
    list<string> getOutLinks() const {return outLinks;}
    double getPageRank() const {return pageRank;}
    double getDensity() const {return density;}
    double getDensityScore() const {return densityScore;}
    int getWordCount() const {return wordCount;}
    double getTotalDensityScore() const {return totalDensityScore;}
    double getBacklinkScore() const {return backLinkScore;}

    void setContent(string content) {fullContent = content;}
    void setOutLinks(list<string> links) {outLinks = links;}
    void setPageRank(double rank) {pageRank = rank;}
    void setDensity(double d) {density = d;}
    void setDensityScore(double ds) {densityScore = ds;}
    void setTotalDensityScore(double tds) {totalDensityScore = tds;}
    void setBacklinkScore(double bls) {backLinkScore = bls;}

    void findTitle();
    void findBody();
    void findDescription();
    void findSnippet();

    int countLength();

    void countWord(string word);

    list<string> extractLinksFromHTML(const string& body);

};

#endif
