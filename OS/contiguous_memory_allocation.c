#include <stdio.h>
#include <stdlib.h>

#define debug 0

#define INFINITE 99999
#define NONE -1

int* copy(int*, int);
void arrset(int*, int);
void input();
void p_result(int*);
void ff();  // first-fit algorithm
void bf();  // best-fit algorithm
void wf();  // worst-fit algorithm

int totalSize;
int numOfHole;
int* holes;  // index is hole no.
int numOfReq;
int* reqs;   // index is req no.
int* match;  // index is req no., content is hole no.

int main() {
    input();

    ff();
    bf();
    wf();
}

/** return a copy version of original array */
int* copy(int* arr, int len) {
    int* copy = malloc(sizeof(int) * len);
    for (int i = 0; i < len; ++i) copy[i] = arr[i];
    return copy;
}

void arrset(int* arr, int v) {
    while (*arr != 0) *arr++ = v;
}

void input() {
    // total memory size
    printf("Total memory size: ");
    scanf("%d", &totalSize);

    // get hole info
    printf("Number of holes: ");
    scanf("%d", &numOfHole);
    holes = malloc(sizeof(int) * numOfHole);
    printf("Size of holes (sep with space): ");
    for (int i = 0; i < numOfHole; ++i) scanf("%d", &holes[i]);

    // get requests info
    printf("Number of memory requests: ");
    scanf("%d", &numOfReq);
    reqs = malloc(sizeof(int) * numOfReq);
    printf("Size of requests (sep with space): ");
    for (int i = 0; i < numOfReq; ++i) scanf("%d", &reqs[i]);

    // init match array
    match = malloc(numOfReq * sizeof(int));
    arrset(match, -1);  // -1 for none
}

// print results
void p_result(int* hh) {
    int sum = 0;
    for (int i = 0; i < numOfHole; ++i) sum += hh[i];

    for (int hno = 0; hno < numOfHole; ++hno) {
        printf("Hole %d [%4d->%4d]: ", hno, holes[hno], hh[hno]);
        for (int rno = 0; rno < numOfReq; ++rno) {
            if (match[rno] == hno) printf("%d(%d) ", reqs[rno], rno);
        }
        printf("\n");
    }
    printf("Unsatisfied req: ");
    for (int rno = 0; rno < numOfReq; ++rno)
        if (match[rno] == NONE) printf("%d(%d) ", reqs[rno], rno);
    printf("\n");

    printf("Unused space after compaction: %d\n", sum);

    printf("Ultrilization: %.1f\n", (float)(totalSize - sum) * 100 / totalSize);
}

void ff() {
    printf("---------First-fit---------");
    int* hh = copy(holes, numOfHole);  // copy of holes array

    if (debug) {
        printf("Hole");
        for (int i = 0; i < numOfHole; ++i) printf("%4d ", i + 1);
        printf("\n");

        printf("    ");
        for (int i = 0; i < numOfHole; ++i) printf("%4d ", hh[i]);
        printf("    (start)\n");
    }

    for (int rno = 0; rno < numOfReq; ++rno) {  // 'rno' for request no.
        // print holes
        if (debug) {
            printf("    ");
            for (int i = 0; i < numOfHole; ++i) printf("%4d ", hh[i]);
            printf("    ");
        }

        for (int hno = 0; hno < numOfHole; ++hno) {  // 'hno' for hole no.
            if (hh[hno] >= reqs[rno]) {
                match[rno] = hno;
                hh[hno] -= reqs[rno];
                break;
            }
        }

        if (debug) {
            if (match[rno] == -1) {
                printf("req [%d|%d] not satisfied\n", rno + 1, reqs[rno]);
            } else {
                printf("req [%d|%d] go to hole [%d]\n", rno + 1, reqs[rno],
                       match[rno] + 1);
            }
        }
    }

    // print results
    p_result(hh);
}

// find smallest fitted hole
void bf() {
    printf("---------Best-fit---------");
    int* hh = copy(holes, numOfHole);              // copy of holes array
    int* queue = malloc(sizeof(int) * numOfHole);  // -1 means none
    int qidx;

    // 'rno' for request no.; 'hno' for hole no.
    for (int rno = 0; rno < numOfReq; ++rno) {
        // init queue
        arrset(queue, NONE);
        qidx = 0;

        // record every fit hole in queue
        for (int hno = 0; hno < numOfHole; ++hno) {
            if (hh[hno] >= reqs[rno]) {
                queue[qidx++] = hno;
            }
        }

        // find best hole
        int shno = NONE;  // smallest hole no.
        int smallest = INFINITE;
        for (int i = 0; i < qidx; ++i) {
            if (hh[queue[i]] < smallest) {
                smallest = hh[queue[i]];
                shno = queue[i];
            }
        }
        match[rno] = shno;
        if (rno != NONE) hh[shno] -= reqs[rno];
    }

    // print results
    p_result(hh);
}

// find biggest fitted hole
void wf() {
    printf("\n---------Worst-fit---------\n");
    int* hh = copy(holes, numOfHole);              // copy of holes array
    int* queue = malloc(sizeof(int) * numOfHole);  // -1 means none
    int qidx;

    // 'rno' for request no.; 'hno' for hole no.
    for (int rno = 0; rno < numOfReq; ++rno) {
        qidx = 0;  // init queue

        // record every fit hole in queue
        for (int hno = 0; hno < numOfHole; ++hno) {
            if (hh[hno] >= reqs[rno]) {
                queue[qidx++] = hno;
            }
        }

        // find best hole
        int bhno = NONE;  // biggest hole no.
        int biggest = -INFINITE;
        for (int i = 0; i < qidx; ++i) {
            if (hh[queue[i]] > biggest) {
                biggest = hh[queue[i]];
                bhno = queue[i];
            }
        }
        match[rno] = bhno;
        if (bhno != NONE) hh[bhno] -= reqs[rno];
    }

    // print results
    p_result(hh);
}

/*
5000
4
200 400 600 300
6
280 180 320 400 120 160


1000
3
100 180 120
10
31 79 24 75 34 65 46 11 27 18

*/
