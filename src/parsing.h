#include "types.h"
#include <stdint.h>
#include <stdio.h>

#ifndef PARSING_H
#define PARSING_H

#define MAX_LINE_LENGTH 10000

// public
Tests *read_test_file(const char *file_name);

// private
static Tests *parse_test_file(FILE *fp);
static int count_integers(const char *line);
static int parse_line(const char *line, int **arr);
static void free_arrays(size_t n, Array *arrays);

Tests *read_test_file(const char *file_name) {
    FILE *fp = fopen(file_name, "r");
    if (!fp) {
        perror("fopen");
        return NULL;
    }

    Tests *tests = parse_test_file(fp);

    fclose(fp);
    return tests;
}

static Tests *parse_test_file(FILE *fp) {
    size_t n;
    if (fscanf(fp, "%zu", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid N\n");
        return NULL;
    }

    char c;
    while ((c = fgetc(fp)) != '\n' && c != EOF)
        continue;

    Tests *tests = (Tests *)malloc(sizeof(Tests));
    if (!tests) {
        perror("malloc");
        return NULL;
    }
    tests->n = n;
    tests->arrays = (Array *)malloc(sizeof(Array) * n);
    if (!tests->arrays) {
        perror("malloc");
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        tests->arrays[i].size = 0;
        tests->arrays[i].data = NULL;
    }

    char line[MAX_LINE_LENGTH];
    for (size_t i = 0; i < n; i++) {
        if (!fgets(line, sizeof(line), fp)) {
            fprintf(stderr, "Unexpected end of file at line %zu\n", i + 1);
            free_arrays(n, tests->arrays);
            free(tests);
            return NULL;
        }

        int count = parse_line(line, &tests->arrays[i].data);
        if (count < 0) {
            perror("malloc");
            free_arrays(n, tests->arrays);
            free(tests);
            return NULL;
        }
        tests->arrays[i].size = count;
    }

    return tests;
}

static int count_integers(const char *line) {
    int count = 0;
    const char *p = line;

    while (*p) {
        while (*p && isspace((unsigned char)*p))
            p++;
        if (!*p)
            break;
        count++;
        while (*p && !isspace((unsigned char)*p))
            p++;
    }
    return count;
}

static int parse_line(const char *line, int **arr) {
    size_t count = count_integers(line);
    *arr = NULL;

    if (count == 0)
        return 0;

    *arr = malloc(count * sizeof(int));
    if (!*arr)
        return -1;

    const char *p = line;
    for (size_t i = 0; i < count; i++) {
        while (*p && isspace((unsigned char)*p))
            p++;
        (*arr)[i] = (int)strtol(p, (char **)&p, 10);
    }
    return (int)count;
}

static void free_arrays(size_t n, Array *arrays) {
    for (size_t i = 0; i < n; i++) {
        free(arrays[i].data);
    }
    free(arrays);
}

#endif