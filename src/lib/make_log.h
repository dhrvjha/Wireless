#ifndef MAKELOG_H
#define MAKELOG_H

/*
    filelog takes a message and a success code to print
    output to a log file.
*/
void filelog(char *message, int success);

/*
    check takes a message and a success code and exitcon code
    -- if success print log to screen
    -- if failure
        -- print log to screen
        -- if exitcon == 1
            -- exit the program with 1
*/
void check(char *message, int success, int exitcon);

#endif  //MAKELOG_H