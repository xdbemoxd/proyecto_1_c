#ifndef NODO_H_
#define NODO_H_ 

#include <iostream>

using namespace std;

template <class Tipo>
class Nodo{
	private:
		Tipo Elemento;
		Nodo<Tipo> *Siguiente;
	public:
		//Constructores
		Nodo();
		void ModiElemento(Tipo Nuevo);
		Tipo ObtElemento();
		Nodo<Tipo>* ObtProximo();
		void ModiSiguiente(Nodo<Tipo>* Proximo);
};

template <class Tipo>
Nodo<Tipo>::Nodo(){
	
	this->Siguiente=NULL;
}

template <class Tipo>
void Nodo<Tipo>::ModiElemento(Tipo Nuevo){
	this->Elemento=Nuevo;
}

template <class Tipo>
Tipo Nodo<Tipo>::ObtElemento(){
	return (this->Elemento);
}

template <class Tipo>
Nodo<Tipo>* Nodo<Tipo>::ObtProximo(){
	return (this->Siguiente);
}

template <class Tipo>
void Nodo<Tipo>::ModiSiguiente(Nodo<Tipo>* Proximo){
	this->Siguiente=Proximo;
}


#endif