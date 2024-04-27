#ifndef MAIN_H
#define MAIN_H

#define PATH_CAP 512
#define IGNORED_CAP 3
#define CORRUPTED_FILES_CAP 1024

#define OPEN_DIR(dp_name, ep_name, dir_path)                                   \
    DIR *(dp_name);                                                            \
    struct dirent *(ep_name);                                                  \
    (dp_name) = opendir(dir_path);                                             \
    if (!(dp_name)) {                                                          \
        perror("Couldn't open the directory");                                 \
        exit(1);                                                               \
    }

extern const char* const IGNORED[IGNORED_CAP];

int isignored(const char* name)
{
    for (size_t i = 0; i < IGNORED_CAP; ++i) {
        if (strcmp(name, IGNORED[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

int isfile(const char *name)
{
    struct stat statbuf;
    if (stat(name, &statbuf) != 0) return 0;
    return S_ISREG(statbuf.st_mode);
}

#endif // MAIN_H
