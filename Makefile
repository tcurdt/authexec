all:authexec

authexec.i386:
	gcc authexec.c -arch i386 -o authexec.i386 -framework Security

authexec.ppc:
	gcc authexec.c -arch ppc -o authexec.ppc -framework Security

authexec: authexec.i386 authexec.ppc
	lipo -create -output authexec -arch i386 authexec.i386 -arch ppc authexec.ppc
	-rm authexec.i386 authexec.ppc

clean: 
	-rm authexec
