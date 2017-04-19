
RM=/bin/rm
PREFIX=/usr/local
MAN=/share/man
CC=clang
CFLAGS+= -O2 -Wall -g -pedantic
LDFLAGS+= -lm
OBJS=expr.c 
TARGETS=expr

expr: 
	$(CC) -o $@ $(CFLAGS) $(OBJS) $(LDFLAGS) 

clean:	
	$(RM) -f $(TARGETS) *.o

install:
	install -pm 755 expr 		$(PREFIX)/bin
	install -pm 644 expr.man 	$(PREFIX)$(MAN)/man1/expr.1
