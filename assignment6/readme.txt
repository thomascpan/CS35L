The first issue I encountered was simply learning how to use the pthreads interface and how to correctly pass arguments into each thread. 

The second issue I encountered was a bug where the index passed into the pthread_create fuction was different from when I printed it out in the fuction. It turns out that this was because I was using 
the same argument, but I was just updating the "id" field each time. This resulted in a race condition, where the index could already have been incremented by the loop surrounding the pthread_create 
functions. I eventually resolved this by creating a new set of arguments for each thread.

The third issue I encountered was simply printing out the results. I couldn't figure out why my images were all scrambled. I eventually realized this was because I was printing my results from within 
the thread. This resulted in values being printed out of order. I eventually solved this by creating a global array. As the threads ran, I would assign the results to their respective location in the 
array. After all the threads have completed their work, I would iterate through the array and print out the results in order. 


From the time logs below, we can see that multithreading results in a substantial increase in performance. The fastest time achieved with multithreading (8 threads) was around 10s. Without 
multithreading, it took the program 47s, which is almost 5 times longer. However, it does appear that multithreading by N threads does not make the program N times faster, and that adding more 
threads does have some diminishing returns. 

time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m47.620s
user	0m47.611s
sys	0m0.003s
mv 1-test.ppm.tmp 1-test.ppm

time ./srt 2-test.ppm >2-test.ppm.tmp

real	0m24.363s
user	0m47.660s
sys	0m0.008s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real	0m16.258s
user	0m48.487s
sys	0m0.004s
mv 4-test.ppm.tmp 4-test.ppm

time ./srt 8-test.ppm >8-test.ppm.tmp

real	0m10.359s
user	0m49.933s
sys	0m0.002s