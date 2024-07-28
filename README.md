The main goal of this project is to create a localized version of a search engine and explore web crawling through recursion.

SCOPE:
The project will only use a local folder (with subdirectories) as the location for all the search queries/web crawling.
All the files used as input are HTML files.
The search functionality will be case-sensitive.
When performing a search, the program will not consider substrings of a word to be a valid match. 

SUPPORTED COMMANDS:
localsearch.exe html_files/index.html input.txt
Here, "localsearch.exe" is the name of the program. 
"html_files/index.html" is the mock seed URL for the project.
"input.txt" is the text file containing the search queries, where each given line is a different query.
Running this command should return different "output.txt" files, one for each search query in the "input.txt" file.
