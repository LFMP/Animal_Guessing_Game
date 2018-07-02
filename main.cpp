#include <iostream>
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string>

using namespace std;

#define VAZIO " "

typedef	struct tipo_item{
	string nome;
}item;	

typedef struct tipo_no{
	string pergunta;
	struct tipo_item animal;
	struct tipo_no *sim, *nao;
}no;

typedef struct tipo_arvore{
	no *raiz;
}arvore;

no* cria_no(string novo_animal, string pergunta){
	no *novo = (no*)malloc(sizeof(no));
	novo->pergunta = pergunta;
	novo->animal.nome = novo_animal;
	novo->sim = NULL;
	novo->nao = NULL;

	return novo;
}

void inicializa(arvore *a){
	a->raiz = cria_no(VAZIO, "O animal possui asas? ");
	a->raiz->sim = cria_no("Galinha", VAZIO);
	a->raiz->nao = cria_no("Cachorro", VAZIO);
}

int verif_reposta(char sn){
	if(sn == 's' || sn == 'S')
		return true;
	return false;
}

void adiciona_animal(no* n){
	string novo_animal, carac, nova_perg;

	cout << "Qual foi o animal pensado? ";
	cin >> novo_animal;
	cout << "O que diferencia " << novo_animal << " de " << n->animal.nome << "? ";
	__fpurge(stdin);
	getline(cin, carac);
	nova_perg = carac + "? ";
	n->nao = cria_no(VAZIO, nova_perg);
	n->nao->sim = cria_no(novo_animal, VAZIO);

}

void fazer_pergunta_no(no* n, no* n_pai, int flag){
	char resp;
	string novo_animal, carac, nova_perg;

	if(n->pergunta == VAZIO){
		cout << "Seu animal é " << n->animal.nome << "? ";
		cin >> resp;
		if(!verif_reposta(resp)){
			adiciona_animal(n);
			if(flag){
				n_pai->sim = n->nao;
				n->nao->nao = n;
				n->nao = NULL;
			}
			else{
				n_pai->nao = n->nao;
				n->nao->nao = n;
				n->nao = NULL;
			}
		}
		else cout << "ACERTEI!!!" << endl;
	}
	else{
		cout << n->pergunta;
		cin >> resp;
		if(verif_reposta(resp))
			fazer_pergunta_no(n->sim, n, 1);
		else fazer_pergunta_no(n->nao, n, 0);
	}
}

void fazer_perguntas(arvore *a){
	fazer_pergunta_no(a->raiz, a->raiz, 0);
}

int main(){
	arvore A;
	char repete = 's';

	inicializa(&A);

	do{
		system("clear");
		fazer_perguntas(&A);
		cout << "Quer continuar? ";
		__fpurge(stdin);
		cin >> repete;
	}while(verif_reposta(repete));


}