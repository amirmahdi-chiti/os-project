#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "decoder.h"
#include "placer.h"

int main() {
    pid_t decoder, finder, placer;
    // Adresses of fifo files
    char fifos[3][100] = {"../pipes/decoderFifo.txt",
                        "../pipes/finderFifo.txt",
                        "../pipes/placer.Fifo.txt" };

    /* 
        We have 3 processes and to satisfy this assumption we should
    do something not to have 8 processes with 3 forks, so we define 3
    conditions as below to be sure that we do not duplicate the things 
    we suppose to do.
        The conditions check that the fifo related file of each
    process is made or not, it made, it won't fork again and if
    the related file doesn't exist then forks.
    */
    if (!access(fifos[0], F_OK)) {
        mkfifo(fifos[0], 0666);
        decoder = fork();
    }
    if (!access(fifos[1], F_OK)) {
        mkfifo(fifos[1], 0666);
        finder = fork();
    }
    if (!access(fifos[2], F_OK)) {
        mkfifo(fifos[2], 0666);
        placer = fork();
    }

    int f;

    // It means that we are in the child process of decoder
    if (decoder == 0) {
        f = open(fifos[0], O_RDONLY);
    }
    // It means that we are in the child process of finder 
    if (finder == 0) {
        f = open(fifos[1], O_RDONLY);
    }
    // It means that we are in the child process of placer
    if (placer == 0) {
        f = open(fifos[2], O_RDONLY);
    }

    return 0;
}