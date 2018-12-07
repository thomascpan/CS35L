randlibhw.so: randlibhw.c
	$(CC) $(CFLAGS) randlibhw.c -o $@ -shared -fPIC
randlibsw.so: randlibsw.c
	$(CC) $(CFLAGS) randlibsw.c -o $@ -shared -fPIC
randmain: randmain.o randcpuid.o
	$(CC) $(CFLAGS) randmain.o randcpuid.o -o $@ -ldl -Wl,-rpath=$(PWD)