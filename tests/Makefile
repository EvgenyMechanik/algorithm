SUBDIRS = c cpp

.PHONY: subdirs $(SUBDIRS) clean

subdirs: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ 
tests: c cpp

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done