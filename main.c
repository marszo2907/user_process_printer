#include "CLIOptions.h"
#include "UserPrinter.h"

#include <stdio.h>

int main(int argc, char **argv) {
    CLIFlags cliFlags;
    if (0 == getCLIFlags(argc, &argv, &cliFlags)) {
        printCurrentUsers(&cliFlags);
    }
    return 0;
}
