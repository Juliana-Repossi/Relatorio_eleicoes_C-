#include "Partido.h"

Partido::Partido(string nome, int numero, int votoLegenda, string sigla)
{
  this->nome = nome;
	this->numero = numero;
	this->votoLegenda = votoLegenda;
	this->sigla = sigla;  
  this->votoNominal = 0;
	this->qtdEleitos=0;
}

int Partido::getNumero()const
{
  return this->numero;  
}
string Partido::getSigla()const
{
  return this->sigla;
}
int Partido::getVotoLegenda()const
{
  return this->votoLegenda;
}
int Partido::getVotoNominal()const
{
  return this->votoNominal;
}
const vector<Candidato*>& Partido::getCandidatos() const
{
  return this->candidatos;
}
void Partido::setAddVotoNominal(int votoNominal)
{
		this->votoNominal = this->votoNominal + votoNominal;
}
void Partido::setAddQtdEleitos(int qtdEleitos)
{
	this->qtdEleitos = this->qtdEleitos + qtdEleitos;
}
void Partido::addCandidato(Candidato *candidato) 
{
	this->candidatos.push_back(candidato);
}

void Partido::print()const
{
  string voto = " voto";
	string nominal = " nominal";
	string candidatoEleito = " candidato eleito";
		
	if(votoNominal > 1)
	{
		nominal = " nominais";
		voto += "s"; 
	}
	else if (votoLegenda + votoNominal > 1)
	{
		voto += "s"; 
	}
  if (qtdEleitos > 1)
  {
    candidatoEleito = " candidatos eleitos";
	}
		
	cout << sigla + " - " << numero << ", " << (votoLegenda+votoNominal) << voto << " (" << votoNominal << nominal << " e " << votoLegenda << " de legenda), " << qtdEleitos << candidatoEleito;
  
}

void Partido::recebePartidos(vector<Partido*>& lista, const string& arquivo)
{
  ifstream in(arquivo);
  if (! in.good()) 
  {
    in.close();
    cout << "Falha na abertura do arquivo:" << arquivo;
    //tentei fazer com exceções, mas não tava dando certo
    //e devido ao num de atividades entreguei assim
	  exit(1);
  }

  string line;
	//le cabeçalho do arquivo
	getline(in,line);

	//ler informações até o fim do arq			
	while(getline(in,line))
	{
		//recortar nas virgulas
    Tokenizer separar(line,',');
		vector<string> vetor = separar.remaining();
		
		int numero = stoi(vetor[0]);
		int votoLegenda = stoi(vetor[1]);	
		string nome = vetor[2];
		string sigla = vetor[3];
															
		//alocando o partido e adicionando na lista
		lista.push_back(new Partido(nome, numero, votoLegenda, sigla));
	}			
}

void Partido::ordenaCandidatosPartidos()
{
  sort(this->candidatos.begin(),this->candidatos.end(),Candidato::comparaCandidatos);  
}

//comparador
bool Partido::comparaPartido(const Partido *partido1, const Partido *partido2) 
{
  int VotoPartido1 = partido1->votoLegenda+partido1->votoNominal;
  int VotoPartido2 = partido2->votoLegenda+partido2->votoNominal;
  
  if( VotoPartido1 == VotoPartido2 )
	{
		return partido1->numero < partido2->numero;
	}
	else
	{
		return VotoPartido1 > VotoPartido2;
	}
}	

bool Partido::comparaVotoLegenda(const Partido *partido,const Partido *outroPartido)
{
	if(partido->votoLegenda == outroPartido->votoLegenda)
	{
		if(partido->votoNominal == outroPartido->votoLegenda)
		{
			return partido->numero < outroPartido->numero;
		}
		else
		{
			return partido->votoNominal > outroPartido->votoNominal;
		}
	}
	return  partido->votoLegenda > outroPartido->votoLegenda;
}	

bool Partido::comparaVotoNominalUmCandidato(const Partido *partido,const Partido *outroPartido)
{		
	if(partido->votoNominal == 0 && outroPartido->votoNominal == 0)
	{
		//garantir ordenação estável
		return true;
	}
	else if(outroPartido->votoNominal == 0)
	{
		return true;
	}
	else if(partido->votoNominal == 0)
	{
		return false;
	}
	else
	{
		if(partido->candidatos[0]->getQtdVotos() == outroPartido->candidatos[0]->getQtdVotos())
		{
			return partido->getNumero() < outroPartido->getNumero();
		}
		return partido->candidatos[0]->getQtdVotos() >outroPartido->candidatos[0]->getQtdVotos();
	}	
}	

void Partido::liberaPartidos(vector<Partido*>& listaPartidos)
{
  for(Partido *partido: listaPartidos)
  {    
    delete partido;
  }
  listaPartidos.clear();
}