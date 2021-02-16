#include <stdio.h>
#include <ctype.h>
enum Statetype {START, FORWARD, COMMENT, STAR, SINGLE, 
                DOUBLE, SINGLE_BACK, DOUBLE_BACK};

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

enum Statetype handleForward(char ch) {
    if (ch == '/') {
        putchar(ch);
        return FORWARD;
    }
    else if (ch == '*'){
        putchar(' ');
        return COMMENT;
    }
    else {
        putchar('/');
        putchar(ch);
        return START;
    }
}

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

enum Statetype handleStar(char ch) {
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

enum Statetype handleSingle(char ch) {
    if (ch == '\'') {
        putchar(ch);
        return START;
    }
    else if (ch == '\\') {
        putchar(ch);
        return SINGLE_BACK;
    }
    else {
        putchar(ch);
        return SINGLE;
    }
}

enum Statetype handleSingleBack(char ch) {
    putchar(ch);
    return SINGLE;
}

enum Statetype handleDouble(char ch) {
    if (ch == '"') {
        putchar(ch);
        return START;
    }
    else if (ch == '\\') {
        putchar(ch);
        return DOUBLE_BACK;
    }
    else {
        putchar(ch);
        return DOUBLE;
    }
}

enum Statetype handleDoubleBack(char ch) {
    putchar(ch);
    return DOUBLE;
}

int main() {
    int ch;
    int lineNum = 1;
    ch = getchar();
    enum Statetype state = START;
    while (ch != EOF)
    {
        if (ch == '\n') {
            lineNum += 1;
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
        fprintf(stderr, "Error: line %d: unterminated comment", lineNum);
    }
    else if (state == FORWARD) {
        putchar('/');
    }
    return 0;
}
