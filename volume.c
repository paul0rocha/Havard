#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define HEADER_SIZE 44

int main(int argc, char *argv[])
{
    // Verifica os argumentos
    if (argc != 4)
    {
        printf("Uso: %s entrada.wav saida.wav fator\n", argv[0]);
        return 1;
    }

    // Abre o arquivo de entrada
    FILE *input = fopen(argv[1], "rb");

    if (input == NULL)
    {
        printf("Não foi possível abrir o arquivo de entrada.\n");
        return 1;
    }

    // Abre o arquivo de saída
    FILE *output = fopen(argv[2], "wb");

    if (output == NULL)
    {
        printf("Não foi possível criar o arquivo de saída.\n");
        fclose(input);
        return 1;
    }

    // Converte o fator para float
    float factor = atof(argv[3]);

    // Copia o cabeçalho WAV
    uint8_t header[HEADER_SIZE];

    if (fread(header, sizeof(uint8_t), HEADER_SIZE, input) != HEADER_SIZE)
    {
        printf("Erro ao ler o cabeçalho.\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // Lê e altera cada amostra de áudio
    int16_t buffer;

    while (fread(&buffer, sizeof(int16_t), 1, input) == 1)
    {
        buffer = (int16_t)(buffer * factor);

        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Fecha os arquivos
    fclose(input);
    fclose(output);

    printf("Arquivo criado com sucesso!\n");

    return 0;
}
