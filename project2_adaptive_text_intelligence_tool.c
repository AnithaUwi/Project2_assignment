#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_NAME 40

struct wordStat {
    char name[MAX_WORD_NAME];
    int count;
};

typedef void (*TextAnalysisFn)(char *, struct wordStat *, int, int);

void to_lowercase(char *text) {
    while (*text != '\0') {
        *text = (char)tolower((unsigned char)*text);
        text++;
    }
}

int is_word_char(char character) {
    return isalnum((unsigned char)character) || character == '\'';
}

int parse_words(char *text, struct wordStat **stats, int *unique_count) {
    int cap = 16;
    int total_words = 0;
    char *p = text;

    *stats = (struct wordStat *)malloc(sizeof(struct wordStat) * cap);
    if (*stats == NULL) {
        return -1;
    }
    *unique_count = 0;

    while (*p != '\0') {
        char word[MAX_WORD_NAME];
        int length = 0;
        int found = -1;
        int i;

        while (*p != '\0' && !is_word_char(*p)) {
            p++;
        }

        if (*p == '\0') {
            break;
        }

        while (*p != '\0' && is_word_char(*p)) {
            if (length < MAX_WORD_NAME - 1) {
                word[length++] = *p;
            }
            p++;
        }
        word[length] = '\0';

        if (length == 0) {
            continue;
        }

        total_words++;

        for (i = 0; i < *unique_count; i++) {
            if (strcmp((*stats)[i].name, word) == 0) {
                found = i;
                break;
            }
        }

        if (found >= 0) {
            (*stats)[found].count++;
        } else {
            if (*unique_count == cap) {
                struct wordStat *tmp;
                cap *= 2;
                tmp = (struct wordStat *)realloc(*stats, sizeof(struct wordStat) * cap);
                if (tmp == NULL) {
                    free(*stats);
                    *stats = NULL;
                    return -1;
                }
                *stats = tmp;
            }

            strcpy((*stats)[*unique_count].name, word);
            (*stats)[*unique_count].count = 1;
            (*unique_count)++;
        }
    }

    return total_words;
}

void count_words(char *text, struct wordStat *stats, int unique_count, int total_words) {
    (void)text;
    (void)stats;
    printf("Total words: %d\n", total_words);
    printf("Unique words: %d\n", unique_count);
}

void longest_word(char *text, struct wordStat *stats, int unique_count, int total_words) {
    int i;
    int max_len = 0, len;
    char longest[MAX_WORD_NAME] = "";

    (void)text;
    (void)total_words;

    for (i = 0; i < unique_count; i++) {
        len = (int)strlen(stats[i].name);
        if (len > max_len) {
            max_len = len;
            strcpy(longest, stats[i].name);
        }
    }

    if (max_len == 0) {
        printf("Longest word: N/A\n");
    } else {
        printf("Longest word: %s (%d chars)\n", longest, max_len);
    }
}

void most_frequent(char *text, struct wordStat *stats, int unique_count, int total_words) {
    int i;
    int best = -1;

    (void)text;
    (void)total_words;

    if (unique_count == 0) {
        printf("Most frequent word: N/A\n");
        return;
    }

    best = 0;
    for (i = 1; i < unique_count; i++) {
        if (stats[i].count > stats[best].count) {
            best = i;
        }
    }

    printf("Most frequent word: %s (%d times)\n", stats[best].name, stats[best].count);
}

void vowel_density(char *text, struct wordStat *stats, int unique_count, int total_words) {
    int vowel_count = 0;
    int letter_count = 0;
    float density;

    (void)stats;
    (void)unique_count;
    (void)total_words;

    while (*text != '\0') {
        char c = (char)tolower((unsigned char)*text);
        if (isalpha((unsigned char)c)) {
            letter_count++;
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                vowel_count++;
            }
        }
        text++;
    }

    if (letter_count == 0) {
        printf("Custom Analysis - Vowel Density: 0.00%%\n");
        return;
    }

    density = ((float)vowel_count / (float)letter_count) * 100.0f;
    printf("Custom Analysis - Vowel Density: %.2f%%\n", density);
}

void display_word_stats(struct wordStat *stats, int unique_count) {
    int i;
    struct wordStat *p = stats;
    printf("\nWord Frequency Table\n");
    
    for (i = 0; i < unique_count; i++, p++) {
        printf("%-20s : %d\n", p->name, p->count);
    }
}

int main(void) {
    char *text;
    int text_capacity = 2048;
    struct wordStat *stats = NULL;
    int unique_count = 0;
    int total_words;
    int choice;

    TextAnalysisFn analysis_functions[4] = {
        count_words,
        longest_word,
        most_frequent,
        vowel_density
    };

    text = (char *)malloc(sizeof(char) * text_capacity);
    if (text == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Custom Analysis Function: Vowel Density\n");
    printf("Enter a paragraph from any book/article (max 2047 chars):\n");
    if (fgets(text, text_capacity, stdin) == NULL) {
        printf("No input received.\n");
        free(text);
        return 1;
    }

    to_lowercase(text);
    total_words = parse_words(text, &stats, &unique_count);

    if (total_words < 0 || stats == NULL) {
        printf("Failed to analyze text due to memory error.\n");
        free(text);
        return 1;
    }

    printf("\nText stored at memory address: %p\n", (void *)text);
    printf("Word array stored at memory address: %p\n", (void *)stats);

    display_word_stats(stats, unique_count);

    while (1) {
        printf("\n Adaptive Text Intelligence Tool\n");
        printf("1. Count words\n");
        printf("2. Find longest word\n");
        printf("3. Find most frequent word\n");
        printf("4. Run custom analysis (vowel density)\n");
        printf("5. Run all analyses\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4) {
            analysis_functions[choice - 1](text, stats, unique_count, total_words);
        } else if (choice == 5) {
            int i;
            for (i = 0; i < 4; i++) {
                analysis_functions[i](text, stats, unique_count, total_words);
            }
        } else if (choice == 6) {
            break;
        } else {
            printf("Invalid option.\n");
        }
    }

    free(stats);
    free(text);
    return 0;
}