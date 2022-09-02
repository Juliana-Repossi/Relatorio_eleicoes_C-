#ifndef DATA_H
#define DATA_H

#include <iostream>
using namespace std;

class Data
{
  private:
    int dia;
    int mes;
    int ano;

  public:
    //construtor
    Data(int dia, int mes, int ano);

    //não precisamos de declarar gets e sets
    //vamos declarar a classe pessoa como amiga da data
    friend class Pessoa;
   
    //imprimir a data
    void print()const;
};
#endif