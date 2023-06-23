#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void info();
void addStudent();
void showStudents();
void showStudentsAR(int r);
int saveData();
void clear();

char className[100] = "Turma sem Nome";
int classSize = 0;

typedef struct student student;
struct student
{
    char name[100];
    float grade[3];
    student *next;
};

student *studentList;

int main () {
    studentList = (student *) malloc(sizeof(student));
    studentList->next = NULL;

    char c = 'h';
    while (c != 'g') {
        printf(
            "(a) Definir Informacoes da Turma\n"
            "(b) Inserir Aluno e Notas\n"
            "(c) Exibir Alunos e Medias\n"
            "(d) Exibir Alunos Aprovados\n"
            "(e) Exibir Alunos Reprovados\n"
            "(f) Salvar Dados em Disco\n"
            "(g) Sair do Programa\n"
        );
        c = fgetc(stdin);

        switch (c) {
            case 'a':
                info();
                break;
            case 'b':
                addStudent();
                break;
            case 'c':
                showStudents();
                fgetc(stdin);
                break;
            case 'd':
                showStudentsAR(0);
                fgetc(stdin);
                break;
            case 'e':
                showStudentsAR(1);
                fgetc(stdin);
                break;
            case 'f':
                if (saveData()) {
                    printf("Ocorreu um erro\n");
                }
                fgetc(stdin);
                break;
            case 'g':
                clear();
                break;
        }
    }
}

void info () {
    printf("Número de alunos: ");
    scanf("%d", &classSize);
    fgetc(stdin);
    printf("Nome da turma: ");
    fgets(className, 100, stdin);
}

void addStudent () {
    int c = 1, gradeOk = 0;

    while (c == 1) {
        student *s = (student *) malloc(sizeof(student)), *temp;
        s->next = NULL;
        gradeOk = 0;

        printf("Nome do aluno: ");
        fgetc(stdin);
        fgets(s->name, 100, stdin);
        s->name[strlen(s->name) - 1] = '\0';

        while(gradeOk == 0) {
            printf("Digite as notas do 1°, 2° e 3° semestre: ");
            scanf("%f %f %f", &s->grade[0], &s->grade[1], &s->grade[2]);

            
            for (int i = 0; i < 3; i++) {
                if (s->grade[i] < 0 || s->grade[i] > 10) {
                    gradeOk = 0;
                    printf("Notas incorretas, digite novamente\n");
                    break;
                } else {
                    gradeOk = 1;
                }
            }
        }

        for (temp = studentList; temp->next != NULL; temp = temp->next);
        temp->next = s;

        printf("Deseja adicionar mais alunos? (1 - Sim; 2 - Não) : ");
        scanf("%d", &c);
    }

    fgetc(stdin);
}

void showStudents () {
    student *temp;

    for (temp = studentList->next; temp != NULL; temp = temp->next) {
        printf("Aluno: %s\n", temp->name);
        printf("Média Final: %.2f\n\n", (temp->grade[0] + temp->grade[1] + temp->grade[2]) / 3 );
    }
}

void showStudentsAR(int r) {
    student *temp;
    float finalGrade = 0;

    for (temp = studentList->next; temp != NULL; temp = temp->next) {
        finalGrade = (temp->grade[0] + temp->grade[1] + temp->grade[2]) / 3;
        if (r == 1 && finalGrade < 7) {
            printf("Aluno: %s\n", temp->name);
            printf("Média Final: %.2f\n\n", finalGrade);
        } else if (r == 0 && finalGrade >= 7) {
            printf("Aluno: %s\n", temp->name);
            printf("Média Final: %.2f\n\n", finalGrade);
        }
    }
}

int saveData () {
    FILE *file = fopen("Lista11-27.txt", "w");
    if (file == 0) return 1;
    student *temp;
    float finalGrade = 0;
    
    fprintf(file, "Nome da Turma: %s\nTamanho da Turma: %d\n\n", className, classSize);

    for (temp = studentList->next; temp != NULL; temp = temp->next) {
        finalGrade = (temp->grade[0] + temp->grade[1] + temp->grade[2]) / 3;
        fprintf(file, "Aluno: %s\n", temp->name);
        fprintf(file, "Nota 1: %.2f\nNota 2: %.2f\nNota 3: %.2f\nNota Final: %.2f\n\n", 
        temp->grade[0], temp->grade[1], temp->grade[2], finalGrade);
    }

    fclose(file);
    return 0;
}

void clear () {
    student *temp, *temp2;

    temp = studentList; 
    while (temp != NULL) {
        temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
}