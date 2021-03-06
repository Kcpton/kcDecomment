/*  Name: Kevin Chen 
    File: decomment.c */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* name of all my states */
enum Statetype {START, FORWARD, COMMENT, STAR, SINGLE, 
                DOUBLE, SINGLE_BACK, DOUBLE_BACK};

/*  handleStart Function takes in a char ch, returns a state
    based on input*/
enum Statetype handleStart(char ch) {
    if (ch == '/') {
        return FORWARD;
    }
    else if (ch == '\'') {
        putchar(ch);
        return SINGLE;
    }
    else if (ch == '"') {
        putchar(ch);
        return DOUBLE;
    }
    else {
        putchar(ch);
        return START;
    }
}

/* handleForward Function takes in a char ch, returns a state 
    based on input*/
enum Statetype handleForward(char ch) {
    if (ch == '/') {
        putchar(ch);
        return FORWARD;
    }
    else if (ch == '*'){
        putchar(' ');
        return COMMENT;
    }
    else if (ch == '"') {
        putchar('/');
        putchar(ch);
        return DOUBLE;
    }
    else if (ch == '\'') {
        putchar('/');
        putchar(ch);
        return SINGLE;
    }
    else {
        putchar('/');
        putchar(ch);
        return START;
    }
}

/* handleComment takes in a char ch, returns a state 
    based on input*/
enum Statetype handleComment(char ch) {
    if (ch == '*') {
        return STAR;
    }
    else if (ch == '\n') {
        putchar(ch);
        return COMMENT;
    }
    else {
        return COMMENT;
    }
}

/* handleStar takes in a char ch, returns a state 
    based on input*/
enum Statetype handleStar(char ch) {
    if (ch == '*') {
        return STAR;
    }
    if (ch == '/') {
        return START;
    }
    else if (ch == '\n') {
        putchar(ch);
        return COMMENT;
    }
    else {
        return COMMENT;
    }
}

/* handleSingle takes in a char ch, returns a state 
    based on input*/
enum Statetype handleSingle(char ch) {
    putchar(ch);
    if (ch == '\'') {
        return START;
    }
    else if (ch == '\\') {
        return SINGLE_BACK;
    }
    else {
        return SINGLE;
    }
}

/* handleSingleBack takes in a char ch, returns a state 
    called SINGLE */
enum Statetype handleSingleBack(char ch) {
    putchar(ch);
    return SINGLE;
}

/* handleDouble takes in a char ch, returns a state 
    based on input */
enum Statetype handleDouble(char ch) {
    putchar(ch);
    if (ch == '"') {
        return START;
    }
    else if (ch == '\\') {
        return DOUBLE_BACK;
    }
    else {
        return DOUBLE;
    }
}

/* handleDoubleBack takes in a char ch, returns a state
    called DOUBLE */
enum Statetype handleDoubleBack(char ch) {
    putchar(ch);
    return DOUBLE;
}

/* 
    main takes a standard input and deletes the comments off and 
    return to standard output. 
    It places a space in front of the comment. The line spacing 
    is preserved. If the comment does not close, an error statement 
    is thrown into standard with the line number of the starting
    comment. Returns EXIT_FAILURE if comment doesn't close. 
    Returns 0 otherwise.
*/
int main() {
    int ch;
    int lineNum = 1;
    int enteredLine = 0;
    enum Statetype state = START;
    ch = getchar();
    while (ch != EOF)
    {
        /* two conditionals to keep track of line number and update
            enteredLine when not in comment. */
        if (ch == '\n') {
            lineNum += 1;
        }
        if (state != COMMENT && state != STAR) {
            enteredLine = lineNum;
        }
        
        switch (state) {
            case START:
                state = handleStart(ch);
                break;
            case FORWARD:
                state = handleForward(ch);
                break;
            case COMMENT:
                state = handleComment(ch);
                break;
            case STAR:
                state = handleStar(ch);
                break;
            case SINGLE:
                state = handleSingle(ch);
                break;
            case DOUBLE:
                state = handleDouble(ch);
                break;
            case SINGLE_BACK:
                state = handleSingleBack(ch);
                break;
            case DOUBLE_BACK:
                state = handleDoubleBack(ch);
                break;
        }
        ch = getchar();
    }
    if (state == COMMENT || state == STAR) {
        fprintf(stderr, "Error: line %d: unterminated comment\n", 
        enteredLine);
        return(EXIT_FAILURE);
    }
    else if (state == FORWARD) {
        putchar('/');
    }
    return 0;
}
