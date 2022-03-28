#include <iostream>
#include <cmath>
#include "Tree.h"

//----------------------------------------------------------------------------------------------
// UFC - Campus Quixadá
// AP 03 - Projeto de Implementação - Matrizes Esparsas.
// Aluno: Gabriel Ileis Araújo Vieira
// Matrícula: 493973
// ---------------------------------------------------------------------------------------------

// NODE

// Construtor do nó da arvore.
Node::Node(int key = 0, Node* left = nullptr, Node* right = nullptr){
    this->key = key;
    this->left = left;
    this->right = right;
}

// ---------------------------------------------------------------------------------------------

//FILA DE NODE

// Construtor do nó da fila que armazena nós.
NodeQueue::QueueNode::QueueNode(Node* node, QueueNode* next = nullptr){
    this->data = node;
    this->next = next;
}

// Construtor da fila de nós.
NodeQueue::NodeQueue(){
    head = tail = nullptr;
    size = 0;
}

// Destrutor da fila de nós.
NodeQueue::~NodeQueue(){
    while(head != nullptr){
        QueueNode* aux = head;
        head = head->next;
        delete aux;
    }
}

// Coloca um elemento no final da fila.
// O(1)
void NodeQueue::push(Node* node){
    if(isEmpty())
        head = tail = new QueueNode(node);

    else{
        tail->next = new QueueNode(node);
        tail = tail->next;
    }

    size++;
}

// Tira um elemento do inicio da fila.
// O(1)
void NodeQueue::pop(){
    QueueNode* aux = head;
    head = head->next;
    delete aux;

    if(head == nullptr)
        tail = nullptr;

    size--;
}

// Retorna o nó da vez.
// O(1)
Node* NodeQueue::get(){
    return head->data;
}

// Verifica se a fila está vazia
// O(1)
bool NodeQueue::isEmpty(){
    return (head == nullptr) && (tail == nullptr);
}

// ---------------------------------------------------------------------------------------------

// Ordena o vetor recebido.
// O(n^2 (log(n))^2)
void Tree::sortVec(int* vec, int size){

    root = clear(root);

    if(size > 1){

        high = ceil((log(size) / log(2))) + 1;
        numLeaf = pow(2, high - 1);
        epsilon = maxVec(vec, size) + 1;

        // Criação dos nós folhas

        Node** leaf = new Node* [numLeaf];

        for(int index = 0; index < numLeaf; index++){

            if(index < size)
                leaf[index] = new Node(vec[index]);

            else
                leaf[index] = new Node(epsilon);
        }

        // Criação da arvore

        root = makeTree(root, high - 1); // O(n log(n))

        // Ligar a arvore criada com as folhas

        NodeQueue* leafParents = getLeafParents(); // O(n log(n))

        for(int index = 0; index < numLeaf; index = index + 2){
            Node* node = leafParents->get();
            leafParents->pop();

            node->left = leaf[index];
            node->right = leaf[index + 1];
        }

        delete leafParents;
        delete[] leaf;

        // Vetor ordenado;

        int index = 0;

        root = propagarChaves(root); // O(n log(n))

        while(root->key != epsilon){ // n * log(n) * n log(n) = n^2 (log (n))^2

            vec[index] = root->key;
            index++;

            minLeaf(root)->key = epsilon;
            root = propagarChaves(root);
        }
    }

    return;
}

// Inicializa as variaveis para receberem valores válidos.
Tree::Tree(){
    this->root = nullptr;
    high = 0;
    numLeaf = 0;
    epsilon = 0;
}

// Destrói a arvore criada.
Tree::~Tree(){
    root = clear(root);
}

// Deleta todos os nós existentes na arvore.
// O(n log(n))
// O código passa por todos os nós das arvores.
Node* Tree::clear(Node *node){
    if(node != nullptr){

        node->left = clear(node->left);
        node->right = clear(node->right);

        delete node;
        node = nullptr;
    }

    return node;
}

// Propaga os menores valores de chaves das folhas para os nós ancestrais.
// O(n log(n))
// O código passa por todos os nós das arvores.
Node* Tree::propagarChaves(Node* node){
        
    if(node != nullptr)
        if(!isLeaf(node)){
            node->left = propagarChaves(node->left);
            node->right = propagarChaves(node->right);

            if(node->left->key < node->right->key)
                node->key = node->left->key;
                    
            else
                node->key = node->right->key;
        }

    return node;
}

// Verifica se é um nó folha.
// O(1)
bool Tree::isLeaf(Node *node){
    return ((node->left == nullptr) && (node->right == nullptr));
}

// Faz uma arvore a partir de um nó e uma altura desejada.
// O(n log(n))
// O código cria todos os nós da árvore.
Node* Tree::makeTree(Node *node, int high){
    if(high > 0){
        node = new Node();

        node->left = makeTree(node->left, high - 1);
        node->right = makeTree(node->right, high - 1);
    }

    return node;
}

// Retorna o valor inteiro do maior elemento em um vetor.
// O(n)
// O código percorre o vetor até que ache o maior elemento.
int Tree::maxVec(int* vec, int size){
        
    int max;

    for(int index = 0; index < size; index++){
        if(index == 0)
            max = vec[index];

        else if(vec[index] > max)
            max = vec[index];
    }

    return max;
}

// Retorna uma lista de nós folhas temporários para a inserção de novos nós folhas.
// O(n log(n))
// O código percorre a arvore inteira.
NodeQueue* Tree::getLeafParents(){
    NodeQueue fila;
    NodeQueue *leafParents = new NodeQueue;
    fila.push(root);

    while(!fila.isEmpty()){
        Node *node = fila.get();
        fila.pop();

        if(!isLeaf(node)){
            fila.push(node->left);
            fila.push(node->right);
        }

        else
            leafParents->push(node);
    }

    return leafParents;
}

// Printa a arvore em largura
// O(n log(n))
// O código percorre a arvore inteira.
void Tree::printLargura(){
    NodeQueue fila;
    fila.push(root);

    while(!fila.isEmpty()){
        Node* node = fila.get();
        fila.pop();

        if(node != nullptr){
            fila.push(node->left);
            fila.push(node->right);

            std::cout << node->key << " ";
        }
    }
}

// Busca binária do nó folha que possui o menor valor de chave.
// O(log(n))
// O percurso do código tem como nó máximo a altura da arvore.
Node* Tree::minLeaf(Node* node){
    if(node != nullptr){
        if(!isLeaf(node)){
            if(node->left->key < node->right->key)
                return minLeaf(node->left);
            else
                return minLeaf(node->right);
        }
    }

    return node;
}