TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11
QMAKE_CXXFLAGS += -Wall -Wextra -std=c++11

LIBS += -LC:/SFML/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += C:/SFML/include
DEPENDPATH += C:/SFML/include

SOURCES += \
    src/animation_handler.cpp \
    src/game.cpp \
    src/game_state_editor.cpp \
    src/game_state_start.cpp \
    src/gui.cpp \
    src/map.cpp \
    src/texture_manager.cpp \
    src/tile.cpp \
    main.cpp \
    src/world.cpp \
    src/object/animal.cpp \
    src/object/animal_genetic_code.cpp \
    src/object/plant.cpp \
    src/object/plant_genetic_code.cpp \
    src/object/genetic_code.cpp \
    src/utils/window_value.cpp \
    src/object/carnivorous_animal.cpp \
    src/object/herbivorous_animal.cpp \
    src/utils/Utils2d.cpp \
    src/object/object_manager.cpp

HEADERS  += \
    src/animation_handler.h \
    src/game.h \
    src/game_state.h \
    src/game_state_editor.h \
    src/game_state_start.h \
    src/gui.h \
    src/map.h \
    src/texture_manager.h \
    src/tile.h \
    src/world.h \
    src/utils/Utils2d.h \
    src/utils/window_value.h \
    src/object/animal.h \
    src/object/animal_genetic_code.h \
    src/object/carnivorous_animal.h \
    src/object/genetic_code.h \
    src/object/herbivorous_animal.h \
    src/object/interactive_object.h \
    src/object/plant.h \
    src/object/plant_genetic_code.h \
    src/object/object_manager.h

FORMS    +=
