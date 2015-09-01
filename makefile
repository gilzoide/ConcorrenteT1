export BUILD = $(CURDIR)/build

all :
	$(MAKE) -C src $@

.PHONY : clean
clean :
	$(RM) *~
	$(MAKE) -C src $@
