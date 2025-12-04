#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUD_FILE "students.txt"
#define MARKS_FILE "marks.txt"
#define CGPA_FILE  "cgpa.txt"
#define CRE_FILE   "credentials.txt"

char currentUser[50];
char currentRole[20];

struct Student {
    int roll;
    char name[50];
    float maths, dsa, os;
    float cgpa;
};

int gradePoint(float m) {
    if (m >= 90) return 10;
    if (m >= 80) return 9;
    if (m >= 70) return 8;
    if (m >= 60) return 7;
    if (m >= 50) return 6;
    if (m >= 40) return 5;
    return 0;
}

float calculateCGPA(float m1, float m2, float m3) {
    int gp1 = gradePoint(m1);
    int gp2 = gradePoint(m2);
    int gp3 = gradePoint(m3);

    int c1 = 4, c2 = 3, c3 = 3;
    float total = gp1*c1 + gp2*c2 + gp3*c3;
    return total / 10.0;
}

// -------------------------------- LOGIN --------------------------------

int login() {
    char u[50], p[50], r[20];
    char inUser[50], inPass[50];

    printf("USERNAME: "); scanf("%s", inUser);
    printf("PASSWORD: "); scanf("%s", inPass);

    FILE *fp = fopen(CRE_FILE, "r");
    if (!fp) { printf("Credential file missing!\n"); return 0; }

    while (fscanf(fp, "%s %s %s", u, p, r) == 3) {
        if (strcmp(inUser, u) == 0 && strcmp(inPass, p) == 0) {
            strcpy(currentUser, u);
            strcpy(currentRole, r);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// ------------------------------ ADMIN FUNCTIONS ------------------------------

void addStudent() {
    int roll;
    char name[50];
    float m1, m2, m3;

    printf("Roll: "); scanf("%d", &roll);
    printf("Name: "); scanf(" %[^\n]", name);
    printf("Maths: "); scanf("%f", &m1);
    printf("DSA: "); scanf("%f", &m2);
    printf("OS : "); scanf("%f", &m3);

    float cg = calculateCGPA(m1, m2, m3);

    FILE *fp1 = fopen(STUD_FILE, "a");
    fprintf(fp1, "%d %s\n", roll, name);
    fclose(fp1);

    FILE *fp2 = fopen(MARKS_FILE, "a");
    fprintf(fp2, "%d %.2f %.2f %.2f\n", roll, m1, m2, m3);
    fclose(fp2);

    FILE *fp3 = fopen(CGPA_FILE, "a");
    fprintf(fp3, "%d %.2f\n", roll, cg);
    fclose(fp3);

    printf("\nStudent added successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) { printf("No students found!\n"); return; }

    int roll;
    char name[50];
    printf("\nROLL\tNAME\n--------------------------------\n");

    while (fscanf(fp, "%d %s", &roll, name) == 2) {
        printf("%d\t%s\n", roll, name);
    }
    fclose(fp);
}

void displayCGPA() {
    FILE *fp = fopen(CGPA_FILE, "r");
    if (!fp) { printf("CGPA file missing!\n"); return; }

    int roll;
    float cg;

    printf("\nROLL\tCGPA\n---------------\n");

    while (fscanf(fp, "%d %f", &roll, &cg) == 2) {
        printf("%d\t%.2f\n", roll, cg);
    }
    fclose(fp);
}

void displayMerit() {
    FILE *fp = fopen(CGPA_FILE, "r");
    if (!fp) { printf("CGPA file not found!\n"); return; }

    float cg;
    int roll, total = 0;
    float sum = 0;

    while (fscanf(fp, "%d %f", &roll, &cg) == 2) {
        sum += cg;
        total++;
    }
    fclose(fp);

    printf("\nAverage CGPA of class = %.2f\n", sum / total);
}

void subjectAdvice() {
    int roll;
    printf("Enter roll: ");
    scanf("%d", &roll);

    FILE *fp = fopen(MARKS_FILE, "r");
    int r; float m1, m2, m3;

    while (fscanf(fp, "%d %f %f %f", &r, &m1, &m2, &m3) == 4) {
        if (r == roll) {
            printf("\nWeak Subjects:\n");
            if (m1 < 50) printf("❗ Maths (%.2f)\n", m1);
            if (m2 < 50) printf("❗ DSA (%.2f)\n", m2);
            if (m3 < 50) printf("❗ OS  (%.2f)\n", m3);
            fclose(fp);
            return;
        }
    }
    fclose(fp);
    printf("Student not found!\n");
}

// ------------------------------- MENUS -------------------------------

void adminMenu() {
    int c;
    while (1) {
        printf("\nADMIN MENU\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Display CGPA List\n");
        printf("4. Class Merit %\n");
        printf("5. Subject Advice\n");
        printf("6. Logout\n");

        scanf("%d", &c);

        if (c == 1) addStudent();
        else if (c == 2) displayStudents();
        else if (c == 3) displayCGPA();
        else if (c == 4) displayMerit();
        else if (c == 5) subjectAdvice();
        else return;
    }
}

void staffMenu() {
    int c;
    while (1) {
        printf("\nSTAFF MENU\n");
        printf("1. Display Students\n");
        printf("2. Display CGPA\n");
        printf("3. Logout\n");

        scanf("%d", &c);

        if (c == 1) displayStudents();
        else if (c == 2) displayCGPA();
        else return;
    }
}

void studentMenu() {
    int c;
    while (1) {
        printf("\nSTUDENT MENU\n");
        printf("1. Display CGPA List\n");
        printf("2. Subject Advice\n");
        printf("3. Logout\n");

        scanf("%d", &c);

        if (c == 1) displayCGPA();
        else if (c == 2) subjectAdvice();
        else return;
    }
}

// ------------------------------ MAIN ------------------------------

int main() {
    if (!login()) {
        printf("Invalid login!\n");
        return 0;
    }

    printf("Logged in as: %s\n", currentRole);

    if (strcmp(currentRole, "admin") == 0) adminMenu();
    else if (strcmp(currentRole, "staff") == 0) staffMenu();
    else studentMenu();

    return 0;
}
