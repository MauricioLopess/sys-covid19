#include <stdio.h>
#include <locale.h> //acentuacao no programa

struct tp_endereco {
	char estado[30], cidade[30], bairro[30], rua[30], cep[15];
	int n_casa;
};

struct tp_dnascimento{
	int d_nascimento;
	int m_nascimento;
	int a_nascimento;
};

struct tp_ficha_paciente {
    char nome[40], email[30], comorbidades[40], tel[15];
    char data_cadastro[15];                 //estrutura do paciente
    char sexo, s_comorbidade, s_email;
    char cpf [17];
    int idade;

    struct tp_endereco endereco;      //estrutura de tipo endereco
    struct tp_dnascimento dnascimento;//estrutura de tipo data de nascimento
};

typedef struct tp_ficha_paciente Ficha_paciente;

int a_atual = 2021;
char keyboard [BUFSIZ]; //limpeza do buffer
int tam_lista = 20;
Ficha_paciente lista[20];
int quant_paciente_lista = 0;

int cadastrar(void){
    system("CLS");
	if(quant_paciente_lista <= tam_lista){
		Ficha_paciente paciente;
	    printf("\n\t\t –- Cadastrar paciente --\n\n ");
	    printf(" Preencha os dados abaixo\n\n");

	    printf(" Nome: ");
	    setbuf(stdin, keyboard);
	    scanf (" %40[^\n]s", paciente.nome);

	    printf(" Sexo (m ou f): ");
	    setbuf(stdin, keyboard);
	    paciente.sexo = getchar();

	    printf(" CPF: ");
	    setbuf(stdin, keyboard);
	    scanf (" %17[^\n]s", paciente.cpf);

	    printf(" Dia de nascimento: ");
	    setbuf(stdin, keyboard);
	    scanf (" %d", &paciente.dnascimento.d_nascimento);

        printf(" Mes de nascimento(em número): ");
        setbuf(stdin, keyboard);
        scanf (" %d", &paciente.dnascimento.m_nascimento);

        printf(" Ano de nascimento: ");
       	setbuf(stdin, keyboard);
        scanf (" %d", &paciente.dnascimento.a_nascimento);
        paciente.idade = (a_atual - paciente.dnascimento.a_nascimento);

	    printf(" Possui e-mail? (s ou n) ");
	    setbuf(stdin, keyboard);
	    paciente.s_email = getchar();
	    if (paciente.s_email == 's'){
            printf(" Digite seu e-mai: ");
            setbuf(stdin, keyboard);
            scanf (" %30[^\n]s", paciente.email);
        }else{
            paciente.email[0] = 'N';
            paciente.email[1] = '/';
            paciente.email[2] = 'A';
        }

	    printf(" Telefone: ");
       	setbuf(stdin, keyboard);
        scanf (" %15[^\n]s", paciente.tel);

	    printf (" CEP: ");
        setbuf(stdin, keyboard);
        scanf (" %15[^\n]s", paciente.endereco.cep);

	    printf(" Cidade: ");
        setbuf(stdin, keyboard);
        scanf (" %30[^\n]s", paciente.endereco.cidade);

	    printf(" Estado: ");
        setbuf(stdin, keyboard);
        scanf (" %30[^\n]s", paciente.endereco.estado);

	    printf(" Rua: ");
        setbuf(stdin, keyboard);
        scanf (" %30[^\n]s", paciente.endereco.rua);

	    printf(" Número de residência: ");
        setbuf(stdin, keyboard);
        scanf (" %d", &paciente.endereco.n_casa);

	    printf(" Bairro: ");
        setbuf(stdin, keyboard);
        scanf (" %30[^\n]s", paciente.endereco.bairro);

        printf(" Possui comorbidades? (s ou n) ");
        setbuf(stdin, keyboard);
        paciente.s_comorbidade = getchar();
        if (paciente.s_comorbidade == 's'){
            printf(" Quais? ");
            setbuf(stdin, keyboard);
            scanf (" %40[^\n]s", paciente.comorbidades);
        }else{
            paciente.comorbidades[0] = 'N';
            paciente.comorbidades[1] = '/';
            paciente.comorbidades[2] = 'A';
        }

	    printf(" Data do cadastro(dd/mm/aaaa): ");
	    setbuf(stdin, keyboard);
	    scanf (" %15[^\n]s", paciente.data_cadastro);

	    lista[quant_paciente_lista] = paciente; //Foram passados os pacientes para a
	    quant_paciente_lista++;					//struct "lista"

        system("CLS");
        printf(" Paciente cadastrado com sucesso!\n\n");
	    return 1;
	}
	else{
		printf ("Erro ao cadastrar paciente, a lista esta cheia");
		return 0;
	}
}

int consultar(void){
    system("CLS");
    printf("\n   Pacientes \n\n");
    int i = 0;
    for (i = 0; i < quant_paciente_lista; i++){
    	printf(" Paciente %d\n", i);
    	printf(" Nome: %s\n", lista[i].nome);
	    printf(" Sexo: %c\n", lista[i].sexo);
	    printf(" CPF: %s\n", lista[i].cpf);
	    printf(" Data de nascimento: %d/%d/%d\n", lista[i].dnascimento.d_nascimento, lista[i].dnascimento.m_nascimento, lista[i].dnascimento.a_nascimento);
	    printf(" E-mail: %s\n", lista[i].email);
	    printf(" Telefone: %s\n", lista[i].tel);
	    printf(" Cidade: %s\n", lista[i].endereco.cidade);
	    printf(" Estado: %s\n", lista[i].endereco.estado);
	    printf(" Rua: %s\n", lista[i].endereco.rua);
	    printf(" Número residêncial: %d\n", lista[i].endereco.n_casa);
	    printf(" Bairro: %s\n", lista[i].endereco.bairro);
	    printf(" Comorbidades: %s\n", lista[i].comorbidades);
	    printf(" Data do cadastro: %s\n\n", lista[i].data_cadastro);
 	}
return 1;
}

void salvar_grupoderisco(void){
    FILE *arqgr = fopen("GrupodeRisco.txt", "a");
    if (arqgr){
        int i = 0;
        for (i = 0; i < quant_paciente_lista; i++){
            if (lista[i].idade >= 65){
                fprintf(arqgr," CEP: %s \n", lista[i].endereco.cep);
                fprintf(arqgr," Idade: %d \n\n", lista[i].idade);
            }
        }
        fclose (arqgr);
        system("CLS");
        printf(" Paciente do grupo de risco cadastrado!\n\n ");
    }
}

void salvar_pacientes(void){
    FILE *arq_pacientes = fopen("pacientes.txt", "a");
    int i = 0;
    if(arq_pacientes){
    	for (i = 0; i < quant_paciente_lista; i++){
    		fprintf(arq_pacientes," Nome: %s\n", &lista[i].nome);
    		fprintf(arq_pacientes," Sexo: %c\n", lista[i].sexo);
		    fprintf(arq_pacientes," CPF: %s\n", lista[i].cpf);
		    fprintf(arq_pacientes," Data de nascimento: %d/%d/%d\n", lista[i].dnascimento.d_nascimento, lista[i].dnascimento.m_nascimento, lista[i].dnascimento.a_nascimento);
		    fprintf(arq_pacientes," E-mail: %s\n", &lista[i].email);
		    fprintf(arq_pacientes," Telefone: %s\n", lista[i].tel);
		    fprintf(arq_pacientes," Cidade: %s\n", &lista[i].endereco.cidade);
		    fprintf(arq_pacientes," Estado: %s\n", &lista[i].endereco.estado);
		    fprintf(arq_pacientes," Rua: %s\n", &lista[i].endereco.rua);
		    fprintf(arq_pacientes," Número residêncial: %d\n", lista[i].endereco.n_casa);
		    fprintf(arq_pacientes," Bairro: %s\n", &lista[i].endereco.bairro);
		    fprintf(arq_pacientes," Comorbidades: %s\n", &lista[i].comorbidades);
		    fprintf(arq_pacientes," Data do cadastro: %s\n\n", &lista[i].data_cadastro);
	    }
    	fclose(arq_pacientes);
    	system("CLS");
    	printf(" Informações salvas com sucesso!\n\n");
    }else{
    	printf(" Falha ao salvar no arquivo\n");
    }

}
int main(void)
{
    setlocale(LC_ALL, "Portuguese_Brazil");

    char usuario[] = "0";
    int senha = 0;
    int op = 0;

    printf("\n\t\t –- Sistema de cadastramento --\n\n");

    while ((usuario != "adm") && (senha != 123)) {

        printf(" Usuário: ");
        scanf (" %s", &usuario);
        printf(" Senha: ");
        scanf (" %d", &senha);

  		if ((usuario != "adm") && (senha != 123)){
            system("CLS");
  			printf (" \n  Dados incorretos, tente novamente\n\n");
  		} else{
  		    system("CLS");
  			printf (" \n  Bem vindo(a)!\n\n");
        }
    }

    do {
    	printf(" 1. Cadastrar paciente\n 2. Consultar ficha dos pacientes\n 3. Salvar informações dos pacientes\n");
        printf(" 4. Salvar informações dos pacientes do grupo de risco\n 0. Sair\n\n");
    	printf(" Digite uma opção: ");
    	scanf (" %d", &op);
    	switch (op) {
    		case 0:
    			printf("\n Até mais!\n\n");
    			break;
    		case 1:
    			cadastrar();
    			break;
    		case 2:
    			consultar();
    			break;
    		case 3:
    			salvar_pacientes();
    			break;
            case 4:
                salvar_grupoderisco();
                break;
    		default:
    		 printf(" \nValor incorreto, tente novamente\n\n");
    	}
    }while (op != 0);
   	return 0;
}
