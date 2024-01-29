/*****************************************************
*
* @Propòsit: Evitar el cansament de l'equip de bombers 
*            i calcular el cost de combustible dels diferents vehicles.
* @Autor: David Susagna Holgado
* @Data de creació: 22/10/2022
* @Data de l'última modificació: 25/10/2022
*
*****************************************************/
// Llibreries del sistema
#include <stdio.h>

// Constants
#define MAX_MIN_DAY 1440		//Minuts en un dia.
#define HOUR_MAX 23             //Màximes hores d'un dia.
#define MIN_MAX 59              //Màxims minuts d'una hora
#define MIN_HOUR 60				//Minuts en una hora.
#define OIL_CONSUME 0.05		//Consum mitja de carburant d'un camió de bombers.

// Procediments i funcions
/*****************************************************
*
* @Finalitat: Sol·licitar a l'usuati les hores d'entrada i sortida del bomber. 
* @Paràmetres:	in: option = Indica quina opció del programa sa selecionat.
* @ Retorn : retorna la suma dels minuts i les hores convertits a minuts.
*
*****************************************************/
int scanHours(int option){
	
	int hour = 0, min = 0;      //Variables de temps.
	
	// Bucle que evita errors de l'usuari en la selecció d'hores.
	do{
		switch (option) {
			case 1 :
				printf("Enter start hour: ");
				break;
			case 2 :
	  			printf("Enter end hour: ");
				break;
		} 
		scanf("%d", &hour);
	} while((0 > hour) || (hour > HOUR_MAX));
				
	// Bucle que evita errors de l'usuari en la selecció de minuts.
	do{
		switch (option) {
			case 1 :
				printf("Enter start minute: ");
				break;
			case 2 :
	 			printf("Enter end minute: ");
				break;
		} 
   		scanf("%d", &min);
	} while((0 > min) || (min > MIN_MAX));

	return ((hour * MIN_HOUR) + min);
}

/*****************************************************
*
* @Finalitat: Imprimir per pantalla els minuts en fotmat HHh MMmin.  
* @Paràmetres:	in: time = Els minuts a camviar de format.
* @ Retorn : ----.
*
*****************************************************/
void printTime(int time){

	int hour = 0, min = 0;      //Variables de temps.

	hour = (time / MIN_HOUR);
	min = (time % MIN_HOUR);

	printf("%dh %dmin ", hour,min);
}

/*****************************************************
*
* @Finalitat: 	Calcula el consum del camió en euros. 
* @Paràmetres:	in: price = Preu del carburant per litre.
*				in: time = Minuts totals dus d'un camió.
* @ Retorn : 	Retorna el consum total en euros.
*
*****************************************************/
float consumeOilEuro(float price, int time){
	
	int km_total = 0;			// Total km recorreguts.
	float price_km = 0.0;		// Preu km.
	float consume = 0.0;		// Consum total de carburant.

	km_total = (time * MIN_HOUR) / MIN_HOUR;
	price_km = (OIL_CONSUME * price);
	consume = (price_km * km_total);

	return(consume);
}

/*****************************************************
*
* @Finalitat: 	Calcular valor mínim entre 3 variables. 
* @Paràmetres:	in: a = Valor de la primera variable.
*				in: b = Valor de la segona variable.
*				in: c = Valor de la tercera variable.
* @ Retorn : 	Retorna el caràcter corresponent al valor mínim
*
*****************************************************/
char minimTres(int a, int b, int c){
	
	char min;

	if (a <= b){
		if (a <= c){
			min = 'a';	
		}
		else{
			min = 'c';
		}
	}
	else {
		if (b <= c){
			min = 'b';
		}
		else{
			min = 'c';
		}
	}

	return (min);
}

/*****************************************************
*
* @Finalitat: 	Calcular valor mínim entre 2 variables. 
* @Paràmetres:	in: time_1 = Valor de la primera variable.
*				in: time_2 = Valor de la segona variable.
* @ Retorn : 	Retorna el valor corresponent a la variable més petita.
*
*****************************************************/

int minimDos(int time_1, int time_2){

	if (time_1 < time_2){
		return (time_1);		
	}
	else {
		return (time_2);		
	}

}

/*****************************************************
*
* @Finalitat: 	Calcular valor màxim entre 3 variables. 
* @Paràmetres:	in: a = Valor de la primera variable.
*				in: b = Valor de la segona variable.
*				in: c = Valor de la tercera variable.
* @ Retorn : 	Retorna el caràcter corresponent al valor màxim.
*
*****************************************************/

char maxTres(int a, int b, int c){

	char max;
	
	if(a > b){
		if(a > c){
			max = 'a';
		}
		else{
			max = 'c';
		}
	}
	else{
		if (b > c){
			max = 'b';
		}
		else {
			max = 'c';
		}
	}

	return (max);
}


int main () {

	// Declaració de variables
	char trash;					// Variable per netejar el Buffer.
	char min;					// Variable auxiliar per definir el mínim.
	char max; 					// Variable auxiliar per definir el màxim

    int option = 0;				// Opcions inicals del programa.

	int time_a_in = 0;          // Hora inici servei del bomber A.
	int time_b_in = 0;          // Hora inici servei del bomber B.
	int time_c_in = 0;          // Hora inici servei del bomber C.
    
	int time_a_out = 0;       	// Hora final servei del bomber A.
	int time_b_out = 0;         // Hora final servei del bomber B.
	int time_c_out = 0;         // Hora final servei del bomber C.
	
	int time_a = 0;             // Total minuts en servei del bomber A.
	int time_b = 0;             // Total minuts en servei del bomber B.
	int time_c = 0;             // Total minuts en servei del bomber C.

	int a_available = 1;    	// Disponibilitat del bomber A.
	int b_available = 1;    	// Disponibilitat del bomber B.
	int c_available = 1;    	// Disponibilitat del bomber C.
	int available = 0;			// Quantitat de bombers disponibles.
	
	float price = 0.0;			// Preu del carburant per litre.
	
	char fireman; 				// Identificar el bomber seleccionar.

	float consume_a = 0;		// Consum carburant bomber A.
	float consume_b = 0;		// Consum carburant bomber B.
	float consume_c = 0;		// Consum carburant bomber C.
	float total_consume = 0;	// Consum total de carburant.

    //Output 1. El programa arrenca donant la benvinguda i mostrant les opcions disponibles.

	printf("Welcome to Prog City! \n");
	do{
		printf("\n");
	    printf("1. Start Operation | 2. End Operation | 3. Fuel Balance | 4. Exit \n");
	    printf("Enter option: ");
	    scanf("%d", &option);
    
        //Output 2. El programa mostra un error si l'opció no és vàlida.
        if (((1 > option) || (4 < option))){
            printf("ERROR (Invalid option)\n");
	    }  

        // Opció 1: Start Operation
	    if (1 == option){
			// Oputput 3. Es tria l'opció "start Operation" i s'actica el bomber A, B o C.
			
			// Càlcul quants bombers estan disponibles.
			available = a_available + b_available + c_available;
			
			
			// Se selecciona una de les tres opcions possibles.
			
			switch (available){
				case 3:
					// Quin de les 3 bombes ha treballat menys hores?
					min = minimTres(time_a, time_b, time_c);
					switch (min){
						case 'a':
							// Fireman A disponible
							printf("Fireman A is ready!\n\n");
							// Output 4. L'usuari no introduex correctament algunes dades.
							time_a_in = scanHours(option);
							// Bomber A actualitzat
							a_available = 0;
							break;
						case 'b':
							//Fireman B disponible
							printf("Fireman B is ready!\n\n");
							// Output 4. L'usuari no introduex correctament algunes dades.
							time_b_in = scanHours(option);
							// Bomber B actualitzat
							b_available = 0;
							break;
						case 'c':
							// Fireman C disponible
							printf("Fireman C is ready!\n\n");
							// Output 4. L'usuari no introduex correctament algunes dades.
							time_c_in = scanHours(option);
							// Bomber C actualitzat
							c_available = 0;
							break;
					}
					break;
				case 2:
					// Definir quin bomber no està disponible.
					min = minimTres(a_available, b_available, c_available);
					switch (min){
						case 'a':
							if (time_b == minimDos(time_b, time_c)){
								//Fireman B disponible
								printf("Fireman B is ready!\n\n");
								// Output 4. L'usuari no introduex correctament algunes dades.
								time_b_in = scanHours(option);
								// Bomber B actualitzat
								b_available = 0;
							}
							else{
								// Fireman C disponible
								printf("Fireman C is ready!\n\n");
								// Output 4. L'usuari no introduex correctament algunes dades.
								time_c_in = scanHours(option);
								// Bomber C actualitzat
								c_available = 0;
							}
							break;
						case 'b':
							if (time_a == minimDos(time_a, time_c)){
								// Fireman A disponible
								printf("Fireman A is ready!\n\n");
								// Output 4. L'usuari no introduex correctament algunes dades.
								time_a_in = scanHours(option);
								// Bomber A actualitzat
								a_available = 0;
							}
							else{
								// Fireman C disponible
								printf("Fireman C is ready!\n\n");
								// Output 4. L'usuari no introduex correctament algunes dades.
								time_c_in = scanHours(option);
								// Bomber C actualitzat
								c_available = 0;
							}
							break;
						case 'c':
							if (time_a == minimDos(time_a, time_b)){
								// Fireman A disponible
								printf("Fireman A is ready!\n\n");
								// Output 4. L'usuari no introduex correctament algunes dades.
								time_a_in = scanHours(option);
								// Bomber A actualitzat
								a_available = 0;
							}
							else{
								//Fireman B disponible
								printf("Fireman B is ready!\n\n");
								// Output 4. L'usuari no introduex correctament algunes dades.
								time_b_in = scanHours(option);
								// Bomber B actualitzat
								b_available = 0;
							}
							break;
					}
					break;
				case 1:
					// Trobar quin és l'únic bomber disponible.
					max = maxTres(a_available, b_available, c_available);
					switch (max){
						case 'a':
							// Fireman A disponible
							printf("Fireman A is ready!\n\n");
							// Output 4. L'usuari no introduex correctament algunes dades.
							time_a_in = scanHours(option);
							// Bomber A actualitzat
							a_available = 0;
							break;
						case 'b':
							//Fireman B disponible
							printf("Fireman B is ready!\n\n");
							// Output 4. L'usuari no introduex correctament algunes dades.
							time_b_in = scanHours(option);
							// Bomber B actualitzat
							b_available = 0;
							break;
						case 'c':
							// Fireman C disponible
							printf("Fireman C is ready!\n\n");
							// Output 4. L'usuari no introduex correctament algunes dades.
							time_c_in = scanHours(option);
							// Bomber C actualitzat
							c_available = 0;
							break;
					}
					break;
				default:
					// Output 5. Tots els bombers estan ocupats, es motra un error.
					printf("ERROR (No fireman available)\n");
					break;
			}
		}	
			
		    

	    // Opció 2: End Operation
	    if (2 == option) {
			// Output 6. Es demana a l'usuari que seleccioni el bomber que torna a estar actiu.
			printf("\n");
			do {
				printf("Enter fireman: ");
				scanf("%c", &trash);
				scanf("%c", &fireman);
				
				// Passar minúscules a majúscules
				if (('z' >= fireman) &&  ('a' <= fireman)){
					fireman = fireman - ('a'-'A');
				} 

			} while (('A' != fireman) && ('B' != fireman) && ('C' != fireman) );
			
			switch (fireman){
				// Bomber A end
				case 'A':
					//Output 8. El bomber seleccionat està actiu.
					if(0 == a_available){
						// Output 9. L'usuari no introduex correctament algunes dades.
						time_a_out = scanHours(option);

						//Calculador HORES
						if (time_a_in < time_a_out) {
							time_a = time_a + (time_a_out - time_a_in);
						}
						else{
							time_a = time_a + ((MAX_MIN_DAY - time_a_in) + time_a_out);
						}

						// Bomber A actualitzat
						a_available = 1;
					}
					//Output 7. El bomber seleccionat no està actiu.
					else {
						printf("ERROR (Fireman A is not working) \n");
					}
					break;
				// Bomber B end
				case 'B':
					//Output 8. El bomber seleccionat està actiu.
					if(0 == b_available){
						// Output 9. L'usuari no introduex correctament algunes dades.
						time_b_out = scanHours(option);

						//Calculador HORES
						if (time_b_in < time_b_out) {
							time_b = time_b + (time_b_out - time_b_in);
						}
						else{
							time_b = time_b + ((MAX_MIN_DAY - time_b_in) + time_b_out);
						}

						// Bomber B actualitzat
						b_available = 1;
					}
					//Output 7. El bomber seleccionat no està actiu.
					else {
						printf("ERROR (Fireman B is not working) \n");
					}
					break;
				// Bomber C end
				case 'C':
					//Output 8. El bomber seleccionat està actiu.
					if(0 == c_available){
						// Output 9. L'usuari no introduex correctament algunes dades.
						time_c_out = scanHours(option);

						//Calculador HORES
						if (time_c_in < time_c_out) {
							time_c = time_c +(time_c_out - time_c_in);
						}
						else{
							time_c = time_c + ((MAX_MIN_DAY - time_c_in) + time_c_out);
						}

						// Bomber C actualitzat
						c_available = 1;
					}
					// Output 7. El bomber seleccionat no està actiu.
					else {
						printf("ERROR (Fireman C is not working) \n");
					}
					break;
				default:
					break;
			}
		}

	    // Opció 3: Fuel Balance
		if (3 == option) {
			// Output 10. L'usuari introdueix el preu del carburant per litre. 
			printf("\n");
			printf("Enter price: ");
			scanf("%f", &price);
			printf("\n");

			// Es mostra per pantalla les dades del bomber A. 
			printf("Fireman A: ");
			printTime(time_a);
			consume_a = consumeOilEuro(price, time_a);
			printf("(%.2f euros) \n", consume_a);

			// Es mostra per pantalla les dades del bomber B. 
			printf("Fireman B: ");
			printTime(time_b);
			consume_b = consumeOilEuro(price, time_b);
			printf("(%.2f euros) \n", consume_b);
			
			// Es mostra per pantalla les dades del bomber C. 
			printf("Fireman C: ");
			printTime(time_c);
			consume_c = consumeOilEuro(price, time_c);
			printf("(%.2f euros) \n", consume_c);

			total_consume = (consume_a + consume_b + consume_c);

			printf("Total: %.2f euros \n", total_consume);
		}

		

	} while(4 != option);

	//Opció 4: Exit
    //Output 11. L'opció Exit finalitza l'execució del programa.
    printf("See you later! \n");

    return(0);
}
