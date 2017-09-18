#include <stdio.h>
#include <string.h>


void splitComments ( char * strPointer ) {

// Opening both files
    FILE * codeFile, * commentFile;
    codeFile = fopen("codeFile.c","w");
    commentFile = fopen("commentFile.txt","a");

//
    for(int i = 0; i < (int)strlen(strPointer); i++){

        if(strPointer[i] == '/'){
            if(strPointer[i+1] == '/'){
                do {
                    fprintf(commentFile, "%c",strPointer[i]);
                    i++;
                }while(strPointer[i] != '\n');
                fputc('\n',commentFile);
            }

            else if (strPointer[i+1] == '*'){
                    do {
                        fprintf(commentFile, "%c",strPointer[i]);
                        i++;
                    } while (!(strPointer[i-2] == '*' && strPointer[i-1] == '/'));
                    fputc('\n',commentFile);
            }
        }
        putc(strPointer[i],codeFile);
    }
    fclose(codeFile);
    fclose(commentFile);
}


int main(int argc, char * argv []) {

    char c;
    char fileContents[1000];
    int i;


    FILE * inputFile;
    inputFile = fopen(argv[1],"r");        // Opening a file, read-only
    if (inputFile == NULL)
        printf("ERROR OPENING FILE\n" );

/* getc(FILE * stream) - fgetc(FILE * stream) : Returns the character currently
 * pointed by the INTERNAL FILE POSITION INDICATOR of the specified stream.
 * The INTERNAL FILE POSITION INDICATOR is then advanced to the next character.
 */
    while((c = fgetc(inputFile)) != EOF ){
        fileContents[i] = c;
        i++;
    }
    fclose(inputFile);
    splitComments(fileContents);
    puts("Successfull !");

return 0;
}
