# include $(DIR_LINUX)/.config
include ../../../../linux-2.6.30/.config
 
ifeq ($(CONFIG_RTL_FLASH_MAPPING_ENABLE),y)
	CFLAGS += -DCONFIG_RTL_FLASH_MAPPING_ENABLE
ifdef CONFIG_RTL_FLASH_SIZE
	CFLAGS += -DCONFIG_RTL_FLASH_SIZE=$(CONFIG_RTL_FLASH_SIZE)
endif
ifdef CONFIG_RTL_LINUX_IMAGE_OFFSET
	CFLAGS += -DCONFIG_RTL_LINUX_IMAGE_OFFSET=$(CONFIG_RTL_LINUX_IMAGE_OFFSET)
endif
ifdef CONFIG_RTL_ROOT_IMAGE_OFFSET
	CFLAGS += -DCONFIG_RTL_ROOT_IMAGE_OFFSET=$(CONFIG_RTL_ROOT_IMAGE_OFFSET)
endif
endif

all: rsCert

rsCert: rsCertCommon.o rsCert.o
	$(CC) -o $@ $^ $(LDFLAGS)
	$(STRIP) $@

rsCertCommon.o: rsCertCommon.h rsCertCommon.c

rsCert.o: rsCertCommon.h rsCert.c

clean:
	rm -f *.o rsCert

romfs:
	@echo "Do nothing here."
#	$(ROMFSINST) /bin/rsCert

