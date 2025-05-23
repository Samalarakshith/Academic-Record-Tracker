#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

struct s_list {
    char s_name[50];
    int h_no;
    int math;
    int phy;
    int eng;
    int prog;
    int total;
    int grand_total;
} *ptr, *dup;

// Function declarations
void read(void);
void sort(void);
void search(void);
void print(void);
void sort_semtop(void);
void sort_ovtop(void);
void sort_subtop(void);
void sort_distop(void);
void search_ht(void);
void search_sub(void);
void search_failov(void);
void search_failsem(void);
void search_70(void);

// Global variables
int n, m, f, u, p;
char rname[30], runame[30], profile[3][20], ch1, pass[30], ch2, repas[30], loginpro[3][20], uname[30], ch, pwd[30];

int user_main() {
    int a, ctr = 0;
    system("COLOR E4");

abc:
    printf("\n ENTER THE OPTION YOU WANT : \n");
    printf(" 1. READ THE DATA\n 2. SORT THE DATA\n 3. SEARCH THE DATA\n 4. PRINT THE DATA\n");
    printf(" Enter Your Choice: ");
    scanf("%d", &a);

    switch (a) {
        case 1:
            read();
            ctr++;
            break;
        case 2:
            if (ctr == 0) {
                printf("\nERROR :: to SORT the data first you have to READ the data\n\n");
                goto abc;
            } else {
                sort();
            }
            break;
        case 3:
            if (ctr == 0) {
                printf("\nERROR :: to SEARCH the data first you have to READ the data\n\n");
                goto abc;
            } else {
                search();
            }
            break;
        case 4:
            if (ctr == 0) {
                printf("\nERROR :: to PRINT the data first you have to READ the data\n\n");
                goto abc;
            } else {
                print();
            }
            break;
        default:
            printf("\n SORRY WRONG OPTION IS ENTERED, TRY AGAIN ");
            goto abc;
    }
    return 0;
}

void read() {
    int i, j, c, x = 0;
    char k;

    printf("\n Enter the number of students: ");
    scanf("%d", &n);
    printf("\n Enter the number of semesters: ");
    scanf("%d", &m);

    ptr = (struct s_list *)calloc(n * m, sizeof(struct s_list));
    dup = (struct s_list *)calloc(n * m, sizeof(struct s_list));

    if (ptr == NULL || dup == NULL) {
        printf("\n Insufficient memory allocated.");
        exit(0);
    }

    for (i = 0; i < n; i++) {
        printf("\n ENTER THE DETAILS OF STUDENT[%d]:\n", i + 1);
        printf(" name: ");
        scanf("%s", (ptr + i)->s_name);
        strcpy((dup + i)->s_name, (ptr + i)->s_name);

        printf(" h_no: ");
        scanf("%d", &(ptr + i)->h_no);
        (dup + i)->h_no = (ptr + i)->h_no;
    }

    for (i = 0; i < n; i++) {
        x = 0;
        for (j = 0; j < m; j++) {
            printf("\n MARKS OF '%s'(%d) in %d SEMESTER:\n", (ptr + i)->s_name, (ptr + i)->h_no, j + 1);

            printf(" marks in math: ");
            scanf("%d", &(ptr + (i * m + j))->math);
            (dup + (i * m + j))->math = (ptr + (i * m + j))->math;

            printf(" marks in phy: ");
            scanf("%d", &(ptr + (i * m + j))->phy);
            (dup + (i * m + j))->phy = (ptr + (i * m + j))->phy;

            printf(" marks in eng: ");
            scanf("%d", &(ptr + (i * m + j))->eng);
            (dup + (i * m + j))->eng = (ptr + (i * m + j))->eng;

            printf(" marks in prog: ");
            scanf("%d", &(ptr + (i * m + j))->prog);
            (dup + (i * m + j))->prog = (ptr + (i * m + j))->prog;

            (ptr + (i * m + j))->total =
                (ptr + (i * m + j))->math +
                (ptr + (i * m + j))->phy +
                (ptr + (i * m + j))->eng +
                (ptr + (i * m + j))->prog;

            (dup + (i * m + j))->total = (ptr + (i * m + j))->total;
            x += (ptr + (i * m + j))->total;

            printf(" TOTAL MARKS OF '%s'(%d) in SEMESTER (%d): %d\n",
                   (ptr + i)->s_name, (ptr + i)->h_no, j + 1, (ptr + (i * m + j))->total);
        }

        (ptr + i)->grand_total = x;
        (dup + i)->grand_total = (ptr + i)->grand_total;

        printf("\n Overall Marks of '%s'(%d) in all %d Semesters = %d\n",
               (ptr + i)->s_name, (ptr + i)->h_no, m, (ptr + i)->grand_total);
    }

    system("cls");

abc:
    printf("\n *ENTER AN OPTION** \n");
    printf(" 1. sort the data \n 2. search the data \n 3. print the data\n");
    printf(" Enter Your Choice = ");
    scanf("%d", &c);

    switch (c) {
        case 1:
            sort();
            break;
        case 2:
            search();
            break;
        case 3:
            print();
            break;
        default:
            printf("\n SORRY ENTER THE CORRECT OPTION.......");
            break;
    }

    printf("\n WANT TO SORT, SEARCH OR PRINT DATA AGAIN? (y/n): ");
    scanf(" %c", &k);
    if (k == 'y' || k == 'Y') goto abc;
}
void sort() {
    system("cls");
    int b;
    char o;
abc:
    system("cls");
    printf("\n ENTER THE OPTION YOU WANT TO SORT :\n");
    printf("1. Semwise\n2. Overall\n3. Subject-wise\n4. Distinction-wise\n");
    printf("Enter your choice: ");
    scanf("%d", &b);

    switch (b) {
        case 1: sort_semtop(); break;
        case 2: sort_ovtop(); break;
        case 3: sort_subtop(); break;
        case 4: sort_distop(); break;
        default:
            printf("Sorry, wrong option entered. Kindly try again.\n");
    }

    printf("\nWANT TO TRY SORTING AGAIN? (y/n): ");
    scanf(" %c", &o);  // Note the space to consume previous newline
    if (o == 'y' || o == 'Y') goto abc;
}

// SEMESTER-WISE SORTING
void sort_semtop() {
    int temp_total_sem_wise[n][m], i, j, k, temp;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            temp_total_sem_wise[i][j] = (ptr + (i * m + j))->total;
        }
    }

    for (j = 0; j < m; j++) {
        for (i = 0; i < n - 1; i++) {
            for (k = 0; k < n - i - 1; k++) {
                if (temp_total_sem_wise[k][j] < temp_total_sem_wise[k + 1][j]) {
                    temp = temp_total_sem_wise[k][j];
                    temp_total_sem_wise[k][j] = temp_total_sem_wise[k + 1][j];
                    temp_total_sem_wise[k + 1][j] = temp;
                }
            }
        }
    }

    printf("\nSEM-WISE TOTAL MARKS SORTED LIST:\n");
    for (j = 0; j < m; j++) {
        printf("\nSEMESTER-%d SORTED TOTALS:\n", j + 1);
        for (i = 0; i < n; i++) {
            printf("%d ", temp_total_sem_wise[i][j]);
        }
        printf("\n");
    }
}

// OVERALL TOP SORT
void sort_ovtop() {
    int temp_grand_total[n], temp, i, j;

    for (i = 0; i < n; i++) {
        temp_grand_total[i] = (dup + i)->grand_total;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (temp_grand_total[j] < temp_grand_total[j + 1]) {
                temp = temp_grand_total[j];
                temp_grand_total[j] = temp_grand_total[j + 1];
                temp_grand_total[j + 1] = temp;
            }
        }
    }

    printf("\nOVERALL SORTED LIST IS:\n");
    for (j = 0; j < n; j++) {
        printf("%d ", temp_grand_total[j]);
    }
    printf("\n");
}

// SUBJECT-WISE SORT
void sort_subtop() {
    int l = n * m;
    int math[l], phy[l], eng[l], prog[l];
    int i, j, k = 0, temp;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            math[k] = (dup + (i * m + j))->math;
            phy[k] = (dup + (i * m + j))->phy;
            eng[k] = (dup + (i * m + j))->eng;
            prog[k] = (dup + (i * m + j))->prog;
            k++;
        }
    }

    for (i = 0; i < l; i++) {
        for (j = 0; j < l - i - 1; j++) {
            if (math[j] < math[j + 1]) {
                temp = math[j]; math[j] = math[j + 1]; math[j + 1] = temp;
            }
            if (phy[j] < phy[j + 1]) {
                temp = phy[j]; phy[j] = phy[j + 1]; phy[j + 1] = temp;
            }
            if (eng[j] < eng[j + 1]) {
                temp = eng[j]; eng[j] = eng[j + 1]; eng[j + 1] = temp;
            }
            if (prog[j] < prog[j + 1]) {
                temp = prog[j]; prog[j] = prog[j + 1]; prog[j + 1] = temp;
            }
        }
    }

    printf("\nSorted Maths Marks: ");
    for (i = 0; i < l; i++) printf("%d ", math[i]);

    printf("\nSorted Physics Marks: ");
    for (i = 0; i < l; i++) printf("%d ", phy[i]);

    printf("\nSorted English Marks: ");
    for (i = 0; i < l; i++) printf("%d ", eng[i]);

    printf("\nSorted Programming Marks: ");
    for (i = 0; i < l; i++) printf("%d ", prog[i]);

    printf("\n");
}

// SUBJECT DISTINCTION-WISE SORTING (MARKS >= 70)
void sort_distop() {
    int l = n * m;
    int math[l], phy[l], eng[l], prog[l];
    int i, j, k = 0, temp;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            math[k] = (dup + (i * m + j))->math;
            phy[k] = (dup + (i * m + j))->phy;
            eng[k] = (dup + (i * m + j))->eng;
            prog[k] = (dup + (i * m + j))->prog;
            k++;
        }
    }

    for (i = 0; i < l; i++) {
        for (j = 0; j < l - i - 1; j++) {
            if (math[j] < math[j + 1]) {
                temp = math[j]; math[j] = math[j + 1]; math[j + 1] = temp;
            }
            if (phy[j] < phy[j + 1]) {
                temp = phy[j]; phy[j] = phy[j + 1]; phy[j + 1] = temp;
            }
            if (eng[j] < eng[j + 1]) {
                temp = eng[j]; eng[j] = eng[j + 1]; eng[j + 1] = temp;
            }
            if (prog[j] < prog[j + 1]) {
                temp = prog[j]; prog[j] = prog[j + 1]; prog[j + 1] = temp;
            }
        }
    }

    printf("\nDistinction Maths Marks (>=70): ");
    for (i = 0; i < l; i++) {
        if (math[i] >= 70) printf("%d ", math[i]);
    }

    printf("\nDistinction Physics Marks (>=70): ");
    for (i = 0; i < l; i++) {
        if (phy[i] >= 70) printf("%d ", phy[i]);
    }

    printf("\nDistinction English Marks (>=70): ");
    for (i = 0; i < l; i++) {
        if (eng[i] >= 70) printf("%d ", eng[i]);
    }

    printf("\nDistinction Programming Marks (>=70): ");
    for (i = 0; i < l; i++) {
        if (prog[i] >= 70) printf("%d ", prog[i]);
    }

    printf("\n");
}
void search() {
    int ab;
    char cd;
    
    do {
        system("cls");
        printf("\n*ENTER THE OPTION YOU WANT TO SEARCH FOR*\n");
        printf("\n 1. H.T.NO BASED \n 2. sub-wise \n 3. failed students list sem wise");
        printf("\n 4. failed students list overall \n 5. STUDENTS SCORED 70+MARKS SUB-WISE:\n");
        printf("Enter your choice: ");
        scanf("%d", &ab);

        switch (ab) {
            case 1: search_ht(); break;
            case 2: search_sub(); break;
            case 3: search_failsem(); break;
            case 4: search_failov(); break;
            case 5: search_70(); break;
            default: printf("\n INVALID OPTION!\n"); break;
        }

        printf("\nWANT TO TRY SEARCHING AGAIN...? (y/n): ");
        scanf(" %c", &cd);
    } while (cd == 'y' || cd == 'Y');

}

void search_ht() {
    int hno;
    int i, j, flag;
    char ch;

    do {
        flag = 0;
        printf("\nEnter HallTicket Number to be Searched: ");
        scanf("%d", &hno);

        for (i = 0; i < n; i++) {
            if (hno == (ptr + i)->h_no) {
                flag = 1;
                break;
            }
        }

        if (flag == 1) {
            printf("\nStudent (%d) Found. Details are:\n", hno);
            printf("\nName = %s\nHallTicket No = %d", (ptr + i)->s_name, (ptr + i)->h_no);
            printf("\nSemester-wise Marks:\n");

            for (j = 0; j < m; j++) {
                struct marks *mk = (struct marks *)(ptr + (i * m + j));
                printf("\n Semester %d Marks List\n", j + 1);
                printf("Maths = %d\n",(ptr+(i*m+j))->math);
                printf("Physics = %d\n",(ptr+(i*m+j))->phy);
                printf("English = %d\n", (ptr+(i*m+j))->eng);
                printf("Programming = %d\n", (ptr+(i*m+j))->prog);
                printf("Total Marks = %d\n",(ptr+(i*m+j))->total);
            }

            printf("\nGRAND TOTAL IN %d SEMESTERS = %d\n", m, (ptr + i)->grand_total);
        } else {
            printf("\nIncorrect HallTicket Number Provided.\n");
        }

        printf("\nWanna Try ht_searching again? Enter Y or y to try again: ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');
}
void search_sub() {
    int c, i, j;
    char ch;

    do {
        printf("\nSubjects List\n1. Maths\n2. Physics\n3. English\n4. Programming");
        printf("\nEnter your choice: ");
        scanf("%d", &c);

        switch (c) {
            case 1:
                printf("\nStudents Details (Maths):\n");
                for (i = 0; i < n; i++) {
                    printf("\nName = %s\nHallTicket No = %d", (ptr + i)->s_name, (ptr + i)->h_no);
                    for (j = 0; j < m; j++) {
                        printf("\nSemester %d Marks:\n", j + 1);
                        printf("Maths = %d\n", (ptr + (i * m + j))->math);
                        printf("Total Marks = %d\n", (ptr + (i * m + j))->total);
                    }
                    printf("\nGRAND TOTAL IN %d SEMESTERS = %d\n", m, (ptr + i)->grand_total);
                }
                break;

            case 2:
                printf("\nStudents Details (Physics):\n");
                for (i = 0; i < n; i++) {
                    printf("\nName = %s\nHallTicket No = %d", (ptr + i)->s_name, (ptr + i)->h_no);
                    for (j = 0; j < m; j++) {
                        printf("\nSemester %d Marks:\n", j + 1);
                        printf("Physics = %d\n", (ptr + (i * m + j))->phy);
                        printf("Total Marks = %d\n", (ptr + (i * m + j))->total);
                    }
                    printf("\nGRAND TOTAL IN %d SEMESTERS = %d\n", m, (ptr + i)->grand_total);
                }
                break;

            case 3:
                printf("\nStudents Details (English):\n");
                for (i = 0; i < n; i++) {
                    printf("\nName = %s\nHallTicket No = %d", (ptr + i)->s_name, (ptr + i)->h_no);
                    for (j = 0; j < m; j++) {
                        printf("\nSemester %d Marks:\n", j + 1);
                        printf("English = %d\n", (ptr + (i * m + j))->eng);
                        printf("Total Marks = %d\n", (ptr + (i * m + j))->total);
                    }
                    printf("\nGRAND TOTAL IN %d SEMESTERS = %d\n", m, (ptr + i)->grand_total);
                }
                break;

            case 4:
                printf("\nStudents Details (Programming):\n");
                for (i = 0; i < n; i++) {
                    printf("\nName = %s\nHallTicket No = %d", (ptr + i)->s_name, (ptr + i)->h_no);
                    for (j = 0; j < m; j++) {
                        printf("\nSemester %d Marks:\n", j + 1);
                        printf("Programming = %d\n", (ptr + (i * m + j))->prog);
                        printf("Total Marks = %d\n", (ptr + (i * m + j))->total);
                    }
                    printf("\nGRAND TOTAL IN %d SEMESTERS = %d\n", m, (ptr + i)->grand_total);
                }
                break;

            default:
                printf("\nInvalid Choice\n");
                break;
        }

        printf("\nWanna Try Subject-based Searching Again? Enter Y or y to try again: ");
        scanf(" %c", &ch);

    } while (ch == 'y' || ch == 'Y');
}
void search_failsem() {
    char ch;
    int i, j, flag, count;

    do {
        count = 0;
        for (i = 0; i < n; i++) {
            flag = 0;
            for (j = 0; j < m; j++) {
                if ((ptr + (i * m + j))->total <= 180) {
                    if (flag == 0) {
                        printf("\n**");
                        printf("\nName = %s\nHallTicket No = %d", (ptr + i)->s_name, (ptr + i)->h_no);
                    }
                    printf("\nSemester %d Marks List\n", j + 1);
                    printf("Maths = %d\n", (ptr + (i * m + j))->math);
                    printf("Physics = %d\n", (ptr + (i * m + j))->phy);
                    printf("English = %d\n", (ptr + (i * m + j))->eng);
                    printf("Programming = %d\n", (ptr + (i * m + j))->prog);
                    printf("Total Marks = %d\n", (ptr + (i * m + j))->total);
                    flag = 1;
                }
            }
            if (flag) {
                printf("\nGRAND TOTAL IN %d SEMESTERS = %d", m, (ptr + i)->grand_total);
                count++;
            }
        }

        if (count == 0) {
            printf("\nNo students failed semester-wise (total <= 180).");
        }

        printf("\nWanna Try Sem-wise failure search Again? Enter Y or y to try again: ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');
}
void search_failov() {
    char ch;
    int i, j, count;

    do {
        count = 0;
        for (i = 0; i < n; i++) {
            if ((ptr + i)->grand_total < (180 * m)) {
                printf("\n**");
                printf("\nName = %s\nHallTicket No = %d", (ptr + i)->s_name, (ptr + i)->h_no);
                for (j = 0; j < m; j++) {
                    printf("\nSemester %d Marks List\n", j + 1);
                    printf("Maths = %d\n", (ptr + (i * m + j))->math);
                    printf("Physics = %d\n", (ptr + (i * m + j))->phy);
                    printf("English = %d\n", (ptr + (i * m + j))->eng);
                    printf("Programming = %d\n", (ptr + (i * m + j))->prog);
                    printf("Total Marks = %d\n", (ptr + (i * m + j))->total);
                }
                printf("\nGRAND TOTAL IN %d SEMESTERS = %d", m, (ptr + i)->grand_total);
                count++;
            }
        }

        if (count == 0) {
            printf("\nNo students failed overall (grand total < %d).\n", 180 * m);
        }

        printf("\nWanna Try Overall failure search Again? Enter Y or y to try again: ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');
}
void search_70() {
    char ch;
    int i, j, c, flag;

    do {
        printf("\nSubjects List\n1. Maths\n2. Physics\n3. English\n4. Programming");
        printf("\nEnter your choice: ");
        scanf("%d", &c);

        switch (c) {
            case 1:
                printf("\nStudents with 70+ in Maths:\n");
                for (i = 0; i < n; i++) {
                    flag = 0;
                    for (j = 0; j < m; j++) {
                        if ((ptr + (i * m + j))->math >= 70) {
                            if (flag == 0)
                                printf("\nName = %s\nHallTicket No = %d", (ptr + i)->s_name, (ptr + i)->h_no);
                            printf("\nSemester %d: Maths = %d, Total = %d", j + 1, (ptr + (i * m + j))->math, (ptr + (i * m + j))->total);
                            flag = 1;
                        }
                    }
                    if (flag)
                        printf("\nGRAND TOTAL = %d\n", (ptr + i)->grand_total);
                }
                break;

            case 2:
                printf("\nStudents with 70+ in Physics:\n");
                for (i = 0; i < n; i++) {
                    flag = 0;
                    for (j = 0; j < m; j++) {
                        if ((ptr + (i * m + j))->phy >= 70) {
                            if (flag == 0)
                                printf("\nName = %s\nHallTicket No = %d", (ptr + i)->s_name, (ptr + i)->h_no);
                            printf("\nSemester %d: Physics = %d, Total = %d", j + 1, (ptr + (i * m + j))->phy, (ptr + (i * m + j))->total);
                            flag = 1;
                        }
                    }
                    if (flag)
                        printf("\nGRAND TOTAL = %d\n", (ptr + i)->grand_total);
                }
                break;

            case 3:
                printf("\nStudents with 70+ in English:\n");
                for (i = 0; i < n; i++) {
                    flag = 0;
                    for (j = 0; j < m; j++) {
                        if ((ptr + (i * m + j))->eng >= 70) {
                            if (flag == 0)
                                printf("\nName = %s\nHallTicket No = %d", (ptr + i)->s_name, (ptr + i)->h_no);
                            printf("\nSemester %d: English = %d, Total = %d", j + 1, (ptr + (i * m + j))->eng, (ptr + (i * m + j))->total);
                            flag = 1;
                        }
                    }
                    if (flag)
                        printf("\nGRAND TOTAL = %d\n", (ptr + i)->grand_total);
                }
                break;

            case 4:
                printf("\nStudents with 70+ in Programming:\n");
                for (i = 0; i < n; i++) {
                    flag = 0;
                    for (j = 0; j < m; j++) {
                        if ((ptr + (i * m + j))->prog >= 70) {
                            if (flag == 0)
                                printf("\nName = %s\nHallTicket No = %d", (ptr + i)->s_name, (ptr + i)->h_no);
                            printf("\nSemester %d: Programming = %d, Total = %d", j + 1, (ptr + (i * m + j))->prog, (ptr + (i * m + j))->total);
                            flag = 1;
                        }
                    }
                    if (flag)
                        printf("\nGRAND TOTAL = %d\n", (ptr + i)->grand_total);
                }
                break;

            default:
                printf("\nInvalid Option\n");
        }

        printf("\nWanna Try searching for 70+ marks Again? Enter Y or y to try again: ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');
}
void print() {
    system("cls");  // Clears the screen (Windows only)
    int i, j;

    printf("\n********* Students Details ********\n");
    for (i = 0; i < n; i++) {
        printf("\n**");
        printf("\nName = %s\nHallTicket No = %d", (ptr + i)->s_name, (ptr + i)->h_no);
        for (j = 0; j < m; j++) {
            printf("\nSemester %d Marks List\n", j + 1);
            printf("Maths = %d\n", (ptr + (i * m + j))->math);
            printf("Physics = %d\n", (ptr + (i * m + j))->phy);
            printf("English = %d\n", (ptr + (i * m + j))->eng);
            printf("Programming = %d\n", (ptr + (i * m + j))->prog);
            printf("Total Marks = %d\n", (ptr + (i * m + j))->total);
        }
        printf("\nGRAND TOTAL IN %d SEMESTERS = %d", m, (ptr + i)->grand_total);
    }
}
int login() {
    char profile1[2][20] = {"team4sem", "1234"};
    char uname[20], pwd[20], ch;
    int u, p, f, c = 0;

    do {
        f = 0;
        printf("\n\nLogin Form.....");
        printf("\nEnter User Name: ");
        scanf("%s", uname);

        printf("\nEnter Password: ");
        while ((ch = getch()) != '\r') {
            pwd[f++] = ch;
            printf("*");
        }
        pwd[f] = '\0';

        u = strcmp(uname, profile1[0]);
        p = strcmp(pwd, profile1[1]);

        printf("\n\nPlease wait, Credential Verification is in Process....");
        Sleep(3000);  // Windows sleep in milliseconds
        system("cls");

        if (u == 0 && p == 0) {
            printf("\nSEMESTER SCORE LIST::..................SCR.................\n");
            user_main();  // Assume this is your main menu
            return 0;
        } else {
            printf("\n\nCredentials are wrong.....please try again.....");
            c++;
            printf("\n\nLeft %d attempt(s)\n", 3 - c);
        }
    } while (c < 3);

    printf("\nToo many failed attempts.\n");
    return 1;
}
int signin() {
    char rname[30], runame[20], pass[20], repass[20];
    char profile[2][20];
    char ch, ch2;
    int f = 0, c = 0;

    FILE *fptr = fopen("semester.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("\n------------ SEMESTER WISE MARKS FORM ---------------");
    printf("\nNAME:\t\t");
    scanf("%s", rname);
    printf("\nUSER NAME (no special characters allowed): ");
    scanf("%s", runame);
    strcpy(profile[0], runame);

pw:
    f = 0;
    printf("\nPASSWORD: ");
    while ((ch = getch()) != '\r') {
        pass[f++] = ch;
        printf("*");
    }
    pass[f] = '\0';
    strcpy(profile[1], pass);

    f = 0;
    printf("\n\nRE-ENTER PASSWORD: ");
    while ((ch2 = getch()) != '\r') {
        repass[f++] = ch2;
        printf("*");
    }
    repass[f] = '\0';

    if (strcmp(pass, repass) != 0) {
        printf("\nPasswords do not match. Please re-enter.\n");
        goto pw;
    }

    fprintf(fptr, "NAME = %s\nUSERNAME = %s\nPASSWORD = %s\n", rname, runame, pass);
    fclose(fptr);

    printf("\n\nStoring the details...");
    Sleep(1000);
    printf("\n\nREGISTRATION SUCCESSFUL!\n");

    // Login after registration
    f = 0;
    do {
        char uname[20], pwd[20];

        printf("\n\nLogin Form.....");
        printf("\nEnter User Name: ");
        scanf("%s", uname);

        printf("\nEnter Password: ");
        f = 0;
        while ((ch = getch()) != '\r') {
            pwd[f++] = ch;
            printf("*");
        }
        pwd[f] = '\0';

        int u = strcmp(uname, profile[0]);
        int p = strcmp(pwd, profile[1]);

        printf("\n\nPlease wait, Credential Verification is in Process....");
        Sleep(2000);
        system("cls");

        if (u == 0 && p == 0) {
            printf("\nSEMESTER SCORE LIST::..................SCR.................\n");
            user_main();  // Call your main user interface
            return 0;
        } else {
            printf("\n\nCredentials are wrong.....please try again.....");
            c++;
            printf("\n\nLeft %d attempt(s)\n", 3 - c);
        }
    } while (c < 3);

    return 1;
}
