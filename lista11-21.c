#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno aluno;
struct aluno {
	char nome[41];
	float notaFinal;
	aluno *prox;
};

aluno *listaAlunos;

int salvarBin (void);
int lerBin (void);

int main () {
	listaAlunos = (aluno *) malloc(sizeof(aluno));
	listaAlunos->prox = NULL;
	int numeroAlunos;
	aluno *alunoAnterior, *novoAluno;
	
	printf("Número de alunos da disciplina: ");
	scanf("%d", &numeroAlunos);
	
	alunoAnterior = listaAlunos;
	for (int c = 0; c < numeroAlunos; c++) {
		novoAluno = (aluno *) malloc(sizeof(aluno));
		novoAluno->prox = NULL;
		printf("Digite o nome do %dº aluno: ", c+1);
		
		fgetc(stdin);
		fgets(novoAluno->nome, 41, stdin);
		
		int n = strlen(novoAluno->nome);
		while (n < 41) {
			novoAluno->nome[n] = ' ';
			n++;
		}
		novoAluno->nome[n] = '\0';
		
		printf("Digite a nota do %dº aluno: ", c+1);
		scanf("%f", &novoAluno->notaFinal);
		
		alunoAnterior->prox = novoAluno;
		alunoAnterior = alunoAnterior->prox;
	}
	
	if (salvarBin()) {
		lerBin();
	}
}

int salvarBin (void) {
	FILE *arquivo = fopen("lista11-21.bin", "wb");
	if (arquivo == NULL) return 0;

	for (aluno *a = listaAlunos->prox; a != NULL; a = a->prox) {
		fwrite(a, sizeof(aluno), 1, arquivo);
	}

	fclose(arquivo);
	return 1;
}

int lerBin (void) {
	float maiorNota = 0;
	
	FILE *arquivo = fopen("lista11-21.bin", "rb");
	if (arquivo == NULL) return 0;
	
	aluno *a = (aluno *) malloc(sizeof(aluno));
	
	while (fread(a, sizeof(aluno), 1, arquivo)) {
		if (a->notaFinal > maiorNota) maiorNota = a->notaFinal;
	}

	fclose(arquivo);
	printf("\nA maior nota é: %.2f", maiorNota);
	return 1;
}
