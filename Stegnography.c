#include <stdio.h>
#include <stdlib.h>
#define IMAGE_WIDTH 512
#define IMAGE_HEIGHT 512

// FUNCTION PROTOTYPES
int loadPGMText(const char*fileName, unsigned char*pixelData, int imgWidth, int imgHeight);
int savePGMText(const char*fileName, unsigned char*pixelData, int imgWidth, int imgHeight);
int savePGMBinary(const char*fileName, unsigned char*pixelData, int imgWidth, int imgHeight);
void hideImageLSB(unsigned char*baseImage, unsigned char*hiddenImage, int imgWidth, int imgHeight);
void revealImageLSB(unsigned char*encodedImage, unsigned char*decodedImage, int imgWidth, int imgHeight);

// FUNCTION DEFINITIONS
// Function to read a PGM image in text format.
int loadPGMText(const char*fileName, unsigned char*pixelData, int imgWidth, int imgHeight) {
    FILE*pgmFile = fopen(fileName, "r");
    if (!pgmFile) {
        printf("Error: Unable to open file '%s'.\n", fileName);
        return 1;
    }

    char format[3];
    fscanf(pgmFile, "%2s", format);
    if (format[0] != 'P' || format[1] != '2') {
        printf("Error: File '%s' is not in PGM text format.\n", fileName);
        fclose(pgmFile);
        return 1;
    }

    // Skip comments, read dimensions and max grayscale value
    while (fgetc(pgmFile) == '#') {
        while (fgetc(pgmFile) != '\n');
    }
    fseek(pgmFile, -1, SEEK_CUR);  // Return to before the last read character

    int width, height, maxGray;
    fscanf(pgmFile, "%d %d %d", &width, &height, &maxGray);
    if (width != imgWidth || height != imgHeight) {
        printf("Error: Image dimensions mismatch in '%s'.\n", fileName);
        fclose(pgmFile);
        return 1;
    }

    for (int i = 0; i < imgWidth * imgHeight; i++) {
        int pixelValue;
        if (fscanf(pgmFile, "%d", &pixelValue) != 1 || pixelValue < 0 || pixelValue > 255) {
            printf("Error: Invalid pixel value in '%s'.\n", fileName);
            fclose(pgmFile);
            return 1;
        }
        pixelData[i] = (unsigned char)pixelValue;
    }

    fclose(pgmFile);
    return 0;
}

// Function to save a PGM image in text format.
int savePGMText(const char*fileName, unsigned char*pixelData, int imgWidth, int imgHeight) {
    FILE*pgmFile = fopen(fileName, "w");
    if (!pgmFile) {
        printf("Error: Unable to create file '%s'.\n", fileName);
        return 1;
    }

    fprintf(pgmFile, "P2\n%d %d\n255\n", imgWidth, imgHeight);
    for (int i = 0; i < imgWidth * imgHeight; i++) {
        fprintf(pgmFile, "%d\n", pixelData[i]);
    }

    fclose(pgmFile);
    return 0;
}

// Function to save a PGM image in binary format.
int savePGMBinary(const char*fileName, unsigned char*pixelData, int imgWidth, int imgHeight) {
    FILE*pgmFile = fopen(fileName, "wb");
    if (!pgmFile) {
        printf("Error: Unable to create file '%s'.\n", fileName);
        return 1;
    }

    fprintf(pgmFile, "P5\n%d %d\n255\n", imgWidth, imgHeight);
    fwrite(pixelData, sizeof(unsigned char), imgWidth * imgHeight, pgmFile);

    fclose(pgmFile);
    return 0;
}

// Function to embed a hidden image using the 4-bit LSB steganography algorithm.
void hideImageLSB(unsigned char*baseImage, unsigned char*hiddenImage, int imgWidth, int imgHeight) {
    for (int i = 0; i < imgWidth* imgHeight; i++) {
        baseImage[i] = (baseImage[i] & 0xF0) | ((hiddenImage[i] & 0xF0) >> 4);
    }
}

// Function to extract the hidden image using the 4-bit LSB steganography algorithm.
void revealImageLSB(unsigned char*encodedImage, unsigned char*decodedImage, int imgWidth, int imgHeight) {
    for (int i = 0; i < imgWidth * imgHeight; i++) {
        decodedImage[i] = (encodedImage[i] & 0x0F) << 4;
    }
}

// MAIN FUNCTION
int main() {
    const char*coverFile = "baboon.pgm";
    const char*hiddenFile = "farm.pgm";
    const char*stegoFile = "stego_image_bin.pgm";
    const char*outputFile = "secret.pgm";

    unsigned char*coverData = (unsigned char*)malloc(IMAGE_WIDTH * IMAGE_HEIGHT);
    unsigned char*hiddenData = (unsigned char*)malloc(IMAGE_WIDTH * IMAGE_HEIGHT);
    unsigned char*decodedData = (unsigned char*)malloc(IMAGE_WIDTH * IMAGE_HEIGHT);

    if (!coverData || !hiddenData || !decodedData) {
        printf("Error: Memory allocation failed.\n");
        free(coverData);
        free(hiddenData);
        free(decodedData);
        return 1;
    }

    if (loadPGMText(coverFile, coverData, IMAGE_WIDTH, IMAGE_HEIGHT) ||
        loadPGMText(hiddenFile, hiddenData, IMAGE_WIDTH, IMAGE_HEIGHT)) {
        free(coverData);
        free(hiddenData);
        free(decodedData);
        return 1;
    }

    hideImageLSB(coverData, hiddenData, IMAGE_WIDTH, IMAGE_HEIGHT);
    if (savePGMBinary(stegoFile, coverData, IMAGE_WIDTH, IMAGE_HEIGHT)) {
        free(coverData);
        free(hiddenData);
        free(decodedData);
        return 1;
    }

    revealImageLSB(coverData, decodedData, IMAGE_WIDTH, IMAGE_HEIGHT);
    if (savePGMText(outputFile, decodedData, IMAGE_WIDTH, IMAGE_HEIGHT)) {
        free(coverData);
        free(hiddenData);
        free(decodedData);
        return 1;
    }

    free(coverData);
    free(hiddenData);
    free(decodedData);

    printf("Steganography process completed successfully.\n");
    return 0;
}
