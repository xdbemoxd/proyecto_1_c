#ifndef LISTA_H_
#define LISTA_H_

#include <iostream>
#include "Nodo.h"

using namespace std;

template<class Tipo>
class Lista : public Nodo<Tipo>{
	private:
		int Longitud;
		Nodo<Tipo>* Primero;
		Nodo<Tipo>* Ultimo;
		void ErrorPosicion();
	public:
		Lista();
		bool EsVacia();
		int Tamano();
		void Insertar(Tipo Ele,int Posicion);
		void FirstIn(Tipo Ele);
		void LastIn(Tipo Ele);
		Tipo Consultar(int Posicion);
		void Eliminar(int Posicion);
		int Esta(Tipo Ele);
		void VerLista();
		int EleRepetido(Tipo Ele);
		void Vaciar();
};

template<class Tipo>
Lista<Tipo>::Lista()
{

	this->Primero=NULL;
	this->Ultimo=NULL;
	this->Longitud=0;
}

template<class Tipo>
bool Lista<Tipo>::EsVacia()
{

	bool x=false;

	if (this->Longitud==0)
	{
		x=true;
	}

	return (x);
}

template<class Tipo>
int Lista<Tipo>::Tamano()
{

	return (this->Longitud);
}

template<class Tipo>
void Lista<Tipo>::Insertar(Tipo Ele,int Posicion)
{

	Nodo<Tipo> *Actual=new Nodo<Tipo>(),*Nuevo=new Nodo<Tipo>();


	Actual=this->Primero;
	Nuevo->ModiElemento(Ele);

	if(Posicion == 1)
	{
		Nuevo->ModiSiguiente(Actual);
		this->Primero=Nuevo;
		this->Longitud=this->Longitud+1;
	
	}else
	{
		
		if(Posicion <= this->Longitud+1)
		{
			
			while(Posicion>2)
			{
				Actual=Actual->ObtProximo();
				Posicion--;
			}
			
			Nuevo->ModiSiguiente(Actual->ObtProximo());
			Actual->ModiSiguiente(Nuevo);
			this->Longitud=this->Longitud+1;
			
			if (Actual==this->Ultimo)
			{
				this->Ultimo=Nuevo;
			}

		}else
		{
			this->ErrorPosicion();
		}
	}
}

template<class Tipo>
Tipo Lista<Tipo>::Consultar(int Posicion)
{

	Nodo<Tipo> *Actual=new Nodo<Tipo>();
	
	if (Posicion>this->Longitud || Posicion<=0)
	{
		this->ErrorPosicion();

	}else
	{
		Actual=this->Primero;
		
		while(Posicion>1)
		{
			Actual=Actual->ObtProximo();
			Posicion--;
		}
	}
	
	return(Actual->ObtElemento());
}

template<class Tipo>
void Lista<Tipo>::Eliminar(int Posicion)
{
	
	Nodo<Tipo> *Actual=new Nodo<Tipo>(),*Anterior=new Nodo<Tipo>();

	if(Posicion>this->Longitud)
	{
		this->ErrorPosicion();
	
	}else
	{
		Actual=this->Primero;
		
		if(Posicion==1)
		{
			Anterior=Actual->ObtProximo();
			this->Primero=Anterior;
			Actual->ModiSiguiente(NULL);
		
		}else
		{
			while(Posicion>1)
			{
				Anterior=Actual;
				Actual=Actual->ObtProximo();
				Posicion--;
			}
			
			Anterior->ModiSiguiente(Actual->ObtProximo());
			Actual->ModiSiguiente(NULL);
			
			if (Actual == this->Ultimo)
			{
				this->Ultimo=Anterior;
			}
		}
		
		this->Longitud=this->Longitud-1;
		
		delete Actual;
	}
}

template<class Tipo>
int Lista<Tipo>::Esta(Tipo Ele)
{

	Nodo<Tipo> *Actual=new Nodo<Tipo>();
	int i=1;

	Actual=this->Primero;

	while(Actual->ObtElemento()!=Ele && i<=this->Longitud)
	{
		Actual=Actual->ObtProximo();
		i++;
	}

	if(i>this->Longitud)
	{
		i=-1;
	}

	return i;
}

template <class Tipo>
void Lista<Tipo>::ErrorPosicion()
{
	cout<<"Error al ingresar la posicion, verifique si la posicion ingresada es un numero < 0 o si es mayor "<<this->Longitud<<endl;
}

template <class Tipo>
void Lista<Tipo>::VerLista()
{
	Nodo<Tipo> *Actual=new Nodo<Tipo>();

	Actual=this->Primero;

	while(Actual!=NULL)
	{
		cout<<Actual->ObtElemento()<<endl;
		Actual=Actual->ObtProximo();
	}
}

template <class Tipo>
void Lista<Tipo>::FirstIn(Tipo Ele)
{
	Nodo<Tipo> *Nuevo=new Nodo<Tipo>();

	Nuevo->ModiElemento(Ele);
	this->Primero=Nuevo;
	this->Ultimo=Nuevo;

	this->Longitud=this->Longitud+1;
}

template <class Tipo>
void Lista<Tipo>::LastIn(Tipo Ele)
{
	Nodo<Tipo> *Actual=new Nodo<Tipo>(),*Nuevo=new Nodo<Tipo>();

	Actual=this->Ultimo;
	Nuevo->ModiElemento(Ele);

	Actual->ModiSiguiente(Nuevo);
	this->Ultimo=Nuevo;

	this->Longitud=this->Longitud+1;
}

template <class Tipo>
int Lista<Tipo>::EleRepetido(Tipo Ele)
{
	Nodo<Tipo> *Actual=new Nodo<Tipo>();
	int cont=0;

	Actual=this->Primero;
	while(Actual!=NULL)
	{
		if(Actual->ObtElemento() == Ele)
		{
			cont++;
		}
		Actual=Actual->ObtProximo();
	}	
	return cont;
}

template <class Tipo>
void Lista<Tipo>::Vaciar()
{
	Nodo<Tipo> *Actual=new Nodo<Tipo>(),*Siguiente=new Nodo<Tipo>();

	Actual=this->Primero;
	this->Primero=NULL;
	this->Ultimo=NULL;
	this->Longitud=0;
	Siguiente=Actual->ObtProximo();

	while(Actual!=NULL)
	{
		Actual->ModiSiguiente(NULL);
		delete Actual;
		Actual=Siguiente;
		Siguiente=Siguiente->ObtProximo();
	}
}
#endif