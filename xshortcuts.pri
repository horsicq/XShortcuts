INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/dialogshortcuts.h \
    $$PWD/xshortcuts.h \
    $$PWD/xshortcutsdialog.h \
    $$PWD/xshortcutstscrollarea.h \
    $$PWD/xshortcutswidget.h

SOURCES += \
    $$PWD/dialogshortcuts.cpp \
    $$PWD/xshortcuts.cpp \
    $$PWD/xshortcutsdialog.cpp \
    $$PWD/xshortcutstscrollarea.cpp \
    $$PWD/xshortcutswidget.cpp

FORMS += \
    $$PWD/dialogshortcuts.ui

DISTFILES += \
    $$PWD/xshortcuts.cmake
