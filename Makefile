#
# Quake3 Unix Makefile
#
# Nov '98 by Zoid <zoid@idsoftware.com>
#
# Loki Hacking by Bernd Kreimeier
#  and a little more by Ryan C. Gordon.
#  and a little more by Rafael Barrero
#  and a little more by the ioq3 cr3w
#
# GNU Make required
#

COMPILE_PLATFORM=$(shell uname|sed -e s/_.*//|tr '[:upper:]' '[:lower:]')

ifeq ($(COMPILE_PLATFORM),darwin)
  # Apple does some things a little differently...
  COMPILE_ARCH=$(shell uname -p | sed -e s/i.86/i386/)
else
  COMPILE_ARCH=$(shell uname -m | sed -e s/i.86/i386/)
endif

ifeq ($(COMPILE_PLATFORM),mingw32)
  ifeq ($(COMPILE_ARCH),i386)
    COMPILE_ARCH=x86
  endif
endif

ifndef USE_CCACHE
USE_CCACHE=0
endif
export USE_CCACHE

#############################################################################
#
# If you require a different configuration from the defaults below, create a
# new file named "Makefile.local" in the same directory as this file and define
# your parameters there. This allows you to change configuration without
# causing problems with keeping up to date with the repository.
#
#############################################################################
-include Makefile.local

ifndef PLATFORM
PLATFORM=$(COMPILE_PLATFORM)
endif
export PLATFORM

ifndef ARCH
ARCH=$(COMPILE_ARCH)
endif

ifeq ($(ARCH),powerpc)
  ARCH=ppc
endif
export ARCH

ifneq ($(PLATFORM),$(COMPILE_PLATFORM))
  CROSS_COMPILING=1
else
  CROSS_COMPILING=0

  ifneq ($(ARCH),$(COMPILE_ARCH))
    CROSS_COMPILING=1
  endif
endif
export CROSS_COMPILING

ifndef COPYDIR
COPYDIR="/usr/local/games/quake3"
endif

BD=debug-$(PLATFORM)-$(ARCH)
BR=release-$(PLATFORM)-$(ARCH)
LIBSDIR=lib/

## Defaults
INSTALL=install
MKDIR=mkdir

#############################################################################
# SETUP AND BUILD -- LINUX
#############################################################################
ifeq ($(PLATFORM),linux)
  CC=g++

  ifeq ($(ARCH),alpha)
    ARCH=axp
  else
  ifeq ($(ARCH),x86_64)
    LIB=lib64
  else
  ifeq ($(ARCH),ppc64)
    LIB=lib64
  else
  ifeq ($(ARCH),s390x)
    LIB=lib64
  endif
  endif
  endif
  endif

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -pipe -Werror # -Wstrict-prototypes

  OPTIMIZE = -O3 -ffast-math -funroll-loops -fomit-frame-pointer

  ifeq ($(ARCH),x86_64)
    OPTIMIZE = -O3 -fomit-frame-pointer -ffast-math -funroll-loops -falign-loops=2 -falign-jumps=2 -falign-functions=2 -fstrength-reduce
  else
  ifeq ($(ARCH),i386)
    OPTIMIZE = -O3 -march=i586 -fomit-frame-pointer -ffast-math -funroll-loops -falign-loops=2 -falign-jumps=2 -falign-functions=2 -fstrength-reduce
  else
  ifeq ($(ARCH),ppc)
    BASE_CFLAGS += -maltivec
  endif
  endif
  endif

  DEBUG_CFLAGS = $(BASE_CFLAGS) -g -O0

  RELEASE_CFLAGS=$(BASE_CFLAGS) -DNDEBUG $(OPTIMIZE)

  SHLIBEXT=.so
  SHLIBCFLAGS=-fPIC
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  THREAD_LDFLAGS=-lpthread
  LDFLAGS=-ldl -lm

  ifeq ($(ARCH),i386)
    # linux32 make ...
    BASE_CFLAGS += -m32
    LDFLAGS+=-m32
  endif

  CLIENT_LDFLAGS=-L/usr/X11R6/$(LIB) -lX11 -lXext -lXxf86dga -lXxf86vm
  GL_CFLAGS = -I/usr/X11R6/include

else # ifeq Linux

#############################################################################
# SETUP AND BUILD -- MAC OS X
#############################################################################
ifeq ($(PLATFORM),darwin)
  CC=gcc
  BASE_CFLAGS=
  CLIENT_LDFLAGS=
  LDFLAGS=
  OPTIMIZE=

  ifeq ($(BUILD_MACOSX_UB),ppc)
    CC=gcc-3.3
    BASE_CFLAGS += -arch ppc -DSMP \
      -DMAC_OS_X_VERSION_MIN_REQUIRED=1020 -nostdinc \
      -F/Developer/SDKs/MacOSX10.2.8.sdk/System/Library/Frameworks \
      -I/Developer/SDKs/MacOSX10.2.8.sdk/usr/include/gcc/darwin/3.3 \
      -isystem /Developer/SDKs/MacOSX10.2.8.sdk/usr/include
    # when using the 10.2 SDK we are not allowed the two-level namespace so
    # in order to get the OpenAL dlopen() stuff to work without major
    # modifications, the controversial -m linker flag must be used.  this
    # throws a ton of multiply defined errors which cannot be suppressed.
    LDFLAGS += -arch ppc \
      -L/Developer/SDKs/MacOSX10.2.8.sdk/usr/lib/gcc/darwin/3.3 \
      -F/Developer/SDKs/MacOSX10.2.8.sdk/System/Library/Frameworks \
      -Wl,-syslibroot,/Developer/SDKs/MacOSX10.2.8.sdk,-m 
    ARCH=ppc

    # OS X 10.2 sdk lacks dlopen() so ded would need libSDL anyway
    BUILD_SERVER=0

    # because of a problem with linking on 10.2 this will generate multiply
    # defined symbol errors.  The errors can be turned into warnings with
    # the -m linker flag, but you can't shut up the warnings 
    USE_OPENAL_DLOPEN=1
  else
  ifeq ($(BUILD_MACOSX_UB),i386)
    CC=gcc-4.0
    BASE_CFLAGS += -arch i386 -DSMP \
      -mmacosx-version-min=10.4 \
      -DMAC_OS_X_VERSION_MIN_REQUIRED=1040 -nostdinc \
      -F/Developer/SDKs/MacOSX10.4u.sdk/System/Library/Frameworks \
      -I/Developer/SDKs/MacOSX10.4u.sdk/usr/lib/gcc/i686-apple-darwin8/4.0.1/include \
      -isystem /Developer/SDKs/MacOSX10.4u.sdk/usr/include
    LDFLAGS = -arch i386 -mmacosx-version-min=10.4 \
      -L/Developer/SDKs/MacOSX10.4u.sdk/usr/lib/gcc/i686-apple-darwin8/4.0.1 \
      -F/Developer/SDKs/MacOSX10.4u.sdk/System/Library/Frameworks \
      -Wl,-syslibroot,/Developer/SDKs/MacOSX10.4u.sdk
    ARCH=i386
    BUILD_SERVER=0
  else
    # for whatever reason using the headers in the MacOSX SDKs tend to throw 
    # errors even though they are identical to the system ones which don't
    # therefore we shut up warning flags when running the universal build
    # script as much as possible.
    BASE_CFLAGS += -Wall -Wimplicit -Wstrict-prototypes
  endif
  endif

  ifeq ($(ARCH),ppc)
    OPTIMIZE += -faltivec
    # Carbon is required on PPC only to make a call to MakeDataExecutable
    # in the PPC vm (should be a better non-Carbon way).
    LDFLAGS += -framework Carbon
  endif
  ifeq ($(ARCH),i386)
    OPTIMIZE += -msse2
    # x86 vm will crash without -mstackrealign since MMX instructions will be
    # used no matter what and they corrupt the frame pointer in VM calls
    BASE_CFLAGS += -mstackrealign
  endif

  BASE_CFLAGS += -fno-strict-aliasing -DMACOS_X -fno-common -pipe

  # Always include debug symbols...you can strip the binary later...
  BASE_CFLAGS += -gfull

  OPTIMIZE += -O3 -ffast-math -falign-loops=16

  DEBUG_CFLAGS = $(BASE_CFLAGS) -g -O0

  RELEASE_CFLAGS=$(BASE_CFLAGS) -DNDEBUG $(OPTIMIZE)

  SHLIBEXT=.dylib
  SHLIBCFLAGS=-fPIC -fno-common
  SHLIBLDFLAGS=-dynamiclib $(LDFLAGS)

  NOTSHLIBCFLAGS=-mdynamic-no-pic
else # ifeq darwin

#############################################################################
# SETUP AND BUILD -- MINGW32
#############################################################################
ifeq ($(PLATFORM),mingw32)
  CC=i586-mingw32msvc-gcc
  WINDRES=i586-mingw32msvc-windres

  ARCH=x86

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes -I/usr/i586-mingw32msvc/

  GL_CFLAGS =
  MINGW_CFLAGS = -DDONT_TYPEDEF_INT32

  OPTIMIZE = -O3 -march=i586 -fomit-frame-pointer -ffast-math -falign-loops=2 -funroll-loops -falign-jumps=2 -falign-functions=2 -fstrength-reduce

  DEBUG_CFLAGS=$(BASE_CFLAGS) -g -O0

  RELEASE_CFLAGS=$(BASE_CFLAGS) -DNDEBUG $(OPTIMIZE)

  SHLIBEXT=.dll
  SHLIBCFLAGS=
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  BINEXT=.exe

  LDFLAGS= -mwindows -lwsock32 -lgdi32 -lwinmm -lole32
  CLIENT_LDFLAGS=

  ifeq ($(ARCH),x86)
    # build 32bit
    BASE_CFLAGS += -m32
    LDFLAGS+=-m32
  endif

  BUILD_SERVER = 0
  BUILD_CLIENT_SMP = 0
else # ifeq mingw32

#############################################################################
# SETUP AND BUILD -- FREEBSD
#############################################################################
ifeq ($(PLATFORM),freebsd)
  ifneq (,$(findstring alpha,$(shell uname -m)))
    ARCH=axp
  else #default to i386
    ARCH=i386
  endif #alpha test

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes

  GL_CFLAGS = -I/usr/X11R6/include

  DEBUG_CFLAGS=$(BASE_CFLAGS) -g

  ifeq ($(ARCH),axp)
    CC=gcc
    BASE_CFLAGS += -DNO_VM_COMPILED
    RELEASE_CFLAGS=$(BASE_CFLAGS) -DNDEBUG -O3 -ffast-math -funroll-loops -fomit-frame-pointer -fexpensive-optimizations
  else
  ifeq ($(ARCH),i386)
    CC=gcc
    RELEASE_CFLAGS=$(BASE_CFLAGS) -DNDEBUG -O3 -mtune=pentiumpro -march=pentium -fomit-frame-pointer -pipe -ffast-math -falign-loops=2 -falign-jumps=2 -falign-functions=2 -funroll-loops -fstrength-reduce
  endif
  endif

  SHLIBEXT=.so
  SHLIBCFLAGS=-fPIC
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  THREAD_LDFLAGS=-lpthread
  # don't need -ldl (FreeBSD)
  LDFLAGS=-lm

  CLIENT_LDFLAGS =
else # ifeq freebsd

#############################################################################
# SETUP AND BUILD -- NETBSD
#############################################################################
ifeq ($(PLATFORM),netbsd)
  ifeq ($(shell uname -m),i386)
    ARCH=i386
  endif

  CC=gcc
  LDFLAGS=-lm
  SHLIBEXT=.so
  SHLIBCFLAGS=-fPIC
  SHLIBLDFLAGS=-shared $(LDFLAGS)
  THREAD_LDFLAGS=-lpthread

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes
  DEBUG_CFLAGS=$(BASE_CFLAGS) -g

  ifneq ($(ARCH),i386)
    BASE_CFLAGS += -DNO_VM_COMPILED
  endif

  BUILD_CLIENT = 0
else # ifeq netbsd

#############################################################################
# SETUP AND BUILD -- IRIX
#############################################################################
ifeq ($(PLATFORM),irix)

  ARCH=mips  #default to MIPS

  CC=cc
  BASE_CFLAGS=-Dstricmp=strcasecmp -Xcpluscomm -woff 1185 -mips3 -nostdinc -I. -I$(ROOT)/usr/include -DNO_VM_COMPILED
  RELEASE_CFLAGS=$(BASE_CFLAGS) -O3
  DEBUG_CFLAGS=$(BASE_CFLAGS) -g

  SHLIBEXT=.so
  SHLIBCFLAGS=
  SHLIBLDFLAGS=-shared

  LDFLAGS=-ldl -lm
  CLIENT_LDFLAGS=-L/usr/X11/$(LIB) -lGL -lX11 -lXext -lm

else # ifeq IRIX

#############################################################################
# SETUP AND BUILD -- SunOS
#############################################################################
ifeq ($(PLATFORM),sunos)
  CC=gcc
  INSTALL=ginstall
  MKDIR=gmkdir
  COPYDIR="/usr/local/share/games/quake3"

  ifneq (,$(findstring i86pc,$(shell uname -m)))
    ARCH=i386
  else #default to sparc
    ARCH=sparc
  endif

  ifneq ($(ARCH),i386)
    ifneq ($(ARCH),sparc)
      $(error arch $(ARCH) is currently not supported)
    endif
  endif

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes -pipe

  OPTIMIZE = -O3 -ffast-math -funroll-loops

  ifeq ($(ARCH),sparc)
    OPTIMIZE = -O3 -ffast-math -falign-loops=2 \
      -falign-jumps=2 -falign-functions=2 -fstrength-reduce \
      -mtune=ultrasparc -mv8plus -mno-faster-structs \
      -funroll-loops
    BASE_CFLAGS += -DNO_VM_COMPILED
  else
  ifeq ($(ARCH),i386)
    OPTIMIZE = -O3 -march=i586  -ffast-math \
      -falign-loops=2 -falign-jumps=2 -falign-functions=2 \
      -funroll-loops -fstrength-reduce
  endif
  endif

  DEBUG_CFLAGS = $(BASE_CFLAGS) -ggdb -O0

  RELEASE_CFLAGS=$(BASE_CFLAGS) -DNDEBUG $(OPTIMIZE)

  SHLIBEXT=.so
  SHLIBCFLAGS=-fPIC
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  THREAD_LDFLAGS=-lpthread
  LDFLAGS=-lsocket -lnsl -ldl -lm

  BOTCFLAGS=-O0

  ifeq ($(ARCH),i386)
    # Solarix x86 make ...
    BASE_CFLAGS += -m32
    LDFLAGS+=-m32
  endif
else # ifeq sunos

#############################################################################
# SETUP AND BUILD -- GENERIC
#############################################################################
  CC=cc
  BASE_CFLAGS=-DNO_VM_COMPILED
  DEBUG_CFLAGS=$(BASE_CFLAGS) -g
  RELEASE_CFLAGS=$(BASE_CFLAGS) -DNDEBUG -O3

  SHLIBEXT=.so
  SHLIBCFLAGS=-fPIC
  SHLIBLDFLAGS=-shared
endif #Linux
endif #darwin
endif #mingw32
endif #FreeBSD
endif #NetBSD
endif #IRIX
endif #SunOS

SO=source/
BN=bin/

TARGETS += $(LIBSDIR)libtexgen.$(ARCH)$(SHLIBEXT)

ifneq ($(BUILD_SERVER),0)
  TARGETS += $(BN)recoil-ded.$(ARCH)$(BINEXT)
endif

ifneq ($(BUILD_CLIENT),0)
  TARGETS += $(BN)recoil.$(ARCH)$(BINEXT)
#  ifneq ($(BUILD_CLIENT_SMP),0)
#    TARGETS += $(BN)recoil-smp.$(ARCH)$(BINEXT)
#  endif
endif

ifeq ($(USE_CCACHE),1)
  CC := ccache $(CC)
endif

CLEANUP=astyle

DO_CC=$(CLEANUP) $< ; $(CC) $(NOTSHLIBCFLAGS) $(CFLAGS) -o $@ -c $<
DO_GL_CC=$(DO_CC) $(GL_CFLAGS) $(MINGW_CFLAGS)
DO_TGD_CC=$(CLEANUP) $< ; $(CC) -DLIBTEXGEN=\"$(LIBSDIR)libtexgen.$(ARCH)$(SHLIBEXT)\" $(NOTSHLIBCFLAGS) $(CFLAGS) -o $@ -c $<
DO_SMP_CC=$(CLEANUP) $< ; $(CC) $(NOTSHLIBCFLAGS) $(CFLAGS) -DSMP -o $@ -c $< $(SAVEOUTPUT)
DO_BOT_CC=$(CLEANUP) $< ; $(CC) $(NOTSHLIBCFLAGS) $(CFLAGS) $(BOTCFLAGS) -DBOTLIB -o $@ -c $<
DO_SHLIB_CC=$(CLEANUP) $< ; $(CC) $(CFLAGS) $(SHLIBCFLAGS) -o $@ -c $<
DO_DED_CC=$(CLEANUP) $< ; $(CC) $(NOTSHLIBCFLAGS) -DDEDICATED $(CFLAGS) -o $@ -c $<
DO_WINDRES=$(WINDRES) -i $< -o $@

ifneq ($(SAVEOUTPUT),0)
  SAVEOUTPUT= > output.txt
#  DO_CC += $(SAVEOUTPUT)
#  DO_GL_CC += $(SAVEOUTPUT)
#  DO_TGD_CC += $(SAVEOUTPUT)
#  DO_SMP_CC += $(SAVEOUTPUT)
#  DO_BOT_CC += $(SAVEOUTPUT)
#  DO_SHLIB_CC += $(SAVEOUTPUT)
#  DO_DED_CC += $(SAVEOUTPUT)
#  DO_WINDRES += $(SAVEOUTPUT)
endif

RBC=$(SO)engine/client-$(B)/
RBD=$(SO)engine/ded-$(B)/
TG=$(SO)texgen/$(B)/
TE=$(SO)tgEdit/$(B)/

#############################################################################
# MAIN TARGETS
#############################################################################

default: build_release

debug: build_debug
release: build_release

build_debug: B=$(BD)
build_debug: makedirs
	$(MAKE) targets B=$(BD) CFLAGS="$(CFLAGS) $(DEBUG_CFLAGS) $(DEPEND_CFLAGS)" $(SAVEOUTPUT)

build_release: B=$(BR)
build_release: makedirs
	$(MAKE) targets B=$(BR) CFLAGS="$(CFLAGS) $(RELEASE_CFLAGS) $(DEPEND_CFLAGS)" $(SAVEOUTPUT)

#Build both debug and release builds
all:build_debug build_release

targets: clear_output $(TARGETS)

clear_output:
	@if [ -d output.txt ]; then rm output.txt; fi

makedirs:
	@if [ ! -d $(SO)engine/client-$(B) ];then $(MKDIR) $(SO)engine/client-$(B);fi
	@if [ ! -d $(SO)engine/ded-$(B) ];then $(MKDIR) $(SO)engine/ded-$(B);fi
	@if [ ! -d $(SO)texgen/$(B) ];then $(MKDIR) $(SO)texgen/$(B);fi
	@if [ ! -d $(SO)tgEdit/$(B) ];then $(MKDIR) $(SO)tgEdit/$(B);fi

## ========================================================================
## Recoil engine, game, cgame, botlib and ui
##  all into one executable file
## ========================================================================

RECOILOBJS=\
	$(RBC)jcapimin.o\
	$(RBC)jcmaster.o\
	$(RBC)jdatadst.o\
	$(RBC)jdmaster.o\
	$(RBC)jfdctint.o\
	$(RBC)jcomapi.o\
	$(RBC)jdatasrc.o\
	$(RBC)jdmerge.o\
	$(RBC)jidctflt.o\
	$(RBC)jmemnobs.o\
	$(RBC)jccoefct.o\
	$(RBC)jcparam.o\
	$(RBC)jdcoefct.o\
	$(RBC)jdphuff.o\
	$(RBC)jidctfst.o\
	$(RBC)jccolor.o\
	$(RBC)jcphuff.o\
	$(RBC)jdcolor.o\
	$(RBC)jdpostct.o\
	$(RBC)jidctint.o\
	$(RBC)jquant1.o\
	$(RBC)jcdctmgr.o\
	$(RBC)jcprepct.o\
	$(RBC)jddctmgr.o\
	$(RBC)jdsample.o\
	$(RBC)jidctred.o\
	$(RBC)jquant2.o\
	$(RBC)jchuff.o\
	$(RBC)jcsample.o\
	$(RBC)jdhuff.o\
	$(RBC)jdtrans.o\
	$(RBC)jutils.o\
	$(RBC)jcinit.o\
	$(RBC)jctrans.o\
	$(RBC)jdinput.o\
	$(RBC)jerror.o\
	$(RBC)jcmainct.o\
	$(RBC)jdapimin.o\
	$(RBC)jdmainct.o\
	$(RBC)jfdctflt.o\
	$(RBC)jcmarker.o\
	$(RBC)jdapistd.o\
	$(RBC)jdmarker.o\
	$(RBC)jfdctfst.o\
	$(RBC)jmemmgr.o\
	\
	$(RBC)cl_cgame.o\
	$(RBC)cm_test.o\
	$(RBC)snd_wavelet.o\
	$(RBC)tr_cmds.o\
	$(RBC)tr_rtt.o\
	$(RBC)cl_cin.o\
	$(RBC)cm_trace.o\
	$(RBC)sv_bot.o\
	$(RBC)tr_curve.o\
	$(RBC)tr_scene.o\
	$(RBC)cl_console.o\
	$(RBC)common.o\
	$(RBC)sv_ccmds.o\
	$(RBC)tr_extentions.o\
	$(RBC)tr_shade.o\
	$(RBC)cl_input.o\
	$(RBC)cvar.o\
	$(RBC)sv_client.o\
	$(RBC)tr_flares.o\
	$(RBC)tr_shade_calc.o\
	$(RBC)cl_keys.o\
	$(RBC)files.o\
	$(RBC)sv_game.o\
	$(RBC)tr_font.o\
	$(RBC)tr_shader.o\
	$(RBC)cl_main.o\
	$(RBC)huffman.o\
	$(RBC)sv_init.o\
	$(RBC)tr_glshader.o\
	$(RBC)tr_shadows.o\
	$(RBC)cl_net_chan.o\
	$(RBC)md4.o\
	$(RBC)sv_main.o\
	$(RBC)tr_image.o\
	$(RBC)tr_sky.o\
	$(RBC)cl_parse.o\
	$(RBC)msg.o\
	$(RBC)sv_net_chan.o\
	$(RBC)tr_init.o\
	$(RBC)tr_surface.o\
	$(RBC)cl_scrn.o\
	$(RBC)net_chan.o\
	$(RBC)tr_light.o\
	$(RBC)tr_texgen.o\
	$(RBC)cl_ui.o\
	$(RBC)python.o\
	$(RBC)sv_snapshot.o\
	$(RBC)tr_main.o\
	$(RBC)tr_world.o\
	$(RBC)cmd.o\
	$(RBC)snd_adpcm.o\
	$(RBC)sv_world.o\
	$(RBC)tr_marks.o\
	$(RBC)unzip.o\
	$(RBC)cm_load.o\
	$(RBC)snd_dma.o\
	$(RBC)tr_animation.o\
	$(RBC)tr_mesh.o\
	$(RBC)cm_patch.o\
	$(RBC)snd_mem.o\
	$(RBC)tr_backend.o\
	$(RBC)tr_model.o\
	$(RBC)cm_polylib.o\
	$(RBC)snd_mix.o\
	$(RBC)tr_bsp.o\
	$(RBC)tr_noise.o\
	$(RBC)tr_qgl.o\
	\
	$(RBC)ai_chat.o\
	$(RBC)ai_vcmd.o\
	$(RBC)g_active.o\
	$(RBC)g_items.o\
	$(RBC)g_trigger.o\
	$(RBC)ai_cmd.o\
	$(RBC)bg_default.o\
	$(RBC)g_arenas.o\
	$(RBC)g_main.o\
	$(RBC)g_session.o\
	$(RBC)g_utils.o\
	$(RBC)ai_dmnet.o\
	$(RBC)bg_lib.o\
	$(RBC)g_bot.o\
	$(RBC)g_mem.o\
	$(RBC)g_spawn.o\
	$(RBC)g_weapon.o\
	$(RBC)ai_dmq3.o\
	$(RBC)bg_misc.o\
	$(RBC)g_client.o\
	$(RBC)g_misc.o\
	$(RBC)g_svcmds.o\
	$(RBC)q_math.o\
	$(RBC)ai_main.o\
	$(RBC)bg_pmove.o\
	$(RBC)g_cmds.o\
	$(RBC)g_missile.o\
	$(RBC)g_target.o\
	$(RBC)q_shared.o\
	$(RBC)ai_team.o\
	$(RBC)bg_slidemove.o\
	$(RBC)g_combat.o\
	$(RBC)g_mover.o\
	$(RBC)g_team.o\
	\
	$(RBC)cg_consolecmds.o\
	$(RBC)cg_event.o\
	$(RBC)cg_particles.o\
	$(RBC)cg_servercmds.o\
	$(RBC)cg_draw.o\
	$(RBC)cg_info.o\
	$(RBC)cg_players.o\
	$(RBC)cg_snapshot.o\
	$(RBC)cg_drawtools.o\
	$(RBC)cg_localents.o\
	$(RBC)cg_playerstate.o\
	$(RBC)cg_view.o\
	$(RBC)cg_effects.o\
	$(RBC)cg_main.o\
	$(RBC)cg_predict.o\
	$(RBC)cg_weapons.o\
	$(RBC)cg_ents.o\
	$(RBC)cg_marks.o\
	$(RBC)cg_scoreboard.o\
	\
	$(RBC)ui_addbots.o\
	$(RBC)ui_specifyserver.o\
	$(RBC)ui_atoms.o\
	$(RBC)ui_main.o\
	$(RBC)ui_splevel.o\
	$(RBC)ui_cinematics.o\
	$(RBC)ui_menu.o\
	$(RBC)ui_removebots.o\
	$(RBC)ui_sppostgame.o\
	$(RBC)ui_confirm.o\
	$(RBC)ui_mfield.o\
	$(RBC)ui_saveconfig.o\
	$(RBC)ui_spreset.o\
	$(RBC)ui_connect.o\
	$(RBC)ui_mods.o\
	$(RBC)ui_serverinfo.o\
	$(RBC)ui_spskill.o\
	$(RBC)ui_controls2.o\
	$(RBC)ui_network.o\
	$(RBC)ui_servers2.o\
	$(RBC)ui_startserver.o\
	$(RBC)ui_credits.o\
	$(RBC)ui_options.o\
	$(RBC)ui_setup.o\
	$(RBC)ui_team.o\
	$(RBC)ui_demo2.o\
	$(RBC)ui_playermodel.o\
	$(RBC)ui_shared.o\
	$(RBC)ui_teamorders.o\
	$(RBC)ui_display.o\
	$(RBC)ui_players.o\
	$(RBC)ui_video.o\
	$(RBC)ui_gameinfo.o\
	$(RBC)ui_playersettings.o\
	$(RBC)ui_sound.o\
	$(RBC)ui_ingame.o\
	$(RBC)ui_preferences.o\
	$(RBC)ui_sparena.o\
	$(RBC)ui_loadconfig.o\
	$(RBC)ui_qmenu.o\
	\
	$(RBC)be_aas_bspq3.o\
	$(RBC)be_aas_move.o\
	$(RBC)be_ai_char.o\
	$(RBC)be_ai_weight.o\
	$(RBC)l_memory.o\
	$(RBC)be_aas_cluster.o\
	$(RBC)be_aas_optimize.o\
	$(RBC)be_ai_chat.o\
	$(RBC)be_ea.o\
	$(RBC)l_precomp.o\
	$(RBC)be_aas_debug.o\
	$(RBC)be_aas_reach.o\
	$(RBC)be_ai_gen.o\
	$(RBC)be_interface.o\
	$(RBC)l_script.o\
	$(RBC)be_aas_entity.o\
	$(RBC)be_aas_routealt.o\
	$(RBC)be_ai_goal.o\
	$(RBC)l_crc.o\
	$(RBC)l_struct.o\
	$(RBC)be_aas_file.o\
	$(RBC)be_aas_route.o\
	$(RBC)be_ai_move.o\
	$(RBC)l_libvar.o\
	$(RBC)be_aas_main.o\
	$(RBC)be_aas_sample.o\
	$(RBC)be_ai_weap.o\
	$(RBC)l_log.o

ifeq ($(PLATFORM),mingw32)
	RECOILOBJS += \
		$(RBC)win_gamma.o \
		$(RBC)win_glimp.o \
		$(RBC)win_input.o \
		$(RBC)win_main.o \
		$(RBC)win_net.o \
		$(RBC)win_shared.o \
		$(RBC)win_snd.o \
		$(RBC)win_syscon.o \
		$(RBC)win_wndproc.o \
		$(RBC)win_resource.o
else
	RECOILOBJS += \
		$(RBC)unix_main.o \
		$(RBC)unix_net.o \
		$(RBC)unix_shared.o \
		$(RBC)linux_signals.o \
		$(RBC)linux_snd.o \
		$(RBC)linux_common.o

	ifeq ($(PLATFORM),linux)
		RECOILOBJS += $(RBC)linux_joystick.o
	endif

	RECOILOBJS_SP = \
		$(RBC)linux_glimp.o
	
	RECOILOBJS_SMP = \
		$(RBC)linux_glimp_smp.o
endif

$(BN)recoil.$(ARCH)$(BINEXT): $(RECOILOBJS) $(RECOILOBJS_SP)
	$(CC) -o $@ $(RECOILOBJS) $(RECOILOBJS_SP) $(CLIENT_LDFLAGS) $(LDFLAGS)

$(BN)recoil-smp.$(ARCH)$(BINEXT): $(RECOILOBJS) $(RECOILOBJS_SMP)
	$(CC) -o $@ $(RECOILOBJS) $(RECOILOBJS_SMP) $(CLIENT_LDFLAGS) $(THREAD_LDFLAGS) $(LDFLAGS)

$(RBC)jcapimin.o: $(SO)engine/jpeg-6/jcapimin.c; $(DO_CC)
$(RBC)jcmaster.o: $(SO)engine/jpeg-6/jcmaster.c; $(DO_CC)
$(RBC)jdatadst.o: $(SO)engine/jpeg-6/jdatadst.c; $(DO_CC)
$(RBC)jdmaster.o: $(SO)engine/jpeg-6/jdmaster.c; $(DO_CC)
$(RBC)jfdctint.o: $(SO)engine/jpeg-6/jfdctint.c; $(DO_CC)
$(RBC)jmemname.o: $(SO)engine/jpeg-6/jmemname.c; $(DO_CC)
$(RBC)jcapistd.o: $(SO)engine/jpeg-6/jcapistd.c; $(DO_CC)
$(RBC)jcomapi.o: $(SO)engine/jpeg-6/jcomapi.c; $(DO_CC)
$(RBC)jdatasrc.o: $(SO)engine/jpeg-6/jdatasrc.c; $(DO_CC)
$(RBC)jdmerge.o: $(SO)engine/jpeg-6/jdmerge.c; $(DO_CC)
$(RBC)jidctflt.o: $(SO)engine/jpeg-6/jidctflt.c; $(DO_CC)
$(RBC)jmemnobs.o: $(SO)engine/jpeg-6/jmemnobs.c; $(DO_GL_CC)
$(RBC)jccoefct.o: $(SO)engine/jpeg-6/jccoefct.c; $(DO_CC)
$(RBC)jcparam.o: $(SO)engine/jpeg-6/jcparam.c; $(DO_CC)
$(RBC)jdcoefct.o: $(SO)engine/jpeg-6/jdcoefct.c; $(DO_CC)
$(RBC)jdphuff.o: $(SO)engine/jpeg-6/jdphuff.c; $(DO_CC)
$(RBC)jidctfst.o: $(SO)engine/jpeg-6/jidctfst.c; $(DO_CC)
$(RBC)jccolor.o: $(SO)engine/jpeg-6/jccolor.c; $(DO_CC)
$(RBC)jcphuff.o: $(SO)engine/jpeg-6/jcphuff.c; $(DO_CC)
$(RBC)jdcolor.o: $(SO)engine/jpeg-6/jdcolor.c; $(DO_CC)
$(RBC)jdpostct.o: $(SO)engine/jpeg-6/jdpostct.c; $(DO_CC)
$(RBC)jidctint.o: $(SO)engine/jpeg-6/jidctint.c; $(DO_CC)
$(RBC)jquant1.o: $(SO)engine/jpeg-6/jquant1.c; $(DO_CC)
$(RBC)jcdctmgr.o: $(SO)engine/jpeg-6/jcdctmgr.c; $(DO_CC)
$(RBC)jcprepct.o: $(SO)engine/jpeg-6/jcprepct.c; $(DO_CC)
$(RBC)jddctmgr.o: $(SO)engine/jpeg-6/jddctmgr.c; $(DO_CC)
$(RBC)jdsample.o: $(SO)engine/jpeg-6/jdsample.c; $(DO_CC)
$(RBC)jidctred.o: $(SO)engine/jpeg-6/jidctred.c; $(DO_CC)
$(RBC)jquant2.o: $(SO)engine/jpeg-6/jquant2.c; $(DO_CC)
$(RBC)jchuff.o: $(SO)engine/jpeg-6/jchuff.c; $(DO_CC)
$(RBC)jcsample.o: $(SO)engine/jpeg-6/jcsample.c; $(DO_CC)
$(RBC)jdhuff.o: $(SO)engine/jpeg-6/jdhuff.c; $(DO_CC)
$(RBC)jdtrans.o: $(SO)engine/jpeg-6/jdtrans.c; $(DO_CC)
$(RBC)jutils.o: $(SO)engine/jpeg-6/jutils.c; $(DO_CC)
$(RBC)jcinit.o: $(SO)engine/jpeg-6/jcinit.c; $(DO_CC)
$(RBC)jctrans.o: $(SO)engine/jpeg-6/jctrans.c; $(DO_CC)
$(RBC)jdinput.o: $(SO)engine/jpeg-6/jdinput.c; $(DO_CC)
$(RBC)jerror.o: $(SO)engine/jpeg-6/jerror.c; $(DO_GL_CC) 
$(RBC)jmemansi.o: $(SO)engine/jpeg-6/jmemansi.c; $(DO_CC)
$(RBC)jcmainct.o: $(SO)engine/jpeg-6/jcmainct.c; $(DO_CC)
$(RBC)jdapimin.o: $(SO)engine/jpeg-6/jdapimin.c; $(DO_CC)
$(RBC)jdmainct.o: $(SO)engine/jpeg-6/jdmainct.c; $(DO_CC)
$(RBC)jfdctflt.o: $(SO)engine/jpeg-6/jfdctflt.c; $(DO_CC)
$(RBC)jmemdos.o: $(SO)engine/jpeg-6/jmemdos.c; $(DO_CC)
$(RBC)jcmarker.o: $(SO)engine/jpeg-6/jcmarker.c; $(DO_CC)
$(RBC)jdapistd.o: $(SO)engine/jpeg-6/jdapistd.c; $(DO_CC)
$(RBC)jdmarker.o: $(SO)engine/jpeg-6/jdmarker.c; $(DO_CC)
$(RBC)jfdctfst.o: $(SO)engine/jpeg-6/jfdctfst.c; $(DO_CC)
$(RBC)jmemmgr.o: $(SO)engine/jpeg-6/jmemmgr.c; $(DO_CC)

$(RBC)linux_common.o: $(SO)engine/unix/linux_common.c; $(DO_CC)
$(RBC)linux_joystick.o: $(SO)engine/unix/linux_joystick.c; $(DO_CC)
$(RBC)linux_signals.o: $(SO)engine/unix/linux_signals.c; $(DO_CC)
$(RBC)unix_main.o: $(SO)engine/unix/unix_main.c; $(DO_CC)
$(RBC)unix_shared.o: $(SO)engine/unix/unix_shared.c; $(DO_CC)
$(RBC)linux_glimp.o: $(SO)engine/unix/linux_glimp.c; $(DO_CC)
$(RBC)linux_snd.o: $(SO)engine/unix/linux_snd.c; $(DO_CC)
$(RBC)unix_net.o: $(SO)engine/unix/unix_net.c; $(DO_CC)

$(RBC)win_gamma.o: $(SO)engine/win32/win_gamma.c; $(DO_CC)
$(RBC)win_input.o: $(SO)engine/win32/win_input.c ; $(DO_CC)
$(RBC)win_net.o: $(SO)engine/win32/win_net.c; $(DO_CC)
$(RBC)win_shared.o: $(SO)engine/win32/win_shared.c; $(DO_CC)
$(RBC)win_syscon.o: $(SO)engine/win32/win_syscon.c; $(DO_CC)
$(RBC)win_glimp.o: $(SO)engine/win32/win_glimp.c; $(DO_CC)
$(RBC)win_main.o: $(SO)engine/win32/win_main.c; $(DO_CC)
$(RBC)win_snd.o: $(SO)engine/win32/win_snd.c; $(DO_CC)
$(RBC)win_wndproc.o: $(SO)engine/win32/win_wndproc.c; $(DO_CC)
$(RBC)win_resource.o: $(SO)engine/win32/winquake.rc; $(DO_WINDRES)

$(RBC)tr_qgl.o: $(SO)engine/tr_qgl.c; $(DO_CC) $(GL_CFLAGS)
$(RBC)cl_cgame.o: $(SO)engine/cl_cgame.c; $(DO_CC)
$(RBC)cm_test.o: $(SO)engine/cm_test.c; $(DO_CC)
$(RBC)snd_wavelet.o: $(SO)engine/snd_wavelet.c; $(DO_CC)
$(RBC)tr_cmds.o: $(SO)engine/tr_cmds.c; $(DO_GL_CC)
$(RBC)tr_rtt.o: $(SO)engine/tr_rtt.c; $(DO_GL_CC)
$(RBC)cl_cin.o: $(SO)engine/cl_cin.c; $(DO_CC)
$(RBC)cm_trace.o: $(SO)engine/cm_trace.c; $(DO_CC)
$(RBC)sv_bot.o: $(SO)engine/sv_bot.c; $(DO_CC)
$(RBC)tr_curve.o: $(SO)engine/tr_curve.c; $(DO_GL_CC)
$(RBC)tr_scene.o: $(SO)engine/tr_scene.c; $(DO_GL_CC)
$(RBC)cl_console.o: $(SO)engine/cl_console.c; $(DO_CC)
$(RBC)common.o: $(SO)engine/common.c; $(DO_CC)
$(RBC)sv_ccmds.o: $(SO)engine/sv_ccmds.c; $(DO_CC)
$(RBC)tr_extentions.o: $(SO)engine/tr_extentions.c; $(DO_GL_CC)
$(RBC)tr_shade.o: $(SO)engine/tr_shade.c; $(DO_GL_CC)
$(RBC)cl_input.o: $(SO)engine/cl_input.c; $(DO_CC)
$(RBC)cvar.o: $(SO)engine/cvar.c; $(DO_CC)
$(RBC)sv_client.o: $(SO)engine/sv_client.c; $(DO_CC)
$(RBC)tr_flares.o: $(SO)engine/tr_flares.c; $(DO_GL_CC)
$(RBC)tr_shade_calc.o: $(SO)engine/tr_shade_calc.c; $(DO_GL_CC)
$(RBC)cl_keys.o: $(SO)engine/cl_keys.c; $(DO_CC)
$(RBC)files.o: $(SO)engine/files.c; $(DO_CC)
$(RBC)sv_game.o: $(SO)engine/sv_game.c; $(DO_CC)
$(RBC)tr_font.o: $(SO)engine/tr_font.c; $(DO_GL_CC)
$(RBC)tr_shader.o: $(SO)engine/tr_shader.c; $(DO_GL_CC)
$(RBC)cl_main.o: $(SO)engine/cl_main.c; $(DO_CC)
$(RBC)huffman.o: $(SO)engine/huffman.c; $(DO_CC)
$(RBC)sv_init.o: $(SO)engine/sv_init.c; $(DO_CC)
$(RBC)tr_glshader.o: $(SO)engine/tr_glshader.c; $(DO_CC)
$(RBC)tr_shadows.o: $(SO)engine/tr_shadows.c; $(DO_CC)
$(RBC)cl_net_chan.o: $(SO)engine/cl_net_chan.c; $(DO_CC)
$(RBC)md4.o: $(SO)engine/md4.c; $(DO_CC)
$(RBC)sv_main.o: $(SO)engine/sv_main.c; $(DO_CC)
$(RBC)tr_image.o: $(SO)engine/tr_image.c; $(DO_GL_CC)
$(RBC)tr_sky.o: $(SO)engine/tr_sky.c; $(DO_GL_CC)
$(RBC)cl_parse.o: $(SO)engine/cl_parse.c; $(DO_CC)
$(RBC)msg.o: $(SO)engine/msg.c; $(DO_CC)
$(RBC)sv_net_chan.o: $(SO)engine/sv_net_chan.c; $(DO_CC)
$(RBC)tr_init.o: $(SO)engine/tr_init.c; $(DO_GL_CC)
$(RBC)tr_surface.o: $(SO)engine/tr_surface.c; $(DO_GL_CC)
$(RBC)cl_scrn.o: $(SO)engine/cl_scrn.c; $(DO_CC)
$(RBC)net_chan.o: $(SO)engine/net_chan.c; $(DO_CC)
$(RBC)sv_rankings.o: $(SO)engine/sv_rankings.c; $(DO_CC)
$(RBC)tr_light.o: $(SO)engine/tr_light.c; $(DO_GL_CC)
$(RBC)tr_texgen.o: $(SO)engine/tr_texgen.c; $(DO_TGD_CC)
$(RBC)cl_ui.o: $(SO)engine/cl_ui.c; $(DO_CC)
$(RBC)python.o: $(SO)engine/python.c; $(DO_CC)
$(RBC)sv_snapshot.o: $(SO)engine/sv_snapshot.c; $(DO_CC)
$(RBC)tr_main.o: $(SO)engine/tr_main.c; $(DO_GL_CC)
$(RBC)tr_world.o: $(SO)engine/tr_world.c; $(DO_GL_CC)
$(RBC)cmd.o: $(SO)engine/cmd.c; $(DO_CC)
$(RBC)snd_adpcm.o: $(SO)engine/snd_adpcm.c; $(DO_CC)
$(RBC)sv_world.o: $(SO)engine/sv_world.c; $(DO_CC)
$(RBC)tr_marks.o: $(SO)engine/tr_marks.c; $(DO_GL_CC)
$(RBC)unzip.o: $(SO)engine/unzip.c; $(DO_CC)
$(RBC)cm_load.o: $(SO)engine/cm_load.c; $(DO_CC)
$(RBC)snd_dma.o: $(SO)engine/snd_dma.c; $(DO_CC)
$(RBC)tr_animation.o: $(SO)engine/tr_animation.c; $(DO_GL_CC)
$(RBC)tr_mesh.o: $(SO)engine/tr_mesh.c; $(DO_GL_CC)
$(RBC)cm_patch.o: $(SO)engine/cm_patch.c; $(DO_CC)
$(RBC)snd_mem.o: $(SO)engine/snd_mem.c; $(DO_CC)
$(RBC)tr_backend.o: $(SO)engine/tr_backend.c; $(DO_GL_CC)
$(RBC)tr_model.o: $(SO)engine/tr_model.c; $(DO_GL_CC)
$(RBC)cm_polylib.o: $(SO)engine/cm_polylib.c; $(DO_CC)
$(RBC)snd_mix.o: $(SO)engine/snd_mix.c; $(DO_CC)
$(RBC)tr_bsp.o: $(SO)engine/tr_bsp.c; $(DO_GL_CC)
$(RBC)tr_noise.o: $(SO)engine/tr_noise.c; $(DO_GL_CC)

$(RBC)ai_chat.o: $(SO)game/ai_chat.c; $(DO_CC)
$(RBC)ai_vcmd.o: $(SO)game/ai_vcmd.c; $(DO_CC)
$(RBC)g_active.o: $(SO)game/g_active.c; $(DO_CC)
$(RBC)g_items.o: $(SO)game/g_items.c; $(DO_CC)
$(RBC)g_trigger.o: $(SO)game/g_trigger.c; $(DO_CC)
$(RBC)ai_cmd.o: $(SO)game/ai_cmd.c; $(DO_CC)
$(RBC)bg_default.o: $(SO)game/bg_default.c; $(DO_CC)
$(RBC)g_arenas.o: $(SO)game/g_arenas.c; $(DO_CC)
$(RBC)g_main.o: $(SO)game/g_main.c; $(DO_CC)
$(RBC)g_session.o: $(SO)game/g_session.c; $(DO_CC)
$(RBC)g_utils.o: $(SO)game/g_utils.c; $(DO_CC)
$(RBC)ai_dmnet.o: $(SO)game/ai_dmnet.c; $(DO_CC)
$(RBC)bg_lib.o: $(SO)game/bg_lib.c; $(DO_CC)
$(RBC)g_bot.o: $(SO)game/g_bot.c; $(DO_CC)
$(RBC)g_mem.o: $(SO)game/g_mem.c; $(DO_CC)
$(RBC)g_spawn.o: $(SO)game/g_spawn.c; $(DO_CC)
$(RBC)g_weapon.o: $(SO)game/g_weapon.c; $(DO_CC)
$(RBC)ai_dmq3.o: $(SO)game/ai_dmq3.c; $(DO_CC)
$(RBC)bg_misc.o: $(SO)game/bg_misc.c; $(DO_CC)
$(RBC)g_client.o: $(SO)game/g_client.c; $(DO_CC)
$(RBC)g_misc.o: $(SO)game/g_misc.c; $(DO_CC)
$(RBC)g_svcmds.o: $(SO)game/g_svcmds.c; $(DO_CC)
$(RBC)q_math.o: $(SO)game/q_math.c; $(DO_CC)
$(RBC)ai_main.o: $(SO)game/ai_main.c; $(DO_CC)
$(RBC)bg_pmove.o: $(SO)game/bg_pmove.c; $(DO_CC)
$(RBC)g_cmds.o: $(SO)game/g_cmds.c; $(DO_CC)
$(RBC)g_missile.o: $(SO)game/g_missile.c; $(DO_CC)
$(RBC)g_target.o: $(SO)game/g_target.c; $(DO_CC)
$(RBC)q_shared.o: $(SO)game/q_shared.c; $(DO_CC)
$(RBC)ai_team.o: $(SO)game/ai_team.c; $(DO_CC)
$(RBC)bg_slidemove.o: $(SO)game/bg_slidemove.c; $(DO_CC)
$(RBC)g_combat.o: $(SO)game/g_combat.c; $(DO_CC)
$(RBC)g_mover.o: $(SO)game/g_mover.c; $(DO_CC)
$(RBC)g_team.o: $(SO)game/g_team.c; $(DO_CC)

$(RBC)cg_consolecmds.o: $(SO)cgame/cg_consolecmds.c; $(DO_CC)
$(RBC)cg_event.o: $(SO)cgame/cg_event.c; $(DO_CC)
$(RBC)cg_particles.o: $(SO)cgame/cg_particles.c; $(DO_CC)
$(RBC)cg_servercmds.o: $(SO)cgame/cg_servercmds.c; $(DO_CC)
$(RBC)cg_draw.o: $(SO)cgame/cg_draw.c; $(DO_CC)
$(RBC)cg_info.o: $(SO)cgame/cg_info.c; $(DO_CC)
$(RBC)cg_players.o: $(SO)cgame/cg_players.c; $(DO_CC)
$(RBC)cg_snapshot.o: $(SO)cgame/cg_snapshot.c; $(DO_CC)
$(RBC)cg_drawtools.o: $(SO)cgame/cg_drawtools.c; $(DO_CC)
$(RBC)cg_localents.o: $(SO)cgame/cg_localents.c; $(DO_CC)
$(RBC)cg_playerstate.o: $(SO)cgame/cg_playerstate.c; $(DO_CC)
$(RBC)cg_view.o: $(SO)cgame/cg_view.c; $(DO_CC)
$(RBC)cg_effects.o: $(SO)cgame/cg_effects.c; $(DO_CC)
$(RBC)cg_main.o: $(SO)cgame/cg_main.c; $(DO_CC)
$(RBC)cg_predict.o: $(SO)cgame/cg_predict.c; $(DO_CC)
$(RBC)cg_weapons.o: $(SO)cgame/cg_weapons.c; $(DO_CC)
$(RBC)cg_ents.o: $(SO)cgame/cg_ents.c; $(DO_CC)
$(RBC)cg_marks.o: $(SO)cgame/cg_marks.c; $(DO_CC)
$(RBC)cg_scoreboard.o: $(SO)cgame/cg_scoreboard.c; $(DO_CC)

$(RBC)ui_addbots.o: $(SO)ui/ui_addbots.c; $(DO_CC)
$(RBC)ui_login.o: $(SO)ui/ui_login.c; $(DO_CC)
$(RBC)ui_rankings.o: $(SO)ui/ui_rankings.c; $(DO_CC)
$(RBC)ui_specifyserver.o: $(SO)ui/ui_specifyserver.c; $(DO_CC)
$(RBC)ui_atoms.o: $(SO)ui/ui_atoms.c; $(DO_CC)
$(RBC)ui_main.o: $(SO)ui/ui_main.c; $(DO_CC)
$(RBC)ui_rankstatus.o: $(SO)ui/ui_rankstatus.c; $(DO_CC)
$(RBC)ui_splevel.o: $(SO)ui/ui_splevel.c; $(DO_CC)
$(RBC)ui_cinematics.o: $(SO)ui/ui_cinematics.c; $(DO_CC)
$(RBC)ui_menu.o: $(SO)ui/ui_menu.c; $(DO_CC)
$(RBC)ui_removebots.o: $(SO)ui/ui_removebots.c; $(DO_CC)
$(RBC)ui_sppostgame.o: $(SO)ui/ui_sppostgame.c; $(DO_CC)
$(RBC)ui_confirm.o: $(SO)ui/ui_confirm.c; $(DO_CC)
$(RBC)ui_mfield.o: $(SO)ui/ui_mfield.c; $(DO_CC)
$(RBC)ui_saveconfig.o: $(SO)ui/ui_saveconfig.c; $(DO_CC)
$(RBC)ui_spreset.o: $(SO)ui/ui_spreset.c; $(DO_CC)
$(RBC)ui_connect.o: $(SO)ui/ui_connect.c; $(DO_CC)
$(RBC)ui_mods.o: $(SO)ui/ui_mods.c; $(DO_CC)
$(RBC)ui_serverinfo.o: $(SO)ui/ui_serverinfo.c; $(DO_CC)
$(RBC)ui_spskill.o: $(SO)ui/ui_spskill.c; $(DO_CC)
$(RBC)ui_controls2.o: $(SO)ui/ui_controls2.c; $(DO_CC)
$(RBC)ui_network.o: $(SO)ui/ui_network.c; $(DO_CC)
$(RBC)ui_servers2.o: $(SO)ui/ui_servers2.c; $(DO_CC)
$(RBC)ui_startserver.o: $(SO)ui/ui_startserver.c; $(DO_CC)
$(RBC)ui_credits.o: $(SO)ui/ui_credits.c; $(DO_CC)
$(RBC)ui_options.o: $(SO)ui/ui_options.c; $(DO_CC)
$(RBC)ui_setup.o: $(SO)ui/ui_setup.c; $(DO_CC)
$(RBC)ui_team.o: $(SO)ui/ui_team.c; $(DO_CC)
$(RBC)ui_demo2.o: $(SO)ui/ui_demo2.c; $(DO_CC)
$(RBC)ui_playermodel.o: $(SO)ui/ui_playermodel.c; $(DO_CC)
$(RBC)ui_shared.o: $(SO)ui/ui_shared.c; $(DO_CC)
$(RBC)ui_teamorders.o: $(SO)ui/ui_teamorders.c; $(DO_CC)
$(RBC)ui_display.o: $(SO)ui/ui_display.c; $(DO_CC)
$(RBC)ui_players.o: $(SO)ui/ui_players.c; $(DO_CC)
$(RBC)ui_signup.o: $(SO)ui/ui_signup.c; $(DO_CC)
$(RBC)ui_video.o: $(SO)ui/ui_video.c; $(DO_CC)
$(RBC)ui_gameinfo.o: $(SO)ui/ui_gameinfo.c; $(DO_CC)
$(RBC)ui_playersettings.o: $(SO)ui/ui_playersettings.c; $(DO_CC)
$(RBC)ui_sound.o: $(SO)ui/ui_sound.c; $(DO_CC)
$(RBC)ui_ingame.o: $(SO)ui/ui_ingame.c; $(DO_CC)
$(RBC)ui_preferences.o: $(SO)ui/ui_preferences.c; $(DO_CC)
$(RBC)ui_sparena.o: $(SO)ui/ui_sparena.c; $(DO_CC)
$(RBC)ui_loadconfig.o: $(SO)ui/ui_loadconfig.c; $(DO_CC)
$(RBC)ui_qmenu.o: $(SO)ui/ui_qmenu.c; $(DO_CC)
$(RBC)ui_specifyleague.o: $(SO)ui/ui_specifyleague.c; $(DO_CC)

$(RBC)be_aas_bspq3.o: $(SO)botlib/be_aas_bspq3.c; $(DO_BOT_CC)
$(RBC)be_aas_move.o: $(SO)botlib/be_aas_move.c; $(DO_BOT_CC)
$(RBC)be_ai_char.o: $(SO)botlib/be_ai_char.c; $(DO_BOT_CC)
$(RBC)be_ai_weight.o: $(SO)botlib/be_ai_weight.c; $(DO_BOT_CC)
$(RBC)l_memory.o: $(SO)botlib/l_memory.c; $(DO_BOT_CC)
$(RBC)be_aas_cluster.o: $(SO)botlib/be_aas_cluster.c; $(DO_BOT_CC)
$(RBC)be_aas_optimize.o: $(SO)botlib/be_aas_optimize.c; $(DO_BOT_CC)
$(RBC)be_ai_chat.o: $(SO)botlib/be_ai_chat.c; $(DO_BOT_CC)
$(RBC)be_ea.o: $(SO)botlib/be_ea.c; $(DO_BOT_CC)
$(RBC)l_precomp.o: $(SO)botlib/l_precomp.c; $(DO_BOT_CC)
$(RBC)be_aas_debug.o: $(SO)botlib/be_aas_debug.c; $(DO_BOT_CC)
$(RBC)be_aas_reach.o: $(SO)botlib/be_aas_reach.c; $(DO_BOT_CC)
$(RBC)be_ai_gen.o: $(SO)botlib/be_ai_gen.c; $(DO_BOT_CC)
$(RBC)be_interface.o: $(SO)botlib/be_interface.c; $(DO_BOT_CC)
$(RBC)l_script.o: $(SO)botlib/l_script.c; $(DO_BOT_CC)
$(RBC)be_aas_entity.o: $(SO)botlib/be_aas_entity.c; $(DO_BOT_CC)
$(RBC)be_aas_routealt.o: $(SO)botlib/be_aas_routealt.c; $(DO_BOT_CC)
$(RBC)be_ai_goal.o: $(SO)botlib/be_ai_goal.c; $(DO_BOT_CC)
$(RBC)l_crc.o: $(SO)botlib/l_crc.c; $(DO_BOT_CC)
$(RBC)l_struct.o: $(SO)botlib/l_struct.c; $(DO_BOT_CC)
$(RBC)be_aas_file.o: $(SO)botlib/be_aas_file.c; $(DO_BOT_CC)
$(RBC)be_aas_route.o: $(SO)botlib/be_aas_route.c; $(DO_BOT_CC)
$(RBC)be_ai_move.o: $(SO)botlib/be_ai_move.c; $(DO_BOT_CC)
$(RBC)l_libvar.o: $(SO)botlib/l_libvar.c; $(DO_BOT_CC)
$(RBC)be_aas_main.o: $(SO)botlib/be_aas_main.c; $(DO_BOT_CC)
$(RBC)be_aas_sample.o: $(SO)botlib/be_aas_sample.c; $(DO_BOT_CC)
$(RBC)be_ai_weap.o: $(SO)botlib/be_ai_weap.c; $(DO_BOT_CC)
$(RBC)l_log.o: $(SO)botlib/l_log.c; $(DO_BOT_CC)

RECOILDOBJS = \
	$(RBD)sv_bot.o \
	$(RBD)sv_client.o \
	$(RBD)sv_ccmds.o \
	$(RBD)sv_game.o \
	$(RBD)sv_init.o \
	$(RBD)sv_main.o \
	$(RBD)sv_net_chan.o \
	$(RBD)sv_snapshot.o \
	$(RBD)sv_world.o \
	\
	$(RBD)ai_chat.o\
	$(RBD)ai_vcmd.o\
	$(RBD)g_active.o\
	$(RBD)g_items.o\
	$(RBD)g_trigger.o\
	$(RBD)ai_cmd.o\
	$(RBD)bg_default.o\
	$(RBD)g_arenas.o\
	$(RBD)g_main.o\
	$(RBD)g_session.o\
	$(RBD)g_utils.o\
	$(RBD)ai_dmnet.o\
	$(RBD)bg_lib.o\
	$(RBD)g_bot.o\
	$(RBD)g_mem.o\
	$(RBD)g_spawn.o\
	$(RBD)g_weapon.o\
	$(RBD)ai_dmq3.o\
	$(RBD)bg_misc.o\
	$(RBD)g_client.o\
	$(RBD)g_misc.o\
	$(RBD)g_svcmds.o\
	$(RBD)ai_main.o\
	$(RBD)bg_pmove.o\
	$(RBD)g_cmds.o\
	$(RBD)g_missile.o\
	$(RBD)g_target.o\
	$(RBD)ai_team.o\
	$(RBD)bg_slidemove.o\
	$(RBD)g_combat.o\
	$(RBD)g_mover.o\
	$(RBD)g_team.o\
	\
	$(RBD)cm_load.o \
	$(RBD)cm_patch.o \
	$(RBD)cm_polylib.o \
	$(RBD)cm_test.o \
	$(RBD)cm_trace.o \
	$(RBD)cmd.o \
	$(RBD)common.o \
	$(RBD)cvar.o \
	$(RBD)files.o \
	$(RBD)md4.o \
	$(RBD)msg.o \
	$(RBD)net_chan.o \
	$(RBD)huffman.o \
	\
	$(RBD)q_math.o \
	$(RBD)q_shared.o \
	\
	$(RBD)unzip.o \
	\
	$(RBD)be_aas_bspq3.o \
	$(RBD)be_aas_cluster.o \
	$(RBD)be_aas_debug.o \
	$(RBD)be_aas_entity.o \
	$(RBD)be_aas_file.o \
	$(RBD)be_aas_main.o \
	$(RBD)be_aas_move.o \
	$(RBD)be_aas_optimize.o \
	$(RBD)be_aas_reach.o \
	$(RBD)be_aas_route.o \
	$(RBD)be_aas_routealt.o \
	$(RBD)be_aas_sample.o \
	$(RBD)be_ai_char.o \
	$(RBD)be_ai_chat.o \
	$(RBD)be_ai_gen.o \
	$(RBD)be_ai_goal.o \
	$(RBD)be_ai_move.o \
	$(RBD)be_ai_weap.o \
	$(RBD)be_ai_weight.o \
	$(RBD)be_ea.o \
	$(RBD)be_interface.o \
	$(RBD)l_crc.o \
	$(RBD)l_libvar.o \
	$(RBD)l_log.o \
	$(RBD)l_memory.o \
	$(RBD)l_precomp.o \
	$(RBD)l_script.o \
	$(RBD)l_struct.o \
	\
        $(RBD)linux_common.o \
	$(RBD)linux_signals.o \
	$(RBD)unix_main.o \
	$(RBD)unix_net.o \
	$(RBD)unix_shared.o \
	\
	$(RBD)null_client.o \
	$(RBD)null_input.o \
	$(RBD)null_snddma.o

$(BN)recoil-ded.$(ARCH)$(BINEXT): $(RECOILDOBJS)
	$(CC) -o $@ $(RECOILDOBJS) $(LDFLAGS)

$(RBD)ai_chat.o: $(SO)game/ai_chat.c; $(DO_DED_CC)
$(RBD)ai_vcmd.o: $(SO)game/ai_vcmd.c; $(DO_DED_CC)
$(RBD)g_active.o: $(SO)game/g_active.c; $(DO_DED_CC)
$(RBD)g_items.o: $(SO)game/g_items.c; $(DO_DED_CC)
$(RBD)g_trigger.o: $(SO)game/g_trigger.c; $(DO_DED_CC)
$(RBD)ai_cmd.o: $(SO)game/ai_cmd.c; $(DO_DED_CC)
$(RBD)bg_default.o: $(SO)game/bg_default.c; $(DO_DED_CC)
$(RBD)g_arenas.o: $(SO)game/g_arenas.c; $(DO_DED_CC)
$(RBD)g_main.o: $(SO)game/g_main.c; $(DO_DED_CC)
$(RBD)g_session.o: $(SO)game/g_session.c; $(DO_DED_CC)
$(RBD)g_utils.o: $(SO)game/g_utils.c; $(DO_DED_CC)
$(RBD)ai_dmnet.o: $(SO)game/ai_dmnet.c; $(DO_DED_CC)
$(RBD)bg_lib.o: $(SO)game/bg_lib.c; $(DO_DED_CC)
$(RBD)g_bot.o: $(SO)game/g_bot.c; $(DO_DED_CC)
$(RBD)g_mem.o: $(SO)game/g_mem.c; $(DO_DED_CC)
$(RBD)g_spawn.o: $(SO)game/g_spawn.c; $(DO_DED_CC)
$(RBD)g_weapon.o: $(SO)game/g_weapon.c; $(DO_DED_CC)
$(RBD)ai_dmq3.o: $(SO)game/ai_dmq3.c; $(DO_DED_CC)
$(RBD)bg_misc.o: $(SO)game/bg_misc.c; $(DO_DED_CC)
$(RBD)g_client.o: $(SO)game/g_client.c; $(DO_DED_CC)
$(RBD)g_misc.o: $(SO)game/g_misc.c; $(DO_DED_CC)
$(RBD)g_svcmds.o: $(SO)game/g_svcmds.c; $(DO_DED_CC)
$(RBD)ai_main.o: $(SO)game/ai_main.c; $(DO_DED_CC)
$(RBD)bg_pmove.o: $(SO)game/bg_pmove.c; $(DO_DED_CC)
$(RBD)g_cmds.o: $(SO)game/g_cmds.c; $(DO_DED_CC)
$(RBD)g_missile.o: $(SO)game/g_missile.c; $(DO_DED_CC)
$(RBD)g_target.o: $(SO)game/g_target.c; $(DO_DED_CC)
$(RBD)ai_team.o: $(SO)game/ai_team.c; $(DO_DED_CC)
$(RBD)bg_slidemove.o: $(SO)game/bg_slidemove.c; $(DO_DED_CC)
$(RBD)g_combat.o: $(SO)game/g_combat.c; $(DO_DED_CC)
$(RBD)g_mover.o: $(SO)game/g_mover.c; $(DO_DED_CC)
$(RBD)g_team.o: $(SO)game/g_team.c; $(DO_DED_CC)

$(RBD)sv_bot.o: $(SO)engine/sv_bot.c; $(DO_DED_CC)
$(RBD)sv_client.o: $(SO)engine/sv_client.c; $(DO_DED_CC)
$(RBD)sv_ccmds.o: $(SO)engine/sv_ccmds.c; $(DO_DED_CC)
$(RBD)sv_game.o: $(SO)engine/sv_game.c; $(DO_DED_CC)
$(RBD)sv_init.o: $(SO)engine/sv_init.c; $(DO_DED_CC)
$(RBD)sv_main.o: $(SO)engine/sv_main.c; $(DO_DED_CC)
$(RBD)sv_net_chan.o: $(SO)engine/sv_net_chan.c; $(DO_DED_CC)
$(RBD)sv_snapshot.o: $(SO)engine/sv_snapshot.c; $(DO_DED_CC)
$(RBD)sv_world.o: $(SO)engine/sv_world.c; $(DO_DED_CC)
\
$(RBD)cm_load.o: $(SO)engine/cm_load.c; $(DO_DED_CC)
$(RBD)cm_patch.o: $(SO)engine/cm_patch.c; $(DO_DED_CC)
$(RBD)cm_polylib.o: $(SO)engine/cm_polylib.c; $(DO_DED_CC)
$(RBD)cm_test.o: $(SO)engine/cm_test.c; $(DO_DED_CC)
$(RBD)cm_trace.o: $(SO)engine/cm_trace.c; $(DO_DED_CC)
$(RBD)cmd.o: $(SO)engine/cmd.c; $(DO_DED_CC)
$(RBD)common.o: $(SO)engine/common.c; $(DO_DED_CC)
$(RBD)cvar.o: $(SO)engine/cvar.c; $(DO_DED_CC)
$(RBD)files.o: $(SO)engine/files.c; $(DO_DED_CC)
$(RBD)md4.o: $(SO)engine/md4.c; $(DO_DED_CC)
$(RBD)msg.o: $(SO)engine/msg.c; $(DO_DED_CC)
$(RBD)net_chan.o: $(SO)engine/net_chan.c; $(DO_DED_CC)
$(RBD)huffman.o: $(SO)engine/huffman.c; $(DO_DED_CC)
\
$(RBD)q_math.o: $(SO)game/q_math.c; $(DO_DED_CC)
$(RBD)q_shared.o: $(SO)game/q_shared.c; $(DO_DED_CC)
\
$(RBD)unzip.o: $(SO)engine/unzip.c; $(DO_DED_CC)
\
$(RBD)be_aas_bspq3.o: $(SO)botlib/be_aas_bspq3.c; $(DO_BOT_CC)
$(RBD)be_aas_cluster.o: $(SO)botlib/be_aas_cluster.c; $(DO_BOT_CC)
$(RBD)be_aas_debug.o: $(SO)botlib/be_aas_debug.c; $(DO_BOT_CC)
$(RBD)be_aas_entity.o: $(SO)botlib/be_aas_entity.c; $(DO_BOT_CC)
$(RBD)be_aas_file.o: $(SO)botlib/be_aas_file.c; $(DO_BOT_CC)
$(RBD)be_aas_main.o: $(SO)botlib/be_aas_main.c; $(DO_BOT_CC)
$(RBD)be_aas_move.o: $(SO)botlib/be_aas_move.c; $(DO_BOT_CC)
$(RBD)be_aas_optimize.o: $(SO)botlib/be_aas_optimize.c; $(DO_BOT_CC)
$(RBD)be_aas_reach.o: $(SO)botlib/be_aas_reach.c; $(DO_BOT_CC)
$(RBD)be_aas_route.o: $(SO)botlib/be_aas_route.c; $(DO_BOT_CC)
$(RBD)be_aas_routealt.o: $(SO)botlib/be_aas_routealt.c; $(DO_BOT_CC)
$(RBD)be_aas_sample.o: $(SO)botlib/be_aas_sample.c; $(DO_BOT_CC)
$(RBD)be_ai_char.o: $(SO)botlib/be_ai_char.c; $(DO_BOT_CC)
$(RBD)be_ai_chat.o: $(SO)botlib/be_ai_chat.c; $(DO_BOT_CC)
$(RBD)be_ai_gen.o: $(SO)botlib/be_ai_gen.c; $(DO_BOT_CC)
$(RBD)be_ai_goal.o: $(SO)botlib/be_ai_goal.c; $(DO_BOT_CC)
$(RBD)be_ai_move.o: $(SO)botlib/be_ai_move.c; $(DO_BOT_CC)
$(RBD)be_ai_weap.o: $(SO)botlib/be_ai_weap.c; $(DO_BOT_CC)
$(RBD)be_ai_weight.o: $(SO)botlib/be_ai_weight.c; $(DO_BOT_CC)
$(RBD)be_ea.o: $(SO)botlib/be_ea.c; $(DO_BOT_CC)
$(RBD)be_interface.o: $(SO)botlib/be_interface.c; $(DO_BOT_CC)
$(RBD)l_crc.o: $(SO)botlib/l_crc.c; $(DO_BOT_CC)
$(RBD)l_libvar.o: $(SO)botlib/l_libvar.c; $(DO_BOT_CC)
$(RBD)l_log.o: $(SO)botlib/l_log.c; $(DO_BOT_CC)
$(RBD)l_memory.o: $(SO)botlib/l_memory.c; $(DO_BOT_CC)
$(RBD)l_precomp.o: $(SO)botlib/l_precomp.c; $(DO_BOT_CC)
$(RBD)l_script.o: $(SO)botlib/l_script.c; $(DO_BOT_CC)
$(RBD)l_struct.o: $(SO)botlib/l_struct.c; $(DO_BOT_CC)
\
$(RBD)linux_common.o: $(SO)engine/unix/linux_common.c; $(DO_DED_CC)
$(RBD)linux_signals.o: $(SO)engine/unix/linux_signals.c; $(DO_DED_CC)
$(RBD)unix_main.o: $(SO)engine/unix/unix_main.c; $(DO_DED_CC)
$(RBD)unix_net.o: $(SO)engine/unix/unix_net.c; $(DO_DED_CC)
$(RBD)unix_shared.o: $(SO)engine/unix/unix_shared.c; $(DO_DED_CC)
\
$(RBD)null_client.o: $(SO)engine/null_client.c; $(DO_DED_CC)
$(RBD)null_input.o: $(SO)engine/null_input.c; $(DO_DED_CC)
$(RBD)null_snddma.o: $(SO)engine/null_snddma.c; $(DO_DED_CC)

TEXGENOBJS=\
	$(TG)filters.o\
	$(TG)generators.o\
	$(TG)generic.o\
	$(TG)main.o\
	$(TG)script.o\
	$(TG)util.o

$(LIBSDIR)libtexgen.$(ARCH)$(SHLIBEXT): $(TEXGENOBJS)
	$(CC) $(SHLIBLDFLAGS) -o $@ $(TEXGENOBJS)

$(TG)filters.o: $(SO)texgen/filters.c; $(DO_SHLIB_CC)
$(TG)generators.o: $(SO)texgen/generators.c; $(DO_SHLIB_CC)
$(TG)generic.o: $(SO)texgen/generic.c; $(DO_SHLIB_CC)
$(TG)main.o: $(SO)texgen/main.c; $(DO_SHLIB_CC)
$(TG)script.o: $(SO)texgen/script.c; $(DO_SHLIB_CC)
$(TG)util.o: $(SO)texgen/util.c; $(DO_SHLIB_CC)

#################################################################
## Clean and other misc
#################################################################

clean: clean-debug clean-release

clean2:
	rm -f $(TEXGENOBJS) $(RECOILDOBJS) $(RECOILOBJS) $(RECOILOBJS_SP) $(RECOILOBJS_SMP)
	rm -f $(TARGETS)

clean-debug:
	$(MAKE) clean2 B=$(BD) CFLAGS="$(DEBUG_CFLAGS)"

clean-release:
	$(MAKE) clean2 B=$(BR) CFLAGS="$(RELEASE_CFLAGS)"