CC=$(CROSS_COMPILE)gcc

DEBUG = -O -g

CINCLUDE_PATH += ./inc

CFLAGS += $(addprefix -I,$(CINCLUDE_PATH))
CFLAGS += $(DEBUG)

LDFLAGS += $(DEBUG)

OBJS += src/main.o
OBJS += src/prase_args.o
OBJS += src/serial.o
OBJS += src/tty_key_map.o

serial2win:$(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

%.o:%.c
	$(CC) -c $^ $(CFLAGS) -o $@

PHONY+=clean
clean:
	$(RM) $(OBJS)
	$(RM) serial2win

.PHONY:$(PHONY)