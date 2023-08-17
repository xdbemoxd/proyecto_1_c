#include <iostream>
#include <string>
#include "Lista.h"
using namespace std;

void Vivir(Lista<int>* LE,Lista<string>* LN,int N,int K,int T);
string QuitarComa(string Nombre);

int main()
{
	int cant,N,K,T,Casta;
	/*cant: es la cantidad de casos que se van a resolver, N,K,T y casta: son las pautadas por el profesor 
	en el ejercicio */
	string Nombre;
	//Nombre: utilizado para la entrada de los nombres, inicialmente vienen con ','
	char C;
	//C: caracter utilizado para omitir la entrada de "() , []", esos 3
	Lista<int>* L= new Lista<int>();
	//L: alamcena la casta de cada persona en el juego
	Lista<string>* LAux= new Lista<string>();
	//LAux: se utiliza para almacenar los nombres de los participantes
	bool Yapaso=false;
	//Yapaso:verifica que ya haya pasado por vivir, quedaba de primero el sobreviviente del juego anterior

	cin>>cant;
	//entra la cantidad de casos para el juego

	for (int i = 0; i < cant; i++)
	{
	
		cin>>N;
		cin>>K;
		cin>>T;
		cin>>C;
		//inicializando N,K y T, el C es utilizado para omitir el caracter '['
		
		while(C!=']')//condicion de parada, cuando llega a ese caracter, es porque no va a recolectar mas datos
		{
			cin>>C;

			if(C=='(')/*dada la entrada del caracter anterior, si es un '(', significa que tengo que tomar 
			los nombres y las castas, correspondientes a cada participante*/
			{
				cin>>Nombre;
				cin>>Casta;
				
				if (LAux->EsVacia())
				{
					/*verifico que la lista este vacia, para asi agregar el primer elemento con la funcion FirstIn*/
					LAux->FirstIn(Nombre);
					L->FirstIn(Casta);
				}else
				{
					/*en caso contrario agrego al ultimo con la funcion LastIn*/
					LAux->LastIn(Nombre);
					L->LastIn(Casta);
				}
			}
		}

		if (Yapaso==true)//verifico que no haya ocurrido un juego anteriormente
		{
			/*como el sobreviviente de la anterior le gusto el juego, quiere participar de nuevo, con esto lo saco*/
			LAux->Eliminar(1);
			L->Eliminar(1);
		}
		Vivir(L,LAux,N,K,T);//Funcion que decide quien va a morir y dictamina el sobreviviente
		Yapaso=true;//ya jugaron un juego anterior
	}
}
/*LE: es la lista donde estan almacenas lor orden las clases de cada participante
LN: aqui se almacenan por orden los nombre, tiene le mismo orden que la lista LE
N,K y T : son las prpuestas en el ejercicio por el profesor, decidi no cambiar el nombre por conveniencia*/
void Vivir(Lista<int>* LE,Lista<string>* LN,int N,int K,int T)
{
	int CantCasBaja,CantCasAlta,CastaBaja=N,CastaAlta=1,i,Posicion=1,CantMuertos=T,NombreRepetido=0;
	/*CantCAsBaja: es de suma importancia, gracias a ella se cambia la clase baja cuando no quedan sobrevivientes de la misma
	CantCasAlta: tiene la misma funcion de la CantCasBaja; CastaBaja: guarda la casta mas baja en ese momento, cambia de valor
	cuando no tiene poblacion; CastaAlta: funciona de la misma manera que Casta Baja; i: es un iterador, utilizado para determinar
	el valor de posicion; Posicion: turno del que le toca ser evaluado bajo las condiciones pautadas; 
	CantMuertos: cuenta la cantidad de participantes muertos antes de cambiar la prioridad de clases;
	NombreRepetido: es un contador de cuantas veces se a repetido el nombre*/
	bool MuerteCastaAlta=false,Muerte=true;
	/*MuerteCastaAlta: dictamina cual es la prioridad de muerte; Muerte: Verifica si en cada turno
	murio alguien, mas adelante sera explicado con mas detalle*/ 
	string AuxNombre="";
	//AuxNombre: aqui guarda el nombre del turno anterior, por si cae de nuevo

	CantCasBaja=LE->EleRepetido(N);
	CantCasAlta=LE->EleRepetido(1);
	// Utilizo la funcion EleRepetido, para ver cuantas personas hay de la misma casta

	while(LE->Tamano()>1)//verifico que no haya mas de un sobreviviente, en caso contrario el juego continua
	{

		while(CantCasBaja==0)
		{
			//si la cantidad personas de casta baja se acabo, esto se encarga de buscar la proxima casta mas baja 
			CastaBaja--;
			CantCasBaja=LE->EleRepetido(CastaBaja);
		}

		while(CantCasAlta==0)
		{
			//funciona igual que la anterior, pero esta lo hace con los casta alta
			CastaAlta++;
			CantCasAlta=LE->EleRepetido(CastaAlta);
		}

		//utilizada para determinar la posicion del proximo participante a evaluar
		i=K-1;
		while(i>0)
		{
			Posicion++;
			if(Posicion>LE->Tamano())
			{
				Posicion=1;
			}
			i--;
		}
		
		if (MuerteCastaAlta==true && LE->Consultar(Posicion)==CastaAlta )//Aqui se verifia que Casta tiene prioridad de muerte, si es verdad, la prioridad son los de casta alta
		{
			//si el participante actual es de casta alta, automaticamente muere
			LE->Eliminar(Posicion);
			LN->Eliminar(Posicion);
				
			Muerte=true;
			CantCasAlta=CantCasAlta-1;

		}else
		{
			//esta es muy parecida a la anterior, verifico que pertenezca a la casta con prioridad de muerte
			if (LE->Consultar(Posicion)==CastaBaja && MuerteCastaAlta==false)
			{
				//en caso de pertenecer a la casta con prioridad, elimino al participante
				LE->Eliminar(Posicion);
				LN->Eliminar(Posicion);
			
				Muerte=true;
				CantCasBaja=CantCasBaja-1;
				
			}else
			{
				//inicialice la Cadena como un espacio vacio, en caso de estar asi, simplemente la modifico cambiando su contenido
				if (AuxNombre=="")
				{
					//aqui agrego el nombre a la variable, aumento la cantidad de veces que se a repetido el nombre y actulizo muerto a falso
					AuxNombre=LN->Consultar(Posicion);
					NombreRepetido=NombreRepetido+1;
					Muerte=false;
				}else
				{	
					//en caso que el nombre se repita, verificare 2 posibles casos
					if(AuxNombre == LN->Consultar(Posicion))
					{
						//Si el nombre se repite mas de T veces el participante debe morir
						if ( NombreRepetido == T )
						{
							//con este condicional verifico a que casta pertece el fallecido
							if (LE->Consultar(Posicion)==CastaAlta)
							{

								CantCasAlta=CantCasAlta-1;
							
							}else
							{
								//en caso de que  no pertenezca ni a casta alta ni a baja no lo tomo en cuenta
								if(LE->Consultar(Posicion)==CastaBaja)
								{
									CantCasBaja=CantCasBaja-1;
								}
							}

							//aqui elimino al participante de ambas listas y actualizo la variable muerte
							LE->Eliminar(Posicion);
							LN->Eliminar(Posicion);
							Muerte=true;

						}else
						{
							//en caso que el nombre no se repita mas de T veces, aumento las veces que se repitio el nombre
							NombreRepetido=NombreRepetido+1;
							Muerte=false;
						}
					}else
					{
						//En caso de ser distinto guardo el nuevo nombre
						AuxNombre=LN->Consultar(Posicion);
						NombreRepetido=1;
						Muerte=false;
					}
				}	
			}
		}
		//con esta verifico la cantidad de muertes antes de cambiar la prioridad de clase
		if (Muerte==true && MuerteCastaAlta==true)
		{
			/*este condicional me sirve para cambiar la prioridad de muerte, si ya murieron T personas, CantMuertos=0
			por ende debo cambiar la prioridad, en caso contrario, simplemente le resto uno a la CantMuertos*/
			if (CantMuertos-1<1)
			{
				CantMuertos=T;
				MuerteCastaAlta=false;
					
			}else
			{
				CantMuertos=CantMuertos-1;
			
			}
		}else
		{
			/*funciona igual que la anterior, solo que esta es con casta baja, sirve para priorizar 
			la muerte de la casta alta en caso de que ya hayan muerto T personas Casta Baja*/
			if (Muerte==true && MuerteCastaAlta==false)
			{
				if (CantMuertos-1<1)
				{
					CantMuertos=T;
					MuerteCastaAlta=true;
					
				}else
				{
					CantMuertos=CantMuertos-1;
			
				}
			}
		}

		//Verifico que la posicion no sea el tamaño de la lista mas 1, de ser asi el siguiente seria el primero
		if (Muerte==true)
		{
			if(Posicion>LE->Tamano())
			{
				Posicion=1;
			}
		}
	}
	cout<<QuitarComa( LN->Consultar(1) )<<endl;//muestra en pantalla al sobreveviviente
}

//funcion para quitar la coma del nombre del participante
string QuitarComa(string Nombre)
{
	int Posicion;//esta sirve para guardar la posicion de la coma
	string Cadena;//donde se almacena el nombre sin coma

	Posicion=Nombre.find(',');//busco la posicion de la coma
	Cadena=Nombre.substr(0,Posicion);//copio todo hasta un espacio menos de la posicion de la coma
	
	return Cadena;//retorno el nombre sin coma
}