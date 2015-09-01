export BUILD = "$(CURDIR)/build"
export exe = main

all :
	$(MAKE) -C src $@

run :
	@$(BUILD)/$(exe)

.PHONY : clean
clean :
	$(RM) *~
	$(MAKE) -C src $@
