all:authexec

authexec.x86_64:
	$(CC) authexec.c -arch x86_64 -o authexec.x86_64 -framework Security

authexec.i386:
	$(CC) authexec.c -arch i386 -o authexec.i386 -framework Security

authexec.ppc:
	$(CC) authexec.c -arch ppc -o authexec.ppc -framework Security

authexec: authexec.i386 authexec.x86_64
	lipo -create -output authexec -arch i386 authexec.i386 -arch x86_64 authexec.x86_64 # -arch ppc authexec.ppc
	-rm authexec.i386 authexec.x86_64 # authexec.ppc

clean: 
	-rm authexec
