#ifndef PARTIDO_H
#define PARTIDO_H

#include <algorithm>
#include "Candidato.h"

class Partido
{
  private:
    string nome;
	  int numero;
	  int votoLegenda;
	  string sigla;
	  int votoNominal;
	  vector<Candidato*> candidatos;
	  int qtdEleitos;
	
  public:

    Partido(string nome, int numero, int votoLegenda, string sigla);

    //gets and seters
    int getNumero()const;
    string getSigla()const;
    int getVotoLegenda()const;
    int getVotoNominal()const;
    const vector<Candidato*>& getCandidatos()const;

    void setAddVotoNominal(int votoNominal);
    void setAddQtdEleitos(int qtdEleitos);
    void addCandidato(Candidato *candidato);

    void print()const;

    static void recebePartidos(vector<Partido*>& lista, const string& arquivo);
    
    void ordenaCandidatosPartidos();

    //comparadores
    static bool comparaPartido(const Partido *partido1, const Partido *partido2);
    static bool comparaVotoLegenda(const Partido *partido, const Partido *outroPartido);
    static bool comparaVotoNominalUmCandidato(const Partido *partido, const Partido *outroPartido);

     static void liberaPartidos(vector<Partido*>& listaPartidos);
};

#endif