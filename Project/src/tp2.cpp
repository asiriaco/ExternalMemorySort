#include <stdlib.h>
#include "estruturas.hpp"

using namespace std;

int main(int argc, char** argv){
    
    string inputfile = argv[1];
    string outputfile = argv[2];
    int nFitas = atoi(argv[4]);
    int nSites = atoi(argv[3]);

    ifstream arquivo;
    arquivo.open(inputfile);

    for (int i = 0; i < nFitas; i++)
    {
        GeraRodada(nSites, i+1, arquivo);
        arquivo.ignore();
    }
    

    PilhaArranjo* pilhas = new PilhaArranjo[nFitas];
 

    LeFitas(pilhas, nFitas, nSites);
    Heap heap(nFitas, pilhas);
    heap.HeapInicial();
    heap.Intercala(outputfile);


    delete [] pilhas;
    return 0;

}