// Elian Alderuccio - 4A Informatica - AS: 2017/2018

#include<stdio.h>
#include<pthread.h>
#include<windows.h>
#include<conio.h>

//   *****   Inizio prototipi, dichiarazioni globali e funzione printfxy   *****

void Tutorial();
void Menu();
void Sparo();
void Win();
void GameOver();
void Inizializza();
void Controlla();
void * MovimentoSpara(void * c);
void * MovimentoNavicelle(void * l);

int x,y;
int ya,xa;
int Array[100];int a;
int point=0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int printfxy(int x, int y, char string[]){
	int rc;
	rc = pthread_mutex_lock (&mutex);
	COORD dwCursorPosition={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),dwCursorPosition);
	printf("%s",string);
	pthread_mutex_unlock(&mutex);	
}

//   *****   Fine prototipi, dichiarazioni globali e funzione printfxy   *****

//   *****   Inizio funzione main   *****

int main(void){
    Menu();
	return 0;
}

//   *****   Fine funzione main   *****

//   *****   Inizio funzione menù   *****

void Menu(){
	int scelta=0;
	char torna,riga[100],riga3[100],riga7[100];
	FILE *FM,*FC,*FE;

	do{
        system("cls");  
        FM = fopen("Menù.txt","r");
        if(FM==NULL)printf("Il file non e' stato aperto correttamente");
        while(!feof(FM)){
        	  fgets(riga,100,FM);
        	  printf("%s",riga);
        	  Sleep(30);
		}
		fclose(FM);
		printf("\n\n				Select one of the three option: ");
		scanf("%d",&scelta);

		switch (scelta){
			case 1:
				system("cls");
	            FC = fopen("Contorno.txt","r");
                if(FC==NULL)printf("Il file non e' stato aperto correttamente");
                while(!feof(FC)){
        	        fgets(riga3,100,FC);
                 	printf("%s",riga3);
                 	Sleep(30);
		        }
		        fclose(FC);
				pthread_t Spara,Navicelle,Spa;	
	            pthread_create(&Spara, NULL, &MovimentoSpara, NULL);
				pthread_create(&Navicelle, NULL, &MovimentoNavicelle, NULL);
				pthread_join(Spara, NULL);
				pthread_join(Navicelle, NULL);
				system("cls");
				break;
				
			case 2:
				system("cls");
	            Tutorial();
				system("pause");
				system("cls");
				break;
				
			case 3:
				system("cls");
				FE = fopen("Exit.txt","r");
                if(FE==NULL)printf("Il file non e' stato aperto correttamente");
                while(!feof(FE)){
        	       fgets(riga7,100,FE);
        	       printf("%s",riga7);
        	       Sleep(30);
		           }
		        fclose(FE);
		        getch();
				return;
				system("cls");
				break;
			
			default:
				printf("Invalid number\n");
		}
		printf("Press a key and then enter to return to the main menu:");
		scanf("%s",&torna);
	}
	while (torna!=0);
}

//   *****   Fine funzione menù   *****

//   *****   Inizio funzioni di gestione   *****

void * MovimentoSpara(void * c){	
	x=35;
	y=25;
	char tasto;
	
	while(ya!=25){
		tasto = getch();
		if(tasto==75)x--;
		if(tasto==77)x++;
		if(x<30)x=30;
		if(x>80)x=80;
		if(tasto==32)Sparo();
		
		printfxy(x,y,"x");
		printfxy(x-1,y," ");
		printfxy(x+1,y," ");
	}
}

void Sparo(){
	int y=24;
	while(y>ya){
	    printfxy(x,y," ");
		y--;
		printfxy(x,y,"^");
		Sleep(40);
	}
	printfxy(x,y," ");
	Controlla();
}

void Controlla(){
	for(int c=0;c<a;c++){
		if(Array[c]==x){
		  Array[c]=0;
		  point++;
		}
	}
}

void Inizializza(){
	xa=30;int c;
	for(c=0;c<6;c++){
		Array[c]=xa;
		xa+=10;
	}
	a=c;
}

void * MovimentoNavicelle(void * l){
	ya=1;int c;
	Inizializza();
	while((ya!=25)&&(point<a)){
		for(c=0;c<a;c++){
			if(Array[c]>0)printfxy(Array[c],ya,"X");
		}
		Sleep(1000);
		for(c=0;c<a;c++)printfxy(Array[c],ya," ");
		ya++;
	}
	system("cls");
	if(point==a){
		Win();
		getch();
		Menu();
	}
	if(point!=a){
		GameOver();
		getch();
		Menu();
	}
}

//   *****   Fine funzioni di gestione   *****

//   *****   Inizio funzioni di apertura e lettura file txt   *****

void Tutorial(){
    FILE *FI, *FT;
    char riga4[100],riga5[100];
	
    FI = fopen("Info.txt","r");
    if(FI==NULL)printf("Il file non e' stato aperto correttamente");
    while(!feof(FI)){
    	fgets(riga4,100,FI);
    	printf("%s",riga4);
    	Sleep(30);
	}
	fclose(FI);
	
	printf("Press a key to view the tutorial: ");
	getch();
	system("cls");
	
	FT = fopen("Tutorial.txt","r");
    if(FT==NULL)printf("Il file non e' stato aperto correttamente");
    while(!feof(FT)){
    	fgets(riga5,100,FT);
    	printf("%s",riga5);
    	Sleep(30);
	}
	fclose(FT);
}

void Win(){
	FILE *FW;
	char riga1[100];
	FW = fopen("Win.txt","r");
    if(FW==NULL)printf("Il file non e' stato aperto correttamente");
    while(!feof(FW)){
        fgets(riga1,100,FW);
       	printf("%s",riga1);
       	Sleep(30);
	}
	fclose(FW);
}

void GameOver(){
	FILE *FG;
	char riga2[100];
	FG = fopen("GameOver.txt","r");
    if(FG==NULL)printf("Il file non e' stato aperto correttamente");
    while(!feof(FG)){
       	fgets(riga2,100,FG);
       	printf("%s",riga2);
       	Sleep(30);
	}
	fclose(FG);
}

//   *****   Fine funzioni di apertura e lettura file txt   *****
