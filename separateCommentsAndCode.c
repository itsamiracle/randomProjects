#include <stdio.h>
#include <string.h>

// char *strchr(char *str, int ch) -> Returns a pointer to the first occurrence of character in the C string str.
// char *strrchr(char *str, int ch) -> searches the string in reverse order

/* This function takes a char pointer (char array) as a parameter
 * It will separate the comments , writing all the comments
 * into 'commentFile.txt' and the rest into 'codeFile.c'
 * The original c file wont change
 */
void separateComments ( char * strPointer ) {

    if (strPointer == NULL) {
        printf("Error, Invalid Pointer!\n");
        return;
    }
// Opening both files.  w -> Write   a-> Append
    FILE * codeFile, * commentFile;
    codeFile = fopen("codeFile.c","w");
    commentFile = fopen("commentFile.txt","a");

// Iterating through each char in the array till we find // or */
    for(int i = 0; i < (int)strlen(strPointer); i++){

        if(strPointer[i] == '/'){
            if(strPointer[i+1] == '/'){
                // we found a comment line. Now we will write this line to our file
                // untill we hit the '\n' char in our array. Then we know
                // its the end of the comment line
                do {
                    fprintf(commentFile, "%c",strPointer[i]);
                    i++;
                }while(strPointer[i] != '\n');
                fputc('\n',commentFile);
            }

            else if (strPointer[i+1] == '*'){
                // we found the start of a comment -> /*
                // write each char to our commentFile
                // untill we hit the end -> */
                    do {
                        fprintf(commentFile, "%c",strPointer[i]);
                        i++;
                    } while (!(strPointer[i-2] == '*' && strPointer[i-1] == '/'));
                    fputc('\n',commentFile);
            }
        }
// All other characters which are not comments will be written to the codeFile
        putc(strPointer[i],codeFile);
    }
// closing both our Files
    fclose(codeFile);
    fclose(commentFile);
}


int main(int argc, char * argv []) {

    if(argc == 1){
        printf("Please run the program with the name of your file!\n" );
        return 0;
    }
    char c;
    char fileContents[1000];
    // int * abc = NULL; complier gives Segmentation fault (core dumped) error ?
    int i;

// Opening the file. The name of the file was passed as a parameter
    FILE * inputFile = NULL;
    inputFile = fopen(argv[1],"r");
    if (inputFile == NULL){
        printf("ERROR WHILE OPENING THE FILE\n" );
        return 0;
    }
/* getc(FILE * stream) - fgetc(FILE * stream) : Returns the character currently
 * pointed by the INTERNAL FILE POSITION INDICATOR of the specified stream.
 * The INTERNAL FILE POSITION INDICATOR is then advanced to the next character.
 *
 * Writing the content of our file into a character array "fileContents"
 * with this array we will call the separateComments funtion
 */
    while((c = fgetc(inputFile)) != EOF ){
       fileContents[i] = c;
       i++;
    }
    fclose(inputFile);
    separateComments(fileContents);
    puts("Successfull !");

return 0;
}
