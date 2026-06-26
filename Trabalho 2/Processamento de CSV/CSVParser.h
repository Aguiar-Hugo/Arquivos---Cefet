#ifndef __CSV_PARSER__
#define __CSV_PARSER__

#define CSV_MAX_ROW_SIZE 4096
#define CSV_MAX_COLS 512

typedef struct {
    int state;
    char buf[CSV_MAX_ROW_SIZE];
    int buflen;
    char* fields[CSV_MAX_COLS];
    int fieldCount;
} CSVParser;

void CSVParser_init(CSVParser*);
void CSVParser_processLines(CSVParser*, const char*, int, void(*)(char**,int,void*), void*);

#endif
