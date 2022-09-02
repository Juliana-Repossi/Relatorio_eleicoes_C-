#include "Eleicao.h"

using namespace std;

static void relatorio1 (Eleicao& eleicao)
{
		cout << "Número de vagas: " << eleicao.getQtdEleitos() << endl << endl;
}

static void relatorio2 (Eleicao& eleicao)
{
	cout << "Vereadores eleitos:"<< endl;
	eleicao.imprimeListaEleitos();
	cout << endl;	
}

static void relatorio3 (Eleicao& eleicao)
{
	cout <<"Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):"<<endl;
	eleicao.imprimeTopVotados(eleicao.getQtdEleitos());		
  cout << endl;	
}

static void relatorio4 (Eleicao& eleicao)
{
	cout <<"Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:" << endl << "(com sua posição no ranking de mais votados)" << endl;
	eleicao.imprimePrejudicadosPeloSistemaProporcional();	
	cout << endl;	
}

static void relatorio5 (Eleicao& eleicao)
{
	cout << "Eleitos, que se beneficiaram do sistema proporcional:" << endl << "(com sua posição no ranking de mais votados)" << endl;
	eleicao.imprimeBeneficiadosPeloSistemaProporcional();
	cout << endl;	
}

static void relatorio6 (Eleicao& eleicao)
{
	cout << "Votação dos partidos e número de candidatos eleitos:" << endl;
	eleicao.imprimeEstatisticasPartidos();
	cout << endl;	
}

static void relatorio7 (Eleicao& eleicao)
{
	cout << "Votação dos partidos (apenas votos de legenda):" << endl;
	eleicao.imprimePesoVotoLegenda();
	cout << endl;		
}
		
static void relatorio8 (Eleicao& eleicao)
{
	cout << "Primeiro e último colocados de cada partido:" << endl;
	eleicao.imprimeMelhorPiorColocadoPartido();
	cout << endl;		
}

static void relatorio9 (Eleicao& eleicao)
{
	cout << "Eleitos, por faixa etária (na data da eleição):" << endl;
	eleicao.imprimePorcentagemEleitosFaixaEtaria();
}

static void relatorio10 (Eleicao& eleicao)
{
	cout << "Eleitos, por sexo:" << endl;
	eleicao.imprimePorcentagemEleitosSexo();	
	cout << endl;
}

static void relatorio11 (Eleicao& eleicao)
{
	eleicao.imprimePorcentagemRelacaoVotos();
  cout << endl;
}


int main(int argc , char **argv)
{ 
  if(argc != 4)
  {
    cout << "Erro na passagem de argumentos por linha de comando"<< endl;
    exit(2);      
    }
  
  //lista de candidatos
  vector<Candidato*> listaCandidatos;
  //abrir o arquivo e ler as informações dos candidatos
  Candidato::recebeCandidatos(listaCandidatos,argv[1], argv[3]);
  
  //lista de partidos
  vector<Partido*> listaPartidos;    
  //abrir o arquivo e ler as informações dos partidos
  Partido::recebePartidos(listaPartidos,argv[2]);

  //instanciar eleição
	Eleicao eleicao2020(listaCandidatos, listaPartidos);
  
  //afiliar/ligar partidos aos candidatos e vice-versa
	eleicao2020.afiliaCandidatosPartidos();

  //preencher os demais dados sobre as eleições de 2020
	eleicao2020.processaEleicao();
 
  //1 - Numero de vagas
	relatorio1 (eleicao2020);

  //2 - Candidatos eleitos
	relatorio2 (eleicao2020);

	//3 - Candidatos mais votados dentro do número de vagas
  relatorio3 (eleicao2020);
	
  //4 - Candidatos não eleitos e que seriam eleitos se a votação fosse majoritária
	relatorio4 (eleicao2020);

	//5 - Candidatos eleitos no sistema proporcional vigente, e que não seriam eleitos se a votação fosse majoritária;
	relatorio5 (eleicao2020);
		
  //6 - Votos totalizados por partido e número de candidatos eleitos
  relatorio6(eleicao2020);

	//7 - Votos de legenda (com a porcentagem destes votos frente ao total de votos no partido);
	relatorio7 (eleicao2020);
		
	//8 - Primeiro e último colocados de cada partido.
	relatorio8 (eleicao2020);

	//9 - Distribuição de eleitos por faixa etária, considerando a idade do candidato no dia da eleição;
	relatorio9 (eleicao2020);
	
	//10 - Distribuição de eleitos por sexo;
	relatorio10 (eleicao2020);
  
	//11 - Total de votos, total de votos nominais e total de votos de legenda.
	relatorio11 (eleicao2020);

  //liberar as listas de personagens alocados dinamicamente
  Candidato::liberaCandidatos(listaCandidatos);
  Partido::liberaPartidos(listaPartidos);
}

