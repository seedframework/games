TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG += sdl2

BASE = ../../
INCLUDEPATH += $${BASE}/include
include($${BASE}/compiler.pri)
include($${BASE}/platform.pri)


unix:!macx {
		DEFINES += LINUX PHYSFS_NO_CDROM_SUPPORT
		LIBS += -lseed -lseedcontrib -lGL -lopenal -ldl -lpthread

		#Configs
		APP_CONFIG_FILES.files = $$files($${PWD}/resources/configs/*.*)
		APP_CONFIG_FILES.path = $${OUT_PWD}/$${DESTDIR}/configs
		APP_CONFIG_FILES.commands += test -d $${APP_CONFIG_FILES.path} || mkdir -p $${APP_CONFIG_FILES.path} &&
		APP_CONFIG_FILES.commands += ${COPY_FILE} $$APP_CONFIG_FILES.files $${APP_CONFIG_FILES.path}
		#Fonts
		APP_FONT_FILES.files = $$files($${PWD}/resources/fonts/*.*)
		APP_FONT_FILES.path = $${OUT_PWD}/$${DESTDIR}/fonts
		APP_FONT_FILES.commands += test -d $${APP_FONT_FILES.path} || mkdir -p $${APP_FONT_FILES.path} &&
		APP_FONT_FILES.commands += ${COPY_FILE} $$APP_FONT_FILES.files $${APP_FONT_FILES.path}
		#Scenes
		APP_SCENE_FILES.files = $$files($${PWD}/resources/scenes/*.*)
		APP_SCENE_FILES.path = $${OUT_PWD}/$${DESTDIR}/scenes
		APP_SCENE_FILES.commands += test -d $${APP_SCENE_FILES.path} || mkdir -p $${APP_SCENE_FILES.path} &&
		APP_SCENE_FILES.commands += ${COPY_FILE} $$APP_SCENE_FILES.files $${APP_SCENE_FILES.path}
		#Textures
		APP_TEXTURE_FILES.files = $$files($${PWD}/resources/textures/*.*)
		APP_TEXTURE_FILES.path = $${OUT_PWD}/$${DESTDIR}/textures
		APP_TEXTURE_FILES.commands += test -d $${APP_TEXTURE_FILES.path} || mkdir -p $${APP_TEXTURE_FILES.path} &&
		APP_TEXTURE_FILES.commands += ${COPY_FILE} $$APP_TEXTURE_FILES.files $${APP_TEXTURE_FILES.path}
		#Gui
				#Styles
				APP_GUI_STYLE_FILES.files = $$files($${PWD}/resources/gui/styles/*.*)
				APP_GUI_STYLE_FILES.path = $${OUT_PWD}/$${DESTDIR}/gui/styles
				APP_GUI_STYLE_FILES.commands += test -d $${APP_GUI_STYLE_FILES.path} || mkdir -p $${APP_GUI_STYLE_FILES.path} &&
				APP_GUI_STYLE_FILES.commands += ${COPY_FILE} $$APP_GUI_STYLE_FILES.files $${APP_GUI_STYLE_FILES.path}
				#Views
				APP_GUI_VIEW_FILES.files = $$files($${PWD}/resources/gui/views/*.*)
				APP_GUI_VIEW_FILES.path = $${OUT_PWD}/$${DESTDIR}/gui/views
				APP_GUI_VIEW_FILES.commands += test -d $${APP_GUI_VIEW_FILES.path} || mkdir -p $${APP_GUI_VIEW_FILES.path} &&
				APP_GUI_VIEW_FILES.commands += ${COPY_FILE} $$APP_GUI_VIEW_FILES.files $${APP_GUI_VIEW_FILES.path}
				#Texures
				APP_GUI_TEXTURE_FILES.files = $$files($${PWD}/resources/gui/textures/*.*)
				APP_GUI_TEXTURE_FILES.path = $${OUT_PWD}/$${DESTDIR}/gui/textures
				APP_GUI_TEXTURE_FILES.commands += test -d $${APP_GUI_TEXTURE_FILES.path} || mkdir -p $${APP_GUI_TEXTURE_FILES.path} &&
				APP_GUI_TEXTURE_FILES.commands += ${COPY_FILE} $$APP_GUI_TEXTURE_FILES.files $${APP_GUI_TEXTURE_FILES.path}
		#Sounds
		APP_SOUND_FILES.files = $$files($${PWD}/resources/sounds/*.*)
		APP_SOUND_FILES.path = $${OUT_PWD}/$${DESTDIR}/sounds
		APP_SOUND_FILES.commands += test -d $${APP_SOUND_FILES.path} || mkdir -p $${APP_SOUND_FILES.path} &&
		APP_SOUND_FILES.commands += ${COPY_FILE} $$APP_SOUND_FILES.files $${APP_SOUND_FILES.path}
		#Maps
		APP_MAPS_FILES.files = $$files($${PWD}/resources/*.*)
		APP_MAPS_FILES.path = $${OUT_PWD}/$${DESTDIR}/
		APP_MAPS_FILES.commands += test -d $${APP_MAPS_FILES.path} || mkdir -p $${APP_MAPS_FILES.path} &&
		APP_MAPS_FILES.commands += ${COPY_FILE} $$APP_MAPS_FILES.files $${APP_MAPS_FILES.path}
		#Prefabs
		APP_PREFABS_FILES.files = $$files($${PWD}/resources/prefabs/*.*)
		APP_PREFABS_FILES.path = $${OUT_PWD}/$${DESTDIR}/prefabs
		APP_PREFABS_FILES.commands += test -d $${APP_PREFABS_FILES.path} || mkdir -p $${APP_PREFABS_FILES.path} &&
		APP_PREFABS_FILES.commands += ${COPY_FILE} $$APP_PREFABS_FILES.files $${APP_PREFABS_FILES.path}

		QMAKE_EXTRA_TARGETS += APP_CONFIG_FILES APP_FONT_FILES APP_SCENE_FILES APP_TEXTURE_FILES APP_GUI_STYLE_FILES \
							APP_GUI_VIEW_FILES APP_GUI_TEXTURE_FILES APP_SOUND_FILES APP_MAPS_FILES APP_PREFABS_FILES
		POST_TARGETDEPS += APP_CONFIG_FILES APP_FONT_FILES APP_SCENE_FILES APP_TEXTURE_FILES APP_GUI_STYLE_FILES \
							APP_GUI_VIEW_FILES APP_GUI_TEXTURE_FILES APP_SOUND_FILES APP_MAPS_FILES APP_PREFABS_FILES
}

macx {
		DEFINES += LINUX TARGET_API_MAC_CARBON TARGET_API_MAC_OSX _THREAD_SAFE USE_API_SOIL
		LIBS += -lseed -lseedcontrib -framework OpenAL -framework OpenGL -framework Cocoa -framework IOKit -framework QTKit -framework CoreFoundation -framework CoreAudio -framework AudioUnit -framework ForceFeedback -framework Carbon -framework AudioToolbox
		CONFIG -= sdl
		CONFIG -= glfw
		CONFIG += sdl2

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
		#Prefabs
		APP_PREFABS_FILES.files = $$OTHER_FILES_PREFABS
		APP_PREFABS_FILES.path = Contents/Resources/prefabs/

		QMAKE_BUNDLE_DATA += APP_CONFIG_FILES APP_FONT_FILES APP_SCENE_FILES \
						APP_TEXTURE_FILES APP_GUI_STYLE_FILES APP_GUI_VIEW_FILES \
						APP_GUI_TEXTURE_FILES APP_SOUND_FILES APP_MAPS_FILES APP_PREFABS_FILES
}
