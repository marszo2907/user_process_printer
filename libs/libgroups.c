#include "libgroups.h"

#include <grp.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>

void getGroups(const struct utmp *const entry, char *buffer, const int bufferSize) {
    const char *trailingComma = ", ";

    bool addTrailingComma = false;
    gid_t *groups;
    int remainingCharacters = bufferSize;

    buffer[0] = '\0';
    remainingCharacters -= 1;

    struct passwd *passwd = getpwnam(entry->ut_user);
    if (NULL != passwd) {
        groups = malloc(sizeof(gid_t));
        int ngroups = 1;
        if (-1 == getgrouplist(entry->ut_user, passwd->pw_gid, groups, &ngroups)) {
            groups = realloc(groups, ngroups * sizeof(gid_t));
            getgrouplist(entry->ut_user, passwd->pw_gid, groups, &ngroups);
        }
        for (int i = 0; ngroups > i && remainingCharacters > 0; ++i) {
            if (addTrailingComma) {
                strncat(buffer, trailingComma, remainingCharacters);
                remainingCharacters -= strlen(trailingComma);
            } else {
                addTrailingComma = true;
            }
            char *group_name = getgrgid(groups[i])->gr_name;
            strncat(buffer, group_name, remainingCharacters);
            remainingCharacters -= strlen(group_name);
        }
        free(groups);
    }
}
