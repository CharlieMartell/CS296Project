
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <jni.h>
#include <android/log.h>

//I know this looks silly but Eclipse was trying to like have local debug with c++ with doesnt like NULL
#ifndef NULL
#define NULL   ((void *) 0)
#endif

typedef struct
{
    int row;
    int column;
    int (* board)[9];
} boardstate;

void * check_rows(void * params);
void * check_columns(void * params);
void * check_square(void * params);

//Check to Ensure Each Row/Column contains all values 1-9
void * check_rows(void * params) {
    boardstate * data = (boardstate *) params;
    int startRow = data->row, startCol = data->column;
    int i,j;
    for (i = startRow; i < 9; ++i) {
        int row[10] = {0};
        for (j = startCol; j < 9; ++j) {
            int val = data->board[i][j];
            if (row[val] != 0)
                return (void *) 0;
            else
                row[val] = 1;
        }
    }
    return (void *) 1;
}

void * check_columns(void * params) {
    boardstate * data = (boardstate *) params;
    int startRow = data->row, startCol = data->column, i,j;
    for (i = startCol; i < 9; ++i) {
        int col[10] = {0};
        for (j = startRow; j < 9; ++j) {
            int val = data->board[j][i];
            if (col[val] != 0)
                return (void *) 0;
            else
                col[val] = 1;
        }
    }
    return (void *) 1;
}

//Check to ensure each 3x3 grid contains #'s 1-9
void * check_square(void * params) {
    boardstate * data = (boardstate *) params;
    int startRow = data->row, startCol = data->column, saved[10] = {0}, i,j;
    for (i = startRow; i < startRow + 3; ++i) {
        for (j = startCol; j < startCol + 3; ++j) {
            int val = data->board[i][j];
            if (saved[val] != 0)
                return (void *) 0;
            else
                saved[val] = 1;
        }
    }
    return (void *) 1;
}


JNIEXPORT jint JNICALL Java_com_example_sudokusolver_MainActivity_mainSolve(JNIEnv *env, jobject obj, jstring input)
{
	//Get board form input by converting to C String then casting to int and subtracting '0' giving you the value
	jbyte * numbers = (*env)->GetStringUTFChars(env,input,0);
	char c[81];
	strcpy(c, numbers);
	int board[9][9] = {
				{(int)c[0] - '0', (int)c[1] - '0', (int)c[2] - '0', (int)c[3] - '0', (int)c[4] - '0', (int)c[5] - '0', (int)c[6] - '0', (int)c[7] - '0', (int)c[8] - '0'},
				{(int)c[9] - '0', (int)c[10] - '0', (int)c[11] - '0', (int)c[12] - '0', (int)c[13] - '0', (int)c[14] - '0', (int)c[15] - '0', (int)c[16] - '0', (int)c[17] - '0'},
				{(int)c[18] - '0', (int)c[19] - '0', (int)c[20] - '0', (int)c[21] - '0', (int)c[22] - '0', (int)c[23] - '0', (int)c[24] - '0', (int)c[25] - '0', (int)c[26] - '0'},
				{(int)c[27] - '0', (int)c[28] - '0', (int)c[29] - '0', (int)c[30] - '0', (int)c[31] - '0', (int)c[32] - '0', (int)c[33] - '0', (int)c[34] - '0', (int)c[35] - '0'},
				{(int)c[36] - '0', (int)c[37] - '0', (int)c[38] - '0', (int)c[39] - '0', (int)c[40] - '0', (int)c[41] - '0', (int)c[42] - '0', (int)c[43] - '0', (int)c[44] - '0'},
				{(int)c[45] - '0', (int)c[46] - '0', (int)c[47] - '0', (int)c[48] - '0', (int)c[49] - '0', (int)c[50] - '0', (int)c[51] - '0', (int)c[52] - '0', (int)c[53] - '0'},
				{(int)c[54] - '0', (int)c[55] - '0', (int)c[56] - '0', (int)c[57] - '0', (int)c[58] - '0', (int)c[59] - '0', (int)c[60] - '0', (int)c[61] - '0', (int)c[62] - '0'},
				{(int)c[63] - '0', (int)c[64] - '0', (int)c[65] - '0', (int)c[66] - '0', (int)c[67] - '0', (int)c[68] - '0', (int)c[69] - '0', (int)c[70] - '0', (int)c[71] - '0'},
				{(int)c[72] - '0', (int)c[73] - '0', (int)c[74] - '0', (int)c[75] - '0', (int)c[76] - '0', (int)c[77] - '0', (int)c[78] - '0', (int)c[79] - '0', (int)c[80] - '0'}
			};

	//Setup the boardpartitions to check the 3x3 grids
	boardstate * boardpartition0 = (boardstate *) malloc(sizeof(boardstate));
    boardpartition0->row = 0;
    boardpartition0->column = 0;
    boardpartition0->board = board;

    boardstate * boardpartition1 = (boardstate *) malloc(sizeof(boardstate));
    boardpartition1->row = 0;
    boardpartition1->column = 0;
    boardpartition1->board = board;

    boardstate * boardpartition2 = (boardstate *) malloc(sizeof(boardstate));
    boardpartition2->row = 0;
    boardpartition2->column = 3;
    boardpartition2->board = board;

    boardstate * boardpartition3 = (boardstate *) malloc(sizeof(boardstate));
    boardpartition3->row = 0;
    boardpartition3->column = 6;
    boardpartition3->board = board;

    boardstate * boardpartition4 = (boardstate *) malloc(sizeof(boardstate));
    boardpartition4->row = 3;
    boardpartition4->column = 0;
    boardpartition4->board = board;

    boardstate * boardpartition5 = (boardstate *) malloc(sizeof(boardstate));
    boardpartition5->row = 3;
    boardpartition5->column = 3;
    boardpartition5->board = board;

    boardstate * boardpartition6 = (boardstate *) malloc(sizeof(boardstate));
    boardpartition6->row = 3;
    boardpartition6->column = 6;
    boardpartition6->board = board;

    boardstate * boardpartition7 = (boardstate *) malloc(sizeof(boardstate));
    boardpartition7->row = 6;
    boardpartition7->column = 0;
    boardpartition7->board = board;

    boardstate * boardpartition8 = (boardstate *) malloc(sizeof(boardstate));
    boardpartition8->row = 6;
    boardpartition8->column = 3;
    boardpartition8->board = board;

    boardstate * boardpartition9 = (boardstate *) malloc(sizeof(boardstate));
    boardpartition9->row = 6;
    boardpartition9->column = 6;
    boardpartition9->board = board;

    //Create Pthreads to all go through and perform these checks
    pthread_t thread_rows, thread_cols, thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9;

    void * valid_rows, * valid_columns, * square1, * square2, * square3, * square4, * square5, * square6, * square7, * square8, * square9;

    pthread_create(&thread_rows, NULL, check_rows, (void *) boardpartition0);
    pthread_create(&thread_cols, NULL, check_columns, (void *) boardpartition0);
    pthread_create(&thread1, NULL, check_square, (void *) boardpartition1);
    pthread_create(&thread2, NULL, check_square, (void *) boardpartition2);
    pthread_create(&thread3, NULL, check_square, (void *) boardpartition3);
    pthread_create(&thread4, NULL, check_square, (void *) boardpartition4);
    pthread_create(&thread5, NULL, check_square, (void *) boardpartition5);
    pthread_create(&thread6, NULL, check_square, (void *) boardpartition6);
    pthread_create(&thread7, NULL, check_square, (void *) boardpartition7);
    pthread_create(&thread8, NULL, check_square, (void *) boardpartition8);
    pthread_create(&thread9, NULL, check_square, (void *) boardpartition9);

    pthread_join(thread_rows, &valid_rows);
    pthread_join(thread_cols, &valid_columns);
    pthread_join(thread1, &square1);
    pthread_join(thread2, &square2);
    pthread_join(thread3, &square3);
    pthread_join(thread4, &square4);
    pthread_join(thread5, &square5);
    pthread_join(thread6, &square6);
    pthread_join(thread7, &square7);
    pthread_join(thread8, &square8);
    pthread_join(thread9, &square9);

    if ((int) valid_rows == 1 && (int) valid_columns == 1 && (int) square1 == 1 &&
            (int) square2 == 1 && (int) square3 == 1 && (int) square4 == 1 &&
            (int) square5 == 1 && (int) square6 == 1 && (int) square7 == 1 &&
            (int) square8 == 1 && (int) square9 == 1 )
        return 1;
    else
    	return 0;

    return 0;
}





