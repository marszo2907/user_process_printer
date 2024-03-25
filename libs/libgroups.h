#ifndef LIB_GROUPS_H
#define LIB_GROUPS_H

#include <utmp.h>

void getGroups(const struct utmp *const entry, char *buffer, const int bufferSize);

#endif // LIB_GROUPS_H
