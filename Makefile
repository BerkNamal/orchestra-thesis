CONTIKI_PROJECT = udp-server udp-client
all: $(CONTIKI_PROJECT)

CONTIKI = ../../..

MAKE_MAC = MAKE_MAC_TSCH

MODULES += os/services/orchestra
#MODULES += os/services/tsch-cs
MODULES += os/services/shell

include $(CONTIKI)/Makefile.include 


