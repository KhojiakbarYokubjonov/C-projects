### It implements a simplified version of the grep command that can be found on many UNIX systems
This program expects between 0 and 3 flag arguments, and one additional argument which specifies
what to search for. The program supports these three flag arguments in any position on the command
line:
 *  `-o` Only print the exact part(s) of each line that matches the search, not the entire line. The default
behavior of sgrep will be to print the whole line if a match is found.
 *  `-i` Use a case-insensitive search. The default behavior will be to search case-sensitive.
 *  `-e` Search using a pattern specification. The default behavior will be to search for the exact search
string provided.

The other command-line argument will be some sequence of ascii-characters that represent what to search for.
The `search term` can either function in a literal search (search of the exact string the user provides) or, with the
`-e` flag, the user can give a `pattern` (one search term that can match multiple strings).
The program supports the arguments being specified in any order.

The search will act on whatever is “fed” to the program via standard input, and continues to search until
`EOF` is reached. The search results will be printed to standard output. A few examples of valid ways to run
this program (after being compiled to an executable file named sgrep): <br>
 &emsp; $ cat todo.txt | ./sgrep orange <br>
&emsp; Print out every line containing the string “orange” from todo.txt <br>
&emsp; $ cat words.txt | ./sgrep -i -o ee <br>
&emsp; Print out every occurrence of the string “ee” “Ee” “eE” or “EE” from words.txt <br>
&emsp; $ cat stuff.txt | ./sgrep -e b#z <br>
&emsp; Print out every line containing a subsequence that starts with “b” and ends with “z” from
stuff.txt <br>
&emsp; $ cat words.txt | ./sgrep -e a..z <br>
&emsp; Print out every line containing a subsequence that starts with “a”, ends with “z”, and contains
two characters in-between from words.txt
