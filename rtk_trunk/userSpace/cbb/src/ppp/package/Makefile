#
# PPP module Makefile 
# 
# Copyright (C) 2016, Tenda Tech. Co., All Rights Reserved.
# This is UNPUBLISHED PROPRIETARY SOURCE CODE of Tenda Tech. Co.;
# the contents of this file may not be disclosed to third parties, copied
# or duplicated in any form, in whole or in part, without the prior
# written permission of Tenda Tech. Co.
#
# @ Id: Makefile,v 1.0 2016/01/11 @
#	@ author: zhuhuan @
#

MODULE = obj-$(shell pwd | sed "s/.*\///" ).o

all: $(MODULE)

# router config
include $(TENDA_APP_DIR)/.config

#
# EXTRA_CFLAG propogats to subdirectory
#

#
# Enumerate subdirectories
#
# obj-$(CONFIG_PPPOE) += pppoecd
# obj-$(CONFIG_L2TP) += l2tpcd
# obj-$(CONFIG_PPTP) += pptpcd

SUBDIRS = pppd
SUBDIRS += pppoecd
SUBDIRS += tenda_crypto

subdirs: $(patsubst %, _dir_%, $(SUBDIRS))
$(patsubst %, _dir_%, $(SUBDIRS)) :
	$(MAKE) CFLAGS="$(CFLAGS)" ENDIAN=$(ENDIAN) -C $(patsubst _dir_%, %, $@)

SUB_OBJS = $(join $(SUBDIRS), $(patsubst %, /obj-%.o, $(SUBDIRS)))

#
# Node rule to make
#
ifneq ($(wildcard $(MODULE).gz),$(MODULE).gz)
$(MODULE): subdirs $(SUB_OBJS)
	$(LD) -r $(TDAPP_LDFLAGS) -o $@ $(SUB_OBJS)
endif

# prebuild
prebuild: $(MODULE)
	@gzip -f $(MODULE)

clean:
	find . -name '*.[od]' -type f -print | xargs rm -f

.PHONY:	clean
