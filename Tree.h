#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>

//----------------------------------------------------------------------------------------------
// UFC - Campus Quixadá
// AP 03 - Projeto de Implementação - Matrizes Esparsas.
// Aluno: Gabriel Ileis Araújo Vieira
// Matrícula: 493973
// ---------------------------------------------------------------------------------------------

// NODE

struct Node{
    int key;
    Node* left;
    Node* right;

    // Construtor.
    Node(int key, Node* left, Node* right);
};

// ---------------------------------------------------------------------------------------------

//FILA DE NODE

class NodeQueue{

    struct QueueNode{
        Node* data;
        QueueNode* next;

        // Construtor.
        QueueNode(Node* node, QueueNode* next);
    };

    QueueNode* head;
    QueueNode* tail;
    int size;

    public:

    // Construtor.
    NodeQueue();

    // Destrutor.
    ~NodeQueue();

    // Coloca o nó na fila.
    void push(Node* node);

    // Tira um nó da fila.    
    void pop();

    // Retorna o nó da vez.
    Node* get();

    // Retorna se a fila está vazia.
    bool isEmpty();
};

// ---------------------------------------------------------------------------------------------

class Tree{

    private:

    Node* root;
    int high;
    int numLeaf;
    int epsilon;

    public:

    // Recebe um vector e seu tamanho e o ordena em ordem crescente.
    void sortVec(int* vec, int size);

    // Construtor.
    Tree();

    // Destrutor.
    ~Tree();

    private:

    // Deleta todos os nós existentes na arvore.
    Node* clear(Node *node);

    // Propaga os menores valores de chaves das folhas para os nós ancestrais.
    Node* propagarChaves(Node* node);

    // Verifica se é um nó folha.
    bool isLeaf(Node *node);

    // Faz uma arvore a partir de um nó e uma altura desejada.
    Node* makeTree(Node *node, int high);

    // Retorna o valor inteiro do maior elemento em um vetor.
    int maxVec(int* vec, int size);

    // Retorna uma lista de nós folhas temporários para a inserção de novos nós folhas.
    NodeQueue* getLeafParents();

    // Printa a arvore em largura
    void printLargura();

    // Busca binária do nó folha que possui o menor valor de chave.
    Node* minLeaf(Node* node);
};

#endif

// - CRIAÇÃO DE ARVORE CHEIA USANDO RECURÇÃO COM LIMITADOR DE NIVEL - função(Node *node, int nivel);
//   (PRÉ ORDEM)                                                      função(node, nivel - 1);
//
// - IMPLEMENTAR FILA DE NÓ (fila simplesmente encadeada sem nó cabeça)
//
// - USO DE PÓS ORDEM PARA A PROPAGAÇÃO DE CHAVES DOS FILHOS PARA OS PAIS
//
// - A ORDENAÇÃO DO VETOR ACONTECE ATÉ QUE O VALOR DA RAIZ SEJA EPSILON,
//   JÁ QUE A CADA TROCA DO MENOR VALOR DE FOLHA POR EPSILON A RAIZ FICA
//   COM O MENOR VALOR EXISTENTE NA ARVORE.