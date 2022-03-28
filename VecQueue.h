#ifndef VECQUEUE_H
#define VECQUEUE_H
#include <iostream>

//----------------------------------------------------------------------------------------------
// UFC - Campus Quixadá
// AP 03 - Projeto de Implementação - Matrizes Esparsas.
// Aluno: Gabriel Ileis Araújo Vieira
// Matrícula: 493973
// ---------------------------------------------------------------------------------------------

class VecQueue{

    private:

    // Nó da fila de Vetores.
    struct VecQueueNode{
        int* vec;
        int size;
        VecQueueNode* next;

        // Construtor do nó.
        VecQueueNode(int* vec, int size, VecQueueNode* next);
    };

    VecQueueNode* head;
    VecQueueNode* tail;

    public:

    // Construtor da fila.
    VecQueue();

    // Destrutor da fila.
    ~VecQueue();

    // Coloca um vetor na fila.
    void push(int* vec, int size);

    // Tira um vetor da fila.
    void pop();
    
    // Desaloca e tira um vetor da fila.
    void popAndDel();

    // Printa um vetor inteiro.
    void printVec();

    // Retorna o ponteiro para o primeiro elemento do vetor.
    int* getVec();

    // Retorna o tamanho do vetor.
    int getSizeVec();

    // Verifica se a fila está vazia.
    bool isEmpty();
};

#endif