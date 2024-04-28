#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#   include <windows.h>
#else
#   include <errno.h>
#   include <dirent.h>
#   include <sys/stat.h>
#   include <sys/types.h>
#endif

#define PATH_CAP 512
#define IGNORED_CAP 3
#define CORRUPTED_FILES_CAP 1024

#ifdef _WIN32
#   define ERROR_BUF_CAP 256
#   define DELIM "\\"
#   define CHAR_DELIM '\\'
#   define OPEN_DIR(hFind, findData, dir_path)                                 \
        const TCHAR *path = TEXT((dir_path));                                  \
        WIN32_FIND_DATA (findData);                                            \
        HANDLE (hFind) = FindFirstFile(path, &(findData));                     \
        if ((hFind) == INVALID_HANDLE_VALUE) {                                 \
            TCHAR error_buf[ERROR_BUF_CAP];                                    \
            FormatMessage(                                                     \
                FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,    \
                NULL,                                                          \
                GetLastError(),                                                \
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),                     \
                error_buf,                                                     \
                ERROR_BUF_CAP / sizeof(TCHAR),                                 \
                NULL);                                                         \
            printf("ERROR: Couldn't open \"%s\": %s",                          \
                   (dir_path),                                                 \
                   error_buf);                                                 \
            exit(1);                                                           \
        }
#else
#   define DELIM "/"
#   define CHAR_DELIM '/'
#   define OPEN_DIR(dp_name, ep_name, dir_path)                                \
        DIR *(dp_name);                                                        \
        struct dirent *(ep_name);                                              \
        (dp_name) = opendir(dir_path);                                         \
        if (!(dp_name)) {                                                      \
            fprintf(stderr, "ERROR: Couldn't open \"%s\": %s\n",               \
                    dir_path,                                                  \
                    strerror(errno));                                          \
            exit(1);                                                           \
        }
#endif

#define GET_PATH(path, dir_path, name)                                         \
    snprintf((path), PATH_CAP, "%s%s%s",                                       \
            (dir_path),                                                        \
            (dir_path)[strlen((dir_path)) - 1] == CHAR_DELIM ? "" : DELIM,     \
            (name));                                                           \

extern const char* const IGNORED[IGNORED_CAP];

#ifdef _WIN32
int isfile(const char* const name)
{
    DWORD attributes = GetFileAttributes(name);

    if (attributes == INVALID_FILE_ATTRIBUTES) {
        DWORD error = GetLastError();

        if (error != ERROR_FILE_NOT_FOUND && error != ERROR_PATH_NOT_FOUND) {
            TCHAR error_buf[ERROR_BUF_CAP];
            FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                          NULL,
                          error,
                          MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                          error_buf,
                          ERROR_BUF_CAP / sizeof(TCHAR),
                          NULL);

            fprintf(stderr, "ERROR: retrieving attributes for \"%s\": %s\n",
                    name,
                    error_buf);
        }
        return 0;
    }

    return !(attributes & FILE_ATTRIBUTE_DIRECTORY);
}
#else
int isfile(const char* const name)
{
    struct stat statbuf;
    if (stat(name, &statbuf) != 0) return 0;
    return S_ISREG(statbuf.st_mode);
}
#endif

int isignored(const char* const name)
{
    for (size_t i = 0; i < IGNORED_CAP; ++i)
        if (strcmp(name, IGNORED[i]) == 0)
            return 0;
    return 1;
}

#endif // MAIN_H
