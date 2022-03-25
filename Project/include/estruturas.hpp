#ifndef ESTURUTRAS_H
#define ESTRUTURAS_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

//Se parece com o TAD "Entidade", mas possui um atributo que informa de qual fita a entidade veio. 
struct ElementosHeap{
    int nAcessos;
    int Fita;
    string URL;
};

//Representa cada entidade lida.
struct Entidade
{
    int n;
    string URL;
};

//Implementa uma estrutura do tipo Pilha alocada estáticamente. O parâmetro MAXTAM pode ser alterado diretamente nessa parte do código. 
class PilhaArranjo {
    public: 

        PilhaArranjo();
        void Empilha(Entidade elemento);
        Entidade Desempilha();
        void Limpa();
        int getTopo();

    private:
        int topo;
        int tamanho;
        static const int MAXTAM = 50;
        Entidade elementos[MAXTAM];
  
};

//Implementa um Heap, cujo fim é intercalar as rodadas, desempilhando o maior valor disponível. 
class Heap
{
private:
    ElementosHeap* elementos;
    int size; 
    int posicoesVazias;
    PilhaArranjo* pilhas;   
    void Constroi(int n);
    void Refaz(int Esq, int Dir);

public:
    
    Heap(int fitas, PilhaArranjo* _pilhas);
    ~Heap();  
    void HeapInicial();
    void Intercala(string output);
    bool HeapVazio();
};



void LeFitas(PilhaArranjo* pilhas, int nFitas, int nSites);
void Quicksort(Entidade* entidades, int begin, int end);
void GeraRodada(int num, int ID, ifstream &inputfile);

#endif