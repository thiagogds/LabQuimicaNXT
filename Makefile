APP = labquimica

include $(SDK_DIR)/Makefile.defs

OBJS = \
    $(ASSETS).gen.o \
    main.o \
    app.o \
    cube.o \
    calculators.o \
    substance.o

ASSETDEPS += *.png $(ASSETS).lua
CDEPS += *.h

include $(SDK_DIR)/Makefile.rules
