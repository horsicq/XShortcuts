/* Copyright (c) 2021-2022 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef XSHORTCUTS_H
#define XSHORTCUTS_H

#include <QApplication>
#include <QDir>
#include <QKeySequence>
#include <QMap>
#include <QSettings>
#include <QShortcut>

#define X_ID_FILE_OPEN XShortcuts::createShortcutsId(XShortcuts::GROUPID_FILE, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_OPEN)
#define X_ID_FILE_SAVE XShortcuts::createShortcutsId(XShortcuts::GROUPID_FILE, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_SAVE)
#define X_ID_FILE_SAVEAS XShortcuts::createShortcutsId(XShortcuts::GROUPID_FILE, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_SAVEAS)
#define X_ID_FILE_CLOSE XShortcuts::createShortcutsId(XShortcuts::GROUPID_FILE, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_CLOSE)
#define X_ID_FILE_PRINT XShortcuts::createShortcutsId(XShortcuts::GROUPID_FILE, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_PRINT)
#define X_ID_FILE_EXIT XShortcuts::createShortcutsId(XShortcuts::GROUPID_FILE, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_EXIT)

#define X_ID_STRINGS_COPY_STRING XShortcuts::createShortcutsId(XShortcuts::GROUPID_STRINGS, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_STRING)
#define X_ID_STRINGS_COPY_OFFSET XShortcuts::createShortcutsId(XShortcuts::GROUPID_STRINGS, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_OFFSET)
#define X_ID_STRINGS_COPY_SIZE XShortcuts::createShortcutsId(XShortcuts::GROUPID_STRINGS, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_SIZE)
#define X_ID_STRINGS_FOLLOWIN_HEX XShortcuts::createShortcutsId(XShortcuts::GROUPID_STRINGS, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FOLLOWIN, XShortcuts::BASEID_HEX)
#define X_ID_STRINGS_DEMANGLE XShortcuts::createShortcutsId(XShortcuts::GROUPID_STRINGS, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_DEMANGLE)
#define X_ID_STRINGS_EDIT_STRING XShortcuts::createShortcutsId(XShortcuts::GROUPID_STRINGS, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_EDIT, XShortcuts::BASEID_STRING)

#define X_ID_SIGNATURES_COPY_NAME XShortcuts::createShortcutsId(XShortcuts::GROUPID_SIGNATURES, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_NAME)
#define X_ID_SIGNATURES_COPY_SIGNATURE \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_SIGNATURES, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_SIGNATURE)
#define X_ID_SIGNATURES_COPY_ADDRESS \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_SIGNATURES, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_ADDRESS)
#define X_ID_SIGNATURES_COPY_OFFSET \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_SIGNATURES, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_OFFSET)
#define X_ID_SIGNATURES_FOLLOWIN_HEX \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_SIGNATURES, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FOLLOWIN, XShortcuts::BASEID_HEX)

#define X_ID_HEX_DUMPTOFILE XShortcuts::createShortcutsId(XShortcuts::GROUPID_HEX, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_DUMPTOFILE)
#define X_ID_HEX_GOTO_OFFSET XShortcuts::createShortcutsId(XShortcuts::GROUPID_HEX, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_GOTO, XShortcuts::BASEID_OFFSET)
#define X_ID_HEX_GOTO_ADDRESS XShortcuts::createShortcutsId(XShortcuts::GROUPID_HEX, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_GOTO, XShortcuts::BASEID_ADDRESS)
#define X_ID_HEX_SIGNATURE XShortcuts::createShortcutsId(XShortcuts::GROUPID_HEX, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_SIGNATURE)
#define X_ID_HEX_FIND_STRING XShortcuts::createShortcutsId(XShortcuts::GROUPID_HEX, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_STRING)
#define X_ID_HEX_FIND_SIGNATURE XShortcuts::createShortcutsId(XShortcuts::GROUPID_HEX, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_SIGNATURE)
#define X_ID_HEX_FIND_VALUE XShortcuts::createShortcutsId(XShortcuts::GROUPID_HEX, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_VALUE)
#define X_ID_HEX_FIND_NEXT XShortcuts::createShortcutsId(XShortcuts::GROUPID_HEX, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_NEXT)
#define X_ID_HEX_SELECT_ALL XShortcuts::createShortcutsId(XShortcuts::GROUPID_HEX, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_SELECT, XShortcuts::BASEID_ALL)
#define X_ID_HEX_COPY_HEX XShortcuts::createShortcutsId(XShortcuts::GROUPID_HEX, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_HEX)
#define X_ID_HEX_COPY_OFFSET XShortcuts::createShortcutsId(XShortcuts::GROUPID_HEX, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_OFFSET)
#define X_ID_HEX_COPY_ADDRESS XShortcuts::createShortcutsId(XShortcuts::GROUPID_HEX, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_ADDRESS)
#define X_ID_HEX_FOLLOWIN_DISASM XShortcuts::createShortcutsId(XShortcuts::GROUPID_HEX, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FOLLOWIN, XShortcuts::BASEID_DISASM)
#define X_ID_HEX_FOLLOWIN_MEMORYMAP \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_HEX, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FOLLOWIN, XShortcuts::BASEID_MEMORYMAP)
#define X_ID_HEX_FOLLOWIN_HEX XShortcuts::createShortcutsId(XShortcuts::GROUPID_HEX, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FOLLOWIN, XShortcuts::BASEID_HEX)
#define X_ID_HEX_EDIT_HEX XShortcuts::createShortcutsId(XShortcuts::GROUPID_HEX, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_EDIT, XShortcuts::BASEID_HEX)

#define X_ID_DISASM_DUMPTOFILE XShortcuts::createShortcutsId(XShortcuts::GROUPID_DISASM, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_DUMPTOFILE)
#define X_ID_DISASM_GOTO_OFFSET XShortcuts::createShortcutsId(XShortcuts::GROUPID_DISASM, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_GOTO, XShortcuts::BASEID_OFFSET)
#define X_ID_DISASM_GOTO_ADDRESS XShortcuts::createShortcutsId(XShortcuts::GROUPID_DISASM, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_GOTO, XShortcuts::BASEID_ADDRESS)
#define X_ID_DISASM_GOTO_ENTRYPOINT \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DISASM, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_GOTO, XShortcuts::BASEID_ENTRYPOINT)
#define X_ID_DISASM_SIGNATURE XShortcuts::createShortcutsId(XShortcuts::GROUPID_DISASM, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_SIGNATURE)
#define X_ID_DISASM_HEX_SIGNATURE XShortcuts::createShortcutsId(XShortcuts::GROUPID_DISASM, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_HEX, XShortcuts::BASEID_SIGNATURE)
#define X_ID_DISASM_FIND_STRING XShortcuts::createShortcutsId(XShortcuts::GROUPID_DISASM, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_STRING)
#define X_ID_DISASM_FIND_SIGNATURE XShortcuts::createShortcutsId(XShortcuts::GROUPID_DISASM, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_SIGNATURE)
#define X_ID_DISASM_FIND_VALUE XShortcuts::createShortcutsId(XShortcuts::GROUPID_DISASM, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_VALUE)
#define X_ID_DISASM_FIND_NEXT XShortcuts::createShortcutsId(XShortcuts::GROUPID_DISASM, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_NEXT)
#define X_ID_DISASM_SELECT_ALL XShortcuts::createShortcutsId(XShortcuts::GROUPID_DISASM, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_SELECT, XShortcuts::BASEID_ALL)
#define X_ID_DISASM_COPY_HEX XShortcuts::createShortcutsId(XShortcuts::GROUPID_DISASM, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_HEX)
#define X_ID_DISASM_COPY_OFFSET XShortcuts::createShortcutsId(XShortcuts::GROUPID_DISASM, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_OFFSET)
#define X_ID_DISASM_COPY_ADDRESS XShortcuts::createShortcutsId(XShortcuts::GROUPID_DISASM, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_ADDRESS)
#define X_ID_DISASM_FOLLOWIN_HEX XShortcuts::createShortcutsId(XShortcuts::GROUPID_DISASM, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FOLLOWIN, XShortcuts::BASEID_HEX)
#define X_ID_DISASM_EDIT_HEX XShortcuts::createShortcutsId(XShortcuts::GROUPID_DISASM, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_EDIT, XShortcuts::BASEID_HEX)

// TODO Hardware breakpoints !!!
#define X_ID_DEBUGGER_FILE_OPEN XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FILE, XShortcuts::BASEID_OPEN)
#define X_ID_DEBUGGER_FILE_CLOSE XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FILE, XShortcuts::BASEID_CLOSE)
#define X_ID_DEBUGGER_FILE_ATTACH XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FILE, XShortcuts::BASEID_ATTACH)
#define X_ID_DEBUGGER_FILE_DETACH XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FILE, XShortcuts::BASEID_DETACH)
#define X_ID_DEBUGGER_FILE_EXIT XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_FILE, XShortcuts::BASEID_EXIT)
#define X_ID_DEBUGGER_VIEW_CPU XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_VIEW, XShortcuts::BASEID_CPU)
#define X_ID_DEBUGGER_VIEW_LOG XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_VIEW, XShortcuts::BASEID_LOG)
#define X_ID_DEBUGGER_VIEW_BREAKPOINTS \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_VIEW, XShortcuts::BASEID_BREAKPOINTS)
#define X_ID_DEBUGGER_VIEW_MEMORYMAP \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_VIEW, XShortcuts::BASEID_MEMORYMAP)
#define X_ID_DEBUGGER_VIEW_CALLSTACK \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_VIEW, XShortcuts::BASEID_CALLSTACK)
#define X_ID_DEBUGGER_VIEW_THREADS XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_VIEW, XShortcuts::BASEID_THREADS)
#define X_ID_DEBUGGER_VIEW_HANDLES XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_VIEW, XShortcuts::BASEID_HANDLES)
#define X_ID_DEBUGGER_VIEW_MODULES XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_VIEW, XShortcuts::BASEID_MODULES)
#define X_ID_DEBUGGER_VIEW_SYMBOLS XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_VIEW, XShortcuts::BASEID_SYMBOLS)
#define X_ID_DEBUGGER_TOOLS_SHORTCUTS \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_TOOLS, XShortcuts::BASEID_SHORTCUTS)
#define X_ID_DEBUGGER_TOOLS_OPTIONS \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_TOOLS, XShortcuts::BASEID_OPTIONS)
#define X_ID_DEBUGGER_HELP_ABOUT XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_HELP, XShortcuts::BASEID_ABOUT)
#define X_ID_DEBUGGER_DEBUG_RUN XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DEBUG, XShortcuts::BASEID_RUN)
#define X_ID_DEBUGGER_DEBUG_PAUSE XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DEBUG, XShortcuts::BASEID_PAUSE)
#define X_ID_DEBUGGER_DEBUG_STEPINTO \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DEBUG, XShortcuts::BASEID_STEPINTO)
#define X_ID_DEBUGGER_DEBUG_STEPOVER \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DEBUG, XShortcuts::BASEID_STEPOVER)
#define X_ID_DEBUGGER_DEBUG_CLOSE XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DEBUG, XShortcuts::BASEID_CLOSE)
#define X_ID_DEBUGGER_DEBUG_RESTART \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DEBUG, XShortcuts::BASEID_RESTART)
#define X_ID_DEBUGGER_ANIMATE_STEPINTO \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_ANIMATE, XShortcuts::BASEID_STEPINTO)
#define X_ID_DEBUGGER_ANIMATE_STEPOVER \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_ANIMATE, XShortcuts::BASEID_STEPOVER)
#define X_ID_DEBUGGER_ANIMATE_STOP XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_ANIMATE, XShortcuts::BASEID_STOP)
#define X_ID_DEBUGGER_TRACE_STEPINTO \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_TRACE, XShortcuts::BASEID_STEPINTO)
#define X_ID_DEBUGGER_TRACE_STEPOVER \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_TRACE, XShortcuts::BASEID_STEPOVER)
#define X_ID_DEBUGGER_TRACE_STOP XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_TRACE, XShortcuts::BASEID_STOP)
#define X_ID_DEBUGGER_DISASM_BREAKPOINT_TOGGLE                                                                                                                \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DISASM << XShortcuts::GROUPID_BREAKPOINT, \
                                  XShortcuts::BASEID_TOGGLE)
#define X_ID_DEBUGGER_DISASM_DUMPTOFILE \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DISASM, XShortcuts::BASEID_DUMPTOFILE)
#define X_ID_DEBUGGER_DISASM_GOTO_ADDRESS \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DISASM << XShortcuts::GROUPID_GOTO, XShortcuts::BASEID_ADDRESS)
#define X_ID_DEBUGGER_DISASM_HEX_SIGNATURE \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DISASM << XShortcuts::GROUPID_HEX, XShortcuts::BASEID_SIGNATURE)
#define X_ID_DEBUGGER_DISASM_SIGNATURE \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DISASM, XShortcuts::BASEID_SIGNATURE)
#define X_ID_DEBUGGER_DISASM_FIND_STRING \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DISASM << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_STRING)
#define X_ID_DEBUGGER_DISASM_FIND_VALUE \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DISASM << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_VALUE)
#define X_ID_DEBUGGER_DISASM_FIND_SIGNATURE                                                                                                             \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DISASM << XShortcuts::GROUPID_FIND, \
                                  XShortcuts::BASEID_SIGNATURE)
#define X_ID_DEBUGGER_DISASM_FIND_NEXT \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DISASM << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_NEXT)
#define X_ID_DEBUGGER_DISASM_COPY_HEX \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DISASM << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_HEX)
#define X_ID_DEBUGGER_DISASM_COPY_ADDRESS \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DISASM << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_ADDRESS)
#define X_ID_DEBUGGER_DISASM_SELECT_ALL \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DISASM, XShortcuts::BASEID_DUMPTOFILE)
#define X_ID_DEBUGGER_DISASM_EDIT_HEX \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DISASM << XShortcuts::GROUPID_EDIT, XShortcuts::BASEID_HEX)
#define X_ID_DEBUGGER_DISASM_FOLLOWIN_HEX \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_DISASM << XShortcuts::GROUPID_FOLLOWIN, XShortcuts::BASEID_HEX)
#define X_ID_DEBUGGER_HEX_DUMPTOFILE \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_HEX, XShortcuts::BASEID_DUMPTOFILE)
#define X_ID_DEBUGGER_HEX_FIND_STRING \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_HEX << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_STRING)
#define X_ID_DEBUGGER_HEX_FIND_VALUE \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_HEX << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_VALUE)
#define X_ID_DEBUGGER_HEX_FIND_SIGNATURE \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_HEX << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_SIGNATURE)
#define X_ID_DEBUGGER_HEX_FIND_NEXT \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_HEX << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_NEXT)
#define X_ID_DEBUGGER_HEX_GOTO_ADDRESS \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_HEX << XShortcuts::GROUPID_GOTO, XShortcuts::BASEID_ADDRESS)
#define X_ID_DEBUGGER_HEX_SIGNATURE \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_HEX, XShortcuts::BASEID_SIGNATURE)
#define X_ID_DEBUGGER_HEX_COPY_HEX \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_HEX << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_HEX)
#define X_ID_DEBUGGER_HEX_COPY_ADDRESS \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_HEX << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_ADDRESS)
#define X_ID_DEBUGGER_HEX_SELECT_ALL \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_HEX, XShortcuts::BASEID_DUMPTOFILE)
#define X_ID_DEBUGGER_HEX_EDIT_HEX \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_HEX << XShortcuts::GROUPID_EDIT, XShortcuts::BASEID_HEX)
#define X_ID_DEBUGGER_HEX_FOLLOWIN_DISASM \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_HEX << XShortcuts::GROUPID_FOLLOWIN, XShortcuts::BASEID_DISASM)
#define X_ID_DEBUGGER_STACK_GOTO_ADDRESS \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_STACK << XShortcuts::GROUPID_GOTO, XShortcuts::BASEID_ADDRESS)
#define X_ID_DEBUGGER_STACK_COPY_ADDRESS \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_STACK << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_ADDRESS)
#define X_ID_DEBUGGER_STACK_COPY_VALUE \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_STACK << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_VALUE)
#define X_ID_DEBUGGER_STACK_EDIT_HEX \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_STACK << XShortcuts::GROUPID_EDIT, XShortcuts::BASEID_HEX)
#define X_ID_DEBUGGER_STACK_FOLLOWIN_HEX \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_STACK << XShortcuts::GROUPID_FOLLOWIN, XShortcuts::BASEID_HEX)
#define X_ID_DEBUGGER_STACK_FOLLOWIN_DISASM                                                                                                                \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_STACK << XShortcuts::GROUPID_FOLLOWIN, \
                                  XShortcuts::BASEID_DISASM)
#define X_ID_DEBUGGER_STACK_VALUE_FOLLOWIN_HEX                  \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER, \
                                  QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_STACK << XShortcuts::GROUPID_VALUE << XShortcuts::GROUPID_FOLLOWIN, XShortcuts::BASEID_HEX)
#define X_ID_DEBUGGER_STACK_VALUE_FOLLOWIN_DISASM                                                                                                         \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_DEBUGGER,                                                                                           \
                                  QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_STACK << XShortcuts::GROUPID_VALUE << XShortcuts::GROUPID_FOLLOWIN, \
                                  XShortcuts::BASEID_DISASM)
// TODO Registers

#define X_ID_PROCESS_STRUCTS XShortcuts::createShortcutsId(XShortcuts::GROUPID_PROCESS, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_STRUCTS)
#define X_ID_PROCESS_DUMPTOFILE XShortcuts::createShortcutsId(XShortcuts::GROUPID_PROCESS, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_DUMPTOFILE)
#define X_ID_PROCESS_MEMORY_HEX XShortcuts::createShortcutsId(XShortcuts::GROUPID_PROCESS, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_MEMORY, XShortcuts::BASEID_HEX)
#define X_ID_PROCESS_MEMORY_STRINGS \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_PROCESS, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_MEMORY, XShortcuts::BASEID_STRINGS)
#define X_ID_PROCESS_MEMORY_SIGNATURES \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_PROCESS, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_MEMORY, XShortcuts::BASEID_SIGNATURES)
#define X_ID_PROCESS_MEMORY_MEMORYMAP \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_PROCESS, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_MEMORY, XShortcuts::BASEID_MEMORYMAP)
#define X_ID_PROCESS_MEMORY_MODULES \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_PROCESS, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_MEMORY, XShortcuts::BASEID_MODULES)
#define X_ID_PROCESS_SHOWIN_VIEWER XShortcuts::createShortcutsId(XShortcuts::GROUPID_PROCESS, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_SHOWIN, XShortcuts::BASEID_VIEWER)
#define X_ID_PROCESS_SHOWIN_FOLDER XShortcuts::createShortcutsId(XShortcuts::GROUPID_PROCESS, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_SHOWIN, XShortcuts::BASEID_FOLDER)
#define X_ID_PROCESS_COPY_PID XShortcuts::createShortcutsId(XShortcuts::GROUPID_PROCESS, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_PID)
#define X_ID_PROCESS_COPY_NAME XShortcuts::createShortcutsId(XShortcuts::GROUPID_PROCESS, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_NAME)
#define X_ID_PROCESS_COPY_FILENAME XShortcuts::createShortcutsId(XShortcuts::GROUPID_PROCESS, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_FILENAME)

#define X_ID_ARCHIVE_OPEN XShortcuts::createShortcutsId(XShortcuts::GROUPID_ARCHIVE, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_OPEN)
#define X_ID_ARCHIVE_SCAN XShortcuts::createShortcutsId(XShortcuts::GROUPID_ARCHIVE, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_SCAN)
#define X_ID_ARCHIVE_HEX XShortcuts::createShortcutsId(XShortcuts::GROUPID_ARCHIVE, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_HEX)
#define X_ID_ARCHIVE_STRINGS XShortcuts::createShortcutsId(XShortcuts::GROUPID_ARCHIVE, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_STRINGS)
#define X_ID_ARCHIVE_ENTROPY XShortcuts::createShortcutsId(XShortcuts::GROUPID_ARCHIVE, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_ENTROPY)
#define X_ID_ARCHIVE_HASH XShortcuts::createShortcutsId(XShortcuts::GROUPID_ARCHIVE, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_HASH)
#define X_ID_ARCHIVE_COPY_FILENAME XShortcuts::createShortcutsId(XShortcuts::GROUPID_ARCHIVE, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_COPY, XShortcuts::BASEID_FILENAME)
#define X_ID_ARCHIVE_DUMPTOFILE XShortcuts::createShortcutsId(XShortcuts::GROUPID_ARCHIVE, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_DUMPTOFILE)

#define X_ID_MODULES_DUMPTOFILE XShortcuts::createShortcutsId(XShortcuts::GROUPID_MODULES, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_DUMPTOFILE)
#define X_ID_MODULES_SHOWIN_FOLDER XShortcuts::createShortcutsId(XShortcuts::GROUPID_MODULES, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_SHOWIN, XShortcuts::BASEID_FOLDER)

#define X_ID_MEMORYMAP_DUMPTOFILE XShortcuts::createShortcutsId(XShortcuts::GROUPID_MEMORYMAP, QList<XShortcuts::GROUPID>(), XShortcuts::BASEID_DUMPTOFILE)
#define X_ID_MEMORYMAP_SHOWIN_FOLDER \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_MEMORYMAP, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_SHOWIN, XShortcuts::BASEID_FOLDER)

#define X_ID_SCAN_EDITOR_FIND_STRING \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_SCAN, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_EDITOR << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_STRING)
#define X_ID_SCAN_EDITOR_FIND_NEXT \
    XShortcuts::createShortcutsId(XShortcuts::GROUPID_SCAN, QList<XShortcuts::GROUPID>() << XShortcuts::GROUPID_EDITOR << XShortcuts::GROUPID_FIND, XShortcuts::BASEID_NEXT)

class XShortcuts : public QObject {
    Q_OBJECT

public:
    enum GROUPID {
        GROUPID_UNKNOWN = 0,
        GROUPID_SCAN,
        GROUPID_EDITOR,
        GROUPID_FILE,
        GROUPID_VIEW,
        GROUPID_DEBUGGER,
        GROUPID_DEBUG,
        GROUPID_TRACE,
        GROUPID_ANIMATE,
        GROUPID_ACTION,
        GROUPID_STRING,
        GROUPID_STRINGS,
        GROUPID_SIGNATURE,
        GROUPID_SIGNATURES,
        GROUPID_STRUCT,
        GROUPID_STRUCTS,
        GROUPID_HEX,
        GROUPID_DISASM,
        GROUPID_STACK,
        GROUPID_REGISTER,
        GROUPID_REGISTERS,
        GROUPID_ARCHIVE,
        GROUPID_TABLE,
        GROUPID_PROCESS,
        GROUPID_MEMORY,
        GROUPID_MEMORYMAP,
        GROUPID_MODULES,
        GROUPID_COPY,
        GROUPID_GOTO,
        GROUPID_EDIT,
        GROUPID_FIND,
        GROUPID_TOOLS,
        GROUPID_HELP,
        GROUPID_SELECT,
        GROUPID_FOLLOWIN,
        GROUPID_SHOWIN,
        GROUPID_BREAKPOINT,
        GROUPID_VALUE,
    };

    enum BASEID {
        BASEID_UNKNOWN = 0,
        BASEID_COPY,
        BASEID_SHOW,
        BASEID_OPEN,
        BASEID_SAVE,
        BASEID_SAVEAS,
        BASEID_CLOSE,
        BASEID_PRINT,
        BASEID_EXIT,
        BASEID_DUMPTOFILE,
        BASEID_OFFSET,
        BASEID_ADDRESS,
        BASEID_ENTRYPOINT,
        BASEID_SIZE,
        BASEID_STRING,
        BASEID_STRINGS,
        BASEID_SIGNATURE,
        BASEID_SIGNATURES,
        BASEID_HEX,
        BASEID_DEMANGLE,
        BASEID_NAME,
        BASEID_NEXT,
        BASEID_VALUE,
        BASEID_ALL,
        BASEID_DISASM,
        BASEID_MEMORYMAP,
        BASEID_ATTACH,
        BASEID_DETACH,
        BASEID_CPU,
        BASEID_LOG,
        BASEID_BREAKPOINTS,
        BASEID_CALLSTACK,
        BASEID_THREADS,
        BASEID_HANDLES,
        BASEID_MODULES,
        BASEID_SYMBOLS,
        BASEID_SHORTCUTS,
        BASEID_OPTIONS,
        BASEID_ABOUT,
        BASEID_FILENAME,
        BASEID_STRUCTS,
        BASEID_VIEWER,
        BASEID_FOLDER,
        BASEID_PID,
        BASEID_RUN,
        BASEID_PAUSE,
        BASEID_STEPINTO,
        BASEID_STEPOVER,
        BASEID_STOP,
        BASEID_RESTART,
        BASEID_TOGGLE,
        BASEID_SCAN,
        BASEID_ENTROPY,
        BASEID_HASH,
        BASEID_STACK
    };

    static const qint32 GROUP_SH = 24;  // 0xFF000000 // TODO remove !!!

    // TODO remove !!!
    // TODO Check projects
    enum ID {
        ID_UNKNOWN = 0,
        ID_ACTION = GROUPID_ACTION << GROUP_SH,
        ID_ACTION__END,
        ID_STRINGS = GROUPID_STRINGS << GROUP_SH,
        ID_STRINGS__END,
        ID_SIGNATURES = GROUPID_SIGNATURES << GROUP_SH,
        ID_SIGNATURES__END,
        ID_HEX = GROUPID_HEX << GROUP_SH,
        ID_HEX__END,
        ID_DISASM = GROUPID_DISASM << GROUP_SH,
        ID_DISASM__END,
        ID_DEBUGGER = GROUPID_DEBUGGER << GROUP_SH,
        ID_DEBUGGER__END,
        ID_ARCHIVE = GROUPID_ARCHIVE << GROUP_SH,
        ID_ARCHIVE__END,
        ID_TABLE = GROUPID_TABLE << GROUP_SH,
        ID_TABLE__END,
        ID_PROCESS = GROUPID_PROCESS << GROUP_SH,
        ID_PROCESS__END,
        ID_MEMORYMAP = GROUPID_MEMORYMAP << GROUP_SH,
        ID_MEMORYMAP__END,
        ID_MODULES = GROUPID_MODULES << GROUP_SH,
        ID_MODULES__END,
    };

    explicit XShortcuts(QObject *pParent = nullptr);

    void setName(QString sValue);
    void setNative(bool bValue);
    void addGroup(GROUPID groupId);
    void addId(quint64 nId);
    void addGroup(ID id);  // TODO remove Check all projects
    QList<quint64> getShortcutsIDs();
    void load();
    void save();
    QKeySequence getShortcut(quint64 nId);
    void setShortcut(quint64 nId, QKeySequence keyValue);
    bool checkShortcut(quint64 nId, QKeySequence keyValue);
    static QString idToSettingsString(quint64 nId);
    static QKeySequence getDefault(quint64 nId);
    static QString groupIdToString(GROUPID groupId);
    static QString baseIdToString(BASEID baseId);
    // |quin32 main|quint32 subgroups|quint32 reserverd|quint32 nID
    // TODO make defines
    static quint64 createShortcutsId(GROUPID groupId, QList<GROUPID> listSubgroup, BASEID baseId);
    static GROUPID getGroupId(quint64 nShortcutId);
    static QList<GROUPID> getSubgroupIds(quint64 nShortcutId);
    static BASEID getBaseId(quint64 nShortcutId);
    static QString baseIdToSettingsString(BASEID baseId);
    static QString groupIdToSettingsString(GROUPID groupId);

private:
    bool g_bIsNative;
    QString g_sName;
    QString g_sFilePath;
    QMap<quint64, QKeySequence> g_mapValues;
};

#endif  // XSHORTCUTS_H
