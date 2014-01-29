main: Engine Clean

Engine: Engine.c Headers
	gcc Engine.c -o execute
Headers: headers.h
	gcc headers.h
Clean:
	rm headers.h.gch