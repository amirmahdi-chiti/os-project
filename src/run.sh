rm /tmp/fifo*

gcc decoder.c -o decoder
gcc finder.c -o finder
gcc placer.c -o placer
gcc MainProcess.c -o MainProcess

./MainProcess
