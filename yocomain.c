/* simple driver to compile with compiled #YOCO program
   calls yocomain with up to 3 arguments and prints returned value.
 */

#include <stdio.h>
#include <stdlib.h>

int yocomain(int a, int b, int c);

int main(int argc, char **argv) {
    int a=0, b=0, c=0, n;
    if (argc > 1) a = atoi(argv[1]);
    if (argc > 2) b = atoi(argv[2]);
    if (argc > 3) c = atoi(argv[3]);
    printf("running yocomain(%d, %d, %d)...\n", a, b, c);
    n = yocomain(a, b, c);
    printf("result = %d\n", n);
    return 0;
}
