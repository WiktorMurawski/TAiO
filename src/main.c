#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "parsing.h"
#include "types.h"

void usage(const char *program_name);
void print_array(const Array *arr);
void solve(Array *arr);

int main(int argc, char **argv) {
    if (argc != 2) {
        usage(argv[0]);
        return 1;
    }

    Tests *tests = read_test_file(argv[1]);
    if (!tests)
        return 2;

    for (size_t i = 0; i < tests->n; i++) {
        printf("Test #%zu\n", i + 1);
        solve(&tests->arrays[i]);
    }

    free(tests);
    return 0;
}

void solve(Array *arr) {
    printf("N = %zu\n", arr->size);
    printf("S = { ");
    print_array(arr);
    printf("}\n");
}

void print_array(const Array *arr) {
    if (!arr)
        return;

    size_t n = arr->size;
    for (size_t i = 0; i < n - 1; i++) {
        printf("%d, ", arr->data[i]);
    }
    printf("%d ", arr->data[n - 1]);
}

void usage(const char *program_name) {
    printf("usage: %s test_file", program_name);
}

void free_tests(Tests *tests) {
    for (size_t i = 0; i < tests->n; i++) {
        free(tests->arrays[i].data);
    }
    free(tests);
}
