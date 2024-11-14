#include <iostream>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <new>
#include <queue> 
#define TAM 10

using namespace std;

struct No {
    int chave;
    No* esquerda;
    No* direita;
    int altura;

    No(int valor) : chave(valor), esquerda(nullptr), direita(nullptr), altura(1) {}
};

int altura(No* no) {
    if (no == nullptr)
        return 0;
    return no->altura;
}

int balancear(No* no) {
    if (no == nullptr)
        return 0;
    return altura(no->esquerda) - altura(no->direita);
}

void atualizarAltura(No* no) {
    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));
}

No* rotacao_s_esquerda(No* x) {
    No* y = x->direita;
    No* t2 = y->esquerda;

    y->esquerda = x;
    x->direita = t2;

    atualizarAltura(x);
    atualizarAltura(y);
    return y;
}

No* rotacao_s_direita(No* y) {
    No* x = y->esquerda;
    No* t2 = x->direita;

    x->direita = y;
    y->esquerda = t2;

    atualizarAltura(y);
    atualizarAltura(x);
    return x;
}

No* esquerda_direita(No* no) {
    no->esquerda = rotacao_s_esquerda(no->esquerda);
    return rotacao_s_direita(no);
}

No* direita_esquerda(No* no) {
    no->direita = rotacao_s_direita(no->direita);
    return rotacao_s_esquerda(no);
}

No* balance(No* raiz) {
    int fb = balancear(raiz);

    if (fb > 1 && balancear(raiz->esquerda) >= 0)
        return rotacao_s_direita(raiz);
    if (fb < -1 && balancear(raiz->direita) <= 0)
        return rotacao_s_esquerda(raiz);
    if (fb > 1 && balancear(raiz->esquerda) < 0)
        return esquerda_direita(raiz);
    if (fb < -1 && balancear(raiz->direita) > 0)
        return direita_esquerda(raiz);

    return raiz;
}

No* insert(No* no, int chave) {
    if (no == nullptr)
        return new No(chave);

    if (chave < no->chave)
        no->esquerda = insert(no->esquerda, chave);
    else if (chave > no->chave)
        no->direita = insert(no->direita, chave);
    else {
        return no;
    }

    atualizarAltura(no);
    return balance(no);
}


void printNivel(No* raiz) { // uso de busca em largura 
    if (raiz == nullptr)
        return;

    queue<No*> fila;
    fila.push(raiz);

    int nivel = 0;

    while (!fila.empty()) {
        int tamanhoNivel = fila.size();
        cout << "Nível " << nivel << ": ";

        for (int i = 0; i < tamanhoNivel; i++) {
            No* atual = fila.front();
            fila.pop();

            cout << atual->chave << " ";

            if (atual->esquerda != nullptr)
                fila.push(atual->esquerda);
            if (atual->direita != nullptr)
                fila.push(atual->direita);
        }
        cout << endl;
        nivel++;
    }
}

int main() {
    No* raiz = nullptr;
    int valor;

    cout << "Insira os valores para a árvore AVL (digite -1 para parar): " << endl;
    while (true) {
        cout << "Valor: ";
        cin >> valor;
        if (valor == -1)
            break;
        raiz = insert(raiz, valor);
    }

    cout << "Árvore AVL por níveis de altura:" << endl;
    printNivel(raiz);

    return 0;
}
