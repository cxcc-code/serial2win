CC=$(CROSS_COMPILE)gcc

OBJS += src/main.o

serial2win:$(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

%.o:%.c
	$(CC) -c $^ $(CFLAGS) -o $@

PHONY+=clean
clean:
	$(RM) $(OBJS)
	$(RM) serial2win

.PHONY:$(PHONY)