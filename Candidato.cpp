#include "Candidato.h"

Candidato::Candidato(string nome, string sexo, Data nascimento, const string& dataEleicao, string nomeUrna, int numero, int qtdVotos, string situacao, int numPartido): Pessoa(nome,sexo,nascimento,dataEleicao)
{
  this->nomeUrna = nomeUrna;
	this->numero = numero;
	this->qtdVotos = qtdVotos;
	this->situacao = situacao;
	this->numPartido = numPartido; 
}

int Candidato::getNumPartido()const
{
  return this->numPartido;
}
int Candidato::getQtdVotos()const
{
  return this->qtdVotos;
}
void* Candidato::getPartido()
{
  return this->partido;
}
const string& Candidato::getSituacao()const
{
  return this->situacao;
}
const string& Candidato::getSexo()const
{
  return this->sexo;  
}
const string& Candidato::getNomeUrna()const
{
  return this->nomeUrna;
}
int Candidato::getNumero()const
{
  return this->numero;
}
int Candidato::getIdade()const
{
  return this->idade;
}
void Candidato::setPartido(void *partido)
{
  this->partido = partido;
}
void Candidato::setSiglaPartido(string sigla)
{
  this->siglaPartido=sigla;
}

void Candidato::print()const
{
  string voto = "voto";
		
		if(qtdVotos > 1)
		{
			voto +="s";	
		}

	cout << this->nome << " / " << nomeUrna << " (" << siglaPartido << ", " << qtdVotos << " " << voto << ")";
}

void Candidato::recebeCandidatos(vector<Candidato*>& lista,const string& arquivo, const string& dataEleicao)
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
  //vai auxiliar na comparação
  string valido("Válido");
	//le cabeçalho do arquivo
	getline(in,line);

  //ler informações até o fim do arq			
	while(getline(in,line))
	{
	  //recortar nas virgulas
    Tokenizer separar(line,',');
		vector<string> vetor = separar.remaining();
		int numero = stoi(vetor[0]);
		int qtdVotos = stoi(vetor[1]);	
		string situacao = vetor[2];
		string nome = vetor[3];
		string nomeUrna = vetor[4];
		string sexo = vetor[5];
    string dataNascimento = vetor[6];
    
		//separando a data
    Tokenizer separaData(dataNascimento,'/');
    vector<string> data = separaData.remaining();
  
		int dia = stoi(data[0]);
		int mes = stoi(data[1]);
		int ano = stoi(data[2]);
    
		string destino = vetor[7];
		int numPartido = stoi(vetor[8]);
   
		//só destinos marcados como válido serão considerados para o armazenamento
    if(destino.compare(valido)==0)
    {
      Data nascimento(dia,mes,ano);
			//alocando o candidato e adiciona na lista			
      lista.push_back(new Candidato(nome, sexo, nascimento, dataEleicao, nomeUrna, numero, qtdVotos, situacao, numPartido));
    }
	}			
}

//metodo para auxiliar na comparação em ordenação
bool Candidato::comparaCandidatos(const Candidato *candidato1, const Candidato *candidato2) 
{
  if (candidato1->qtdVotos == candidato2->qtdVotos)
  {
	  return candidato1->idade > candidato2->idade;
  }
  else
  {
  	return candidato1->qtdVotos > candidato2->qtdVotos;
  }
}

void Candidato::liberaCandidatos(vector<Candidato*>& listaCandidatos)
{
  for(Candidato *candidato: listaCandidatos)
  {    
    delete candidato;
  }
  listaCandidatos.clear();
}