ifndef config
  config=grapic
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifeq ($(config),grapic)
  ARCH       = -target x86_64-apple-darwin
  OBJDIR     = Objects/
  TARGETDIR  = .
  TARGET     = $(TARGETDIR)/Program
  DEFINES   += 
  INCLUDES  += -I.. -ISources -ISDL/SDL2.framework -ISDL/SDL2_image.framework -ISDL/SDL2_ttf.framework -ISDL/SDL2.framework/Versions -ISDL/SDL2.framework/Versions/A -ISDL/SDL2.framework/Versions/A/Headers -ISDL/SDL2.framework/Versions/A/Resources -ISDL/SDL2.framework/Versions/A/_CodeSignature -ISDL/SDL2.framework/Versions/A/Headers/SDL2 -ISDL/SDL2_image.framework/Frameworks -ISDL/SDL2_image.framework/Headers -ISDL/SDL2_image.framework/Resources -ISDL/SDL2_image.framework/Versions -ISDL/SDL2_image.framework/Frameworks/webp.framework -ISDL/SDL2_image.framework/Frameworks/webp.framework/Headers -ISDL/SDL2_image.framework/Frameworks/webp.framework/Resources -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions -ISDL/SDL2_image.framework/Frameworks/webp.framework/Headers/webp -ISDL/SDL2_image.framework/Frameworks/webp.framework/Resources/English.lproj -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/A -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/Current -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/A/Headers -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/A/Resources -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/A/_CodeSignature -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/A/Headers/webp -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/A/Resources/English.lproj -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/Current/Headers -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/Current/Resources -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/Current/_CodeSignature -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/Current/Headers/webp -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/Current/Resources/English.lproj -ISDL/SDL2_image.framework/Versions/A -ISDL/SDL2_image.framework/Versions/Current -ISDL/SDL2_image.framework/Versions/A/Frameworks -ISDL/SDL2_image.framework/Versions/A/Headers -ISDL/SDL2_image.framework/Versions/A/Resources -ISDL/SDL2_image.framework/Versions/A/_CodeSignature -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Headers -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Resources -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Headers/webp -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Resources/English.lproj -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/A -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/Current -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/A/Headers -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/A/Resources -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/A/_CodeSignature -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/A/Headers/webp -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/A/Resources/English.lproj -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/Current/Headers -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/Current/Resources -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/Current/_CodeSignature -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/Current/Headers/webp -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/Current/Resources/English.lproj -ISDL/SDL2_image.framework/Versions/Current/Frameworks -ISDL/SDL2_image.framework/Versions/Current/Headers -ISDL/SDL2_image.framework/Versions/Current/Resources -ISDL/SDL2_image.framework/Versions/Current/_CodeSignature -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Headers -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Resources -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Headers/webp -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Resources/English.lproj -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/A -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/Current -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/A/Headers -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/A/Resources -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/A/_CodeSignature -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/A/Headers/webp -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/A/Resources/English.lproj -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/Current/Headers -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/Current/Resources -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/Current/_CodeSignature -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/Current/Headers/webp -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/Current/Resources/English.lproj -ISDL/SDL2_ttf.framework/Versions -ISDL/SDL2_ttf.framework/Versions/A -ISDL/SDL2_ttf.framework/Versions/A/Headers -ISDL/SDL2_ttf.framework/Versions/A/Resources -ISDL/SDL2_ttf.framework/Versions/A/_CodeSignature
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-comment -Wno-narrowing -std=c++17
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -Wl,-x SDL/SDL2.framework/Versions/A/SDL2 SDL/SDL2_image.framework/Versions/A/SDL2_image SDL/SDL2_ttf.framework/Versions/A/SDL2_ttf -rpath @executable_path/SDL
  LIBS      += 
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/Grapic.o \
	$(OBJDIR)/main.o \

RESOURCES := \

SHELLTYPE := posix

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking Start
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)
#   Force make
	@rm -r $(OBJDIR)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
	$(SILENT) mkdir -p $(TARGETDIR)

$(OBJDIR):
	@echo Creating $(OBJDIR)
	$(SILENT) mkdir -p $(OBJDIR)


clean:
	@echo Cleaning Start
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
endif

$(OBJDIR)/Grapic.o: Sources/Grapic.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/main.o: Sources/main.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
