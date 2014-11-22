#include <stdio.h>
#include "opencv.h"
// g++ -ggdb `pkg-config --cflags opencv` main.cpp -o main `pkg-config --libs opencv`

//using namespace cv;
#define FILDERNUM 10
#define FILENO 10

void cal_feature(const char *FileName, int feature_veotors[64]) {
    int i, j, k;
    IplImage *Image = NULL;

    Image = cvLoadImage(FileName, CV_LOAD_IMAGE_GRAYSCALE);

    if (Image == NULL) {
        fprintf(stderr, "Can not load image %s\n", FileName);
        exit(-1);
    }

    BwImage BlockA(Image);

    k = 0;

    for (i = 0; i < Image->height; ++i) {
        for (j = 0; j < Image->width; ++j) {
            k = j + 1;

            if (k < Image->width && BlockA[i][j] != BlockA[i][k]) {
                feature_veotors[i] += 1;
            }

            if (k < Image->width && BlockA[j][i] != BlockA[k][i]) {
                feature_veotors[i + 32] += 1;
            }
        }
    }

#if 1

    for (i = 0; i < Image->height; ++i) {
        for (j = 0; j < Image->width; ++j) {
            printf("%3d ", BlockA[i][j]);
        }

        printf("\n");
    }

    printf("\n");

    for (i = 0; i < 64; ++i) {
        printf("%3d", feature_veotors[i]);
    }

    printf("\n");

    cvShowImage("Show Image", Image);
    cv::waitKey();
#endif

    cvReleaseImage(&Image);

}

void stats_features_veotors(int fildernum, int feature_veotors[64], float feature_veotors_table[][64]) {
    int i;

    for (i = 0; i < 64; ++i) {
        feature_veotors_table[fildernum][i] += feature_veotors[i];
    }
}

void features_train() {
    FILE *pFile;
    char FileName[50];
    float feature_veotors_table[10][64] = {0};
    int i, j;

    for (i = 0; i < FILDERNUM; ++i) {
        for (j = 0; j < FILENO; ++j) {
            int feature_veotors[64] = {0};

            sprintf(FileName, "number1_bmp/%d/%d.bmp", i, j);
            cal_feature(FileName,  feature_veotors);
            stats_features_veotors(i,  feature_veotors, feature_veotors_table);
        }
    }

    printf("\n");

    for (i = 0; i < 10; ++i) {
        sprintf(FileName, "%d.txt", i);
        pFile = fopen(FileName, "w");

        for (j = 0; j < 64; ++j) {
            feature_veotors_table[i][j] /= 10.0;
            fprintf(pFile, "%f\n", feature_veotors_table[i][j]);
            printf("%f ", feature_veotors_table[i][j]);
        }

        fclose(pFile);
        printf("\n\n");
    }
}

void features_train_begin() {
    FILE *pFile;
    int i, j;
    char FileName[50];
    float feature_veotors_table[10][64] = {0} , value;

    features_train();

    printf("\n\n\n\n");

    for (i = 0; i < 10; ++i) {
        sprintf(FileName, "%d.txt", i);
        pFile = fopen(FileName, "r");

        if (!pFile) {
            printf("open file fail...\n");
            exit(1);
        }

        for (j = 0; j < 64; ++j) {
            fscanf(pFile, "%f\n", &value);
            feature_veotors_table[i][j] = value;
            printf("%f ", feature_veotors_table[i][j]);
        }

        printf("\n\n");
        fclose(pFile);
    }
}


int main(int argc, char *argv[]) {
    features_train_begin();

    return 0;
}
