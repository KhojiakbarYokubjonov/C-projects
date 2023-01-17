/**
 * @file sgrep.c
 * @author Khojiakbar Yokubjonov
 * @class CSC352, Fall 2022
 * @brief This program implements a simplified version of the grep unix command. 
 *          it can take up to 3 flag arguments, and one additional argument which specifies
            what to search for. it supports these three flag arguments in any position on the command
            line:
                -o Only print the exact part(s) of each line that matches the search, not the entire line. The default
                behavior of sgrep will be to print the whole line if a match is found.

                -i Use a case-insensitive search. The default behavior will be to search case-sensitive.

                -e Search using a pattern specification. The default behavior will be to search for the exact search
                string provided.
            The other command-line argument will be some sequence of ascii-characters that represent what to search for.
            The program gets its input from standard in. It assumes that the max line width is 200 characters.
 *          
 */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int PERIOD_INT_VAL = 46;
/**
 * @brief it validates the search term. it checks to make sure that each hash char inside the search term 
 *      has a non-hash character immediately before it and after it. Also, it ensures that each search sequence starts
 *      and ends with a non-hash char.
 * 
 * @param searchPattern the search sequence passed with the sgrep command
 * @param length int, the length of the search sequence
 * @return int 1 if valid and 0 otherwise.
 */
int isValid(char searchPattern[128], int length){
    //checking the beginning and the end of the search sequence
    if(searchPattern[0]=='#' || searchPattern[length-1]=='#'){
        return 0;
    }

    //checking all the remaning chars between the first and last chars.
    for(int i = 1; i < length-1; i++){
        if(searchPattern[i]=='#'){
            if(searchPattern[i-1]=='.' || searchPattern[i+1]=='.' || searchPattern[i-1]=='#' || searchPattern[i+1]=='#'){return 0;}
        }
    }

    return 1;
}

/**
 * @brief compares the two given chars and tells if they are equal.
 *        it also has a case-insensitive option.
 * 
 * @param wordChar a char from the search sequence
 * @param bufferChar a char from the stand input
 * @param isCaseInsensitive the case-insensitive flag argument
 * @return int - returns 1 if valid and 0 otherwise.
 */
int compareChars(int wordChar, int bufferChar, int isCaseInsensitive){
    if(!isCaseInsensitive){
        return (wordChar==bufferChar) ||(wordChar == PERIOD_INT_VAL);
    }
    int diff = wordChar - bufferChar;
     if(wordChar != bufferChar && wordChar != PERIOD_INT_VAL && diff!=32 && diff!=-32 ){
                return 0;
    }return 1;

}

/**
 * @brief compares the two given strings and tells if they are equal.
 *        it also has a case-insensitive option.
 * 
 * @param wordChar the search sequence
 * @param bufferChar a string from the stand input
 * @param isCaseInsensitive the case-insensitive flag argument
 * @return int - returns 1 if valid and 0 otherwise.
 */
int compareStrings(char subString[128], char word[128], int length, int caseInsensitive){
    for(int i=0; i<length; i++){
        int char1 = subString[i]; int char2 = word[i]; int diff = char1-char2;
        if(!caseInsensitive){
            if(char1 != char2){return 0;}
        }else{

        }if(char1 != char2 && diff!=32 && diff!=-32 ){
            return 0;
        }
        
    }

    return 1;
}

/**
 * @brief prints the output to standard out
 * 
 * @param word string output to be printed
 * @param length int, the length of the search sequence
 * @param origWordLength int, length of the search sequence
 * @param string - the input from the standard in
 * @param printMatches the flag argument that tells to print the matches only
 */
void display(char word[128], int length,int origWordLength, char string[128], int printMatches){
    //doesn't print the outputs that ar shorter than the search sequence
    if(length < origWordLength){return;}
    if(printMatches){
        printf("%s\n", word);
    }else{
        printf("%s\n", string);
    }

}

/**
 * @brief Iterates over the input string and finds the substrings that match the search pattern
 * 
 * @param word string, the search pattern
 * @param length - int, the length of the search sequence
 * @param string string, the input given via the standard in
 * @param stringLen - int, the length of the input
 * @param printMatches the flag argument that tells to print the matches only
 * @param isCaseInsensitive -the flag argument that specifies case sensitivity
 */
void advancedSearch(char word[128], int length, char string[128], int stringLen, int printMatches, int isCaseInsensitive){
    int i = 0, j = 0;
    int index = 0;  char result[128];      
    int found = 0;
    while(i<stringLen && j < length){
        int status = 0; // tells if there's a mismatch
        //comparing the non-hash part of the sequence
        while(compareChars(word[j], string[i], isCaseInsensitive) && i<stringLen && j<length){
            result[index] = string[i]; j++;
            index++;
            i++;
            if(i<stringLen && j<length){
                if(!compareChars(word[j], string[i], isCaseInsensitive)){  
                    status = -1; }
            }
            //handles the mismatch
        }if(status == -1){
            if(word[j]!='#'){ 
                result[0] = '\0'; 
                j=0; index = 0;
                //ignores mismatch if there's a hash char
            }else{ status = 0;}
        }else if(j==length){ found = 1;
        }
        //handles the part of the search sequence that contain hashes
        if(word[j]=='#'){
            j++;
            //in the case of hash sequence, it adds all the in-between chars until it sees the end char of the hash pattern 
            while(!compareChars(word[j],string[i],isCaseInsensitive) && i<stringLen){ 
                result[index] =  string[i];
                i++;
                index++;
            }
            //checks if the result matches the hash pattern
            if(compareChars(word[j], string[i-1],isCaseInsensitive)){
                result[0] = '\0';
                //adds the end char of the hash pattern to the output
            }if(strlen(result)!=0 && j==length-1){
                result[index] = string[i];
                found = 1;
                j++; i++; index++;
            }
        }else{
            i++;
        }
        //marks the end of output and prints it to the std out
        if(found){
            found = 0;
            result[index] = '\0';
            display(result, strlen(result),strlen(word),string, printMatches);
            if(!printMatches){return;}
            result[0] = '\0'; index = 0; j = 0;
        }
    }
}
/**
 * @brief Iterates over the input string and finds  the substrings that match the search term.
 *         It DOESN'T handle the search with the pattern option.
 * 
 * @param word string, the search pattern
 * @param length - int, the length of the search sequence
 * @param string string, the input given via the standard in
 * @param stringLen - int, the length of the input
 * @param printMatches the flag argument that tells to print the matches only
 * @param isCaseInsensitive -the flag argument that specifies case sensitivity
 */
void simpleSearch(char word[128], int length, char string[128], int stringLen, int printMatches, int caseInsensitive, int usePatternSpec){
    
    // iterates over the input and looks for the matching substrings
    for(int i=0; i<stringLen; i+=1){
        int start = i; int end = i+length-1;
        char subString[128]; int index = 0;
        for(int j=start; j<=end && end<stringLen; j++){
            subString[index] = string[j];
            index++;

        }subString[index] = '\0';
        //compares a substring and prints if it is a match.
        if(compareStrings(subString, word, strlen(word), caseInsensitive)){
            display(subString, strlen(subString), length,string,printMatches);
            if(!printMatches){return;}
        }

    }


}
/**
 * @brief identifies and sets the flag arguments, inlcuding the search term/pattern
 * 
 * @param argc - argument count
 * @param argv - list of command line arguments
 * @param printMatches the flag argument that tells to print the matches only
 * @param isCaseInsensitive -the flag argument that specifies case sensitivity
 * @param usePatternSpec -the flag argument that tells if the pattern will be considered during search.
 * @param wordToSearch - string, the search term given via std in
 * @return the length of the search term
 */
int manageCommandLineInputs(int argc, char* argv[], int*printMatches, int*isCaseInsensitive, int*usePatternSpec, char wordToSearch[128]){
    if(argc==1){
        printf("Requires more command-line arguments.\n");
        exit(2);
    } else if(argc > 5){
        printf("You have entered more than 4 arguments for sgrep\n");
        exit(3);
    }
    // identifies the flags
    for(int i=1; i<argc; i++){
        if(strcmp(argv[i],"-o")==0){
            *printMatches = 1;
        }else if(strcmp(argv[i],"-i")==0){
            *isCaseInsensitive = 1;
        }else if(strcmp(argv[i],"-e")==0){
            *usePatternSpec = 1;
        }else{
            strcpy(wordToSearch, argv[i]); // saves the search term
        }
    }
    return strlen(wordToSearch);

}
int main(int argc, char *argv[]){
    int printMatches = 0;
    int isCaseInsensitive = 0;
    int usePatternSpec = 0;
    char wordToSearch [128];
    int wordLength = manageCommandLineInputs(argc,argv,&printMatches,&isCaseInsensitive,&usePatternSpec, wordToSearch);
   
    if(!isValid(wordToSearch, wordLength)){
        printf("Invalid search term.\n");
        exit(2);
    }
   
    char buffer[200];
    while (fgets(buffer, 199, stdin) != NULL){
        //strips the new line char
        if(buffer[strlen(buffer) - 1] == '\n'){
            buffer[strlen(buffer) - 1] = '\0';
        }
        //decides whether to do a regular search or a pattern search
        if(usePatternSpec){
                advancedSearch(wordToSearch, wordLength, buffer, strlen(buffer), printMatches, isCaseInsensitive);

            }else{
                simpleSearch(wordToSearch, wordLength,buffer, strlen(buffer), printMatches, isCaseInsensitive, usePatternSpec);

            }        
    }

    return 0;
}
