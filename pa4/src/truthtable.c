#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct directive {
    char gate[17];
    int numInputs;
    int numSelectors;
    int *inputIndices;
    int *outputIndices;
    int *selectors;
};

void AND(int *values, int index1, int index2, int outputIndex) {
    values[outputIndex] = values[index1] && values[index2];
}

void OR(int *values, int index1, int index2, int outputIndex) {
    values[outputIndex] = values[index1] || values[index2];
}

void NAND(int *values, int index1, int index2, int outputIndex) {
    values[outputIndex] = !(values[index1] && values[index2]);
}

void NOR(int *values, int index1, int index2, int outputIndex) {
    values[outputIndex] = !(values[index1] || values[index2]);
}

void XOR(int *values, int index1, int index2, int outputIndex) {
    values[outputIndex] = values[index1] ^ values[index2];
}

void NOT(int *values, int iindex, int outputIndex) {
    values[outputIndex] = !values[iindex];
}

void PASS(int *values, int iindex, int outputIndex) {
    values[outputIndex] = values[iindex];
}

void DECODER(int *values, int n, int *index, int *outputIndex) {
    int selector = 0;
    for (int i = 0; i < (1 << n); i++) {
        values[outputIndex[i]] = 0;
    }
    for (int j = 0; j < n; j++) {
        selector += values[index[j]] << (n - j - 1);
    }
    values[outputIndex[selector]] = 1;
}

void MULTIPLEXER(int *values, int n, int *iindex, int *sindex, int outputIndex) {
    int selector = 0;
    for (int i = 0; i < n; i++) {
        selector += values[sindex[i]] << (n - i - 1);
    }
    values[outputIndex] = values[iindex[selector]];
}

int incrementInputs(int *array, int count) {
    for (int i = count + 1; i >= 2; i--) {
        array[i] = !array[i];
        if (array[i] == 1) {
            return 1;
        }
    }
    return 0;
}

void print(int size, char **arr) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", arr[i]);
    }
}

int indexOf(int size, char **arr, char *var) {
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i], var) == 0) {
            return i;
        }
    }
    return -1;
}

void reset(int size, int *arr) {
    for (int i = 0; i < size; i++) {
        arr[i] = 0;
    }
    arr[1] = 1;
}




// MAIN

int main(int argc, char** argv) {

    if (argc - 1 != 1) {
        printf("Invalid number of arguments\n");
        return 0;
    }

    // get file
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Invalid input\n");
        return 0;
    }

    int count = 0;
    struct directive* steps = NULL;
    int size = 2;
    int input_count = 0;
    int output_count = 0;
    int tcount = 0;
    char dir[17];
    char **names;
    int *values = malloc(size * sizeof(int));

    // INPUT info
    fscanf(file, " %s", dir);
    fscanf(file, "%d", &input_count);

    size += input_count;
    names = malloc(size * sizeof(char *));
    names[0] = malloc(2 * sizeof(char));
    names[0] = "0\0";
    names[1] = malloc(2 * sizeof(char));
    names[1] = "1\0";

    for (int i = 0; i < input_count; i++) {
        names[i + 2] = malloc(17 * sizeof(char));
        fscanf(file, "%*[: ]%16s", names[i + 2]);
    }

    // OUTPUT info
    fscanf(file, " %s", dir);
    fscanf(file, "%d", &output_count);
    size += output_count;
    names = realloc(names, size * sizeof(char *));
    for (int j = 0; j < output_count; j++) {
        names[j + input_count + 2] = malloc(17 * sizeof(char));
        fscanf(file, "%*[: ]%16s", names[j + input_count + 2]);
    }

    while (!feof(file)) {
        int numInputs = 2, numOutputs = 1;
        struct directive step;
        int sc = fscanf(file, " %s", dir); 
        if (sc != 1) {
            break;
        }
        count++;
        step.numInputs = 0;
        step.numSelectors = 0;
        strcpy(step.gate, dir);

        if (strcmp(dir, "NOT") == 0) {
            numInputs = 1;
        }
        if (strcmp(dir, "PASS") == 0) {
            numInputs = 1;
        }
        if (strcmp(dir, "DECODER") == 0) {
            fscanf(file, "%d", &numInputs);
            step.numInputs = numInputs;
            numOutputs = 1 << numInputs;
        }
        if (strcmp(dir, "MULTIPLEXER") == 0) {
            fscanf(file, "%d", &numInputs);
            step.numSelectors = numInputs;
            numInputs = 1 << numInputs;
        }

        step.inputIndices = malloc(numInputs * sizeof(int));
        step.outputIndices = malloc(numOutputs * sizeof(int));
        step.selectors = malloc(step.numSelectors * sizeof(int));

        char v[17];
        
        for (int i = 0; i < numInputs; i++) {
            fscanf(file, "%*[: ]%16s", v);
            step.inputIndices[i] = indexOf(size, names, v);
        }

        for (int i = 0; i < step.numSelectors; i++) {
            fscanf(file, "%*[: ]%16s", v);
            step.selectors[i] = indexOf(size, names, v);
        }
 
        for (int i = 0; i < numOutputs; i++) {
            fscanf(file, "%*[: ]%16s", v);
            int idx = indexOf(size, names, v);
            if (idx == -1) {
                size++;
                tcount++;
                names = realloc(names, size * sizeof(char *));
                names[size - 1] = malloc(17 * sizeof(char));
                strcpy(names[size - 1], v);
                step.outputIndices[i] = size - 1;
            }
            else {
                step.outputIndices[i] = idx;
            }
        }
        
        if (!steps) {
            steps = malloc(sizeof(struct directive));
        } else {
            steps = realloc(steps, count * sizeof(struct directive));
        }
        steps[count - 1] = step;
    }

    values = malloc(size * sizeof(int));
    reset(size, values);

    while(1 < 2) {
        for (int i = 0; i < input_count; i++) {
            printf("%d ", values[i + 2]);
        }
        printf("|");

        // calculate outputs
        for (int i = 0; i < count; i++) {
            struct directive step = steps[i];
            if (strcmp(step.gate, "AND") == 0) {
                AND(values, step.inputIndices[0], step.inputIndices[1], step.outputIndices[0]);
            }
            if (strcmp(step.gate, "OR") == 0) {
                OR(values, step.inputIndices[0], step.inputIndices[1], step.outputIndices[0]);
            }
            if (strcmp(step.gate, "NAND") == 0) {
                NAND(values, step.inputIndices[0], step.inputIndices[1], step.outputIndices[0]);
            }
            if (strcmp(step.gate, "NOR") == 0) {
                NOR(values, step.inputIndices[0], step.inputIndices[1], step.outputIndices[0]);
            }
            if (strcmp(step.gate, "XOR") == 0) {
                XOR(values, step.inputIndices[0], step.inputIndices[1], step.outputIndices[0]);
            }
            if (strcmp(step.gate, "NOT") == 0) {
                NOT(values, step.inputIndices[0], step.outputIndices[0]);
            }
            if (strcmp(step.gate, "PASS") == 0) {
                PASS(values, step.inputIndices[0], step.outputIndices[0]);
            }
            if (strcmp(step.gate, "DECODER") == 0) {
                DECODER(values, step.numInputs, step.inputIndices, step.outputIndices);
            }
            if (strcmp(step.gate, "MULTIPLEXER") == 0) {
                MULTIPLEXER(values, step.numSelectors, step.inputIndices, step.selectors, step.outputIndices[0]);
            }
        }

        // print outputs
        for (int i = 0; i < output_count; i++) {
            printf(" %d", values[input_count + i + 2]);
        }
        printf("\n");

        if (!incrementInputs(values, input_count)) {
            break;
        }
    }
    return 0;
}
