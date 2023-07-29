#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>



void menuPrincipal(){//apenas mostra na tela o menu principal, também não possui funcionalidade dinâmica
    printf("\n========================================="); 
    printf("\n            Menu Principal");
    printf("\n=========================================");
    printf("\nOpoções:"); 
    printf("\n1 - Ler turma e estudantes do arquivo"); 
    printf("\n2 - Imprimir turma de estudantes");
    printf("\n3 - Imprimir estatísticas da turma");
    printf("\n4 - Cadastrar novo estudante");
    printf("\n5 - Editar informações de um estudante");
    printf("\n6 - Reler turma de estudantes do arquivo");
    printf("\n0 - Salvar e Sair");
    printf("\n"); 
    printf("Digite um opção:");
}

void lerTurma(){ //apenas mostra na tela o menu da opção 1 do menu principal , não possui funcionalidade dinâmica
    printf("\n========================================="); 
    printf("\n               Ler Turma");
    printf("\n=========================================");
    printf("\nOpoções:"); 
    printf("\n1 - Ler turma existente"); 
    printf("\n2 - Criar nova turma");
    printf("\n3 - Voltar ao menu principal");
    printf("\nDigite um opção:");
}

void existe(){ //está função vai verificar se o arquivo que foi digitado para ser criado já existe . Caso já existir ele retorna para o menu anterior. 
    char nome[15];
    printf("Digite o nome do arquivo de texto com a turma:");
    scanf("%s", nome); 
    FILE* arq = fopen(nome, "r"); 
    if(arq){
        printf("Arquivo %s lido com sucesso!",nome);
    }else{
        printf("Arquivo %s não existe!", nome); 
        lerTurma();
        swichSecundario();
    }
}
void criarArquivo(){ //função responsável pela criação do novo arquivo fazendo parte das très funcionalidades do menu da opção 1.
    char novoArquivo[11]; 
    char resposta;
    printf("Digite o nome do arquivo:");
    scanf("%s", novoArquivo); 

    FILE* newarq = fopen(novoArquivo, "r"); 

    if(newarq != NULL){
        printf("O arquivo %s já existe.",novoArquivo);
        fclose(newarq);
        printf("Deseja sobreescreve-lo? (S/N)");
        scanf("%s", &resposta);
        switch (resposta){ 
        case 's':
            newarq = fopen(novoArquivo, "w");
            break;
        case 'n':
            break;
        default:
            break;
        }
    }
    else{
    FILE* newarq = fopen(novoArquivo, "a"); 
    fclose(newarq); 

    printf("\nAquivo criado!!");
    }
}

void swichSecundario(){//realiza a funcionalidade do segundo menu o que pertence somente a opção 1 do menu principal .
    int opcaoDeLeitura; 
    scanf("%d", &opcaoDeLeitura);
        switch (opcaoDeLeitura)
        {
        case 1:
            existe();
            break;
        case 2:
            criarArquivo(); 
            lerTurma();
            swichSecundario();
            break;
        case 3:
            menuPrincipal();
            swichPrimario(); 
            break;
        default:
            break;
        };
}
typedef struct 
{
    char nome[50],matricula[11]; 
    float n1,n2,n3,t1,t2; 
    int faltas ; 
    char sit[1]; 

}Aluno;

Aluno novo;

void swichPrimario(){ //Aqui está o corpo pricipal da aplicação onde consta a união de todas as funções ela que vai passar a funcionalidade do menu principal.
     Aluno *turma[50]; 
    char arquivo[] = {"texto.txt"}; //variável muito importante é este arquivo que vai ser buscado, é importante que ele já exista na pasta antes de testar a aplicação . 
    int tam = 50, quant = 0, opc; 
    do{ 
    menuPrincipal();
    scanf("%d", &opc); 
    switch (opc)
    {
    case 1:
        lerTurma();
        swichSecundario();
        break;
    case 2:
        imprimir(turma,quant);
        break;
    case 3:
        printf("Você escolheu a opcao 3");
        break;
    case 4:
        getchar();
        quant += cadastrar_aluno(turma, quant, tam);
        break;
    case 5:
        alterar_aluno(turma, quant);
        break;
    case 6:
        quant = ler_arquivo(turma, arquivo);
        break;
    case 0:
        salvar(turma,quant,arquivo);
        break;
    default:
    if(opc !=0)
        printf("\n\tOpcao invalida!!\n"); 
        break;
    }
    }while(opc); 
    return 0 ; 
}

void imprimir(Aluno **c, int quant){ //está função vai se a que mostra o que foi cadastrado como se fosse um comprovante do que foi feito . 
    int i; 

    printf("\t------------------------------------------------------------------------------------\n");
    printf("\n\t                             Estudantes                                           \n");
    printf("\t------------------------------------------------------------------------------------\n");
    printf("\t     Nome\tMatrícula\tN1\tN2\tN3\tT1\tT2\tFal\tFinal\tSit\n"); 
    for(i = 0 ; i < quant;i++){
        printf("\t%d = %s\t%s\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%d\n",  i+1,c[i]->nome,c[i]->matricula,c[i]->n1,c[i]->n2,c[i]->n3,c[i]->t1,c[i]->t2,c[i]->faltas); 
    }
    printf("\t------------------------------------------\n");
}

int cadastrar_aluno(Aluno **c, int quant, int tam){ //realiza o cadastro do novo aluno 
    if(quant<tam){
        Aluno *novo = malloc(sizeof(Aluno));  
        printf("\nDigite o nome:"); 
        scanf("%50[^\n]", novo->nome); 
        printf("\nDigite a matricula:");
        scanf("%s", &novo->matricula);
        printf("\nDigite as três notas da prova:");
        scanf("%f %f %f", &novo->n1,&novo->n2,&novo->n3);
        printf("\nDigite as duas notas dos trabalhos:");
        scanf("%f %f", &novo->t1,&novo->t2);
        printf("\nDigite o número de faltas:");
        scanf("%d", &novo->faltas); 
        getchar();
        c[quant] = novo;
        return 1;
    }else{
        printf("\n\tImpossível fazer novo cadastro. Vetor cheio!\n");
        return 0;
    }
}

void alterar_aluno(Aluno **c, int quant){// executa a funcionalidade de alterar um aluno que já foi cadastrado. Obs: funciona apenas se estiver salvado primeiro . 
    int id; 

    imprimir(c, quant); 

    printf("\n\tDigite o código do contato que deseja alterar:\n");
    scanf("%d", &id); 
    getchar(); 
    id--;  

    if(id >= 0 && id < quant){
        Aluno *novo = malloc(sizeof(Aluno)); 
        printf("\nDigite o nome:"); 
        scanf("%50[^\n]", novo->nome); 
        printf("\nDigite a matricula:");
        scanf("%s", &novo->matricula);
        printf("\nDigite as três notas da prova:");
        scanf("%f%f%f", &novo->n1,&novo->n2,&novo->n3);
        printf("\nDigite as duas notas dos trabalhos:");
        scanf("%f %f",&novo->t1,&novo->t2);
        printf("\nDigite o número de faltas:");
        scanf("%d", &novo->faltas);
        getchar();
        c[id] = novo;
    }
    else{ 
        printf("\n\tCodigo invalido!\n");
    }
        
}
void salvar(Aluno **c,int quant, char arq[]){ //função que vai salvar o cadastro ou a alteração 
    FILE *file = fopen(arq, "w");
    int i;
    if(file){
        fprintf(file, "%d\n", quant); 
    for ( i = 0; i < quant; i++)
    {
        fputs(c[i]->nome, file);
        fputc('\n',file); 
        fprintf(file,"%s\n",c[i]->matricula);
        fprintf(file,"%f %f %f",c[i]->n1,c[i]->n2,c[i]->n3);
        fprintf(file, " %f %f\n", c[i]->t1,c[i]->t2);
        fprintf(file,"%d\n", c[i]->faltas);
    }
    printf("Arquivo salvo com sucesso!!");
    fclose(file);

    }
    else
    printf("\n\tNÃO FOI POSSIVEL ABRIR/CRIAR O ARQUIVO!\n");
}

int ler_arquivo(Aluno **c , char arq[]){//função responsável por fazer a leitura do arquivo depois de alterado e salvado. 
     FILE *file = fopen(arq, "r"); 
    int quant= 0, i; 
    Aluno *novo = malloc(sizeof(Aluno));

    if(file){
        fscanf(file, "%d\n", &quant); 
        for ( i = 0; i < quant; i++){
            fscanf(file,"%50[^\n]", novo->nome);
            fscanf(file,"%s\n", &novo->matricula);
            fscanf(file,"%f%f%f\n", &novo->n1,&novo->n2,&novo->n3);
            fscanf(file, "%f%f\n", &novo->t1,&novo->t2);
            fscanf(file, "%d\n",&novo->faltas);
            c[i] = novo; 
            
            novo = malloc(sizeof(Aluno)); 
        }
        fclose(file);
        
    }else
        printf("\n\tNAO FOI POSSIVEL ABRIR/CRIAR O ARQUIVO!\n");
    return quant; 
}




int main (void)//função principal da aplicação onde se encontra as duas funções secundárias do menu e a excução do primeiro switch onde está as outras funcionalidades .
{
menuPrincipal();
swichPrimario();
}


