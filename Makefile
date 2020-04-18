ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
export CFLAGS := -I$(ROOT_DIR)/include
export CXXFLAGS := -I$(ROOT_DIR)/include
export LDFLAGS := -L$(ROOT_DIR)/c -L$(ROOT_DIR)/cpp

SUBDIRS = c cpp tests

.PHONY: subdirs $(SUBDIRS) clean

subdirs: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ 
tests: c cpp

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done