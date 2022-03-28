#include <iostream>
#include "VecQueue.h"

//----------------------------------------------------------------------------------------------
// UFC - Campus Quixadá
// AP 03 - Projeto de Implementação - Matrizes Esparsas.
// Aluno: Gabriel Ileis Araújo Vieira
// Matrícula: 493973
// ---------------------------------------------------------------------------------------------

// O nó da fila de vetores armazena o ponteiro para o primeiro elemento do vetor e o seu tamanho,
// sendo assim possivel a impressão do vetor.
// O(1)
VecQueue::VecQueueNode::VecQueueNode(int* vec, int size, VecQueueNode* next = nullptr){
    this->vec = vec;
    this->size = size;
    this->next = next;
}

// Construtor.
// O(1)
VecQueue::VecQueue(){
    head = tail = nullptr;
}

// Destrutor.
// O(n)
VecQueue::~VecQueue(){
    while(head !=  nullptr){
        VecQueueNode* aux = head;
        head = head->next;

        delete aux;
    }

    tail = nullptr;
}

// Coloca um vetor na fila.
// O(1)
void VecQueue::push(int* vec, int size){

    if(head == nullptr)
        head = tail = new VecQueueNode(vec,size);

    else{
        tail->next = new VecQueueNode(vec, size);
        tail = tail->next;
    }
}

// Tira um vetor da fila.
// O(1)
void VecQueue::pop(){
    VecQueueNode* aux = head;
    head = head->next;
    delete aux;

    if(head == nullptr)
        tail = nullptr;
}

// Desaloca e tira um vetor da fila.
// O(1)
void VecQueue::popAndDel(){
    delete[] head->vec;
    pop();
}

// Printa um vetor usando o ponteiro para o primeiro elemento e o tamanho do vetor.
// O(n)
void VecQueue::printVec(){
    for(int index = 0; index < getSizeVec(); index++){
        std::cout << getVec()[index] << " ";
    }
}

// Retorna o ponteiro para o primeiro elemento do vetor.
// O(1)
int* VecQueue::getVec(){
    return head->vec;
}

// Retorna o tamanho do vetor.
// O(1)
int VecQueue::getSizeVec(){
    return head->size;
}

// Verifica se a fila está vazia.
// O(1)
bool VecQueue::isEmpty(){
    return (head == nullptr) && (tail == nullptr);
}