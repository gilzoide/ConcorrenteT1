export BUILD = "$(CURDIR)/build"
export exe = main

all :
	$(MAKE) -C src $@

run :
	@$(BUILD)/$(exe) $(multi)

.PHONY : clean
clean :
	$(RM) *~
	$(MAKE) -C src $@
