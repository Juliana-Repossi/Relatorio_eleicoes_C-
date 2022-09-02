#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <vector>
#include <fstream>
#include "Pessoa.h" 


using namespace std;
using namespace cpp_util;

class Candidato : public Pessoa
{
  private:
    string nomeUrna;
	  int numero;
	  int qtdVotos;
	  string situacao;
	  int numPartido;
    string siglaPartido;
	  void *partido;
    //com ponteiro devido o problema da inclusão ciclica

  public:

    //construtor
    Candidato(string nome, string sexo, Data nascimento, const string& dataEleicao, string nomeUrna, int numero, int qtdVotos, string situacao, int numPartido);

    //metodos geters e seters
    int getNumPartido()const;
    int getQtdVotos()const;
    void* getPartido();
    const string& getSituacao()const;
    const string& getSexo()const;
    const string& getNomeUrna()const;
    int getNumero()const;
    int getIdade() const;
  
    void setPartido(void *partido);
    void setSiglaPartido(string sigla);
    
    //impressão
    void print()const;

   /*
	 * Abre um arquivo e faz uma leitura formatada dos candidados
	 * aloca os mesmos em memória e retorna uma lista com todos eles, além de fechar o arquivo
	 * Obs: a data da eleição é necessária para calcular a idade do candidato
	 */
  static void recebeCandidatos(vector<Candidato*>& lista,const string& arquivo, const string& dataEleicao);

  static bool comparaCandidatos(const Candidato *candidato1, const Candidato *candidato2);

  static void liberaCandidatos(vector<Candidato*>& listaCandidatos);

};
#endif