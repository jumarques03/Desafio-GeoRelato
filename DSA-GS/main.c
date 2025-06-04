#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define RAIO_TERRA 6371.0  // Raio da Terra (km)
#define RAIO_MAXIMO 10.0   // Raio máximo permitido (km)
#define PONTO_CENTRAL_LAT -23.574393  // Latitude do ponto central (FIAP-LINS)
#define PONTO_CENTRAL_LON -46.623548  // Longitude do ponto central (FIAP-LINS)

struct Relator {
    char nome[50];
    int documento;
    char email[50];
    int telefone;
    float lat;
    float lon;
};

struct Relato{
   char tipo_catastrofe[50];
   char descricao[150];
   char data[20];
   char hora[20];
   float lat;
   float lon;
};


void infoRelator(struct Relator *relator){
    printf("---Insira seus Dados Pessoais---\n");

    printf("Insira seu nome compelto: ");
    getchar();
    fgets(relator->nome, sizeof(relator->nome), stdin);

    printf("\nInsira seu CPF: ");
    scanf("%d", &relator->documento);

    printf("\nInsira seu email: ");
    getchar();
    fgets(relator->email, sizeof(relator->email), stdin);

    printf("\nInsira seu telefone (somente número): ");
    scanf("%d", &relator->telefone);

    printf("\nInsira sua localização:\n");
    printf("OBS: Entre neste site caso não saiba estas informações -> https://www.mapcoordinates.net/pt \n");
    printf("Latitude: ");
    scanf("%f", &relator->lat);
    printf("Longitude: ");
    scanf("%f", &relator-> lon);

    printf("\n--------------------------------------------------------------------\n");
}


// Função para cálculo da distância entre localização do ponto central e a localização da catástrofe
double calcularDistancia(float lat1, float lon1, float lat2, float lon2) {
    // Converter graus para radianos
    double lat1Rad = lat1 * M_PI / 180.0;
    double lon1Rad = lon1 * M_PI / 180.0;
    double lat2Rad = lat2 * M_PI / 180.0;
    double lon2Rad = lon2 * M_PI / 180.0;

    // Diferenças das coordenadas
    double dLat = lat2Rad - lat1Rad;
    double dLon = lon2Rad - lon1Rad;

    // Fórmula de Haversine
    double a = sin(dLat/2) * sin(dLat/2) +
               cos(lat1Rad) * cos(lat2Rad) *
               sin(dLon/2) * sin(dLon/2);
    
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double distancia = RAIO_TERRA * c;

    return distancia;
}

// Função que permite o cadastro de relatos
void cadastrarRelatos(struct Relato *lista, int n) {
    printf("\n\n---Cadastre seus Relatos---\n");

    for (int i = 0; i < n; i++) {
        printf("\n\nRelato %d\n", i + 1);

        printf("Tipo da catástrofe: ");
        getchar(); 
        fgets(lista[i].tipo_catastrofe, sizeof(lista[i].tipo_catastrofe), stdin);

        printf("Descreva seu relato em poucas palavras: ");
        fgets(lista[i].descricao, sizeof(lista[i].descricao), stdin);

        printf("Insira a data de ocorrência (DD/MM/AAAA): ");
        fgets(lista[i].data, sizeof(lista[i].data), stdin);

        printf("Insira a hora de ocorrência: ");
        fgets(lista[i].hora, sizeof(lista[i].hora), stdin);

        do {
            printf("Insira a localização da catástrofe:\n");
            printf("OBS: Entre neste site caso não saiba estas informações:https://www.mapcoordinates.net/pt \n");
            printf("Latitude: ");
            scanf("%f", &lista[i].lat);
            printf("Longitude: ");
            scanf("%f", &lista[i].lon);

            double distancia = calcularDistancia(PONTO_CENTRAL_LAT, PONTO_CENTRAL_LON, lista[i].lat, lista[i].lon);

            if (distancia > RAIO_MAXIMO) {
                printf("\nERRO: A localização da catástrofe está fora do raio permitido de %.2f km do ponto central.\n", RAIO_MAXIMO);
                printf("Por favor, insira uma localização mais próxima.\n\n");
            } else {
                printf("Localização válida! Relato adicionado a lista de relatos!");
                break;
            }
        } while (1);
    }
}


// Função para listar os relatos
void listarRelatos(struct Relato *lista, int n) {
    int opcao;
    float lat, lon;
    char busca[50];
    
    printf("\n---Insira por qual tipo de dado deseja pesquisar o relato---\n");
    printf("1- Tipo da Catástrofe\n");
    printf("2- Localização da Catástrofe\n");
    printf("3- Data da Catástrofe\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    
    switch (opcao) {
        case 1:
            printf("\nInsira o tipo da catástrofe: ");
            getchar();
            fgets(busca, sizeof(busca), stdin);
            
            for (int i = 0; i < n; i++) {
                // Se elas forem iguais (0)
                if (_stricmp(busca, lista[i].tipo_catastrofe) == 0) {
                    printf("\nRelato %d:\n", i + 1);
                    printf("Tipo: %s\n", lista[i].tipo_catastrofe);
                    printf("Descrição: %s", lista[i].descricao);
                    printf("Data: %s", lista[i].data);
                    printf("Hora: %s", lista[i].hora);
                    printf("Localização: %.6f, %.6f\n", lista[i].lat, lista[i].lon);
                }
            }
            break;
            
        case 2:
            printf("\nInsira a latitude da catástrofe: ");
            scanf("%f", &lat);
            printf("Insira a longitude da catástrofe:: ");
            scanf("%f", &lon);
            
            for (int i = 0; i < n; i++) {
                if (lista[i].lat == lat && lista[i].lon == lon) {
                    printf("\nRelato %d:\n", i + 1);
                    printf("Tipo: %s", lista[i].tipo_catastrofe);
                    printf("Descrição: %s", lista[i].descricao);
                    printf("Data: %s", lista[i].data);
                    printf("Hora: %s", lista[i].hora);
                    printf("Localização: %.4f, %.4f\n", lista[i].lat, lista[i].lon);
                }
            }
            break;
            
        case 3:
            printf("\nInsira a data (DD/MM/AAAA): ");
            getchar();
            fgets(busca, sizeof(busca), stdin);
            
            for (int i = 0; i < n; i++) {
                // Se elas forem iguais (0)
                if (_stricmp(busca, lista[i].data) == 0) {
                    printf("\nRelato %d:\n", i + 1);
                    printf("Tipo: %s", lista[i].tipo_catastrofe);
                    printf("Descrição: %s", lista[i].descricao);
                    printf("Data: %s\n", lista[i].data);
                    printf("Hora: %s", lista[i].hora);
                    printf("Localização: %.4f, %.4f\n", lista[i].lat, lista[i].lon);
                }
            }
            break;
            
        default:
            printf("\nOpção inválida! Nenhuma catástrofe encontrada.\n");
    }
}


int main() {
    struct Relator *pessoa = malloc(sizeof(struct Relator));
    if (pessoa == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    struct Relato *relatos = 0;
    int n = 0;
    int opcao;

    do {
        printf("\n---------------------------------------------------------\n");
        printf("\n--- MENU DE OPÇÕES ---\n");
        printf("1. Cadastrar dados do relator\n");
        printf("2. Cadastrar relatos\n");
        printf("3. Listar relatos\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        printf("\n---------------------------------------------------------\n");

        switch (opcao) {
            case 1:
                infoRelator(pessoa);
                break;

            case 2:
                printf("\nQuantos relatos deseja cadastrar? ");
                scanf("%d", &n);

                relatos = realloc(relatos, n * sizeof(struct Relato));
                if (relatos == NULL) {
                    printf("Erro de alocação de memória.\n");
                    return 1;
                }

                cadastrarRelatos(relatos, n);
                break;

            case 3:
                if (relatos == NULL || n == 0) {
                    printf("Nenhum relato cadastrado ainda.\n");
                } else {
                    listarRelatos(relatos, n);
                }
                break;

            case 4:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 4);

    free(pessoa);
    free(relatos);
    return 0;
}