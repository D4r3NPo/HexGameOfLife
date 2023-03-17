CC         = gcc
CXX        = g++
ARCH       = -target x86_64-apple-darwin
OBJDIR     = Objects
SRCDIR     = Sources
TARGET     = Program
INCLUDES  += -I.. -ISources -ISDL/SDL2.framework -ISDL/SDL2_image.framework -ISDL/SDL2_ttf.framework -ISDL/SDL2.framework/Versions -ISDL/SDL2.framework/Versions/A -ISDL/SDL2.framework/Versions/A/Headers -ISDL/SDL2.framework/Versions/A/Resources -ISDL/SDL2.framework/Versions/A/_CodeSignature -ISDL/SDL2.framework/Versions/A/Headers/SDL2 -ISDL/SDL2_image.framework/Frameworks -ISDL/SDL2_image.framework/Headers -ISDL/SDL2_image.framework/Resources -ISDL/SDL2_image.framework/Versions -ISDL/SDL2_image.framework/Frameworks/webp.framework -ISDL/SDL2_image.framework/Frameworks/webp.framework/Headers -ISDL/SDL2_image.framework/Frameworks/webp.framework/Resources -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions -ISDL/SDL2_image.framework/Frameworks/webp.framework/Headers/webp -ISDL/SDL2_image.framework/Frameworks/webp.framework/Resources/English.lproj -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/A -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/Current -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/A/Headers -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/A/Resources -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/A/_CodeSignature -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/A/Headers/webp -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/A/Resources/English.lproj -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/Current/Headers -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/Current/Resources -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/Current/_CodeSignature -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/Current/Headers/webp -ISDL/SDL2_image.framework/Frameworks/webp.framework/Versions/Current/Resources/English.lproj -ISDL/SDL2_image.framework/Versions/A -ISDL/SDL2_image.framework/Versions/Current -ISDL/SDL2_image.framework/Versions/A/Frameworks -ISDL/SDL2_image.framework/Versions/A/Headers -ISDL/SDL2_image.framework/Versions/A/Resources -ISDL/SDL2_image.framework/Versions/A/_CodeSignature -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Headers -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Resources -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Headers/webp -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Resources/English.lproj -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/A -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/Current -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/A/Headers -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/A/Resources -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/A/_CodeSignature -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/A/Headers/webp -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/A/Resources/English.lproj -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/Current/Headers -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/Current/Resources -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/Current/_CodeSignature -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/Current/Headers/webp -ISDL/SDL2_image.framework/Versions/A/Frameworks/webp.framework/Versions/Current/Resources/English.lproj -ISDL/SDL2_image.framework/Versions/Current/Frameworks -ISDL/SDL2_image.framework/Versions/Current/Headers -ISDL/SDL2_image.framework/Versions/Current/Resources -ISDL/SDL2_image.framework/Versions/Current/_CodeSignature -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Headers -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Resources -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Headers/webp -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Resources/English.lproj -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/A -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/Current -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/A/Headers -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/A/Resources -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/A/_CodeSignature -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/A/Headers/webp -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/A/Resources/English.lproj -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/Current/Headers -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/Current/Resources -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/Current/_CodeSignature -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/Current/Headers/webp -ISDL/SDL2_image.framework/Versions/Current/Frameworks/webp.framework/Versions/Current/Resources/English.lproj -ISDL/SDL2_ttf.framework/Versions -ISDL/SDL2_ttf.framework/Versions/A -ISDL/SDL2_ttf.framework/Versions/A/Headers -ISDL/SDL2_ttf.framework/Versions/A/Resources -ISDL/SDL2_ttf.framework/Versions/A/_CodeSignature
CPPFLAGS  += -MMD -MP $(INCLUDES)
CFLAGS    += $(CPPFLAGS) $(ARCH) -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-comment -Wno-narrowing -std=c++17
CXXFLAGS  += $(CFLAGS)
LDFLAGS   += -Wl,-x SDL/SDL2.framework/Versions/A/SDL2 SDL/SDL2_image.framework/Versions/A/SDL2_image SDL/SDL2_ttf.framework/Versions/A/SDL2_ttf -rpath @executable_path/SDL
RESFLAGS  += $(INCLUDES)
LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(ARCH)

SRCS = $(shell find $(SRCDIR) -name *.cc) $(shell find $(SRCDIR) -name *.cpp)
OBJECTS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(patsubst %.cc,%.o,$(patsubst %.cpp,%.o,$(SRCS))))

#OBJECTS := \
	$(OBJDIR)/Grapic.o \
	$(OBJDIR)/main.o \
	$(OBJDIR)/Complex.o \

vpath %.cpp $(SRCDIR)
vpath %.hpp $(SRCDIR)
vpath %.o $(OBJDIR)

all: $(OBJDIR) $(TARGET)
	rm -r $(OBJDIR)

$(OBJDIR):
	@echo "===== Creating $(OBJDIR) ====="
	@mkdir -p $(OBJDIR)

$(TARGET): $(OBJECTS) $(LDDEPS)
	@echo "===== Linking ====="
	@$(LINKCMD)

clean:
	@echo '==== Cleaning ===='
	rm -f  $(TARGET)
	rm -rf $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	@echo $(notdir $<)
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"