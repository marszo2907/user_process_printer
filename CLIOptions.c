#include "CLIOptions.h"

#include <stdio.h>
#include <unistd.h>

int getCLIFlags(const int argc, char ***argv, CLIFlags * const cliFlags) {
    int flag;
    int retVal = 0;

    if (argv && cliFlags) {
        cliFlags->hostFlag = 0u;
        cliFlags->groupFlag = 0u;
        while (-1 != (flag = getopt(argc, *argv, "hg"))) {
            switch (flag) {
                case 'h':
                    cliFlags->hostFlag = 1u;
                    break;
                case 'g':
                    cliFlags->groupFlag = 1u;
                    break;
                case '?':
                    fprintf(stderr, "Unknown option '-%c'.\n", optopt);
                    // flows through
                default:
                    retVal = 1;
            }
        }
    } else {
        retVal = 2;
    }

    return retVal;
}
