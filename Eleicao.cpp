#include "Eleicao.h"

Eleicao::Eleicao(vector<Candidato*>& candidatos, vector<Partido*>& partidos)
{
	this->candidatos = candidatos;
	this->partidos = partidos;
  this->qtdEleitos = 0;
  this->qtdVotosNominais = 0;
  this->qtdVotosLegenda= 0;
  this->qtdVotosValidos= 0;
  this->qtdMulheresEleitas= 0;
  this->qtdHomensEleitos= 0;
}

int Eleicao::getQtdEleitos()const
{
  return this->qtdEleitos;
}

void Eleicao::afiliaCandidatosPartidos()
{
  int numPartido = 0;
  Partido *partido;
		
	for(Candidato *candidato : this->candidatos)
	{
		//aproveitando que candidatos com o mesmo partido estão juntos
		//ganha eficiência, sem fazer disso uma regra
		if(numPartido != candidato->getNumPartido())
		{
			//procura o partido do afiliado
			for(Partido *buscaPartido: this->partidos)
			{
				if(buscaPartido->getNumero() == candidato->getNumPartido())
				{
					//achou o partido do candidato
          //usei ponteiro pq referência não pode ser mudada
					partido = buscaPartido;
					numPartido = buscaPartido->getNumero();
					break;
				}
			}
		}
		//afilia
		candidato->setPartido(partido);
    candidato->setSiglaPartido(partido->getSigla());
		partido->addCandidato(candidato);    
  }
}

void Eleicao::processaEleicao()
{
  for(Candidato *candidato : this->candidatos)
	{
		this->qtdVotosNominais += candidato->getQtdVotos(); 
			
		//votos nominais no partido respectivo
		((Partido*)candidato->getPartido())->setAddVotoNominal(candidato->getQtdVotos());
		string Eleito("Eleito");
    
    if( Eleito.compare(candidato->getSituacao())== 0)
		{
			this->qtdEleitos ++;
			this->eleitos.push_back(candidato);
				
			//quantidade de eleitos por partido
			((Partido*)candidato->getPartido())->setAddQtdEleitos(1);

      string fem("F");
      string mas("M");
			if(fem.compare(candidato->getSexo())==0)
			{
				this->qtdMulheresEleitas ++;
			}
			else if(mas.compare(candidato->getSexo())==0)
			{
				this->qtdHomensEleitos ++;
			}
		}			
	}
		
	for(Partido *partido : this->partidos) 
  {
		this->qtdVotosLegenda += partido->getVotoLegenda();
	}
		
	this->qtdVotosValidos = this->qtdVotosLegenda + this->qtdVotosNominais;		
}

void Eleicao::imprimeListaEleitos()
{	
	int i=0;		
	//ordenar lista antes de imprimir 
  sort(this->eleitos.begin(),this->eleitos.end(),Candidato::comparaCandidatos);
		
	for(Candidato *eleito: this->eleitos)
  {
		cout << ++i << " - ";
    eleito->print();
    cout<<endl;
	}
}

void Eleicao::imprimeTopVotados(int n)
{
	//ordenar lista antes de imprimir 
	sort(this->candidatos.begin(),this->candidatos.end(),Candidato::comparaCandidatos);

  for(int i=0; i<n; i++)
  {
		cout << i+1 << " - ";
    this->candidatos[i]->print();
    cout<<endl;
	}
}

void Eleicao::imprimePrejudicadosPeloSistemaProporcional()
{
	//ordenar lista antes de imprimir
  sort(this->candidatos.begin(),this->candidatos.end(),Candidato::comparaCandidatos);

  string nEleito("Não eleito");
  string suplente("Suplente");
  
	for(int i=0; i<this->qtdEleitos; i++)
	{
		string situacao = this->candidatos[i]->getSituacao();
					
		if(situacao.compare(nEleito)==0 || situacao.compare(suplente)==0)
		{
			cout << i+1 << " - ";
      this->candidatos[i]->print();
      cout <<endl;
		}				
	}
}

void Eleicao::imprimeBeneficiadosPeloSistemaProporcional()
{
	//ordenar lista antes de imprimir
	sort(this->candidatos.begin(), this->candidatos.end(),Candidato::comparaCandidatos);

  //mudei a execução em relação a impplementação java
	string eleito ("Eleito");
  
	for(long unsigned int i = this->qtdEleitos; i < this->candidatos.size() ; i++ )
  {
    if(eleito.compare(this->candidatos[i]->getSituacao()) == 0)
    {
      //foi beneficiado pelo sistema proporcional
	    cout << i+1 << " - ";
      this->candidatos[i]->print();
      cout << endl;
    }
  }
}

void Eleicao::imprimeEstatisticasPartidos()
{
	//ordena lista de partidos
	sort(this->partidos.begin(),this->partidos.end(),Partido::comparaPartido);
		
	int i=0;
		
	for(Partido *partido: this->partidos)
	{
		cout << ++i << " - ";
    partido->print();
    cout << endl;
	}	
}

void Eleicao::imprimePesoVotoLegenda()
{
	//ordenar partidos
	sort(this->partidos.begin(),this->partidos.end(),Partido::comparaVotoLegenda);
		
	int i=0;
	double percentual = 0;
  
	for(Partido *partido: this->partidos)
	{
		if(partido->getVotoLegenda() + partido->getVotoNominal() != 0)
		{
			percentual = (partido->getVotoLegenda()*100.00)/(partido->getVotoLegenda() + partido->getVotoNominal());
		}
		else
		{
			percentual = 0;
		}
			
		cout << ++i << " - " << partido->getSigla() << " - " << partido->getNumero() << ", " << partido->getVotoLegenda() << " voto";
			
		if (partido->getVotoLegenda()>1)
		{
			cout << "s";
		}
			
		cout << " de legenda ";
			
		if(percentual == 0)
		{
			cout << "(proporção não calculada, 0 voto no partido)" << endl;
		}
		else
		{
      //usei esse por conta das casas decimais
			cout << "(" << formatDoubleCurrency(percentual, LOCALE_PT_BR) << "% do total do partido)"<< endl;
		}			
	}		
}

void Eleicao::imprimeMelhorPiorColocadoPartido()
{  
  //ordenar lista de candidados de cada partido
  for(Partido *partido: this->partidos )
	{  
    //por conta da modularização, função para ordenar dentro do TAD partido
    partido->ordenaCandidatosPartidos();
  }
	
  //ordena partidos 	
	sort(this->partidos.begin(),this->partidos.end(),Partido::comparaVotoNominalUmCandidato);
		
	int i=0;
	
	Candidato *primeiro, *ultimo;
		
	for(Partido *partido: this->partidos)
	{
		if(partido->getVotoNominal() > 0)
		{
			cout << ++i << " - " << partido->getSigla() << " - " << partido->getNumero() << ", ";
								
			//pegar o primeiro / pegar o ultimo
			primeiro = (partido->getCandidatos()).front();
			ultimo = (partido->getCandidatos()).back();
				
			cout << primeiro->getNomeUrna() << " (" << primeiro->getNumero() << ", " << primeiro->getQtdVotos() << " voto";
				
			if(primeiro->getQtdVotos() > 1)
			{
				cout << "s";
			}
			
			cout << ") / " << ultimo->getNomeUrna() << " (" << ultimo->getNumero() << ", " << ultimo->getQtdVotos() << " voto";
				
			if(ultimo->getQtdVotos() > 1)
			{
				cout << "s";
			}
				cout << ")" << endl;;
		}
	}	
}

void Eleicao::imprimePorcentagemEleitosFaixaEtaria()
{
	int faixaMenor30, faixa30, faixa40, faixa50, faixa60Mais;
	faixaMenor30 = faixa30 = faixa40 = faixa50 = faixa60Mais = 0;

  for(Candidato *candidato: this->eleitos)
	{
		int idade = candidato->getIdade();
		
		if(idade<30){faixaMenor30++;}
			else if(idade<40){faixa30++;}
				else if(idade<50){faixa40++;}
					else if(idade<60){faixa50++;}
						else {faixa60Mais++;}
	}
		
	double percentual = (faixaMenor30 * 100.0)/this->qtdEleitos;
	cout << "      Idade < 30: " << faixaMenor30 << " (" << formatDoubleCurrency(percentual, LOCALE_PT_BR) << "%)"<<endl;
		
	percentual = (faixa30 * 100.0)/this->qtdEleitos;
	cout << "30 <= Idade < 40: " << faixa30 << " (" << formatDoubleCurrency(percentual, LOCALE_PT_BR) << "%)"<<endl;
		
	percentual = (faixa40 * 100.0)/this->qtdEleitos;
	cout << "40 <= Idade < 50: " << faixa40 << " (" << formatDoubleCurrency(percentual, LOCALE_PT_BR) << "%)" << endl;

	percentual = (faixa50 * 100.0)/this->qtdEleitos;
	cout << "50 <= Idade < 60: " << faixa50 << " (" << formatDoubleCurrency(percentual, LOCALE_PT_BR) << "%)" << endl;
		
	percentual = (faixa60Mais * 100.0)/this->qtdEleitos;
	cout << "60 <= Idade     : " << faixa60Mais << " (" << formatDoubleCurrency(percentual, LOCALE_PT_BR) << "%)\n" << endl;		
}

void Eleicao::imprimePorcentagemEleitosSexo()
{
		double percentual = (this->qtdMulheresEleitas*100.0)/this->qtdEleitos;
	  cout << "Feminino: " << this->qtdMulheresEleitas << " (" << formatDoubleCurrency(percentual, LOCALE_PT_BR) << "%)"<< endl;
		
		percentual = (this->qtdHomensEleitos*100.0)/this->qtdEleitos;
		cout << "Masculino: " << this->qtdHomensEleitos << " (" << formatDoubleCurrency(percentual, LOCALE_PT_BR) << "%)" << endl;
	}

void Eleicao::imprimePorcentagemRelacaoVotos() 
{
	cout << "Total de votos válidos: " << this->qtdVotosValidos << endl;
		
	double percentual = (this->qtdVotosNominais*100.0)/this->qtdVotosValidos;
	cout << "Total de votos nominais: " << this->qtdVotosNominais << " (" << formatDoubleCurrency(percentual, LOCALE_PT_BR) << "%)"<< endl;
		
	percentual = (this->qtdVotosLegenda*100.0)/this->qtdVotosValidos;
	cout << "Total de votos de legenda: " << this->qtdVotosLegenda << " (" << formatDoubleCurrency(percentual, LOCALE_PT_BR) << "%)" << endl;
}