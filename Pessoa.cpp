#include "Pessoa.h"

Pessoa::Pessoa(string nome, string sexo, Data nascimento, int idade): nascimento(nascimento.dia,nascimento.mes,nascimento.ano)
{
  this->nome = nome;
  this->sexo = sexo;
	this->idade = idade;  
}
    
Pessoa::Pessoa(string nome, string sexo, Data nascimento, const string& dataIdade):nascimento(nascimento.dia,nascimento.mes,nascimento.ano)
{
  this->nome = nome;
	this->sexo = sexo;
	//calcular a idade
	this->idade = calculaIdade(dataIdade, nascimento);	  
}

void Pessoa::print()const
{
  cout << "Pessoa [nome=" << nome << ", sexo=" << sexo << ", nascimento=";
  nascimento.print();
  cout << ", idade=" << idade << "]";
}

int Pessoa::calculaIdade(const string& dataIdade, const Data& nascimento)
{

  //Separando a string data com o utilitário do prof Vitor
  //Separar a dataIdade pelos marcadores de barra;
  Tokenizer separar(dataIdade,'/');
  vector<string> data = separar.remaining();

	int dia = stoi(data[0]);
	int mes = stoi(data[1]);
	int ano = stoi(data[2]);

  //calcular a idade 
	int idade = ano - nascimento.ano;
		
	if(mes > nascimento.mes)
	{
		//já fez aniversário
		return idade;
	}
	else if (mes == nascimento.mes)
	{
		if(dia >= nascimento.dia)
		{
			//já fez aniversário
			return idade;
		}
	}
	return idade - 1;
}

