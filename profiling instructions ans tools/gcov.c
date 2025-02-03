#include<stdio.h> 
int main()
{
        int cond = 1;
        if ( cond ) {
                printf("Condition is true...!\n");
        } else {
                printf("Condition is false...!\n");
                return(1);
        }
        printf("End of program\n");
        return(0);
}

/*
Compile the program using gcc

$ gcc -fprofile-arcs -ftest-coverage -o Example Example.c


This will create .gcno file in addition to the executable.

$ ls
Example  Example.c  Example.gcno


Run the executable

$ ./Example
Condition is true...!
End of program


This will create .gcda file

$ ls
Example  Example.c  Example.gcda  Example.gcno


Now gcov can be run to get the coverage data.

$ gcov -b -c Example.c
File 'Example.c'
Lines executed:75.00% of 8
Branches executed:100.00% of 2
Taken at least once:50.00% of 2
Calls executed:66.67% of 3
Example.c:creating 'Example.c.gcov'


Above command creates .gcov file with contents as shown below

$ cat Example.c.gcov
        -:    0:Source:Example.c
        -:    0:Graph:Example.gcno
        -:    0:Data:Example.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include 
        -:    2:
        -:    3:int main()
function main called 1 returned 100% blocks executed 71%
        1:    4:{
        1:    5:        int cond = 1;
        -:    6:
        1:    7:        if ( cond ) {
branch  0 taken 1 (fallthrough)
branch  1 taken 0
        1:    8:                printf("Condition is true...!\n");
call    0 returned 1
        -:    9:        } else {
    #####:   10:                printf("Condition is false...!\n");
call    0 never executed
    #####:   11:                return(1);
        -:   12:        }
        -:   13:
        1:   14:        printf("End of program\n");
call    0 returned 1
        -:   15:
        1:   16:        return(0);
        -:   17:}
*/
