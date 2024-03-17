/*
Trabalho prático de Matemática Discreta - Fractais
Aluna: Carla Beatriz Ferreira
Data de entrega: 31 de maio de 2023

3 programas da parte 1:
(i) - Somatório da matrícula = 33 = (4*8) + (1) = 1 - Floco de neve onda senoidal 1 de von Koch
(ii) - Matrícula par - Preenchimento de espaço de Hilbert
(iii) - Fractal definido por mim

--------
Entrada Floco de neve onda senoidal 1 de von Koch
linha 1: Axioma = F
linha 2: Angulo dado em graus = 60
linha 3: Regra = F-F++FF-F+F (1° versão no pdf de entradas e saidas)
                 F++FF--F+F (versão 20 de maio no arquivo de enunciado)
--------

*/

//PROGRAMA PARA 1 - (i) - O FLOCO DE NEVE ONDA SENOIDAL 1 DE VON KOCH
#include <stdio.h>
#include <math.h>
#include <string.h>

//Função considerando que o arquivo original já será passado apontando para a posição correta.
void Aplicar_a_regra(FILE *arq_original, FILE *arq_destino, char* regra, char axioma);
void Copia_conteudo_arquivo(FILE *arq_original, FILE *arq_destino);
int Conta_quantidade (FILE *arq_original, char caractere, int posicao_fseek);

int main(){

    //Entradas
    char axioma = 'F';
    int angulo = 60; //não utilizado para aplicar a regra
    char regra[] = "F++FF--F+F"; //char regra[11]

    int quantidade_F = 0;
    int quantidade_simbolos = 0;

    //Arquivos
    //poderia ter um arquivo0 = axioma, se necessário
    FILE *arquivo1 = fopen("arquivo1.txt","w+");
    FILE *arquivo2 = fopen("arquivo2.txt","w+");
    FILE *arquivo3 = fopen("arquivo3.txt","w+");
    FILE *arquivo4 = fopen("arquivo4.txt","w+");
    FILE *arquivo_quantidade_simbolos = fopen("quanidade_simbolos.txt","w+");

    if(arquivo1 == NULL || arquivo2 == NULL || arquivo3 == NULL || arquivo4 == NULL || arquivo_quantidade_simbolos == NULL)
    {
        printf("\nErro na abertura dos arquivos!");
        return 1;
    }

    //ITERAÇÃO 1:
    fprintf(arquivo1, "%s", "Estagio 1: \n");
    fprintf(arquivo1, "%s", regra);

    //ITERAÇÃO 2:
    fseek(arquivo1, 12, SEEK_SET ); //para apontar para a segunda linha do arquivo
    fprintf(arquivo2, "%s", "\n\nEstagio 2: \n"); // \n\n para melhor visualização no aquivo final
    Aplicar_a_regra(arquivo1, arquivo2, regra, axioma);

    //ITERAÇÃO 3:
    fseek(arquivo2, 14, SEEK_SET ); //14 por conta das duas quebra de linhas
    fprintf(arquivo3, "%s", "\n\nEstagio 3: \n");
    Aplicar_a_regra(arquivo2, arquivo3, regra, axioma);

    //ITERAÇÃO 4:
    fseek(arquivo3, 14, SEEK_SET );
    fprintf(arquivo4, "%s", "\n\nEstagio 4: \n");
    Aplicar_a_regra(arquivo3, arquivo4, regra, axioma);

    //QUANTIDADE DE SIMBOLOS
    fprintf(arquivo_quantidade_simbolos, "%s", "\n\n| n \t | #F \t | #Símbolos \t | \n");

    // n = 1
    quantidade_F = Conta_quantidade(arquivo1, 'F', 12);
    quantidade_simbolos = quantidade_F + Conta_quantidade(arquivo1, '+', 12) + Conta_quantidade(arquivo1, '-', 12);
    fprintf(arquivo_quantidade_simbolos, "| 1 \t | %i \t | %i \t\t\t | \n", quantidade_F, quantidade_simbolos);

    // n = 2
    quantidade_F = Conta_quantidade(arquivo2, 'F', 14);
    quantidade_simbolos = quantidade_F + Conta_quantidade(arquivo2, '+', 14) + Conta_quantidade(arquivo2, '-', 14);
    fprintf(arquivo_quantidade_simbolos, "| 2 \t | %i \t | %i \t\t\t | \n", quantidade_F, quantidade_simbolos);

    // n = 3
    quantidade_F = Conta_quantidade(arquivo3, 'F', 14);
    quantidade_simbolos = quantidade_F + Conta_quantidade(arquivo3, '+', 14) + Conta_quantidade(arquivo3, '-', 14);
    fprintf(arquivo_quantidade_simbolos, "| 3 \t | %i \t | %i \t\t\t | \n", quantidade_F, quantidade_simbolos);

    // n = 4
    quantidade_F = Conta_quantidade(arquivo4, 'F', 14);
    quantidade_simbolos = quantidade_F + Conta_quantidade(arquivo4, '+', 14) + Conta_quantidade(arquivo4, '-', 14);
    fprintf(arquivo_quantidade_simbolos, "| 4 \t | %i \t | %i \t\t | \n", quantidade_F, quantidade_simbolos);
    
    //SE NECESSÁRIO JUNTAR TUDO EM UM SÓ ARQUIVO, verificar nas especificações da monitora:
    FILE *arquivo_final = fopen("i-arquivo.txt","w");
    if(arquivo_final == NULL)
    {
        printf("\nErro na abertura do arquivo final!");
        return 2;
    }
  
    fseek(arquivo1, 0, SEEK_SET);
    fseek(arquivo2, 0, SEEK_SET);
    fseek(arquivo3, 0, SEEK_SET);
    fseek(arquivo4, 0, SEEK_SET);
    fseek(arquivo_quantidade_simbolos, 0, SEEK_SET);

    Copia_conteudo_arquivo(arquivo1, arquivo_final);
    Copia_conteudo_arquivo(arquivo2, arquivo_final);
    Copia_conteudo_arquivo(arquivo3, arquivo_final);
    Copia_conteudo_arquivo(arquivo4, arquivo_final);
    Copia_conteudo_arquivo(arquivo_quantidade_simbolos, arquivo_final);

    //-------
    fclose(arquivo1);
    fclose(arquivo2);
    fclose(arquivo3);
    fclose(arquivo4);
    fclose(arquivo_quantidade_simbolos);
    fclose(arquivo_final);

    //-------
    remove("arquivo1.txt");
    remove("arquivo2.txt");
    remove("arquivo3.txt");
    remove("arquivo4.txt");
    remove("quanidade_simbolos.txt");
  
    return 0;
}

void Aplicar_a_regra(FILE *arq_original, FILE *arq_destino, char* regra, char axioma)
{
    char c = fgetc(arq_original);
    while (c != EOF)
    {
      if (c == axioma) // se igual ao axioma
      {
        //fprintf(arq_destino, "%s", "\n"); //pode ser utilizado para melhor visualização
        fprintf(arq_destino, "%s", regra);
      } else
      {
        fputc(c, arq_destino);
      }
      c = fgetc(arq_original);
    }
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
    return (quantidade);
}
