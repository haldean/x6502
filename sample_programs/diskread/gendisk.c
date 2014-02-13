#include <errno.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE *f = fopen("testdisk.bin", "w");
    if (f == NULL) {
        printf("could not open file, err: %s", strerror(errno));
        return 1;
    }
    fprintf(f, "hello, world, from disk!\n");
    fputc(0, f);
    fseek(f, 0xFF00, SEEK_SET);
    fprintf(f, "hello from a seeked position.\n");
    fclose(f);
    return 0;
}
