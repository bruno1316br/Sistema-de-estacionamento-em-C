#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>  // Adicionei para usar o strcmp

// Struct da vaga
struct vaga {
    char placa[7];  // Placa do carro
    int ocupado;    // Mostrar as vagas (1 = livre, 0 = ocupado)
};

int main() {
    setlocale(LC_ALL, "portuguese"); // Idioma Português

    int menu, i;
    char buscar_placa[7];  // Alterei para char[] para comportar a placa
    struct vaga vagas[16];

    // Inicializa todas as vagas como livres
    for (i = 0; i < 16; i++) {
        vagas[i].ocupado = 1;
    }

    do {
        // Menu
        printf("\n1- Estacionar Veiculo");
        printf("\n2- Retirar um Carro");
        printf("\n3- Mostrar todas as vagas");
        printf("\n4- Sair do Programa\n Opção: ");
        scanf("%d", &menu);

        switch(menu) {
            case 1:
                // Estacionar veículo
                for (i = 0; i < 16; i++) {
                    if (vagas[i].ocupado == 1) {
                        printf("Digite a placa do carro: ");
                        scanf("%s", vagas[i].placa);
                        vagas[i].ocupado = 0; // Marca a vaga como ocupada
                        printf("A vaga %d foi registrada\n", i+1);
                        break;
                    }
                }
                break;

            case 2:
                // Retirar um carro
                printf("Digite a placa do carro: ");
                scanf("%s", buscar_placa);

                // Verifica todas as vagas
                for (i = 0; i < 16; i++) {
                    if (strcmp(vagas[i].placa, buscar_placa) == 0) {  // Comparar as placas
                        if (vagas[i].ocupado == 0) {  // Verifica se a vaga está ocupada
                            printf("A vaga %d com a placa %s foi liberada\n", i+1, vagas[i].placa);
                            vagas[i].ocupado = 1;  // Marca a vaga como liberada
                        } else {
                            printf("A vaga %d já está livre\n", i+1);  // Caso a vaga já esteja livre
                        }
                        break;  // Sai do laço assim que encontrar a vaga
                    }
                }
                // Caso não encontre a placa
                if (i == 16) {
                    printf("Carro com placa %s não encontrado.\n", buscar_placa);
                }
                break;
    	case 3:
    	for(i = 0; i<16; i++){
    		if(vagas[i].ocupado == 0){
    			printf("Vaga %d ocupada Placa :%s \n", i+1, vagas[i].placa);
			}else{
				printf("Vaga %d livre!\n", i+1);
			}
		}
    		break;
        } // Fim do switch

    } while (1);

    return 0;
}

