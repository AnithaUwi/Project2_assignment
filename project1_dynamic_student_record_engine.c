#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NAME_LEN 50
#define STUDENT_ID "1164570746"

typedef struct {
    int id;
    char name[NAME_LEN];
    float grade;
} Student;

typedef struct {
    Student *students;
    int count;
    int capacity;
} StudentDB;

typedef void (*AnalysisFn)(Student *, int);
typedef void (*Operation)(StudentDB *);

void display_students(Student *students, int count) {
    int i, d, dots;
    Student *p = students;

    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    printf("\n%-5s %-20s %s\n", "ID", "Name", "Grade");
    
    for (i = 0; i < count; i++, p++) {
        dots = 24 - (int)strlen(p->name);
        printf("%d. %s", p->id, p->name);
        for (d = 0; d < dots; d++)
            printf(".");
        printf(" %.2f\n", p->grade);
    }
}

int grow_array(StudentDB *db, int needed) {
    Student *tmp;
    int newcap;

    if (db->count + needed <= db->capacity)
        return 1;

    newcap = db->capacity * 2;
    while (newcap < db->count + needed)
        newcap *= 2;

    tmp = (Student *)realloc(db->students, sizeof(Student) * newcap);
    if (tmp == NULL)
        return 0;

    db->students = tmp;
    db->capacity = newcap;
    return 1;
}

void add_students(StudentDB *db) {
    int n, i;
    Student *s;

    printf("How many students to add? ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid.\n");
        return;
    }

    if (!grow_array(db, n)) {
        printf("Not enough memory.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        s = db->students + db->count;
        printf("\nStudent %d\n", db->count + 1);
        printf("Enter ID: ");
        scanf("%d", &s->id);
        printf("Enter Name: ");
        scanf(" %49[^\n]", s->name);
        printf("Enter Grade: ");
        scanf("%f", &s->grade);
        db->count++;
    }
}

int cmp_by_id(const void *a, const void *b) {
    const Student *x = (const Student *)a;
    const Student *y = (const Student *)b;
    return x->id - y->id;
}

int cmp_by_name(const void *a, const void *b) {
    const Student *x = (const Student *)a;
    const Student *y = (const Student *)b;
    return strcmp(x->name, y->name);
}

int cmp_by_grade(const void *a, const void *b) {
    const Student *x = (const Student *)a;
    const Student *y = (const Student *)b;
    if (x->grade < y->grade) return 1;
    if (x->grade > y->grade) return -1;
    return 0;
}

void sort_students(StudentDB *db) {
    int opt;

    if (db->count == 0) {
        printf("Nothing to sort.\n");
        return;
    }

    printf("Sort by: 1) ID  2) Name  3) Grade (high to low): ");
    scanf("%d", &opt);

    if (opt == 1)
        qsort(db->students, db->count, sizeof(Student), cmp_by_id);
    else if (opt == 2)
        qsort(db->students, db->count, sizeof(Student), cmp_by_name);
    else if (opt == 3)
        qsort(db->students, db->count, sizeof(Student), cmp_by_grade);
    else {
        printf("Wrong option.\n");
        return;
    }

    printf("Done.\n");
}

void calculate_average(Student *students, int count) {
    float sum = 0;
    float avg;
    Student *p = students;
    int i;

    if (count == 0) { printf("No data.\n"); return; }

    for (i = 0; i < count; i++, p++)
        sum += p->grade;

    avg = sum / count;
    printf("Class average: %.2f\n", avg);
}

void find_top_student(Student *students, int count) {
    Student *best;
    Student *p;
    int i;

    if (count == 0) { printf("No data.\n"); return; }

    best = students;
    p = students + 1;
    for (i = 1; i < count; i++, p++) {
        if (p->grade > best->grade)
            best = p;
    }

    printf("Top student: %s (ID %d) - %.2f\n", best->name, best->id, best->grade);
}

/* my custom analysis: checks how stable the grades are across students */
/* lower std deviation = more stable = higher score */
void grade_stability_score(Student *students, int count) {
    float sum = 0, mean, sq_sum = 0, diff, stdev, score;
    Student *p = students;
    int i;

    if (count == 0) { printf("No data.\n"); return; }

    for (i = 0; i < count; i++, p++)
        sum += p->grade;
    mean = sum / count;

    p = students;
    for (i = 0; i < count; i++, p++) {
        diff = p->grade - mean;
        sq_sum += diff * diff;
    }

    stdev = sqrtf(sq_sum / count);
    score = 100.0f - stdev;
    if (score < 0) score = 0;

    printf("Grade Stability Score: %.2f / 100\n", score);
    printf("(lower std deviation means grades are more consistent)\n");
}

void perform_analysis_bundle(Student *students, int count, AnalysisFn custom_fn) {
    calculate_average(students, count);
    find_top_student(students, count);
    custom_fn(students, count);
}

void op_add(StudentDB *db)      { add_students(db); }
void op_display(StudentDB *db)  { display_students(db->students, db->count); }
void op_sort(StudentDB *db)     { sort_students(db); }
void op_avg(StudentDB *db)      { calculate_average(db->students, db->count); }
void op_top(StudentDB *db)      { find_top_student(db->students, db->count); }
void op_custom(StudentDB *db)   { grade_stability_score(db->students, db->count); }
void op_all(StudentDB *db)      { perform_analysis_bundle(db->students, db->count, grade_stability_score); }

void seed_initial_data(StudentDB *db) {
    Student data[] = {
        {1, "Aziza", 78.5f},
        {2, "Neema", 66.0f},
        {3, "Shema", 84.0f},
        {4, "Daniel", 72.5f},
        {5, "Faith", 91.0f},
        {6, "Elisa", 58.0f},
        {7, "Claudia", 88.5f},
        {8, "Nancy", 69.0f},
        {9, "Iris", 95.0f},
        {10, "Bruce", 74.5f},
        {11, "Anitha", 74.5f}
    };
    int size = (int)(sizeof(data) / sizeof(data[0]));
    int i;

    grow_array(db, size);
    for (i = 0; i < size; i++) {
        *(db->students + i) = data[i];
    }
    db->count = size;
}

int main(void) {
    StudentDB db;
    int choice, i;

    Operation ops[] = {
        op_add, op_display, op_sort, op_avg,
        op_top, op_custom, op_all
    };
    const char *labels[] = {
        "Add students",
        "Display students",
        "Sort students",
        "Calculate average",
        "Find top student",
        "Run custom analysis",
        "Perform full analysis"
    };
    int n = (int)(sizeof(ops) / sizeof(ops[0]));

    db.capacity = 10;
    db.count = 0;
    db.students = (Student *)malloc(sizeof(Student) * db.capacity);
    if (db.students == NULL) {
        printf("malloc failed\n");
        return 1;
    }

    seed_initial_data(&db);

    printf("Student ID: %s\n", STUDENT_ID);
    printf("Analysis Function: Grade Stability Score\n");

    while (1) {
        printf("\n Student Record Engine \n");
        for (i = 0; i < n; i++)
            printf("%d. %s\n", i + 1, labels[i]);
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= n)
            ops[choice - 1](&db);
        else if (choice == 8)
            break;
        else
            printf("Try again.\n");
    }

    free(db.students);
    return 0;
}