#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t decoder, finder, placer;
    char fifos[3][100] = {"../pipes/decoderFifo.txt",
                        "../pipes/finderFifo.txt",
                        "../pipes/placer.Fifo.txt" };

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

    if (decoder == 0) {
        
    }
    if (finder == 0) {

    }
    if (placer == 0) {

    }

    return 0;
}