# Procedure taken from qt-creator/share/qtcreator/translations/translations.pro.
# Windows-specific parts were removed.

include(../../../wikt.pri)

LANGUAGES = cs

defineReplace(prependAll) {
  for(a,$$1):result += $$2$${a}$$3
  return($$result)
}

LUPDATE = $$[QT_INSTALL_BINS]/lupdate -locations relative -no-ui-lines
LRELEASE = $$[QT_INSTALL_BINS]/lrelease
TRANSLATIONS = $$prependAll(LANGUAGES, $$PWD/wikt_,.ts)

ts.commands += (cd $$WIKT_SOURCE_TREE && $$LUPDATE src -ts $$TRANSLATIONS)
QMAKE_EXTRA_TARGETS += ts

TEMPLATE = app
TARGET = phony_target2
CONFIG -= qt
QT = 
LIBS = 

updateqm.input = TRANSLATIONS
updateqm.output = $$WIKT_DATA_PATH/translations/${QMAKE_FILE_BASE}.qm
updateqm.variable_out = PRE_TARGETDEPS
updateqm.commands = $$LRELEASE ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_OUT}
updateqm.name = LRELEASE ${QMAKE_FILE_IN}
updateqm.CONFIG += no_link
QMAKE_EXTRA_COMPILERS += updateqm

QMAKE_LINK = @: IGNORE THIS LINE
OBJECTS_DIR =

qmfiles.files = $$prependAll(LANGUAGES, $$OUT_PWD/wikt_,.qm)
qmfiles.path = /share/wikt/translations
INSTALLS += qmfiles
