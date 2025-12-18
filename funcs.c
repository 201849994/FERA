#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
    FERA – Ferrari Assistant

    Menu 1: Show Ferrari models + vibe
    Menu 2: Buyer quiz (3 questions) with strict yes/no validation
    Menu 3: Recommend top car using scoring
    Menu 4: Finance calculator (24 months) - commas allowed
    Exit: Save session
*/

/* Ferrari model structure */
typedef struct {
    const char *name;
    int power_cv;
    int seats;
    const char *vibe;
} Ferrari;

/* 5 Ferrari models */
static Ferrari cars[5] = {
    {"Roma Spider",   620, 4, "Stylish and confident. You like looking good without shouting."},
    {"296 GTB",       830, 2, "Performance-focused but still flashy. Quietly scary fast."},
    {"SF90 Stradale", 1000,2, "Life of the party energy. Loud, wild, and unapologetic."},
    {"Purosangue",    725, 4, "Practical flex. Ferrari energy but you need space."},
    {"12Cilindri",    830, 2, "Pure Ferrari theatre. Drama, noise, tradition."}
};

/* User answers */
static int quiz_done = 0;
static int need_4_seats = 0;   /* 1 yes, 0 no */
static int want_fast = 1;      /* 1 yes, 0 no */
static int want_flashy = 1;    /* 1 yes, 0 no */

/* Save last recommendation */
static int last_choice = -1;

/* prototypes */
static int score_car(Ferrari c);
static void strip_newline(char *s);
static void remove_commas(char *s);
static void to_lower_str(char *s);
static int is_yes_no_strict(const char *s, int *out_value);

/* remove trailing newline */
static void strip_newline(char *s)
{
    size_t n;
    if (!s) return;
    n = strlen(s);
    if (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) s[n - 1] = '\0';
    n = strlen(s);
    if (n > 0 && (s[n - 1] == '\r')) s[n - 1] = '\0';
}

/* remove commas so "234,000" becomes "234000" */
static void remove_commas(char *s)
{
    int i, j;
    if (!s) return;
    for (i = 0, j = 0; s[i] != '\0'; i++) {
        if (s[i] != ',') {
            s[j] = s[i];
            j++;
        }
    }
    s[j] = '\0';
}

/* lowercase a string in-place */
static void to_lower_str(char *s)
{
    int i;
    if (!s) return;
    for (i = 0; s[i] != '\0'; i++) {
        s[i] = (char)tolower((unsigned char)s[i]);
    }
}

/*
    Strict yes/no validation:
    Accepts ONLY: "y", "n", "yes", "no" 
    Rejects things like "y7s", "nop8", "yes!!"
*/
static int is_yes_no_strict(const char *s, int *out_value)
{
    if (!s || !*s) return 0;

    if (strcmp(s, "y") == 0 || strcmp(s, "yes") == 0) {
        *out_value = 1;
        return 1;
    }
    if (strcmp(s, "n") == 0 || strcmp(s, "no") == 0) {
        *out_value = 0;
        return 1;
    }
    return 0;
}

/* ================= MENU ITEM 1 ================= */
void menu_item_1(void)
{
    int i;

    printf("\n=== Ferrari models ===\n");

    for (i = 0; i < 5; i++) {
        printf("\n%d) %s\n", i + 1, cars[i].name);
        printf("   Power: %d cv | Seats: %d\n", cars[i].power_cv, cars[i].seats);
        printf("   Vibe: %s\n", cars[i].vibe);
    }
}

/* ================= MENU ITEM 2 ================= */
void menu_item_2(void)
{
    char buf[64];
    int val;

    printf("\n=== Buyer quiz (3 quick questions) ===\n");
    printf("Answer ONLY with: y / n / yes / no\n");

    /* Q1 */
    for (;;) {
        printf("\nDo you NEED 4 seats? (y/n): ");
        if (!fgets(buf, sizeof(buf), stdin)) return;
        strip_newline(buf);
        to_lower_str(buf);

        if (is_yes_no_strict(buf, &val)) {
            need_4_seats = val;
            break;
        }
        printf("Invalid input, please try again.\n");
    }

    /* Q2 */
    for (;;) {
        printf("\nDo you mostly want the FASTEST Ferrari? (y/n): ");
        if (!fgets(buf, sizeof(buf), stdin)) return;
        strip_newline(buf);
        to_lower_str(buf);

        if (is_yes_no_strict(buf, &val)) {
            want_fast = val;
            break;
        }
        printf("Invalid input, please try again.\n");
    }

    /* Q3 */
    for (;;) {
        printf("\nDo you like flashy / attention-grabbing cars? (y/n): ");
        if (!fgets(buf, sizeof(buf), stdin)) return;
        strip_newline(buf);
        to_lower_str(buf);

        if (is_yes_no_strict(buf, &val)) {
            want_flashy = val;
            break;
        }
        printf("Invalid input, please try again.\n");
    }

    quiz_done = 1;
    printf("\nQuiz saved.\n");
}

/* ================= SCORING FUNCTION ================= */
static int score_car(Ferrari c)
{
    int score;
    score = 0;

    /* hard rule: if they need 4 seats, reject 2-seat cars */
    if (need_4_seats && c.seats < 4) {
        return -1;
    }

    /* speed preference */
    if (want_fast) {
        if (c.power_cv >= 900) score += 5;
        else if (c.power_cv >= 800) score += 4;
        else score += 2;
    } else {
        if (c.seats == 4) score += 3;
        else score += 1;
    }

    /* flashy preference bonus */
    if (want_flashy) {
        if (c.power_cv >= 830) score += 2;
        if (c.power_cv >= 1000) score += 1;
    }

    return score;
}

/* ================= MENU ITEM 3 ================= */
void menu_item_3(void)
{
    int i;
    int best_i;
    int best_s;
    int s;

    if (!quiz_done) {
        printf("\nPlease complete the buyer quiz first (Menu Item 2).\n");
        return;
    }

    best_i = -1;
    best_s = -999;

    for (i = 0; i < 5; i++) {
        s = score_car(cars[i]);
        if (s > best_s) {
            best_s = s;
            best_i = i;
        }
    }

    if (best_i < 0) {
        printf("\nNo Ferrari matches your seat requirement.\n");
        last_choice = -1;
        return;
    }

    last_choice = best_i;

    printf("\n=== Your Top Recommendation ===\n");
    printf("%s\n", cars[best_i].name);
    printf("Power: %d cv | Seats: %d\n", cars[best_i].power_cv, cars[best_i].seats);
    printf("Vibe: %s\n", cars[best_i].vibe);
}

/* ================= MENU ITEM 4 ================= */
void menu_item_4(void)
{
    char buf[64];
    double price, deposit, apr;
    double loan, total, monthly;

    printf("\n=== Finance calculator (24 months) ===\n");
    printf("Numbers only. Commas allowed. Decimals allowed.\n");

    /* Price */
    for (;;) {
        printf("\nEnter car price (e.g. 234,000): ");
        if (!fgets(buf, sizeof(buf), stdin)) return;
        strip_newline(buf);
        remove_commas(buf);
        price = atof(buf);

        if (price > 0) break;
        printf("Please try again.\n");
    }

    /* Deposit */
    for (;;) {
        printf("Enter deposit (e.g. 5,000): ");
        if (!fgets(buf, sizeof(buf), stdin)) return;
        strip_newline(buf);
        remove_commas(buf);
        deposit = atof(buf);

        if (deposit >= 0 && deposit <= price) break;
        printf("Please try again.\n");
    }

    /* APR */
    for (;;) {
        printf("Enter APR percent (e.g. 7.5): ");
        if (!fgets(buf, sizeof(buf), stdin)) return;
        strip_newline(buf);
        remove_commas(buf);
        apr = atof(buf);

        /* apr  cap  */
        if (apr >= 0 && apr <= 100) break;
        printf("Please try again (APR should normally be between 0 and 100).\n");
    }

    loan = price - deposit;

    /* simple interest over 2 years (24 months) */
    total = loan * (1.0 + (apr / 100.0) * 2.0);
    monthly = total / 24.0;

    printf("\nLoan amount: %.2f\n", loan);
    printf("Total repay: %.2f\n", total);
    printf("Monthly cost: %.2f\n", monthly);
}

/* ================= EXIT ================= */
void save_and_exit(void)
{
    FILE *fp;

    fp = fopen("ferrari_session.txt", "w");
    if (fp == NULL) {
        printf("\nCould not save file. Exiting.\n");
        exit(0);
    }

    fprintf(fp, "FERA - Ferrari Assistant session\n\n");
    fprintf(fp, "Need 4 seats: %s\n", need_4_seats ? "Yes" : "No");
    fprintf(fp, "Want fastest: %s\n", want_fast ? "Yes" : "No");
    fprintf(fp, "Want flashy: %s\n", want_flashy ? "Yes" : "No");

    if (last_choice >= 0) {
        fprintf(fp, "\nRecommended model: %s\n", cars[last_choice].name);
    } else {
        fprintf(fp, "\nRecommended model: none\n");
    }

    fclose(fp);

    printf("\nSession saved to ferrari_session.txt\n");
    printf("Bye!\n");
    exit(0);
}
