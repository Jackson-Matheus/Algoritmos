#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;
void menu(){
	cout << "1 - Imprimir : " << endl;
	cout << "2 - Salvar arquivo em outro: " << endl;
	cout << "3 - Fechar arquivo :  " << endl;
	cout << "4 - Editar arquivo :  " << endl;
	cout << "0 - Sair : " << endl;
}
void menuOpcao(){
	cout << "\t1 - Imprimir : " << endl;
	cout << "\t2 - Trocar elementos: " << endl;
	cout << "\t3 - Inverter  :  " << endl;
	cout << "\t4 - Reduzir (Max Pooling) : " << endl;
	cout << "\t5 - Ampliar (Max Pooling reverse) : " << endl;
	cout << "\t6 - Preenchimento : " << endl;
	cout << "\t0 - Sair : " << endl;
}
void altera(char ** mat , char  proc, char  trocar, int m, int n){
	int i, j;
	for(i = 0; i < m; i++)
		for(j = 0; j < n; j++)
			if(mat[i][j] == proc) mat[i][j] = trocar;	

}
void troca(char ** mat , char x, char y, int m, int n){
	int i, j;
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++){
			if(mat[i][j] == x) mat[i][j] = y ;
		}
	}
}
char maisFrequente(char ** mat , int m, int n){
	int i, j,contj, conti;
	char analisado, candidato;
	int cont = 0;
	int mais_frequente=0;
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++){
			analisado = mat[i][j];
			cont = 0;
			for(conti = 0; conti < m; conti++){
				for(contj = 0; contj < n; contj++){
					if(mat[conti][contj] != ' ' && analisado == mat[conti][contj])cont++;			// Retirar o analisado != ' '
				}
			}
			if(cont > mais_frequente){
				mais_frequente = cont;
				candidato = analisado;
			}
		}
	}
	return candidato;
}
char ** criaMat(int m, int n){
	char ** mat = (char**)malloc(sizeof(char*) * m);
	int i;
	for(i=0; i < m; i++){	
		mat[i] = (char*)malloc(sizeof(char) * n );
	}	
	return mat;
}
void desaloca(char ** mat, int m){
	int i;
	for(i=0; i < m; i++)free(mat[i]); 	
	free(mat);	
}
void imprime(char ** mat, int m, int n){
	int i,j;
	for(i=0; i < m; i++){	
		for(j=0; j < n; j++){
			cout << mat[i][j];
		}
		cout << endl;
	}
} 
int checa(char ** mat, int m, int n, char proc){
	int i,j,cont=0;
	for(i=0; i<m;i++)
		for(j=0;j<n;j++)
			if(mat[i][j] == proc)cont++;
	return cont;	
}
int maior(char ** mat, int m, int n, int i, int j){
	char maior =(char)mat[i][j];
	if(mat[i][j+1] > maior)
		maior = mat[i][j+1];
	if(mat[i+1][j+1] > maior)
		maior = mat[i+1][j+1];
	if(mat[i+1][j] > maior)
		maior = mat[i+1][j];
	return maior;
}
/*copia o mais frequente para o matriz modificada
No entando, só entra na condica de maiores, caracteres que possui apenas uma repeticao
*/
char maxP2(char ** mat, char ** mp, short  int m,short  int n){
	int i, j, conti, contj,candidato = 0;
	char ** mat_aux = criaMat(2,2);
	for(i=0, conti=0; i < m && conti < m/2; i+=2, conti++){
		for(j=0, contj = 0; j < n && contj < n/2; j+=2, contj++){		
			mat_aux[0][0] = mat[i][j];
			mat_aux[0][1] = mat[i][j+1];
			mat_aux[1][0] = mat[i+1][j];
			mat_aux[1][1] = mat[i+1][j+1];			
			candidato  = maisFrequente(mat_aux,2,2);
			if(checa(mat_aux,2,2,candidato) > 1)
				mp[conti][contj] = maisFrequente(mat_aux,2,2);
			else
				mp[conti][contj] = maior(mat_aux, m,n,0,0);
		}
	}
	desaloca(mat_aux,2);
}
void inverte(char ** mat ,short  int m,short  int n){
	int i, j, cond;	
	char troca = maisFrequente(mat, m, n);
	cout << "Mais frequente : " << troca << endl;
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++){
			if(mat[i][j] == ' ')mat[i][j] = troca;	
			else mat[i][j] = ' ';
		}
	}
}
void maxPo(char ** mat, char ** b, short int m, short int n,short int p, short int q){
	int i,j;
	int idx_i, idx_j;
	char maior;
	for(i=0,idx_i=0;i < m && idx_i<p; i+=2, idx_i++){
		for(idx_j = 0,j=0;j < n && idx_j<q ; idx_j++, j+=2){	
			maior =(char) mat[i][j];
			if(mat[i][j+1] > maior)
				maior = mat[i][j+1];
			if(mat[i+1][j+1] > maior)
				maior = mat[i+1][j+1];
			if(mat[i+1][j] > maior)
				maior = mat[i+1][j];
			b[idx_i][idx_j] = maior;
		}
	}
}
void maxPoReverse(char ** mat, char ** matPo, short  int m, short  int n,short  int a, short  int b){
	int idx_i, idx_j,i,j;
	char maior;
	for(i=0,idx_i=0;idx_i<m &&  i < a;i+=2, idx_i++){
		for(j=0, idx_j = 0;idx_j < n && j < b;idx_j++, j+=2){	
			maior =mat[idx_i][idx_j];
			matPo[i][j] = maior;
			matPo[i][j+1] = maior;
			matPo[i+1][j+1] = maior;
			matPo[i+1][j] = maior;
		}
	}
}
void copia(char ** a, char ** b, short int m, short int n){
	// m e n sao da matriz b 
	int i,j;
	for(i=0; i < m; i++){
		for(j = 0; j < n ; j++){
			a[i][j] = b[i][j];
		}
	}	
}
/*Milestone 3*/
void checa(char ** mat, short int m, short int n, int x, int y, char transformar){
		char aux = mat[x][y];
		mat[x][y] = transformar;
		if(x >= 0 && x < m && aux == mat[x+1][y])checa(mat, m, n, x+1, y    , transformar);	
		if(x >= 0 && x < m && aux == mat[x-1][y])checa(mat, m, n, x-1 , y   , transformar);	
		if(y >= 0 && y < n && aux == mat[x][y+1])checa(mat, m, n, x, y+1    , transformar);	
		if(y >= 0 && y < n && aux == mat[x][y-1])checa(mat, m, n, x, y-1    , transformar);		
}

int main(){
	ifstream arq;
	ofstream arq_out;
 	char * nome = new char[15];
 	char ** mat ;
 	int fechou = 1;
 	int cond,i,j;
	short int a,b,p,q,x,y, novo_a=0, novo_b=0;
	char elemento, sair = '0';
	int opcao=0, tem_Arquivo = 1;

	while(sair != 's' && sair != 'S'){ // condicao de saida MENU principal
		if(fechou == 1){		
		/*Quando o arquivo é fechado ou o programa se inicia pela primeira fez, essa condicao é verdadeira
		Porém, quando o arquivo é fechado, essa condicao deve ser levada em conta, pois nao tem mais nada na memoria 
		do computador do arquivo fechado;	*/	
			cout << "Deseja abrir qual arquivo : ";
			//cin.getline(nome, 15);
			cin >> nome;
			arq.open(nome, ios::binary);
			if(!arq.is_open()){
				cout << "Erro ao abrir o arquivo" << endl;
				cout << "Abra novamente o programa e tente novamente" << endl;
				return -1;
			}		
			arq.read((char*)&cond, sizeof(int));
			if(cond != 123456789){
				cout << "Erro ao abrir o arquivo" << endl;
				cout << "Abra novamente o programa e tente novamente" << endl;
				return -1;
			}
			arq.read((char*)&a, sizeof(short int));
			arq.read((char*)&b, sizeof(short int));
			mat = criaMat(a,b);	 // Alocando matriz para pode manipular img
			for(i=0; i < a; i++){	
				for(j=0; j < b; j++){
					arq.read((char*)&elemento, sizeof(char));
					mat[i][j] = elemento;	
				}
			}
			fechou = 1001;
			tem_Arquivo = 1;
		}
		menu();
		cin >> opcao;
		if(opcao == 1){		// Menu da TELA PRINCIPAL
			if(tem_Arquivo == 0){
				cout << "Arquivo " << nome << " foi fechado recentemente" << endl;
				cout << "Abra novamente o programa e tente novamente" << endl;
				delete(nome);
				return -1;			
			}else{
				cout << cond << endl;	
				cout << a << endl;
				cout << b << endl;
				imprime(mat,a,b);	
			}
		}else if(opcao == 2){
			cin.ignore();
			cout << "Deseja salvar em qual arquvo : " << endl;
			cin.getline(nome, 15);
			arq_out.open(nome, ios::binary);
			if(!arq_out.is_open()){
				cout << "Erro ao abrir o arquivo" << endl;
				cout << "Abra novamente o programa e tente novamente" << endl;
				return -1;
			}
			arq_out.write((char*)&cond, sizeof(int));
			arq_out.write((char*)&a, sizeof(short int));
			arq_out.write((char*)&b, sizeof(short int));
			for(i=0; i < a; i++){
				for(j=0; j < b; j++){
					elemento = mat[i][j];
				arq_out << elemento;	
				}
			}
			cout << "Arquivo salvo com sucesso" << endl;
			cout << "Dejesa Sair S/N ? "; 
			cin >> sair;
		}else if(opcao == 3){
			/*Quando o arquivo é fechado, 
				apaga-se tudo que foi salvo na matriz principal, liberando a memoria utilizada
				No entando, ele modifica o estado de arquivo lido para arquivo nao lido
				variavel tem_Arquivo;
			*/
			cout << "Arquivo " << nome << " fechado com sucesso" << endl;
			desaloca(mat, a);
			arq.close();		
			a = 0; b = 0;
			cond = 0;
			cout << "Dejesa Sair S/N ? "; 
			cin >> sair;
			tem_Arquivo = 0;	
			fechou = 1;		
		}else if(opcao == 0){
			cout << " ENCERRANDO EXECUÇÃO " << endl;
			desaloca(mat, a);
			free(nome);
			return -1;
		}else if(opcao == 4){
			char ** mat_mp , ** mprvs, ** mat_aux;
			int op = 1001;
			char sair_ed = '0';
			while(op != 0 ){ // condiçao de saida do menu secundario
				cout << endl;
				menuOpcao();
				cout <<"\tEscolha uma opcao: ";
				cin >> op; // Opcoes da tela secundaria		
				if(op == 1){
					novo_a = a;
					novo_b = b;
					cout << "Altura: "  << novo_a << "    ";
					cout << "Largura: " << novo_b << endl;
					imprime(mat, novo_a, novo_b);
				}
				else if(op == 2){
					char str_1[2], str_2[2];
					char x,y;
					cout << "\tEscolha um caracter e aperte ENTER " << endl;
					cin.ignore();
					cin.getline(str_1,2);
					if(str_1[1] != 0){
						cout << "Caracter invalido " << endl;
						return -1;
					}
					//cin.ignore();
					cin.getline(str_2,2);
					if(str_2[1] != 0){
						cout << "Caracter invalido " << endl;
						return -1;
					}
					x = str_1[0];
					y = str_2[0];
					novo_a = a;
					novo_b = b;
					cout << endl << "Altura: "  << novo_a << "    ";
					cout << "Largura: " << novo_b << endl;
					cout << "Caracteres trocados: "; 
					cout << x << "  " << y << endl;
					troca(mat, x, y, novo_a, novo_b);
					imprime(mat, novo_a, novo_b);
				}else if(op == 3){
					novo_a = a;
					novo_b = b;
					cout << "Invertendo caracteres " << endl;
					cout << "Nao vazio -> vazio /e/ vazio -> Caracter mais frequente" << endl;
					inverte(mat, novo_a, novo_a); 				//Funcao para inverter caracteres 
					imprime(mat, novo_a, novo_a);	
				}else if(op == 4){
					// Max Pooling Diminuindo pela metade
					novo_a = a/2;
					novo_b = b/2;
					cout << "Reduz a imagem pela metade" << endl;
					mat_mp = criaMat(novo_a, novo_b);
					cout << "Altura: "  << novo_a << "    ";
					cout << "Largura: " << novo_b << endl;
					maxP2(mat, mat_mp, a, b);
					desaloca(mat, a);	 			// Desalocando mat princial
					mat = criaMat(novo_a, novo_b);	//Aloca matriz principal com novo tamanho
					copia(mat, mat_mp, novo_a, novo_b);	// copiando matriz modificada para a principal	
					imprime(mat, novo_a, novo_b);
					desaloca(mat_mp, novo_a);
				}else if(op == 5){
					//Max Pooling aumentando 2x
					cout << "Aumenta a imagem em 2x" << endl;
					novo_a = a*2;
					novo_b = b*2;
					mprvs = criaMat(novo_a, novo_b);
					cout << "Altura: "  << novo_a << "    ";
					cout << "Largura: " << novo_b << endl;
					maxPoReverse(mat, mprvs, a, b, novo_a, novo_b);
					desaloca(mat, a);								// Exclui a matriz principal 
					mat = criaMat(novo_a, novo_b);					// Aloca novamento com novo tamanho
					copia(mat, mprvs, novo_a, novo_b);				// copia a matriz modificada para a principal
					imprime(mprvs, novo_a,novo_b);			
					desaloca(mprvs, novo_a);						// desaloca matriz secundaria
				}else if(op == 6){
					novo_a = a;
					novo_b = b;
					cout << "Preenchimento de area" << endl;
					int ind_i,ind_j;
					char trocar_para[2];
					cout << "Posicao (x) :";
					cin >> x;
					cout << "Posicao (y) :";
					cin >> y;
					cin.ignore();
					cout << "Por qual caracter deseja trocar: ";
					cin.getline(trocar_para, 2);
					char aux = trocar_para[0];
					checa(mat, a, b,x,y,aux);
					imprime(mat, novo_a,novo_b);			

				}
				else{
					cout << "******OPCAO INVALIDA******" << endl;
				}
				a = novo_a;
				b = novo_b;
				cout << endl;				
			}		
		}else{
			cout << "******OPCAO INVALIDA******" << endl;
		}	
	}
	delete(nome);	
	desaloca(mat, a);
	return 0;
}
