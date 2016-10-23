APP = lol

OBJDIR = obj

SRCS := $(shell find . -name '*.c')
SRCDIRS := $(shell find . -name '*.c' -exec dirname {} \; | uniq)
OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
DEPS := $(patsubst %.c,$(OBJDIR)/%.d,$(SRCS))

DEBUG = -g
INCLUDES = -I./inc
CFLAGS = $(DEBUG) -Wall -pedantic $(INCLUDES) -std=c11 -c -fopenmp
LDFLAGS = -fopenmp -pthread -L /usr/local/ssl/lib/ -lcrypto -Wall -std=c11 -lsqlite3
LIBS = -lm -fopenmp -latomic

DEPENDS = -MT $@ -MD -MP -MF $(subst .o,.d,$@)

SHELL = /bin/bash

.PHONY: all clean distclean


all: buildrepo $(APP)

$(APP): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $(DEPENDS) $< -o $@

clean:
	$(RM) -r $(OBJDIR)
	$(RM) -Rf $(APP)

distclean: clean
	$(RM) $(APP)

buildrepo:
	@$(call make-repo)

define make-repo
for dir in $(SRCDIRS); \
do \
mkdir -p $(OBJDIR)/$$dir; \
done
endef

ifneq "$(MAKECMDGOALS)" "distclean"
ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPS)
endif
endif