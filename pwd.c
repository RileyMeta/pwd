#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

const char VERSION[] = "0.1";

void info_menu(void);
void help_menu(void);
void invalid(char *arg);

int main(int argc, char* argv[]) {
    char *pwd;
    char buf[PATH_MAX + 1];
    char resolved_path[PATH_MAX];

    pwd = getcwd(buf, sizeof(buf));

    if (argc >= 2) {
        for (int i = 1; i < argc; ++i) {
            if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-V") == 0) {
                info_menu();
                return 0;
            } else if (strcmp(argv[i], "--help") == 0) {
                help_menu();
                return 0;
            } else if (strcmp(argv[i], "-P") == 0) {
                if (realpath(pwd, resolved_path) != NULL)
                    printf("%s\n", resolved_path);
                else
                    perror("realpath() error");
                return 0;
            } else if (strcmp(argv[i], "-L") == 0) {
                printf("%s\n", pwd);
                return 0;
            } else {
                invalid(argv[i]);
                return 1;
            }
        }
    }

    if (pwd == NULL) {
        perror("getcwd() error");
        return 1;
    }

    printf("%s\n", pwd);
    return 0;
}

void info_menu() {
    printf("pwd (Riley's coreutils) %s\n", VERSION);
    printf("Copyright (C) 2025 Riley Ava\n");
    printf("License MIT: <https://opensource.org/license/mit>\n");
    printf("This is free software: you are free to change and redistribute it.\n");
    printf("There is NO WARRANTY, to the extent permitted by law.\n");
    printf("\nWritten by Riley Ava.\n");
}

void help_menu() {
    printf("pwd: pwd [-LP]\n");
    printf("\tPrint the name of the current working directory.\n");
    printf("\n\tOptions:\n");
    printf("\n\t  -L\tprint the value of $PWD if it names the current working\n");
    printf("\t    \tdirectory\n");
    printf("\t  -P\tprint the physical directory, without any symbolic links\n");
    printf("\n\tBy default, `pwd` behaves as if `-L` were specified.\n");
    printf("\n\tExit Status:\n");
    printf("\tReturns 0 unless an invalid option is given or the current directory\n");
    printf("\tcannot be read.\n");
}

void invalid(char *arg) {
    fprintf(stderr, "Invalid option: %s\n", arg);
    fprintf(stderr, "Try '--help' for more information.\n");
}
