TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG += glfw

INCLUDEPATH += ../../seed/include ../../seed/contrib

SOURCES += source/main.cpp \
                source/gameflow.cpp \
                source/states/credits_state.cpp \
                source/states/main_menu_state.cpp \
                source/states/options_state.cpp \
                source/states/game_pause_state.cpp \
                source/states/game_state.cpp \
                source/data/game_data.cpp \
                source/states/game_run_state.cpp \
                source/controller/camera_controller.cpp \
                source/controller/world_controller.cpp \
                source/controller/sound_controller.cpp \
                source/manager/physics_manager.cpp \
                source/scene/game_scene.cpp \
                source/states/gameover_state.cpp \
                source/states/splash_state.cpp \
                source/entity/entity.cpp \
                source/entity/sprite_entity.cpp \
                source/entity/entity_factory.cpp \
                source/entity/player_left_entity.cpp \
                source/entity/player_right_entity.cpp \
                source/util/collision_sensor.cpp \
                source/entity/ball_entity.cpp \
                source/entity/trigger_entity.cpp

HEADERS += \
                source/gameflow.h \
                source/states/main_menu_state.h \
                source/states/credits_state.h \
                source/states/options_state.h \
                source/states/game_pause_state.h \
                source/states/game_state.h \
                source/data/game_data.h \
                source/defines.h \
                source/states/game_run_state.h \
                source/controller/camera_controller.h \
                source/controller/world_controller.h \
                source/controller/sound_controller.h \
                source/manager/physics_manager.h \
                source/scene/game_scene.h \
                source/states/gameover_state.h \
                source/states/splash_state.h \
                source/entity/entity.h \
                source/entity/sprite_entity.h \
                source/entity/entity_factory.h \
                source/entity/player_left_entity.h \
                source/entity/player_right_entity.h \
                source/util/collision_sensor.h \
                source/util/sound.h \
                source/entity/ball_entity.h \
                source/entity/trigger_entity.h

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
                $${OTHER_FILES_SOUND} \
                $${OTHER_FILES_MAPS}

CONFIG(debug, debug|release) {
                DESTDIR = bin
                DEFINES += DEBUG
                LIBS += -L../../seed/lib/debug
} else {
                DESTDIR = bin
                DEFINES += RELEASE
                LIBS += -L../../seed/lib/release
}

unix:!macx {
                DEFINES += LINUX
                LIBS += -lseed -lseedcontrib -lGL -lopenal
                QMAKE_CXXFLAGS += -std=c++0x

                sdl {
                                LIBS += -lSDL -lSDL_image
                }
}

macx {
                DEFINES += LINUX
                INCLUDEPATH += ../../seed/contrib/osx/
                LIBS += -lseed -lseedcontrib -framework OpenAL -framework OpenGL -framework Cocoa -framework IOKit
                CONFIG -= sdl
                CONFIG += glfw

                #Configs
                APP_CONFIG_FILES.files = $$OTHER_FILES_CONFIG
                APP_CONFIG_FILES.path = Contents/Resources/configs
                #Fonts
                APP_FONT_FILES.files = $$OTHER_FILES_FONT
                APP_FONT_FILES.path = Contents/Resources/fonts
                #Scenes
                APP_SCENE_FILES.files = $$OTHER_FILES_SCENE
                APP_SCENE_FILES.path = Contents/Resources/scenes
                #Textures
                APP_TEXTURE_FILES.files = $$OTHER_FILES_TEXTURE
                APP_TEXTURE_FILES.path = Contents/Resources/textures
                #Gui
                                #Styles
                                APP_GUI_STYLE_FILES.files = $$OTHER_FILES_GUI_STYLE
                                APP_GUI_STYLE_FILES.path = Contents/Resources/gui/styles
                                #Views
                                APP_GUI_VIEW_FILES.files = $$OTHER_FILES_GUI_VIEW
                                APP_GUI_VIEW_FILES.path = Contents/Resources/gui/views
                                #Texures
                                APP_GUI_TEXTURE_FILES.files = $$OTHER_FILES_GUI_TEXTURE
                                APP_GUI_TEXTURE_FILES.path = Contents/Resources/gui/textures
                #Sounds
                APP_SOUND_FILES.files = $$OTHER_FILES_SOUND
                APP_SOUND_FILES.path = Contents/Resources/sounds
                #Maps
                APP_MAPS_FILES.files = $$OTHER_FILES_MAPS
                APP_MAPS_FILES.path = Contents/Resources/

                QMAKE_BUNDLE_DATA += APP_CONFIG_FILES APP_FONT_FILES APP_SCENE_FILES \
                                                APP_TEXTURE_FILES APP_GUI_STYLE_FILES APP_GUI_VIEW_FILES \
                                                APP_GUI_TEXTURE_FILES APP_SOUND_FILES APP_MAPS_FILES
}

win32 {
                LIBS += -L../../seed/contrib/windows/ -lseed -lseedcontrib -mwindows -lmingw32 -lopengl32 -lopenal32
                INCLUDEPATH += ../../seed/contrib/windows/
                CONFIG -= glfw
                CONFIG += sdl
                sdl {
                                DEFINES += WIN32 main=SDL_main
                                LIBS += -lSDLmain -lSDL -lSDL_image -lgdi32
                }
}

glfw {
                DEFINES += BUILD_GLFW
} else:sdl {
                DEFINES += BUILD_SDL
}
