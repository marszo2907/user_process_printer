#include "UserPrinter.h"

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>

void (*GetGroups)(const struct utmp *const, char *, const int);

void printCurrentUsers(const CLIFlags *const cliFlags) {
    void *handle = dlopen("libs/libgroups.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return;
    }
    GetGroups = dlsym(handle, "getGroups");

    const int groupsBufferSize = 1024;

    const struct utmp *entry;
    char *const groupsBuffer = malloc(groupsBufferSize * sizeof(char));

    if (cliFlags) {
        while (entry = getutent()) {
            if (USER_PROCESS == entry->ut_type) {
                    printf("%s", entry->ut_user);
                if (cliFlags->hostFlag) {
                    printf(" (%s)", entry->ut_host);
                }
                if (cliFlags->groupFlag) {
                    GetGroups(entry, groupsBuffer, groupsBufferSize);
                    printf(" [%s]", groupsBuffer);
                }
                printf("\n");
            }
        }
    }

    dlclose(handle);
    free(groupsBuffer);
}
