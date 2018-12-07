CONTIKI_PROJECT = parent-child-process
all:	$(CONTIKI_PROJECT)

#UIP_CONF_IPV6 = 1

CONTIKI = /home/user/contiki-3.0/
include $(CONTIKI)/Makefile.include
