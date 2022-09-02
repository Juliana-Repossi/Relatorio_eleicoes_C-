#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include "Data.h"
#include "Tokenizer.h"
#include "StringUtils.h"

using namespace std;
using namespace cpp_util;

class Pessoa
{
  private: 
    string nome;
	  string sexo;
	  Data nascimento;
	  int idade;

  public:
   
    Pessoa(string nome, string sexo, Data nascimento, int idade);
    
	  //Data idade - data para calcular a idade no dia passado
	  Pessoa(string nome, string sexo, Data nascimento, const string& dataIdade);

    //gets and setts
    //faz sentido a candidato ser amiga da pessoa
    friend class Candidato;

    //imprimir 
    void print()const;

    //Calcula a idade da pessoa no dia da data passada
    int calculaIdade(const string& dataIdade, const Data& nascimento);

};

#endif