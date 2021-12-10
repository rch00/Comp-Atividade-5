#ifndef MINIC_ARQ_H
#define MINIC_ARQ_H

typedef struct tagBuffer {
    char *cont;
    long tam;
} Buffer;

Buffer* CriaBuffer(char *nome);
void DestroiBuffer(Buffer *b);

#endif //MINIC_ARQ_H
