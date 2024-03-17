/*
Trabalho prático de Matemática Discreta - Fractais
Aluna: Carla Beatriz Ferreira
Data de entrega: 31 de maio de 2023

3 programas da parte 1:
(i) - Somatório da matrícula = 33 = (4*8) + (1) = 1 - Floco de neve onda senoidal 1 de von Koch
(ii) - Matrícula par - Preenchimento de espaço de Hilbert
(iii) - Fractal definido por mim

--------
Entrada meu axioma (gatinho/batman):
linha 1: Axioma = X
linha 2: Angulo dado em graus = 60
linha 3: Regra = 
X = --YF+FF++F-FF-F++FF+F--
Y = ++XF-FF--F+FF+F--FF-F+ (com um + a menos na simetria)
--------

*/

//PROGRAMA PARA 1 - (iii) - FRACTAL DEFINIDO POR MIM - Floco de gato
#include <stdio.h>
#include <math.h>
#include <string.h>


//Função considerando que o arquivo original já será passado apontando para a posição correta.
void Aplicar_a_regra(FILE *arq_original, FILE *arq_destino, char* primeira_regra, char nome_primeira_regra, char* segunda_regra, char nome_segunda_regra);
void Remover_simbolos_da_regra(FILE* arquivo, char Primeiro_simbolo_a_remover, char Segundo_simbolo_a_remover);
void Copia_conteudo_arquivo(FILE *arq_original, FILE *arq_destino);
int Conta_quantidade (FILE *arq_original, char caractere, int posicao_fseek);

int main(){

    //Entradas
    //char axioma = 'X';
    //int angulo = 60; //não utilizado para aplicar a regra
    char Regra_X[] = "--YF+FF++F-FF-F++FF+F--"; //char Regra_X[12]
    char Regra_Y[] = "++XF-FF--F+FF+F--FF-F+";
    char nome_regra1 = 'X';
    char nome_regra2 = 'Y';

    int quantidade_F = 0;
    int quantidade_simbolos = 0;
    int quantidade_X = 0;
    int quantidade_Y = 0;
    int quantidade_mais = 0;
    int quantidade_menos = 0;

    //Arquivos
    //poderia ter um arquivo0 = axioma, se necessário
    FILE *arquivo1 = fopen("arquivo1.txt","w+");
    FILE *arquivo2 = fopen("arquivo2.txt","w+");
    FILE *arquivo3 = fopen("arquivo3.txt","w+");
    FILE *arquivo4 = fopen("arquivo4.txt","w+");
    FILE *arquivo5 = fopen("arquivo5.txt","w+");
    FILE *arquivo6 = fopen("arquivo6.txt","w+");
    FILE *arquivo7 = fopen("arquivo7.txt","w+");
    FILE *arquivo_quantidade_simbolos = fopen("quanidade_simbolos.txt","w+");

    if(arquivo1 == NULL || arquivo2 == NULL || arquivo3 == NULL || arquivo4 == NULL || arquivo5 == NULL || arquivo6 == NULL || arquivo7 == NULL || arquivo_quantidade_simbolos == NULL)
    {
        printf("\nErro na abertura dos arquivos!");
        return 1;
    }

    //QUANTIDADE DE SIMBOLOS
    fprintf(arquivo_quantidade_simbolos, "%s", "\n\n| n \t | #F \t | #Símbolos \t\t | #X \t\t | #Y \t\t | #+ \t | #- \t | \n");
  
    //ITERAÇÃO 1:
    fprintf(arquivo1, "%s", "Estagio 1: \n");
    fprintf(arquivo1, "%s", Regra_X);

    quantidade_F = Conta_quantidade(arquivo1, 'F', 12);
    quantidade_X = Conta_quantidade(arquivo1, 'X', 12);
    quantidade_Y = Conta_quantidade(arquivo1, 'Y', 12);
    quantidade_mais = Conta_quantidade(arquivo1, '+', 12);
    quantidade_menos = Conta_quantidade(arquivo1, '-', 12);
    quantidade_simbolos = quantidade_F + quantidade_mais + quantidade_menos ;
    fprintf(arquivo_quantidade_simbolos, "| 1 \t | %i \t | %i \t\t\t\t | %i \t\t | %i \t\t | %i \t | %i \t | \n", quantidade_F, quantidade_simbolos, quantidade_X, quantidade_Y, quantidade_mais, quantidade_menos);

    //ITERAÇÃO 2:
    fseek(arquivo1, 12, SEEK_SET); //para apontar para a segunda linha do arquivo
    fprintf(arquivo2, "%s", "\nEstagio 2: \n");
    Aplicar_a_regra(arquivo1, arquivo2, Regra_X, nome_regra1, Regra_Y, nome_regra2);

    quantidade_F = Conta_quantidade(arquivo2, 'F', 12);
    quantidade_simbolos = quantidade_F + Conta_quantidade(arquivo2, '+', 12) + Conta_quantidade(arquivo2, '-', 12);
    quantidade_X = Conta_quantidade(arquivo2, 'X', 12);
    quantidade_Y = Conta_quantidade(arquivo2, 'Y', 12);
    quantidade_mais = Conta_quantidade(arquivo2, '+', 12);
    quantidade_menos = Conta_quantidade(arquivo2, '-', 12);
    quantidade_simbolos = quantidade_F + quantidade_mais + quantidade_menos ;
    fprintf(arquivo_quantidade_simbolos, "| 2 \t | %i \t | %i \t\t\t\t | %i \t\t | %i \t\t | %i \t | %i \t | \n", quantidade_F, quantidade_simbolos, quantidade_X, quantidade_Y, quantidade_mais, quantidade_menos);

    //ITERAÇÃO 3:
    fseek(arquivo2, 13, SEEK_SET);
    fprintf(arquivo3, "%s", "\nEstagio 3: \n");
    Aplicar_a_regra(arquivo2, arquivo3, Regra_X, nome_regra1, Regra_Y, nome_regra2);

    quantidade_F = Conta_quantidade(arquivo3, 'F', 12);
    quantidade_simbolos = quantidade_F + Conta_quantidade(arquivo3, '+', 12) + Conta_quantidade(arquivo3, '-', 12);
    quantidade_X = Conta_quantidade(arquivo3, 'X', 12);
    quantidade_Y = Conta_quantidade(arquivo3, 'Y', 12);
    quantidade_mais = Conta_quantidade(arquivo3, '+', 12);
    quantidade_menos = Conta_quantidade(arquivo3, '-', 12);
    quantidade_simbolos = quantidade_F + quantidade_mais + quantidade_menos ;
    fprintf(arquivo_quantidade_simbolos, "| 3 \t | %i \t | %i \t\t\t\t | %i \t\t | %i \t\t | %i \t | %i \t | \n", quantidade_F, quantidade_simbolos, quantidade_X, quantidade_Y, quantidade_mais, quantidade_menos);

    //ITERAÇÃO 4:
    fseek(arquivo3, 13, SEEK_SET);
    fprintf(arquivo4, "%s", "\nEstagio 4: \n");
    Aplicar_a_regra(arquivo3, arquivo4, Regra_X, nome_regra1, Regra_Y, nome_regra2);

    quantidade_F = Conta_quantidade(arquivo4, 'F', 12);
    quantidade_simbolos = quantidade_F + Conta_quantidade(arquivo4, '+', 12) + Conta_quantidade(arquivo4, '-', 12);
    quantidade_X = Conta_quantidade(arquivo4, 'X', 12);
    quantidade_Y = Conta_quantidade(arquivo4, 'Y', 12);
    quantidade_mais = Conta_quantidade(arquivo4, '+', 12);
    quantidade_menos = Conta_quantidade(arquivo4, '-', 12);
    quantidade_simbolos = quantidade_F + quantidade_mais + quantidade_menos ;
    fprintf(arquivo_quantidade_simbolos, "| 4 \t | %i \t | %i \t\t\t\t | %i \t\t | %i \t\t | %i \t | %i \t | \n", quantidade_F, quantidade_simbolos, quantidade_X, quantidade_Y, quantidade_mais, quantidade_menos);

    //ITERAÇÃO 5:
    fseek(arquivo4, 13, SEEK_SET);
    fprintf(arquivo5, "%s", "\nEstagio 5: \n");
    Aplicar_a_regra(arquivo4, arquivo5, Regra_X, nome_regra1, Regra_Y, nome_regra2);

    quantidade_F = Conta_quantidade(arquivo5, 'F', 12);
    quantidade_simbolos = quantidade_F + Conta_quantidade(arquivo5, '+', 12) + Conta_quantidade(arquivo5, '-', 12);
    quantidade_X = Conta_quantidade(arquivo5, 'X', 12);
    quantidade_Y = Conta_quantidade(arquivo5, 'Y', 12);
    quantidade_mais = Conta_quantidade(arquivo5, '+', 12);
    quantidade_menos = Conta_quantidade(arquivo5, '-', 12);
    quantidade_simbolos = quantidade_F + quantidade_mais + quantidade_menos ;
    fprintf(arquivo_quantidade_simbolos, "| 5 \t | %i \t | %i \t\t\t\t | %i \t\t | %i \t\t | %i \t | %i \t | \n", quantidade_F, quantidade_simbolos, quantidade_X, quantidade_Y, quantidade_mais, quantidade_menos);

    //ITERAÇÃO 6:
    fseek(arquivo5, 13, SEEK_SET);
    fprintf(arquivo6, "%s", "\nEstagio 6: \n");
    Aplicar_a_regra(arquivo5, arquivo6, Regra_X, nome_regra1, Regra_Y, nome_regra2);

    quantidade_F = Conta_quantidade(arquivo6, 'F', 12);
    quantidade_simbolos = quantidade_F + Conta_quantidade(arquivo6, '+', 12) + Conta_quantidade(arquivo6, '-', 12);
    quantidade_X = Conta_quantidade(arquivo6, 'X', 12);
    quantidade_Y = Conta_quantidade(arquivo6, 'Y', 12);
    quantidade_mais = Conta_quantidade(arquivo6, '+', 12);
    quantidade_menos = Conta_quantidade(arquivo6, '-', 12);
    quantidade_simbolos = quantidade_F + quantidade_mais + quantidade_menos ;
    fprintf(arquivo_quantidade_simbolos, "| 6 \t | %i \t | %i \t\t\t\t | %i \t\t | %i \t\t | %i \t | %i \t | \n", quantidade_F, quantidade_simbolos, quantidade_X, quantidade_Y, quantidade_mais, quantidade_menos);

    //ITERAÇÃO 7:
    fseek(arquivo6, 13, SEEK_SET);
    fprintf(arquivo7, "%s", "\nEstagio 7: \n");
    Aplicar_a_regra(arquivo6, arquivo7, Regra_X, nome_regra1, Regra_Y, nome_regra2);

    quantidade_F = Conta_quantidade(arquivo7, 'F', 12);
    quantidade_simbolos = quantidade_F + Conta_quantidade(arquivo7, '+', 12) + Conta_quantidade(arquivo7, '-', 12);
    quantidade_X = Conta_quantidade(arquivo7, 'X', 12);
    quantidade_Y = Conta_quantidade(arquivo7, 'Y', 12);
    quantidade_mais = Conta_quantidade(arquivo7, '+', 12);
    quantidade_menos = Conta_quantidade(arquivo7, '-', 12);
    quantidade_simbolos = quantidade_F + quantidade_mais + quantidade_menos ;
    fprintf(arquivo_quantidade_simbolos, "| 7 \t | %i \t | %i \t\t\t\t | %i \t\t | %i \t\t | %i \t | %i \t | \n", quantidade_F, quantidade_simbolos, quantidade_X, quantidade_Y, quantidade_mais, quantidade_menos);

    //REMOVER SIMBOLOS DA REGRA
    fseek(arquivo1, 12, SEEK_SET);
    Remover_simbolos_da_regra(arquivo1, nome_regra1, nome_regra2);
   
    fseek(arquivo2, 13, SEEK_SET);
    Remover_simbolos_da_regra(arquivo2, nome_regra1, nome_regra2);

    fseek(arquivo3, 13, SEEK_SET);
    Remover_simbolos_da_regra(arquivo3, nome_regra1, nome_regra2);

    fseek(arquivo4, 13, SEEK_SET);
    Remover_simbolos_da_regra(arquivo4, nome_regra1, nome_regra2);

    fseek(arquivo5, 13, SEEK_SET);
    Remover_simbolos_da_regra(arquivo5, nome_regra1, nome_regra2);

    fseek(arquivo6, 13, SEEK_SET);
    Remover_simbolos_da_regra(arquivo6, nome_regra1, nome_regra2);

    fseek(arquivo7, 13, SEEK_SET);
    Remover_simbolos_da_regra(arquivo7, nome_regra1, nome_regra2);

    //SE NECESSÁRIO JUNTAR TUDO EM UM SÓ ARQUIVO:
    FILE *arquivo_final = fopen("iii-arquivo.txt","w");
    if(arquivo_final == NULL)
    {
        printf("\nErro na abertura do arquivo final!");
        return 2;
    }
  
    fseek(arquivo1, 0, SEEK_SET);
    fseek(arquivo2, 0, SEEK_SET);
    fseek(arquivo3, 0, SEEK_SET);
    fseek(arquivo4, 0, SEEK_SET);
    fseek(arquivo5, 0, SEEK_SET);
    fseek(arquivo6, 0, SEEK_SET);
    fseek(arquivo7, 0, SEEK_SET);
    fseek(arquivo_quantidade_simbolos, 0, SEEK_SET);

    Copia_conteudo_arquivo(arquivo1, arquivo_final);
    Copia_conteudo_arquivo(arquivo2, arquivo_final);
    Copia_conteudo_arquivo(arquivo3, arquivo_final);
    Copia_conteudo_arquivo(arquivo4, arquivo_final);
    Copia_conteudo_arquivo(arquivo5, arquivo_final);
    Copia_conteudo_arquivo(arquivo6, arquivo_final);
    Copia_conteudo_arquivo(arquivo7, arquivo_final);
    Copia_conteudo_arquivo(arquivo_quantidade_simbolos, arquivo_final);

    //-------
    fclose(arquivo1);
    fclose(arquivo2);
    fclose(arquivo3);
    fclose(arquivo4);
    fclose(arquivo5);
    fclose(arquivo6);
    fclose(arquivo7);
    fclose(arquivo_quantidade_simbolos);
    fclose(arquivo_final);

    //-------
    remove("arquivo1.txt");
    remove("arquivo2.txt");
    remove("arquivo3.txt");
    remove("arquivo4.txt");
    remove("arquivo5.txt");
    remove("arquivo6.txt");
    remove("arquivo7.txt");
    remove("quanidade_simbolos.txt");
    return 0;
}

void Aplicar_a_regra(FILE *arq_original, FILE *arq_destino, char* primeira_regra, char nome_primeira_regra, char* segunda_regra, char nome_segunda_regra)
{
    char c = fgetc(arq_original);
    while (c != EOF)
    {
      if (c == nome_primeira_regra) // se igual ao axioma
      {
        //fprintf(arq_destino, "%s", "\n"); //pode ser utilizado para melhor visualização
        fprintf(arq_destino, "%s", primeira_regra);
      }else {
        if (c == nome_segunda_regra)
        {
          //fprintf(arq_destino, "%s", "\n"); //!
          fprintf(arq_destino, "%s", segunda_regra);
        } else
        {
          //fprintf(arq_destino, "%s", " else "); 
          fputc(c, arq_destino);
        }
      }
      c = fgetc(arq_original);
    }
}

void Remover_simbolos_da_regra(FILE* arquivo, char Primeiro_simbolo_a_remover, char Segundo_simbolo_a_remover)
{
  FILE *arq_aux = fopen("arquivo_aux.txt","w+");
  
  //copiar arquivo para um arquivo auxiliar
  Copia_conteudo_arquivo(arquivo, arq_aux);
  fprintf(arquivo, "%s", "\n\nEstagio sem X e Y: \n");
  //apontar o auxiliar para o inicio
  fseek(arq_aux, 0, SEEK_SET);
  char c = fgetc(arq_aux);
  while (c != EOF)
  {
    if (c != Primeiro_simbolo_a_remover && c != Segundo_simbolo_a_remover)
    {
      fputc(c, arquivo);
    } //se igual, não faça nada
    c = fgetc(arq_aux);
  }
  fprintf(arquivo, "%s", "\n\n-----------\n"); // Para melhor visualização no arquivo FINAL
  fclose(arq_aux);
  remove("arquivo_aux.txt");
}

void Copia_conteudo_arquivo(FILE *arq_original, FILE *arq_destino)
{
    char c = fgetc(arq_original);
    while (c != EOF)
    {
      fputc(c, arq_destino);
      c = fgetc(arq_original);
    }
}

int Conta_quantidade (FILE *arq_original, char caractere, int posicao_fseek)
{
    int quantidade = 0;
    fseek(arq_original, posicao_fseek, SEEK_SET);
    char c = fgetc(arq_original);
    while (c != EOF)
    {
      if (c == caractere)
      {
        quantidade++;
      }
      c = fgetc(arq_original);
    }
    //printf ("\n Quantidade de %c: %i", caractere, quantidade);
    return (quantidade);
}
