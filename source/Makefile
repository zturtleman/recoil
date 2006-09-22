CFLAGS=-Wall -DBOTLIB
LDFLAGS=-ldl -lm
GLLDFLAGS=-L/usr/X11R6/lib -lX11 -lXext -lXxf86dga -lXxf86vm

DO_CC=$(CC) $(CFLAGS) -o $@ -c $<
DO_WXCXX=$(CXX) $(WXCXXFLAGS) -o $@ -c $<

EF=../bin/

all: engine tools

engine: $(EF)recoil$(ARCH)$(BINEXT)

tools: $(EF)tgEdit$(BINEXT)

clean:
	rm engine/bin/*
	rm texgen/bin/*

## LINUX
LIBEXT=.so

## ========================================================================
## Recoil engine, game, cgame, botlib and ui
##  all into one executable file
## ========================================================================
RB=engine/bin/
RECOILOBJS=\
	$(RB)jcapimin.o\
	$(RB)jcmaster.o\
	$(RB)jdatadst.o\
	$(RB)jdmaster.o\
	$(RB)jfdctint.o\
	$(RB)jcomapi.o\
	$(RB)jdatasrc.o\
	$(RB)jdmerge.o\
	$(RB)jidctflt.o\
	$(RB)jmemnobs.o\
	$(RB)jccoefct.o\
	$(RB)jcparam.o\
	$(RB)jdcoefct.o\
	$(RB)jdphuff.o\
	$(RB)jidctfst.o\
	$(RB)jccolor.o\
	$(RB)jcphuff.o\
	$(RB)jdcolor.o\
	$(RB)jdpostct.o\
	$(RB)jidctint.o\
	$(RB)jquant1.o\
	$(RB)jcdctmgr.o\
	$(RB)jcprepct.o\
	$(RB)jddctmgr.o\
	$(RB)jdsample.o\
	$(RB)jidctred.o\
	$(RB)jquant2.o\
	$(RB)jchuff.o\
	$(RB)jcsample.o\
	$(RB)jdhuff.o\
	$(RB)jdtrans.o\
	$(RB)jutils.o\
	$(RB)jcinit.o\
	$(RB)jctrans.o\
	$(RB)jdinput.o\
	$(RB)jerror.o\
	$(RB)jcmainct.o\
	$(RB)jdapimin.o\
	$(RB)jdmainct.o\
	$(RB)jfdctflt.o\
	$(RB)jcmarker.o\
	$(RB)jdapistd.o\
	$(RB)jdmarker.o\
	$(RB)jfdctfst.o\
	$(RB)jmemmgr.o\
	\
	$(RB)cl_cgame.o\
	$(RB)cm_test.o\
	$(RB)snd_wavelet.o\
	$(RB)tr_cmds.o\
	$(RB)tr_rtt.o\
	$(RB)cl_cin.o\
	$(RB)cm_trace.o\
	$(RB)sv_bot.o\
	$(RB)tr_curve.o\
	$(RB)tr_scene.o\
	$(RB)cl_console.o\
	$(RB)common.o\
	$(RB)sv_ccmds.o\
	$(RB)tr_extentions.o\
	$(RB)tr_shade.o\
	$(RB)cl_input.o\
	$(RB)cvar.o\
	$(RB)sv_client.o\
	$(RB)tr_flares.o\
	$(RB)tr_shade_calc.o\
	$(RB)cl_keys.o\
	$(RB)files.o\
	$(RB)sv_game.o\
	$(RB)tr_font.o\
	$(RB)tr_shader.o\
	$(RB)cl_main.o\
	$(RB)huffman.o\
	$(RB)sv_init.o\
	$(RB)tr_glshader.o\
	$(RB)tr_shadows.o\
	$(RB)cl_net_chan.o\
	$(RB)md4.o\
	$(RB)sv_main.o\
	$(RB)tr_image.o\
	$(RB)tr_sky.o\
	$(RB)cl_parse.o\
	$(RB)msg.o\
	$(RB)sv_net_chan.o\
	$(RB)tr_init.o\
	$(RB)tr_surface.o\
	$(RB)cl_scrn.o\
	$(RB)net_chan.o\
	$(RB)tr_light.o\
	$(RB)tr_texgen.o\
	$(RB)cl_ui.o\
	$(RB)python.o\
	$(RB)sv_snapshot.o\
	$(RB)tr_main.o\
	$(RB)tr_world.o\
	$(RB)cmd.o\
	$(RB)snd_adpcm.o\
	$(RB)sv_world.o\
	$(RB)tr_marks.o\
	$(RB)unzip.o\
	$(RB)cm_load.o\
	$(RB)snd_dma.o\
	$(RB)tr_animation.o\
	$(RB)tr_mesh.o\
	$(RB)cm_patch.o\
	$(RB)snd_mem.o\
	$(RB)tr_backend.o\
	$(RB)tr_model.o\
	$(RB)cm_polylib.o\
	$(RB)snd_mix.o\
	$(RB)tr_bsp.o\
	$(RB)tr_noise.o\
	$(RB)linux_common.o\
	$(RB)linux_joystick.o\
	$(RB)linux_signals.o\
	$(RB)unix_main.o\
	$(RB)unix_shared.o\
	$(RB)linux_glimp.o\
	$(RB)tr_qgl.o\
	$(RB)linux_snd.o\
	$(RB)unix_net.o\
	$(RB)ai_chat.o\
	$(RB)ai_vcmd.o\
	$(RB)g_active.o\
	$(RB)g_items.o\
	$(RB)g_trigger.o\
	$(RB)ai_cmd.o\
	$(RB)bg_default.o\
	$(RB)g_arenas.o\
	$(RB)g_main.o\
	$(RB)g_session.o\
	$(RB)g_utils.o\
	$(RB)ai_dmnet.o\
	$(RB)bg_lib.o\
	$(RB)g_bot.o\
	$(RB)g_mem.o\
	$(RB)g_spawn.o\
	$(RB)g_weapon.o\
	$(RB)ai_dmq3.o\
	$(RB)bg_misc.o\
	$(RB)g_client.o\
	$(RB)g_misc.o\
	$(RB)g_svcmds.o\
	$(RB)q_math.o\
	$(RB)ai_main.o\
	$(RB)bg_pmove.o\
	$(RB)g_cmds.o\
	$(RB)g_missile.o\
	$(RB)g_target.o\
	$(RB)q_shared.o\
	$(RB)ai_team.o\
	$(RB)bg_slidemove.o\
	$(RB)g_combat.o\
	$(RB)g_mover.o\
	$(RB)g_team.o\
	\
	$(RB)cg_consolecmds.o\
	$(RB)cg_event.o\
	$(RB)cg_particles.o\
	$(RB)cg_servercmds.o\
	$(RB)cg_draw.o\
	$(RB)cg_info.o\
	$(RB)cg_players.o\
	$(RB)cg_snapshot.o\
	$(RB)cg_drawtools.o\
	$(RB)cg_localents.o\
	$(RB)cg_playerstate.o\
	$(RB)cg_view.o\
	$(RB)cg_effects.o\
	$(RB)cg_main.o\
	$(RB)cg_predict.o\
	$(RB)cg_weapons.o\
	$(RB)cg_ents.o\
	$(RB)cg_marks.o\
	$(RB)cg_scoreboard.o\
	\
	$(RB)ui_addbots.o\
	$(RB)ui_specifyserver.o\
	$(RB)ui_atoms.o\
	$(RB)ui_main.o\
	$(RB)ui_splevel.o\
	$(RB)ui_cinematics.o\
	$(RB)ui_menu.o\
	$(RB)ui_removebots.o\
	$(RB)ui_sppostgame.o\
	$(RB)ui_confirm.o\
	$(RB)ui_mfield.o\
	$(RB)ui_saveconfig.o\
	$(RB)ui_spreset.o\
	$(RB)ui_connect.o\
	$(RB)ui_mods.o\
	$(RB)ui_serverinfo.o\
	$(RB)ui_spskill.o\
	$(RB)ui_controls2.o\
	$(RB)ui_network.o\
	$(RB)ui_servers2.o\
	$(RB)ui_startserver.o\
	$(RB)ui_credits.o\
	$(RB)ui_options.o\
	$(RB)ui_setup.o\
	$(RB)ui_team.o\
	$(RB)ui_demo2.o\
	$(RB)ui_playermodel.o\
	$(RB)ui_shared.o\
	$(RB)ui_teamorders.o\
	$(RB)ui_display.o\
	$(RB)ui_players.o\
	$(RB)ui_video.o\
	$(RB)ui_gameinfo.o\
	$(RB)ui_playersettings.o\
	$(RB)ui_sound.o\
	$(RB)ui_ingame.o\
	$(RB)ui_preferences.o\
	$(RB)ui_sparena.o\
	$(RB)ui_loadconfig.o\
	$(RB)ui_qmenu.o\
	\
	$(RB)be_aas_bspq3.o\
	$(RB)be_aas_move.o\
	$(RB)be_ai_char.o\
	$(RB)be_ai_weight.o\
	$(RB)l_memory.o\
	$(RB)be_aas_cluster.o\
	$(RB)be_aas_optimize.o\
	$(RB)be_ai_chat.o\
	$(RB)be_ea.o\
	$(RB)l_precomp.o\
	$(RB)be_aas_debug.o\
	$(RB)be_aas_reach.o\
	$(RB)be_ai_gen.o\
	$(RB)be_interface.o\
	$(RB)l_script.o\
	$(RB)be_aas_entity.o\
	$(RB)be_aas_routealt.o\
	$(RB)be_ai_goal.o\
	$(RB)l_crc.o\
	$(RB)l_struct.o\
	$(RB)be_aas_file.o\
	$(RB)be_aas_route.o\
	$(RB)be_ai_move.o\
	$(RB)l_libvar.o\
	$(RB)be_aas_main.o\
	$(RB)be_aas_sample.o\
	$(RB)be_ai_weap.o\
	$(RB)l_log.o

## remember to add windows objects using RECOILOBJECTS += (whatever it needs)
## if i convert to SDL i can use the same files for windows and linux! SDL threads

$(EF)recoil$(ARCH)$(BINEXT): $(RECOILOBJS) /usr/lib/libtexgen$(LIBEXT)
	$(CC) -o $@ $(RECOILOBJS) $(LDFLAGS) $(GLLDFLAGS) -ltexgen

TG=texgen/bin/
TEXGENOBJS=\
	$(TG)filters.o\
	$(TG)generators.o\
	$(TG)generic.o\
	$(TG)main.o\
	$(TG)script.o\
	$(TG)util.o

/usr/lib/libtexgen$(LIBEXT): $(TEXGENOBJS)
	$(CC) -shared -W1,-soname,$@ -o $@ $(TEXGENOBJS)

TE=tgEdit/bin/
TGEDITOROBJS=\
	$(TE)tgEdit.o

$(EF)tgEdit$(BINEXT): $(TGEDITOROBJS) $(EF)texgen$(LIBEXT)
	$(CXX) -o $@ $(TGEDITOROBJS) $(WXLDFLAGS)

$(RB)jcapimin.o: engine/jpeg-6/jcapimin.c; $(DO_CC)
$(RB)jcmaster.o: engine/jpeg-6/jcmaster.c; $(DO_CC)
$(RB)jdatadst.o: engine/jpeg-6/jdatadst.c; $(DO_CC)
$(RB)jdmaster.o: engine/jpeg-6/jdmaster.c; $(DO_CC)
$(RB)jfdctint.o: engine/jpeg-6/jfdctint.c; $(DO_CC)
$(RB)jmemname.o: engine/jpeg-6/jmemname.c; $(DO_CC)
$(RB)jcapistd.o: engine/jpeg-6/jcapistd.c; $(DO_CC)
$(RB)jcomapi.o: engine/jpeg-6/jcomapi.c; $(DO_CC)
$(RB)jdatasrc.o: engine/jpeg-6/jdatasrc.c; $(DO_CC)
$(RB)jdmerge.o: engine/jpeg-6/jdmerge.c; $(DO_CC)
$(RB)jidctflt.o: engine/jpeg-6/jidctflt.c; $(DO_CC)
$(RB)jmemnobs.o: engine/jpeg-6/jmemnobs.c; $(DO_CC)
$(RB)jccoefct.o: engine/jpeg-6/jccoefct.c; $(DO_CC)
$(RB)jcparam.o: engine/jpeg-6/jcparam.c; $(DO_CC)
$(RB)jdcoefct.o: engine/jpeg-6/jdcoefct.c; $(DO_CC)
$(RB)jdphuff.o: engine/jpeg-6/jdphuff.c; $(DO_CC)
$(RB)jidctfst.o: engine/jpeg-6/jidctfst.c; $(DO_CC)
$(RB)jccolor.o: engine/jpeg-6/jccolor.c; $(DO_CC)
$(RB)jcphuff.o: engine/jpeg-6/jcphuff.c; $(DO_CC)
$(RB)jdcolor.o: engine/jpeg-6/jdcolor.c; $(DO_CC)
$(RB)jdpostct.o: engine/jpeg-6/jdpostct.c; $(DO_CC)
$(RB)jidctint.o: engine/jpeg-6/jidctint.c; $(DO_CC)
$(RB)jquant1.o: engine/jpeg-6/jquant1.c; $(DO_CC)
$(RB)jcdctmgr.o: engine/jpeg-6/jcdctmgr.c; $(DO_CC)
$(RB)jcprepct.o: engine/jpeg-6/jcprepct.c; $(DO_CC)
$(RB)jddctmgr.o: engine/jpeg-6/jddctmgr.c; $(DO_CC)
$(RB)jdsample.o: engine/jpeg-6/jdsample.c; $(DO_CC)
$(RB)jidctred.o: engine/jpeg-6/jidctred.c; $(DO_CC)
$(RB)jquant2.o: engine/jpeg-6/jquant2.c; $(DO_CC)
$(RB)jchuff.o: engine/jpeg-6/jchuff.c; $(DO_CC)
$(RB)jcsample.o: engine/jpeg-6/jcsample.c; $(DO_CC)
$(RB)jdhuff.o: engine/jpeg-6/jdhuff.c; $(DO_CC)
$(RB)jdtrans.o: engine/jpeg-6/jdtrans.c; $(DO_CC)
$(RB)jutils.o: engine/jpeg-6/jutils.c; $(DO_CC)
$(RB)jcinit.o: engine/jpeg-6/jcinit.c; $(DO_CC)
$(RB)jctrans.o: engine/jpeg-6/jctrans.c; $(DO_CC)
$(RB)jdinput.o: engine/jpeg-6/jdinput.c; $(DO_CC)
$(RB)jerror.o: engine/jpeg-6/jerror.c; $(DO_CC)
$(RB)jmemansi.o: engine/jpeg-6/jmemansi.c; $(DO_CC)
$(RB)jcmainct.o: engine/jpeg-6/jcmainct.c; $(DO_CC)
$(RB)jdapimin.o: engine/jpeg-6/jdapimin.c; $(DO_CC)
$(RB)jdmainct.o: engine/jpeg-6/jdmainct.c; $(DO_CC)
$(RB)jfdctflt.o: engine/jpeg-6/jfdctflt.c; $(DO_CC)
$(RB)jmemdos.o: engine/jpeg-6/jmemdos.c; $(DO_CC)
$(RB)jcmarker.o: engine/jpeg-6/jcmarker.c; $(DO_CC)
$(RB)jdapistd.o: engine/jpeg-6/jdapistd.c; $(DO_CC)
$(RB)jdmarker.o: engine/jpeg-6/jdmarker.c; $(DO_CC)
$(RB)jfdctfst.o: engine/jpeg-6/jfdctfst.c; $(DO_CC)
$(RB)jmemmgr.o: engine/jpeg-6/jmemmgr.c; $(DO_CC)

$(RB)linux_common.o: engine/unix/linux_common.c; $(DO_CC)
$(RB)linux_joystick.o: engine/unix/linux_joystick.c; $(DO_CC)
$(RB)linux_signals.o: engine/unix/linux_signals.c; $(DO_CC)
$(RB)unix_main.o: engine/unix/unix_main.c; $(DO_CC)
$(RB)unix_shared.o: engine/unix/unix_shared.c; $(DO_CC)
$(RB)linux_glimp.o: engine/unix/linux_glimp.c; $(DO_CC)
$(RB)linux_snd.o: engine/unix/linux_snd.c; $(DO_CC)
$(RB)unix_net.o: engine/unix/unix_net.c; $(DO_CC)

$(RB)win_gamma.o: engine/win32/win_gamma.c; $(DO_CC)
$(RB)win_input.o: engine/win32/win_input.c ; $(DO_CC)
$(RB)win_net.o: engine/win32/win_net.c; $(DO_CC)
$(RB)win_shared.o: engine/win32/win_shared.c; $(DO_CC)
$(RB)win_syscon.o: engine/win32/win_syscon.c; $(DO_CC)
$(RB)win_glimp.o: engine/win32/win_glimp.c; $(DO_CC)
$(RB)win_main.o: engine/win32/win_main.c; $(DO_CC)
$(RB)win_qgl.o: engine/win32/win_qgl.c; $(DO_CC)
$(RB)win_snd.o: engine/win32/win_snd.c; $(DO_CC)
$(RB)win_wndproc.o: engine/win32/win_wndproc.c; $(DO_CC)

$(RB)tr_qgl.o: engine/tr_qgl.c; $(DO_CC)
$(RB)cl_cgame.o: engine/cl_cgame.c; $(DO_CC)
$(RB)cm_test.o: engine/cm_test.c; $(DO_CC)
$(RB)snd_wavelet.o: engine/snd_wavelet.c; $(DO_CC)
$(RB)tr_cmds.o: engine/tr_cmds.c; $(DO_CC)
$(RB)tr_rtt.o: engine/tr_rtt.c; $(DO_CC)
$(RB)cl_cin.o: engine/cl_cin.c; $(DO_CC)
$(RB)cm_trace.o: engine/cm_trace.c; $(DO_CC)
$(RB)sv_bot.o: engine/sv_bot.c; $(DO_CC)
$(RB)tr_curve.o: engine/tr_curve.c; $(DO_CC)
$(RB)tr_scene.o: engine/tr_scene.c; $(DO_CC)
$(RB)cl_console.o: engine/cl_console.c; $(DO_CC)
$(RB)common.o: engine/common.c; $(DO_CC)
$(RB)sv_ccmds.o: engine/sv_ccmds.c; $(DO_CC)
$(RB)tr_extentions.o: engine/tr_extentions.c; $(DO_CC)
$(RB)tr_shade.o: engine/tr_shade.c; $(DO_CC)
$(RB)cl_input.o: engine/cl_input.c; $(DO_CC)
$(RB)cvar.o: engine/cvar.c; $(DO_CC)
$(RB)sv_client.o: engine/sv_client.c; $(DO_CC)
$(RB)tr_flares.o: engine/tr_flares.c; $(DO_CC)
$(RB)tr_shade_calc.o: engine/tr_shade_calc.c; $(DO_CC)
$(RB)cl_keys.o: engine/cl_keys.c; $(DO_CC)
$(RB)files.o: engine/files.c; $(DO_CC)
$(RB)sv_game.o: engine/sv_game.c; $(DO_CC)
$(RB)tr_font.o: engine/tr_font.c; $(DO_CC)
$(RB)tr_shader.o: engine/tr_shader.c; $(DO_CC)
$(RB)cl_main.o: engine/cl_main.c; $(DO_CC)
$(RB)huffman.o: engine/huffman.c; $(DO_CC)
$(RB)sv_init.o: engine/sv_init.c; $(DO_CC)
$(RB)tr_glshader.o: engine/tr_glshader.c; $(DO_CC)
$(RB)tr_shadows.o: engine/tr_shadows.c; $(DO_CC)
$(RB)cl_net_chan.o: engine/cl_net_chan.c; $(DO_CC)
$(RB)md4.o: engine/md4.c; $(DO_CC)
$(RB)sv_main.o: engine/sv_main.c; $(DO_CC)
$(RB)tr_image.o: engine/tr_image.c; $(DO_CC)
$(RB)tr_sky.o: engine/tr_sky.c; $(DO_CC)
$(RB)cl_parse.o: engine/cl_parse.c; $(DO_CC)
$(RB)msg.o: engine/msg.c; $(DO_CC)
$(RB)sv_net_chan.o: engine/sv_net_chan.c; $(DO_CC)
$(RB)tr_init.o: engine/tr_init.c; $(DO_CC)
$(RB)tr_surface.o: engine/tr_surface.c; $(DO_CC)
$(RB)cl_scrn.o: engine/cl_scrn.c; $(DO_CC)
$(RB)net_chan.o: engine/net_chan.c; $(DO_CC)
$(RB)sv_rankings.o: engine/sv_rankings.c; $(DO_CC)
$(RB)tr_light.o: engine/tr_light.c; $(DO_CC)
$(RB)tr_texgen.o: engine/tr_texgen.c; $(DO_CC)
$(RB)cl_ui.o: engine/cl_ui.c; $(DO_CC)
$(RB)python.o: engine/python.c; $(DO_CC)
$(RB)sv_snapshot.o: engine/sv_snapshot.c; $(DO_CC)
$(RB)tr_main.o: engine/tr_main.c; $(DO_CC)
$(RB)tr_world.o: engine/tr_world.c; $(DO_CC)
$(RB)cmd.o: engine/cmd.c; $(DO_CC)
$(RB)snd_adpcm.o: engine/snd_adpcm.c; $(DO_CC)
$(RB)sv_world.o: engine/sv_world.c; $(DO_CC)
$(RB)tr_marks.o: engine/tr_marks.c; $(DO_CC)
$(RB)unzip.o: engine/unzip.c; $(DO_CC)
$(RB)cm_load.o: engine/cm_load.c; $(DO_CC)
$(RB)snd_dma.o: engine/snd_dma.c; $(DO_CC)
$(RB)tr_animation.o: engine/tr_animation.c; $(DO_CC)
$(RB)tr_mesh.o: engine/tr_mesh.c; $(DO_CC)
$(RB)cm_patch.o: engine/cm_patch.c; $(DO_CC)
$(RB)snd_mem.o: engine/snd_mem.c; $(DO_CC)
$(RB)tr_backend.o: engine/tr_backend.c; $(DO_CC)
$(RB)tr_model.o: engine/tr_model.c; $(DO_CC)
$(RB)cm_polylib.o: engine/cm_polylib.c; $(DO_CC)
$(RB)snd_mix.o: engine/snd_mix.c; $(DO_CC)
$(RB)tr_bsp.o: engine/tr_bsp.c; $(DO_CC)
$(RB)tr_noise.o: engine/tr_noise.c; $(DO_CC)

$(RB)ai_chat.o: game/ai_chat.c; $(DO_CC)
$(RB)ai_vcmd.o: game/ai_vcmd.c; $(DO_CC)
$(RB)g_active.o: game/g_active.c; $(DO_CC)
$(RB)g_items.o: game/g_items.c; $(DO_CC)
$(RB)g_trigger.o: game/g_trigger.c; $(DO_CC)
$(RB)ai_cmd.o: game/ai_cmd.c; $(DO_CC)
$(RB)bg_default.o: game/bg_default.c; $(DO_CC)
$(RB)g_arenas.o: game/g_arenas.c; $(DO_CC)
$(RB)g_main.o: game/g_main.c; $(DO_CC)
$(RB)g_session.o: game/g_session.c; $(DO_CC)
$(RB)g_utils.o: game/g_utils.c; $(DO_CC)
$(RB)ai_dmnet.o: game/ai_dmnet.c; $(DO_CC)
$(RB)bg_lib.o: game/bg_lib.c; $(DO_CC)
$(RB)g_bot.o: game/g_bot.c; $(DO_CC)
$(RB)g_mem.o: game/g_mem.c; $(DO_CC)
$(RB)g_spawn.o: game/g_spawn.c; $(DO_CC)
$(RB)g_weapon.o: game/g_weapon.c; $(DO_CC)
$(RB)ai_dmq3.o: game/ai_dmq3.c; $(DO_CC)
$(RB)bg_misc.o: game/bg_misc.c; $(DO_CC)
$(RB)g_client.o: game/g_client.c; $(DO_CC)
$(RB)g_misc.o: game/g_misc.c; $(DO_CC)
$(RB)g_svcmds.o: game/g_svcmds.c; $(DO_CC)
$(RB)q_math.o: game/q_math.c; $(DO_CC)
$(RB)ai_main.o: game/ai_main.c; $(DO_CC)
$(RB)bg_pmove.o: game/bg_pmove.c; $(DO_CC)
$(RB)g_cmds.o: game/g_cmds.c; $(DO_CC)
$(RB)g_missile.o: game/g_missile.c; $(DO_CC)
$(RB)g_target.o: game/g_target.c; $(DO_CC)
$(RB)q_shared.o: game/q_shared.c; $(DO_CC)
$(RB)ai_team.o: game/ai_team.c; $(DO_CC)
$(RB)bg_slidemove.o: game/bg_slidemove.c; $(DO_CC)
$(RB)g_combat.o: game/g_combat.c; $(DO_CC)
$(RB)g_mover.o: game/g_mover.c; $(DO_CC)
$(RB)g_team.o: game/g_team.c; $(DO_CC)

$(RB)cg_consolecmds.o: cgame/cg_consolecmds.c; $(DO_CC)
$(RB)cg_event.o: cgame/cg_event.c; $(DO_CC)
$(RB)cg_particles.o: cgame/cg_particles.c; $(DO_CC)
$(RB)cg_servercmds.o: cgame/cg_servercmds.c; $(DO_CC)
$(RB)cg_draw.o: cgame/cg_draw.c; $(DO_CC)
$(RB)cg_info.o: cgame/cg_info.c; $(DO_CC)
$(RB)cg_players.o: cgame/cg_players.c; $(DO_CC)
$(RB)cg_snapshot.o: cgame/cg_snapshot.c; $(DO_CC)
$(RB)cg_drawtools.o: cgame/cg_drawtools.c; $(DO_CC)
$(RB)cg_localents.o: cgame/cg_localents.c; $(DO_CC)
$(RB)cg_playerstate.o: cgame/cg_playerstate.c; $(DO_CC)
$(RB)cg_view.o: cgame/cg_view.c; $(DO_CC)
$(RB)cg_effects.o: cgame/cg_effects.c; $(DO_CC)
$(RB)cg_main.o: cgame/cg_main.c; $(DO_CC)
$(RB)cg_predict.o: cgame/cg_predict.c; $(DO_CC)
$(RB)cg_weapons.o: cgame/cg_weapons.c; $(DO_CC)
$(RB)cg_ents.o: cgame/cg_ents.c; $(DO_CC)
$(RB)cg_marks.o: cgame/cg_marks.c; $(DO_CC)
$(RB)cg_scoreboard.o: cgame/cg_scoreboard.c; $(DO_CC)

$(RB)ui_addbots.o: ui/ui_addbots.c; $(DO_CC)
$(RB)ui_login.o: ui/ui_login.c; $(DO_CC)
$(RB)ui_rankings.o: ui/ui_rankings.c; $(DO_CC)
$(RB)ui_specifyserver.o: ui/ui_specifyserver.c; $(DO_CC)
$(RB)ui_atoms.o: ui/ui_atoms.c; $(DO_CC)
$(RB)ui_main.o: ui/ui_main.c; $(DO_CC)
$(RB)ui_rankstatus.o: ui/ui_rankstatus.c; $(DO_CC)
$(RB)ui_splevel.o: ui/ui_splevel.c; $(DO_CC)
$(RB)ui_cinematics.o: ui/ui_cinematics.c; $(DO_CC)
$(RB)ui_menu.o: ui/ui_menu.c; $(DO_CC)
$(RB)ui_removebots.o: ui/ui_removebots.c; $(DO_CC)
$(RB)ui_sppostgame.o: ui/ui_sppostgame.c; $(DO_CC)
$(RB)ui_confirm.o: ui/ui_confirm.c; $(DO_CC)
$(RB)ui_mfield.o: ui/ui_mfield.c; $(DO_CC)
$(RB)ui_saveconfig.o: ui/ui_saveconfig.c; $(DO_CC)
$(RB)ui_spreset.o: ui/ui_spreset.c; $(DO_CC)
$(RB)ui_connect.o: ui/ui_connect.c; $(DO_CC)
$(RB)ui_mods.o: ui/ui_mods.c; $(DO_CC)
$(RB)ui_serverinfo.o: ui/ui_serverinfo.c; $(DO_CC)
$(RB)ui_spskill.o: ui/ui_spskill.c; $(DO_CC)
$(RB)ui_controls2.o: ui/ui_controls2.c; $(DO_CC)
$(RB)ui_network.o: ui/ui_network.c; $(DO_CC)
$(RB)ui_servers2.o: ui/ui_servers2.c; $(DO_CC)
$(RB)ui_startserver.o: ui/ui_startserver.c; $(DO_CC)
$(RB)ui_credits.o: ui/ui_credits.c; $(DO_CC)
$(RB)ui_options.o: ui/ui_options.c; $(DO_CC)
$(RB)ui_setup.o: ui/ui_setup.c; $(DO_CC)
$(RB)ui_team.o: ui/ui_team.c; $(DO_CC)
$(RB)ui_demo2.o: ui/ui_demo2.c; $(DO_CC)
$(RB)ui_playermodel.o: ui/ui_playermodel.c; $(DO_CC)
$(RB)ui_shared.o: ui/ui_shared.c; $(DO_CC)
$(RB)ui_teamorders.o: ui/ui_teamorders.c; $(DO_CC)
$(RB)ui_display.o: ui/ui_display.c; $(DO_CC)
$(RB)ui_players.o: ui/ui_players.c; $(DO_CC)
$(RB)ui_signup.o: ui/ui_signup.c; $(DO_CC)
$(RB)ui_video.o: ui/ui_video.c; $(DO_CC)
$(RB)ui_gameinfo.o: ui/ui_gameinfo.c; $(DO_CC)
$(RB)ui_playersettings.o: ui/ui_playersettings.c; $(DO_CC)
$(RB)ui_sound.o: ui/ui_sound.c; $(DO_CC)
$(RB)ui_ingame.o: ui/ui_ingame.c; $(DO_CC)
$(RB)ui_preferences.o: ui/ui_preferences.c; $(DO_CC)
$(RB)ui_sparena.o: ui/ui_sparena.c; $(DO_CC)
$(RB)ui_loadconfig.o: ui/ui_loadconfig.c; $(DO_CC)
$(RB)ui_qmenu.o: ui/ui_qmenu.c; $(DO_CC)
$(RB)ui_specifyleague.o: ui/ui_specifyleague.c; $(DO_CC)

$(RB)be_aas_bspq3.o: botlib/be_aas_bspq3.c; $(DO_CC)
$(RB)be_aas_move.o: botlib/be_aas_move.c; $(DO_CC)
$(RB)be_ai_char.o: botlib/be_ai_char.c; $(DO_CC)
$(RB)be_ai_weight.o: botlib/be_ai_weight.c; $(DO_CC)
$(RB)l_memory.o: botlib/l_memory.c; $(DO_CC)
$(RB)be_aas_cluster.o: botlib/be_aas_cluster.c; $(DO_CC)
$(RB)be_aas_optimize.o: botlib/be_aas_optimize.c; $(DO_CC)
$(RB)be_ai_chat.o: botlib/be_ai_chat.c; $(DO_CC)
$(RB)be_ea.o: botlib/be_ea.c; $(DO_CC)
$(RB)l_precomp.o: botlib/l_precomp.c; $(DO_CC)
$(RB)be_aas_debug.o: botlib/be_aas_debug.c; $(DO_CC)
$(RB)be_aas_reach.o: botlib/be_aas_reach.c; $(DO_CC)
$(RB)be_ai_gen.o: botlib/be_ai_gen.c; $(DO_CC)
$(RB)be_interface.o: botlib/be_interface.c; $(DO_CC)
$(RB)l_script.o: botlib/l_script.c; $(DO_CC)
$(RB)be_aas_entity.o: botlib/be_aas_entity.c; $(DO_CC)
$(RB)be_aas_routealt.o: botlib/be_aas_routealt.c; $(DO_CC)
$(RB)be_ai_goal.o: botlib/be_ai_goal.c; $(DO_CC)
$(RB)l_crc.o: botlib/l_crc.c; $(DO_CC)
$(RB)l_struct.o: botlib/l_struct.c; $(DO_CC)
$(RB)be_aas_file.o: botlib/be_aas_file.c; $(DO_CC)
$(RB)be_aas_route.o: botlib/be_aas_route.c; $(DO_CC)
$(RB)be_ai_move.o: botlib/be_ai_move.c; $(DO_CC)
$(RB)l_libvar.o: botlib/l_libvar.c; $(DO_CC)
$(RB)be_aas_main.o: botlib/be_aas_main.c; $(DO_CC)
$(RB)be_aas_sample.o: botlib/be_aas_sample.c; $(DO_CC)
$(RB)be_ai_weap.o: botlib/be_ai_weap.c; $(DO_CC)
$(RB)l_log.o: botlib/l_log.c; $(DO_CC)

$(TG)filters.o: texgen/filters.c; $(DO_CC) -fPIC
$(TG)generators.o: texgen/generators.c; $(DO_CC) -fPIC
$(TG)generic.o: texgen/generic.c; $(DO_CC) -fPIC
$(TG)main.o: texgen/main.c; $(DO_CC) -fPIC
$(TG)script.o: texgen/script.c; $(DO_CC) -fPIC
$(TG)util.o: texgen/util.c; $(DO_CC) -fPIC