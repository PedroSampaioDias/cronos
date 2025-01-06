#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>

#define NTP_TIMESTAMP_DELTA 2208988800ull
#define NTP_SERVER_PORT 123
#define NTP_PACKET_SIZE 48
#define TIMEOUT_SECONDS 20

// Estrutura do pacote NTP
typedef struct {
    uint8_t li_vn_mode;
    uint8_t stratum;
    uint8_t poll;
    uint8_t precision;
    uint32_t rootDelay;
    uint32_t rootDispersion;
    uint32_t refId;
    uint32_t refTm_s;
    uint32_t refTm_f;
    uint32_t origTm_s;
    uint32_t origTm_f;
    uint32_t rxTm_s;
    uint32_t rxTm_f;
    uint32_t txTm_s;
    uint32_t txTm_f;
} __attribute__((packed)) ntp_packet;

// Função para exibir a data/hora formatada
void print_time(uint32_t txTm) {
    time_t rawtime = (time_t)(txTm - NTP_TIMESTAMP_DELTA);
    struct tm *ptm = localtime(&rawtime);
    char buffer[50];
    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", ptm);
    printf("Data/hora: %s\n", buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <IP do servidor NTP>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *server_ip = argv[1];
    int sockfd;
    struct sockaddr_in server_addr;
    ntp_packet packet;

    // Inicializa o pacote com zeros e configura o campo li_vn_mode
    memset(&packet, 0, sizeof(ntp_packet));
    packet.li_vn_mode = 0x1B; // LI = 0, VN = 3, Mode = 3 (client)

    // Criação do socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("Erro ao criar o socket");
        return EXIT_FAILURE;
    }

    // Configura timeout para recvfrom
    struct timeval timeout = {TIMEOUT_SECONDS, 0};
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        perror("Erro ao configurar timeout");
        close(sockfd);
        return EXIT_FAILURE;
    }

    // Configura endereço do servidor NTP
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(NTP_SERVER_PORT);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("Erro ao configurar o endereço IP");
        close(sockfd);
        return EXIT_FAILURE;
    }

    // Envia o pacote NTP para o servidor
    if (sendto(sockfd, &packet, sizeof(ntp_packet), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Erro ao enviar a mensagem");
        close(sockfd);
        return EXIT_FAILURE;
    }

    // Recebe a resposta do servidor
    socklen_t addr_len = sizeof(server_addr);
    int recv_len = recvfrom(sockfd, &packet, sizeof(ntp_packet), 0, (struct sockaddr *)&server_addr, &addr_len);
    if (recv_len < 0) {
        perror("Erro ao receber dados do servidor");
        close(sockfd);
        return EXIT_FAILURE;
    } else if (recv_len < sizeof(ntp_packet)) {
        fprintf(stderr, "Erro: pacote recebido tem tamanho inesperado (%d bytes)\n", recv_len);
        close(sockfd);
        return EXIT_FAILURE;
    }

    // Verifica se o campo txTm_s é válido antes de usá-lo
    uint32_t txTm = ntohl(packet.txTm_s);
    if (txTm == 0) {
        fprintf(stderr, "Erro: campo txTm_s do pacote está vazio ou inválido.\n");
        close(sockfd);
        return EXIT_FAILURE;
    }

    // Exibe a hora recebida
    print_time(txTm);

    // Fecha o socket
    close(sockfd);
    return EXIT_SUCCESS;
}
