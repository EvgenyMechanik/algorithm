SUBDIRS = c cpp tests
CFLAGS := "-Iinclude"

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@
tests: c cpp