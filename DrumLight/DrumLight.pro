SOURCES += source/main.cpp \
		source/gameflow.cpp \
		source/states/credits_state.cpp \
		source/states/main_menu_state.cpp \
		source/states/options_state.cpp \
		source/states/game/game_pause_state.cpp \
		source/states/game_state.cpp \
		source/data/game_data.cpp \
		source/states/game/game_run_state.cpp \
		source/manager/camera_manager.cpp \
		source/manager/world_manager.cpp \
		source/manager/sound_manager.cpp \
		source/manager/physics_manager.cpp \
		source/scene/game_scene.cpp \
		source/states/gameover_state.cpp \
		source/states/splash_state.cpp \
		source/entity/entity.cpp \
		source/entity/sprite_entity.cpp \
		source/entity/entity_factory.cpp \
		source/util/collision_sensor.cpp \
		source/entity/trigger_entity.cpp \
		source/manager/gui_manager.cpp \
		source/entity/piece_entity.cpp

HEADERS += \
		source/gameflow.h \
		source/states/main_menu_state.h \
		source/states/credits_state.h \
		source/states/options_state.h \
		source/states/game/game_pause_state.h \
		source/states/game_state.h \
		source/data/game_data.h \
		source/defines.h \
		source/states/game/game_run_state.h \
		source/manager/camera_manager.h \
		source/manager/world_manager.h \
		source/manager/sound_manager.h \
		source/manager/physics_manager.h \
		source/scene/game_scene.h \
		source/states/gameover_state.h \
		source/states/splash_state.h \
		source/entity/entity.h \
		source/entity/sprite_entity.h \
		source/entity/entity_factory.h \
		source/util/collision_sensor.h \
		source/util/sound.h \
		source/entity/trigger_entity.h \
		source/manager/gui_manager.h \
	source/entity/piece_entity.h

OTHER_FILES_CONFIG = \
#Configs
		resources/configs/app.config \
		resources/configs/game.config

OTHER_FILES_FONT = \
#Fonts
		resources/fonts/Delicious-Roman.otf \
		resources/fonts/Delicious-Italic.otf \
		resources/fonts/Delicious-Bold.otf \
		resources/fonts/Delicious-BoldItalic.otf

OTHER_FILES_SCENE = \
#Scenes
		resources/scenes/empty.scene \
		resources/scenes/game.scene

OTHER_FILES_TEXTURE = \
#Textures
		resources/textures/player_idle_frame1.png \
		resources/textures/player_idle_frame2.png \
		resources/textures/ball.png \
		resources/textures/Border.png \
		resources/textures/GameAtlas.png

#Gui
OTHER_FILES_GUI_STYLE = \
		#Styles
		resources/gui/styles/common.rcss \
		resources/gui/styles/window.rcss \
		resources/gui/styles/game.rcss

OTHER_FILES_GUI_VIEW = \
		#Views
		resources/gui/views/mainmenu.rml \
		resources/gui/views/window.rml \
		resources/gui/views/gameplay.rml \
		resources/gui/views/credits.rml \
		resources/gui/views/options.rml \
		resources/gui/views/game.rml \
		resources/gui/views/gamepause.rml \
		resources/gui/views/gameover.rml \
		resources/gui/views/splash.rml

OTHER_FILES_GUI_TEXTURE = \
		#Textures
		resources/gui/textures/background_gameover.png \
		resources/gui/textures/menu_background.png \
		resources/gui/textures/UIAtlas.png \
		resources/gui/textures/Background.png \
		resources/gui/textures/Splash.png

OTHER_FILES_SOUND = \
#Sounds
		resources/sounds/sfx.ogg \
		resources/sounds/theme.ogg \
		resources/sounds/wakeup.ogg \
		resources/sounds/powerup.ogg \
		resources/sounds/Pickup_Coin3.ogg \
		resources/sounds/damage.ogg \
		resources/sounds/scottwills_time.ogg \
		resources/sounds/metal_game_over.ogg \
		resources/sounds/jump.ogg \
		resources/sounds/teleport.ogg \
		resources/sounds/menu_music.ogg \
		resources/sounds/gameplay_music.ogg

#Maps
OTHER_FILES_MAPS = \
		resources/game.json

OTHER_FILES += $${OTHER_FILES_CONFIG} \
		$${OTHER_FILES_FONT} \
		$${OTHER_FILES_SCENE} \
		$${OTHER_FILES_TEXTURE} \
		$${OTHER_FILES_GUI_STYLE} \
		$${OTHER_FILES_GUI_VIEW} \
		$${OTHER_FILES_GUI_TEXTURE} \
		$${OTHER_FILES_SOUND} \
		$${OTHER_FILES_MAPS}

include("app.pri")
