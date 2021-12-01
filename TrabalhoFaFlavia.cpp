#include <iostream>
#include <string.h>
#include <Windows.h>
#include <locale>

struct reg
{
	char nome[20];
	char tel[20];
	char email[20];
	char cor[20];
	char modelo[20];
	char marca[20];
	char status;
};

int tamanho(FILE *);
void cadastrar(FILE *);
void consultar(FILE *);
void geraarqtxt(FILE *);
void excluir(FILE *);

int main()
{
	int op;
	FILE *arq;

	if ((arq = fopen("agenda1.dat", "rb+")) == NULL)
	{
		if ((arq = fopen("agenda1.dat", "wb+")) == NULL)
		{
			printf("Falha ao abrir o arquivo!\n");
			system("pause");
		}
	}

	//existentes no arquivo agenda1.dat
	do
	{
		system("CLS");
		printf("\n========== AGENDA DA CONCESSIONARIA ==========");
		printf("\n1.Cadastrar\n");
		printf("\n2.Consultar\n");
		printf("\n3.Gerar arquivo\n");
		printf("\n4.excluir arquivo\n");
		printf("\n5.Sair\n");
		printf("============Contatos: %d=\n", tamanho(arq));
		printf("Opcao: ");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			cadastrar(arq);
			break;
		case 2:
			consultar(arq);
			break;
			
			break;
		case 3: geraarqtxt(arq);

			break;
		case 4: 
			excluir(arq); 
			break;

		case 5: fclose(arq);
		}
	} while (op != 5);
}

void cadastrar(FILE *arq)
{
	reg contato;
	char confirma;
	contato.status = ' ';
	fflush(stdin);

	printf("Cadastrando novo registro: \n");
	printf("\nNumero do registro: %d\n", tamanho(arq) +1);
	printf("Nome do Comprador............: ");
	gets(contato.nome);
	printf("Telefone do Comprador.........:");
	gets(contato.tel);
	printf("e-mail do Comprador...........:");
	gets(contato.email);
	printf("Cor do veiculo................:");
	gets(contato.cor);
	printf("Modelo do veiculo.............:");
	gets(contato.modelo);
	printf("Marca do Veiculo..............:");
	gets(contato.marca);
	printf("\nConfirma <s/n>:");
	scanf("%c", &confirma);

	if (toupper(confirma) == 'S')
	{
		printf("\nCadastro Salvo\n\n");
		fseek(arq, 0, SEEK_END);
		fwrite(&contato, sizeof(reg), 1, arq);

	}
	system("pause");
}

void consultar(FILE *arq)
{
	reg contato;
	int nr;
	printf("\nConsulta pelo codigo\n");
	printf("\nInforme o Codigo...:");
	scanf("%d", &nr);
	if ((nr <= tamanho(arq)) && (nr>0))
	{
		fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		if (contato.status == ' ')
		{
			printf("\nNome do Comprador......:%s",contato.nome);
			printf("\nTelefone do Comprador..:%s",contato.tel);
			printf("\ne-mail do Comprador....:%s",contato.email);
			printf("\nModelo do Veiculo......:%s",contato.modelo);
			printf("\nCor do Veiculo.........:%s",contato.cor);
			printf("\nMarca do Veiculo.......:%s\n",contato.marca);
		}

		else
			printf("\nRegistro excluido! \n");

	}
	else
	{
		printf("\nNumero de registro invalido!\n");
	}
	system("pause");
}

void geraarqtxt(FILE *arq)
{
	char nomearq[20];
	printf("Nome do arquivo texto:");
	scanf("%s", nomearq);
	strcat(nomearq, ".txt");
	FILE *arqtxt = fopen(nomearq, "w");
	if (!arqtxt)
	{
		printf("Nao foi possivel criar esse arquivo!\n");
		system("pause");
	}
	fprintf(arqtxt, "Marca               Modelo                   Cor\n");
	fprintf(arqtxt, "================================================================\n");
	int nr;
	reg contato;
	for (nr = 0; nr<tamanho(arq); nr++)
	{
		fseek(arq, nr * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		fprintf(arqtxt, "%-20s%-20s%-20s- %c\n", contato.marca, contato.modelo, contato.cor, contato.status);
	}
	fprintf(arqtxt, "================================================================\n");
	fclose(arqtxt);
}

void excluir(FILE *arq)
{
	reg contato;
	char confirma;
	int nr;

	printf("\nInforme o codigo do registro para excluir\n");
	scanf("%d", &nr);
	if ((nr <= tamanho(arq)) && (nr>0))
	{
		fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		if (contato.status == ' ')
		{
			printf("\nNome do Comprador......:%s",contato.nome);
			printf("\nTelefone do Comprador..:%s",contato.tel);
			printf("\ne-mail do Comprador....:%s",contato.email);
			printf("\nModelo do Veiculo......:%s",contato.modelo);
			printf("\nCor do Veiculo.........:%s",contato.cor);
			printf("\nMarca do Veiculo.......:%s\n",contato.marca);
			printf("\nConfirma a exclusao: <s/n>\n");
			getchar();
			scanf("%c", &confirma);

			if (toupper(confirma) == 'S')
			{
				printf("\nexcluindo...\n\n");
				fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
				contato.status = '*';
				fwrite(&contato, sizeof(reg), 1, arq);
			}
		}
	else
		printf("Registro inexistente! \n");
	}
	else
	{
		printf("\nNumero de registro invalido!\n");
	}
	system("pause");
}

int tamanho(FILE *arq)
{
	fseek(arq, 0, SEEK_END);
	return ftell(arq) / sizeof(reg);
}

