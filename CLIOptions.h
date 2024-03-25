#ifndef CLI_OPTIONS_H
#define CLI_OPTIONS_H

typedef struct CLIFlags {
    unsigned int hostFlag: 1;
    unsigned int groupFlag: 1;
} CLIFlags;

int getCLIFlags(const int argc, char ***argv, CLIFlags *const cliFlags);

#endif // CLI_OPTIONS_H
