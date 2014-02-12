#include <errno.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE *f = fopen("testdisk.bin", "w");
    if (f == NULL) {
        printf("could not open file, err: %s", strerror(errno));
        return 1;
    }
    fprintf(f, "hello, world!");
    fclose(f);
    return 0;
}
