#include <iostream>

#define SIZE_STR	15000
#define LENGTH_STR	100
using namespace std;
int length(char * a){
        int i=0;
        while(a[i] !=0)i++;
        return i;
}
bool letra(char a){
	return (a >= 'a' && a <= 'z');
}
bool isNumber(char a){
	return (a >= '0' && a <= '9');
}
bool separa(char a){
	return  ( a >=33 && a <= 47) || (a >= 58 && a <= 64)  || (a >= 91 && a <= 96);
}
int strcmp(char a[], char b[]){
	int i  = 0;
	for( i; a[i] && b[i] && a[i] == b[i]; i++);
	return a[i]-b[i];	
}
bool isUpper(char a){
	return (a >= 65 && a <=90);
}
int compara(char a[SIZE_STR][LENGTH_STR], char b[]){
	int i = 0, achou = 0;
	for(i = 0; i < SIZE_STR && !achou; i++){
		if( length(a[i]) == length(b))
			if(strcmp(a[i], b) == 0)achou = 1;
	}
	return achou;
}
void toMinuscule(char* str){
	for(int i = 0; str[i];i++)
		if(isUpper(str[i]))str[i] += 32;
}
void remove(char* str){
	int i;
	for( i = 0;str[i];i++)
		if(separa(str[i]) || isNumber(str[i]))
			 str[i]=' ';
	str[i]=0;
}
void espacos(char* str){
		int tam = length( str);
		int j  = 1;
		for(int i = 1; str[i]; i++){
			if(str[i] != ' ' || str[i - 1] != ' '){
				str[j] = str[i];
				j++;
			}  	
		}
		str[j] = 0;
}
void reduz(char* str){		
	char strCompara[30];
	char newStr[1000];
	int k = 0, i,x = 0 ;
	int tam = length(str);
	for(i = 0; i < 100; i++ ){
		if(letra(str[i]) && str[i - 1] == ' ' && str[i + 1] == ' ')i+=1;
	newStr[x++]=str[i];
	}
	newStr[x] = 0;
	for(i = 0; i < length(newStr); i++)str[i]=newStr[i];
	str[i]=0;		
}
int main(){
	char negativo[SIZE_STR][LENGTH_STR];
	char positivo[SIZE_STR][LENGTH_STR];
	char str[1000];
	char newStr[200];
	int posit = 0, negat = 0;
	int twtPos = 0, twtNeutro = 0, twtNeg = 0;


	int pos,neg;
	int i, j, aux, z;

	cin >> pos;
	for(i=0;i<pos;i++)cin >> positivo[i];
	cin >> neg;
    for(i=0;i<neg;i++)cin >> negativo[i];
	cin.ignore();
	while(cin.getline(str,1000)){
	 	toMinuscule(str);
	 	remove(str);
	 	reduz(str);
	 	espacos(str);
	 	posit = 0; 
		negat = 0;
		for(i = 0; str[i]; i++){
			aux  = 0; 
			for(z = i;str[z] != ' ' && str[z] ; z++){
				newStr[aux] = str[z];
				aux++;
			}
			newStr[aux] = '\0';	
				if(length(newStr) >=2){
					if(compara(positivo, newStr))posit++;
					else if(compara(negativo, newStr))negat++;
				}
		i+=aux;

		}		
		if(posit == negat)twtNeutro++;
		else if( posit < negat)twtNeg++;
		else twtPos++;	

	}
	cout.precision(2);
	cout << "Total de twitts positivos: " << twtPos << endl;
	cout << "Total de twitts negativos: " << twtNeg << endl;
	cout << "Total de twitts neutro: "    << twtNeutro << endl;

	cout << "Porcentagem positiva  " << fixed <<(float)(twtPos*100.0f)/(twtPos + twtNeg + twtNeutro)  <<" " << '%'  <<endl;
	cout << "Porcentagem negativa  " << fixed <<(float)(twtNeg*100.0f)/(twtPos + twtNeg + twtNeutro)  <<" " << '%'  <<endl;

	return 0;

}


