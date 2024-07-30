The main goal of this project is to create a localized version of a search engine and explore web crawling through recursion.

SCOPE:
The project will only use a local folder (with subdirectories) as the location for all the search queries/web crawling.
All the files used as input are HTML files.
The search functionality will be case-sensitive.
When performing a search, the program will not consider substrings of a word to be a valid match. 

OUTPUT INFO:
The output file will display data in a similar way to google.
Each matched search result will have the page's title, URL, and a brief snippet of text that includes the query term.

SUPPORTED COMMANDS:
localsearch.exe html_files/index.html output.txt query1 query2 query3
Here, "localsearch.exe" is the name of the program. 
"html_files/index.html" is the mock seed URL for the project.
"output.txt" is the desired file to output the search data.

This program supports up to 3 different search queries at a time.

TO DO:
Finish outputting the data to the file properly.
Calculate backlinks score to rank pages appropriately.
Add support for phrase searching.
