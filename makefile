all distclean :
	$(foreach LAB,$(wildcard ./lab*),pushd $(LAB) && $(MAKE) $@ && popd;)
