
RM=/bin/rm
PREFIX=/usr/local
MAN=/share/man
#MAN=/man #BSD uncomment
CC=clang
CFLAGS+= -O2 -Wall -g -pedantic
LDFLAGS+= -lm
OBJS=polex.c
TARGETS=polex

polex: 
	$(CC) -o $@ $(CFLAGS) $(OBJS) $(LDFLAGS) 

clean:	
	$(RM) -f $(TARGETS) *.o

install:
	install -pm 755 polex 		$(PREFIX)/bin
	test -d $(PREFIX)$(MAN)/man1 || mkdir -p $(PREFIX)$(MAN)/man1
	install -pm 644 polex.man 	$(PREFIX)$(MAN)/man1/polex.1

uninstall:
	$(RM) $(PREFIX)/bin/polex
	$(RM) $(PREFIX)$(MAN)/man1/polex.1
