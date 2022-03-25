#include "estruturas.hpp"

//implementação do quicksort

void swap(Entidade* a, Entidade* b){
    Entidade temp = *a;
    *a = *b;
    *b = temp;
}

int Particao(Entidade* entidades, int begin, int end){

    Entidade pivo = entidades[end];
    int i = (begin - 1);

    for (int j = begin; j <= end - 1; j++){
        if (entidades[j].n < pivo.n){
            i++;
            swap(&entidades[i], &entidades[j]);
        }
    }

    swap (&entidades[i+1], &entidades[end]);
    return (i+1);

}

void QuickSort(Entidade* entidades, int begin, int end){
    if (begin < end){
        int p = Particao(entidades, begin, end);

        QuickSort(entidades, begin, p-1);
        QuickSort(entidades, p + 1,  end);
    }
}

//implementando as rodadas
void LeRodada(Entidade* entidades, int n, ifstream &inputfile){
    string URL;
    int nAcessos;
    int i = 0;
    while(inputfile>>URL>>nAcessos){
        entidades[i].n = nAcessos;
        entidades[i].URL = URL;
        i++;
        if(i>=n){
            break;
        }
    }
}

void EscreveRodada(Entidade* entidades, int n, int ID){
    ofstream arquivo;
    int i = 0;
    string nomeArquivo = "Rodada-" + to_string(ID) + ".txt";
    arquivo.open(nomeArquivo);
    while(i < n){
        arquivo << entidades[i].URL << ' ' << entidades[i].n << "\n";
        i++;
    }
    arquivo.close();
}

void GeraRodada(int num, int ID, ifstream &inputfile){
    Entidade* entidades = new Entidade[num];
    LeRodada(entidades, num, inputfile);
    QuickSort(entidades, 0, num-1);
    EscreveRodada(entidades, num, ID);
    delete[]entidades;
}


//implementando o HEAP
Heap::Heap(int fitas, PilhaArranjo* _pilhas){
    elementos = new ElementosHeap[fitas];
    pilhas = _pilhas;
    size = fitas;
    posicoesVazias = 0;
}

Heap::~Heap(){
    delete [] elementos;
    
    size = 0;
}

void Heap::Constroi(int n){
    int Esq = n / 2 + 1;
    while (Esq > 0) { 
        Esq--;
        Refaz(Esq-1, n-1);
    }
}

void Heap::Refaz(int Esq, int Dir){
    int i, j;
    if (Esq<0) return;
    ElementosHeap x;
    i = Esq;
    j = (i * 2)+1;
    x = elementos[i];
    while (j <= Dir){
        if (j < Dir)
            if (elementos[j].nAcessos < elementos[j+1].nAcessos) j++;
        if (x.nAcessos >= elementos[j].nAcessos) break;
        elementos[i] = elementos[j];
        i = j;
        j = (i * 2)+1;
    }
    elementos[i] = x;
}

void Heap::HeapInicial(){
    int i = 0;
    for(i=0; i<size; i++){
        elementos[i].Fita = i;
        Entidade aux;
        aux = pilhas[i].Desempilha();
        elementos[i].nAcessos = aux.n;
        elementos[i].URL =  aux.URL;
    }
    
    
}

void escreveEntidadeSaida(ofstream &arquivo, ElementosHeap Entidade){
    arquivo<<Entidade.URL<<' '<<Entidade.nAcessos<<"\n";
}

void Heap::Intercala(string output){
    int i = 0;
    ElementosHeap aux;
    Entidade aux2;

    ofstream arquivo;
    arquivo.open(output);

    do
    {   
        Constroi(size);
        escreveEntidadeSaida(arquivo, elementos[0]);
        aux.Fita = elementos[0].Fita;
        aux2 = pilhas[aux.Fita].Desempilha();
        aux.nAcessos = aux2.n;
        aux.URL = aux2.URL;
        if(aux.nAcessos == -1)posicoesVazias++;
        elementos[0] = aux;    

    } while(!HeapVazio());

    arquivo.close();
}

bool Heap::HeapVazio(){
    return (posicoesVazias == size);
}

//implementando a classe PilhaArranjo

    PilhaArranjo::PilhaArranjo(){
        topo = -1;
        tamanho = 0;
    }

    void PilhaArranjo::Empilha(Entidade elemento){
        if (tamanho == MAXTAM){
            throw "A pilha está cheia!";
        }

        topo++;
        elementos[topo] = elemento;
        tamanho++;    
    }

  

    Entidade PilhaArranjo::Desempilha(){
        Entidade aux;

        if (tamanho == 0){
            aux.n = -1;
            aux.URL = "null";
            return aux;
        }
        
        aux = elementos[topo];
        topo--;
        tamanho--;
        return aux;
    }

    void LeFitas(PilhaArranjo* pilhas, int nFitas, int nSites){
        int i = 0, j = 0;
        int nAcessos;
        string URL;
        
        while(i < nFitas){
            ifstream arquivo;
            string nomeArquivo = "Rodada-" + to_string(i+1) + ".txt";
            arquivo.open(nomeArquivo);
            j = 0;

            while(j < nSites){
                Entidade aux;
                arquivo>>URL>>nAcessos;
                aux.n = nAcessos;
                aux.URL = URL;
                pilhas[i].Empilha(aux);
                j++;
            }
            arquivo.close();
            i++;
            
        }
        
    }