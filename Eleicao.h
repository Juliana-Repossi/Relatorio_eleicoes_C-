#ifndef ELEICAO_H
#define ELEICAO_H

#include <iomanip>
#include "Partido.h"
#include "NumberUtils.h"

using namespace std;

class Eleicao
{
  private:
    int qtdEleitos;
  	vector<Candidato*> candidatos;
  	vector<Candidato*> eleitos;
  	vector<Partido*> partidos;
  	int qtdVotosNominais;
    int qtdVotosLegenda;
  	int qtdVotosValidos;
  	int qtdMulheresEleitas;
    int qtdHomensEleitos;

  public:

    Eleicao(vector<Candidato*>& candidatos, vector<Partido*>& partidos);

    int getQtdEleitos()const;

    void afiliaCandidatosPartidos();

    void processaEleicao();

    void imprimeListaEleitos();

    void imprimeTopVotados(int n);

    void imprimePrejudicadosPeloSistemaProporcional();

    void imprimeBeneficiadosPeloSistemaProporcional();

    void imprimeEstatisticasPartidos();
    
    void imprimePesoVotoLegenda();

    void imprimeMelhorPiorColocadoPartido();

    void imprimePorcentagemEleitosFaixaEtaria();

    void imprimePorcentagemEleitosSexo();

    void imprimePorcentagemRelacaoVotos();    
};
#endif