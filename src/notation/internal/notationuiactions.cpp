/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "notationuiactions.h"

#include <unordered_map>

#include "ui/view/iconcodes.h"

using namespace mu::notation;
using namespace mu::ui;
using namespace mu::actions;

static const ActionCode NOTE_INPUT_ACTION_CODE("note-input");

static const ActionCode SHOW_INVISIBLE_CODE("show-invisible");
static const ActionCode SHOW_UNPRINTABLE_CODE("show-unprintable");
static const ActionCode SHOW_FRAMES_CODE("show-frames");
static const ActionCode SHOW_PAGEBORDERS_CODE("show-pageborders");
static const ActionCode SHOW_IRREGULAR_CODE("mark-irregular");

static const ActionCode TOGGLE_CONCERT_PITCH_CODE("concert-pitch");

const UiActionList NotationUiActions::m_actions = {
    UiAction("escape",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Esc")
             ),
    UiAction("put-note", // args: QPoint pos, bool replace, bool insert
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Put note")
             ),
    UiAction("next-element",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Next element"),
             QT_TRANSLATE_NOOP("action", "Accessibility: Next element")
             ),
    UiAction("prev-element",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Previous element"),
             QT_TRANSLATE_NOOP("action", "Accessibility: Previous element")
             ),
    UiAction("next-chord",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Next chord"),
             QT_TRANSLATE_NOOP("action", "Go to next chord or move text right")
             ),
    UiAction("prev-chord",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Previous chord"),
             QT_TRANSLATE_NOOP("action", "Go to previous chord or move text left")
             ),
    UiAction("next-measure",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Next measure"),
             QT_TRANSLATE_NOOP("action", "Go to next measure or move text right")
             ),
    UiAction("prev-measure",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Previous measure"),
             QT_TRANSLATE_NOOP("action", "Go to previous measure or move text left")
             ),
    UiAction("up-chord",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Up note in chord"),
             QT_TRANSLATE_NOOP("action", "Go to higher pitched note in chord")
             ),
    UiAction("down-chord",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Down note in chord"),
             QT_TRANSLATE_NOOP("action", "Go to lower pitched note in chord")
             ),
    UiAction("top-chord",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Top note in chord"),
             QT_TRANSLATE_NOOP("action", "Go to top note in chord")
             ),
    UiAction("bottom-chord",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Bottom note in chord"),
             QT_TRANSLATE_NOOP("action", "Go bottom note in chord")
             ),
    UiAction("first-element",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "First element"),
             QT_TRANSLATE_NOOP("action", "Go to first element in score")
             ),
    UiAction("last-element",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Last element"),
             QT_TRANSLATE_NOOP("action", "Go to last element in score")
             ),
    UiAction("move-up",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Move up"),
             QT_TRANSLATE_NOOP("action", "Move chord/rest to staff above")
             ),
    UiAction("move-down",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Move down"),
             QT_TRANSLATE_NOOP("action", "Move chord/rest to staff below")
             ),
    UiAction("next-track",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Next staff or voice"),
             QT_TRANSLATE_NOOP("action", "Next staff or voice")
             ),
    UiAction("prev-track",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Previous staff or voice"),
             QT_TRANSLATE_NOOP("action", "Previous staff or voice")
             ),
    UiAction("select-next-chord",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Add next chord to selection"),
             QT_TRANSLATE_NOOP("action", "Add next chord to selection")
             ),
    UiAction("select-prev-chord",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Add previous chord to selection"),
             QT_TRANSLATE_NOOP("action", "Add previous chord to selection")
             ),
    UiAction("pitch-up",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Up"),
             QT_TRANSLATE_NOOP("action", "Pitch up or move text or articulation up")
             ),
    UiAction("pitch-down",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Down"),
             QT_TRANSLATE_NOOP("action", "Pitch down or move text or articulation down")
             ),
    UiAction("pitch-down-octave",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Down octave"),
             QT_TRANSLATE_NOOP("action", "Pitch down by an octave or move text or articulation down")
             ),
    UiAction("pitch-up-octave",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Up octave"),
             QT_TRANSLATE_NOOP("action", "Pitch up by an octave or move text or articulation up")
             ),
    UiAction("double-duration",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Double duration"),
             QT_TRANSLATE_NOOP("action", "Double duration")
             ),
    UiAction("half-duration",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Half duration"),
             QT_TRANSLATE_NOOP("action", "Half duration")
             ),
    UiAction("inc-duration-dotted",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Increase duration dotted"),
             QT_TRANSLATE_NOOP("action", "Increase duration dotted")
             ),
    UiAction("dec-duration-dotted",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Decrease duration dotted"),
             QT_TRANSLATE_NOOP("action", "Decrease duration dotted")
             ),
    UiAction("cut",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Cut")
             ),
    UiAction("copy",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Copy")
             ),
    UiAction("paste",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Paste")
             ),
    UiAction("paste-half",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Paste half duration"),
             QT_TRANSLATE_NOOP("action", "Paste half duration")
             ),
    UiAction("paste-double",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Paste double duration"),
             QT_TRANSLATE_NOOP("action", "Paste double duration")
             ),
    UiAction("paste-special",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Paste special"),
             QT_TRANSLATE_NOOP("action", "Paste special")
             ),
    UiAction("swap",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Swap with clipboard"),
             QT_TRANSLATE_NOOP("action", "Swap with clipboard")
             ),
    UiAction("toggle-visible",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Toggle visibility of elements"),
             QT_TRANSLATE_NOOP("action", "Toggle visibility of elements")
             ),
    UiAction("select-all",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Select all"),
             QT_TRANSLATE_NOOP("action", "Select all")
             ),
    UiAction("select-section",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Select section"),
             QT_TRANSLATE_NOOP("action", "Select section")
             ),
    UiAction("select-similar",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Select: similar"),
             QT_TRANSLATE_NOOP("action", "Select all similar elements")
             ),
    UiAction("select-similar-staff",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Select: in same staff"),
             QT_TRANSLATE_NOOP("action", "Select all similar elements in same staff")
             ),
    UiAction("select-similar-range",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Select: in the range"),
             QT_TRANSLATE_NOOP("action", "Select all similar elements in the range selection")
             ),
    UiAction("select-dialog",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Select dialog"),
             QT_TRANSLATE_NOOP("action", "Select all similar elements with more options")
             ),
    UiAction("delete",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Delete"),
             QT_TRANSLATE_NOOP("action", "Delete the selected element(s)"),
             IconCode::Code::DELETE_TANK
             ),
    UiAction("edit-style",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Style…"),
             QT_TRANSLATE_NOOP("action", "Edit style")
             ),
    UiAction("page-settings",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Page settings…"),
             QT_TRANSLATE_NOOP("action", "Page settings")
             ),
    UiAction("load-style",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Load style…"),
             QT_TRANSLATE_NOOP("action", "Load style")
             ),
    UiAction("transpose",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "&Transpose…"),
             QT_TRANSLATE_NOOP("action", "Transpose")
             ),
    UiAction("explode",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Explode"),
             QT_TRANSLATE_NOOP("action", "Explode contents of top selected staff into staves below")
             ),
    UiAction("implode",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Implode"),
             QT_TRANSLATE_NOOP("action", "Implode contents of selected staves into top selected staff")
             ),
    UiAction("realize-chord-symbols",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Realize chord symbols"),
             QT_TRANSLATE_NOOP("action", "Convert chord symbols into notes")
             ),
    UiAction("time-delete",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Remove selected range"),
             QT_TRANSLATE_NOOP("action", "Remove selected range")
             ),
    UiAction("slash-fill",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fill with slashes"),
             QT_TRANSLATE_NOOP("action", "Fill with slashes")
             ),
    UiAction("slash-rhythm",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Toggle rhythmic slash notation"),
             QT_TRANSLATE_NOOP("action", "Toggle 'rhythmic slash notation'")
             ),
    UiAction("pitch-spell",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Respell pitches"),
             QT_TRANSLATE_NOOP("action", "Respell pitches")
             ),
    UiAction("reset-groupings",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Regroup rhythms"),
             QT_TRANSLATE_NOOP("action", "Combine rests and tied notes from selection and resplit at rhythmical boundaries")
             ),
    UiAction("resequence-rehearsal-marks",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Resequence rehearsal marks"),
             QT_TRANSLATE_NOOP("action", "Resequence rehearsal marks")
             ),
    UiAction("unroll-repeats",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Unroll repeats"),
             QT_TRANSLATE_NOOP("action", "Unroll repeats")
             ),
    UiAction("copy-lyrics-to-clipboard",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Copy lyrics to clipboard"),
             QT_TRANSLATE_NOOP("action", "Copy lyrics to clipboard")
             ),
    UiAction("del-empty-measures",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Remove empty trailing measures"),
             QT_TRANSLATE_NOOP("action", "Remove empty trailing measures")
             ),
    UiAction("parts",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Parts"),
             QT_TRANSLATE_NOOP("action", "Manage parts"),
             IconCode::Code::PAGE
             ),
    UiAction("view-mode-page",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Page View"),
             IconCode::Code::PAGE_VIEW
             ),
    UiAction("view-mode-continuous",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Continuous view (horizontal)"),
             IconCode::Code::CONTINUOUS_VIEW
             ),
    UiAction("view-mode-single",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Continuous view (vertical)"),
             IconCode::Code::CONTINUOUS_VIEW_VERTICAL
             ),
    UiAction("find",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Find / Go To")
             ),
    UiAction("staff-properties",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Staff/part properties…"),
             QT_TRANSLATE_NOOP("action", "Staff/part properties")
             ),
    UiAction("staff-text-properties",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Staff text Properties…"),
             QT_TRANSLATE_NOOP("action", "Staff text properties")
             ),
    UiAction("system-text-properties",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "System text properties…"),
             QT_TRANSLATE_NOOP("action", "System text properties")
             ),
    UiAction("measure-properties",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Measure properties…"),
             QT_TRANSLATE_NOOP("action", "Measure properties")
             ),
    UiAction("add-remove-breaks",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Add/remove system breaks…"),
             QT_TRANSLATE_NOOP("action", "Add/remove system breaks")
             ),
    UiAction("edit-info",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Score properties…"),
             QT_TRANSLATE_NOOP("action", "Edit score properties")
             ),
    UiAction("undo",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Undo"),
             QT_TRANSLATE_NOOP("action", "Undo last change"),
             IconCode::Code::UNDO
             ),
    UiAction("redo",
             mu::context::UiCtxNotationFocused,
             QT_TRANSLATE_NOOP("action", "Redo"),
             QT_TRANSLATE_NOOP("action", "Redo last undo"),
             IconCode::Code::REDO
             ),
    UiAction("voice-x12",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Exchange voice 1-2"),
             QT_TRANSLATE_NOOP("action", "Exchange voice 1-2")
             ),
    UiAction("voice-x13",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Exchange voice 1-3"),
             QT_TRANSLATE_NOOP("action", "Exchange voice 1-3")
             ),
    UiAction("voice-x14",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Exchange voice 1-4"),
             QT_TRANSLATE_NOOP("action", "Exchange voice 1-4")
             ),
    UiAction("voice-x23",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Exchange voice 2-3"),
             QT_TRANSLATE_NOOP("action", "Exchange voice 2-3")
             ),
    UiAction("voice-x24",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Exchange voice 2-4"),
             QT_TRANSLATE_NOOP("action", "Exchange voice 2-4")
             ),
    UiAction("voice-x34",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Exchange voice 3-4"),
             QT_TRANSLATE_NOOP("action", "Exchange voice 3-4")
             ),
    UiAction("system-break",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Toggle system break"),
             QT_TRANSLATE_NOOP("action", "Toggle 'system break'")
             ),
    UiAction("page-break",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Toggle page break"),
             QT_TRANSLATE_NOOP("action", "Toggle 'page break'")
             ),
    UiAction("section-break",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Toggle section break"),
             QT_TRANSLATE_NOOP("action", "Toggle 'section break'")
             ),
    UiAction("split-measure",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Split measure before selected note/rest"),
             QT_TRANSLATE_NOOP("action", "Split measure before selected note/rest")
             ),
    UiAction("join-measures",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Join selected measures"),
             QT_TRANSLATE_NOOP("action", "Join selected measures")
             ),
    UiAction("insert-measure",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Insert one measure"),
             QT_TRANSLATE_NOOP("action", "Insert one measure")
             ),
    UiAction("insert-measures",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Insert measures"),
             QT_TRANSLATE_NOOP("action", "Insert measures")
             ),
    UiAction("append-measure",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Append one measure"),
             QT_TRANSLATE_NOOP("action", "Append one measure")
             ),
    UiAction("append-measures",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Append measures"),
             QT_TRANSLATE_NOOP("action", "Append measures")
             ),
    UiAction("insert-hbox",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Insert horizontal frame"),
             QT_TRANSLATE_NOOP("action", "Insert horizontal frame"),
             IconCode::Code::HORIZONTAL_FRAME
             ),
    UiAction("insert-vbox",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Insert vertical frame"),
             QT_TRANSLATE_NOOP("action", "Insert vertical frame"),
             IconCode::Code::VERTICAL_FRAME
             ),
    UiAction("insert-textframe",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Insert text frame"),
             QT_TRANSLATE_NOOP("action", "Insert text frame"),
             IconCode::Code::TEXT_FRAME
             ),
    UiAction("append-hbox",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Append horizontal frame"),
             QT_TRANSLATE_NOOP("action", "Append horizontal frame")
             ),
    UiAction("append-vbox",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Append vertical frame"),
             QT_TRANSLATE_NOOP("action", "Append vertical frame")
             ),
    UiAction("append-textframe",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Append text frame"),
             QT_TRANSLATE_NOOP("action", "Append text frame")
             ),
    UiAction("acciaccatura",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Acciaccatura")
             ),
    UiAction("appoggiatura",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Appoggiatura")
             ),
    UiAction("grace4",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Grace: quarter")
             ),
    UiAction("grace16",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Grace: 16th")
             ),
    UiAction("grace32",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Grace: 32nd")
             ),
    UiAction("grace8after",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Grace: 8th after")
             ),
    UiAction("grace16after",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Grace: 16th after")
             ),
    UiAction("grace32after",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Grace: 32nd after")
             ),
    UiAction("beam-start",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Beam start"),
             QT_TRANSLATE_NOOP("action", "Beam start"),
             IconCode::Code::BEAM_START
             ),
    UiAction("beam-mid",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Beam middle"),
             QT_TRANSLATE_NOOP("action", "Beam middle"),
             IconCode::Code::BEAM_MIDDLE
             ),
    UiAction("no-beam",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "No beam"),
             QT_TRANSLATE_NOOP("action", "No beam"),
             IconCode::Code::NOTE_HEAD_EIGHTH
             ),
    UiAction("beam-32",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Beam 16th sub"),
             QT_TRANSLATE_NOOP("action", "Beam 16th sub"),
             IconCode::Code::BEAM_32
             ),
    UiAction("beam-64",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Beam 32nd sub"),
             QT_TRANSLATE_NOOP("action", "Beam 32nd sub"),
             IconCode::Code::BEAM_64
             ),
    UiAction("auto-beam",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Auto beam"),
             QT_TRANSLATE_NOOP("action", "Auto beam"),
             IconCode::Code::AUTO_TEXT
             ),
    UiAction("add-brackets",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Add brackets to accidental"),
             QT_TRANSLATE_NOOP("action", "Add brackets to accidental"),
             IconCode::Code::BRACKET
             ),
    UiAction("add-braces",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Add braces to element"),
             QT_TRANSLATE_NOOP("action", "Add braces to element"),
             IconCode::Code::BRACE
             ),
    UiAction("add-parentheses",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Add parentheses to element"),
             QT_TRANSLATE_NOOP("action", "Add parentheses to element"),
             IconCode::Code::BRACKET_PARENTHESES
             ),
    UiAction("interval1",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Unison above"),
             QT_TRANSLATE_NOOP("action", "Enter unison above")
             ),
    UiAction("interval2",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Second above"),
             QT_TRANSLATE_NOOP("action", "Enter second above")
             ),
    UiAction("interval3",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Third above"),
             QT_TRANSLATE_NOOP("action", "Enter third above")
             ),
    UiAction("interval4",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fourth above"),
             QT_TRANSLATE_NOOP("action", "Enter fourth above")
             ),
    UiAction("interval5",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fifth above"),
             QT_TRANSLATE_NOOP("action", "Enter fifth above")
             ),
    UiAction("interval6",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Sixth above"),
             QT_TRANSLATE_NOOP("action", "Enter sixth above")
             ),
    UiAction("interval7",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Seventh above"),
             QT_TRANSLATE_NOOP("action", "Enter seventh above")
             ),
    UiAction("interval8",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Octave above"),
             QT_TRANSLATE_NOOP("action", "Enter octave above")
             ),
    UiAction("interval9",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Ninth above"),
             QT_TRANSLATE_NOOP("action", "Enter ninth above")
             ),
    UiAction("interval-2",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Second below"),
             QT_TRANSLATE_NOOP("action", "Enter second below")
             ),
    UiAction("interval-3",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Third below"),
             QT_TRANSLATE_NOOP("action", "Enter third below")
             ),
    UiAction("interval-4",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fourth below"),
             QT_TRANSLATE_NOOP("action", "Enter fourth below")
             ),
    UiAction("interval-5",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fifth below"),
             QT_TRANSLATE_NOOP("action", "Enter fifth below")
             ),
    UiAction("interval-6",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Sixth below"),
             QT_TRANSLATE_NOOP("action", "Enter sixth below")
             ),
    UiAction("interval-7",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Seventh below"),
             QT_TRANSLATE_NOOP("action", "Enter seventh below")
             ),
    UiAction("interval-8",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Octave below"),
             QT_TRANSLATE_NOOP("action", "Enter octave below")
             ),
    UiAction("interval-9",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Ninth below"),
             QT_TRANSLATE_NOOP("action", "Enter ninth below")
             ),
    UiAction("note-c",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "C"),
             QT_TRANSLATE_NOOP("action", "Enter note C")
             ),
    UiAction("note-d",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "D"),
             QT_TRANSLATE_NOOP("action", "Enter note D")
             ),
    UiAction("note-e",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "E"),
             QT_TRANSLATE_NOOP("action", "Enter note E")
             ),
    UiAction("note-f",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "F"),
             QT_TRANSLATE_NOOP("action", "Enter note F")
             ),
    UiAction("note-g",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "G"),
             QT_TRANSLATE_NOOP("action", "Enter note G")
             ),
    UiAction("note-a",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "A"),
             QT_TRANSLATE_NOOP("action", "Enter note A")
             ),
    UiAction("note-b",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "B"),
             QT_TRANSLATE_NOOP("action", "Enter note B")
             ),
    UiAction("chord-c",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Add C to chord"),
             QT_TRANSLATE_NOOP("action", "Add note C to chord")
             ),
    UiAction("chord-d",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Add D to chord"),
             QT_TRANSLATE_NOOP("action", "Add note D to chord")
             ),
    UiAction("chord-e",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Add E to chord"),
             QT_TRANSLATE_NOOP("action", "Add note E to chord")
             ),
    UiAction("chord-f",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Add F to chord"),
             QT_TRANSLATE_NOOP("action", "Add note F to chord")
             ),
    UiAction("chord-g",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Add G to chord"),
             QT_TRANSLATE_NOOP("action", "Add note G to chord")
             ),
    UiAction("chord-a",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Add A to chord"),
             QT_TRANSLATE_NOOP("action", "Add note A to chord")
             ),
    UiAction("chord-b",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Add B to chord"),
             QT_TRANSLATE_NOOP("action", "Add note B to chord")
             ),
    UiAction("insert-c",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Insert C"),
             QT_TRANSLATE_NOOP("action", "Insert note C")
             ),
    UiAction("insert-d",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Insert D"),
             QT_TRANSLATE_NOOP("action", "Insert note D")
             ),
    UiAction("insert-e",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Insert E"),
             QT_TRANSLATE_NOOP("action", "Insert note E")
             ),
    UiAction("insert-f",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Insert F"),
             QT_TRANSLATE_NOOP("action", "Insert note F")
             ),
    UiAction("insert-g",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Insert G"),
             QT_TRANSLATE_NOOP("action", "Insert note G")
             ),
    UiAction("insert-a",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Insert A"),
             QT_TRANSLATE_NOOP("action", "Insert note A")
             ),
    UiAction("insert-b",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Insert B"),
             QT_TRANSLATE_NOOP("action", "Insert note B")
             ),
    UiAction("rest",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Rest"),
             QT_TRANSLATE_NOOP("action", "Enter rest")
             ),
    UiAction("rest-1",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Whole rest"),
             QT_TRANSLATE_NOOP("action", "Note input: Whole rest")
             ),
    UiAction("rest-2",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Half rest"),
             QT_TRANSLATE_NOOP("action", "Note input: Half rest")
             ),
    UiAction("rest-4",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Quarter rest"),
             QT_TRANSLATE_NOOP("action", "Note input: Quarter rest")
             ),
    UiAction("rest-8",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Eighth rest"),
             QT_TRANSLATE_NOOP("action", "Note input: Eighth rest")
             ),
    UiAction("fret-0",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fret 0 (TAB)"),
             QT_TRANSLATE_NOOP("action", "Add fret 0 on current string (TAB only)")
             ),
    UiAction("fret-1",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fret 1 (TAB)"),
             QT_TRANSLATE_NOOP("action", "Add fret 1 on current string (TAB only)")
             ),
    UiAction("fret-2",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fret 2 (TAB)"),
             QT_TRANSLATE_NOOP("action", "Add fret 2 on current string (TAB only)")
             ),
    UiAction("fret-3",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fret 3 (TAB)"),
             QT_TRANSLATE_NOOP("action", "Add fret 3 on current string (TAB only)")
             ),
    UiAction("fret-4",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fret 4 (TAB)"),
             QT_TRANSLATE_NOOP("action", "Add fret 4 on current string (TAB only)")
             ),
    UiAction("fret-5",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fret 5 (TAB)"),
             QT_TRANSLATE_NOOP("action", "Add fret 5 on current string (TAB only)")
             ),
    UiAction("fret-6",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fret 6 (TAB)"),
             QT_TRANSLATE_NOOP("action", "Add fret 6 on current string (TAB only)")
             ),
    UiAction("fret-7",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fret 7 (TAB)"),
             QT_TRANSLATE_NOOP("action", "Add fret 7 on current string (TAB only)")
             ),
    UiAction("fret-8",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fret 8 (TAB)"),
             QT_TRANSLATE_NOOP("action", "Add fret 8 on current string (TAB only)")
             ),
    UiAction("fret-9",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fret 9 (TAB)"),
             QT_TRANSLATE_NOOP("action", "Add fret 9 on current string (TAB only)")
             ),
    UiAction("fret-10",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fret 10 (TAB)"),
             QT_TRANSLATE_NOOP("action", "Add fret 10 on current string (TAB only)")
             ),
    UiAction("fret-11",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fret 11 (TAB)"),
             QT_TRANSLATE_NOOP("action", "Add fret 11 on current string (TAB only)")
             ),
    UiAction("fret-12",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fret 12 (TAB)"),
             QT_TRANSLATE_NOOP("action", "Add fret 12 on current string (TAB only)")
             ),
    UiAction("fret-13",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fret 13 (TAB)"),
             QT_TRANSLATE_NOOP("action", "Add fret 13 on current string (TAB only)")
             ),
    UiAction("fret-14",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fret 14 (TAB)"),
             QT_TRANSLATE_NOOP("action", "Add fret 14 on current string (TAB only)")
             ),
    UiAction("add-8va",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Ottava 8va alta"),
             QT_TRANSLATE_NOOP("action", "Add ottava 8va alta")
             ),
    UiAction("add-8vb",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Ottava 8va bassa"),
             QT_TRANSLATE_NOOP("action", "Add ottava 8va bassa")
             ),
    UiAction("add-hairpin",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Crescendo"),
             QT_TRANSLATE_NOOP("action", "Add crescendo")
             ),
    UiAction("add-hairpin-reverse",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Decrescendo"),
             QT_TRANSLATE_NOOP("action", "Add decrescendo")
             ),
    UiAction("add-noteline",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Note anchored line"),
             QT_TRANSLATE_NOOP("action", "Note anchored line")
             ),
    UiAction("chord-tie",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Add tied note to chord"),
             QT_TRANSLATE_NOOP("action", "Add tied note to chord")
             ),
    UiAction("title-text",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Title"),
             QT_TRANSLATE_NOOP("action", "Add title text")
             ),
    UiAction("subtitle-text",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Subtitle"),
             QT_TRANSLATE_NOOP("action", "Add subtitle text")
             ),
    UiAction("composer-text",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Composer"),
             QT_TRANSLATE_NOOP("action", "Add composer text")
             ),
    UiAction("poet-text",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Lyricist"),
             QT_TRANSLATE_NOOP("action", "Add lyricist text")
             ),
    UiAction("part-text",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Part name"),
             QT_TRANSLATE_NOOP("action", "Add part name")
             ),
    UiAction("system-text",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "System text"),
             QT_TRANSLATE_NOOP("action", "Add system text")
             ),
    UiAction("staff-text",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Staff text"),
             QT_TRANSLATE_NOOP("action", "Add staff text")
             ),
    UiAction("expression-text",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Expression text"),
             QT_TRANSLATE_NOOP("action", "Add expression text")
             ),
    UiAction("rehearsalmark-text",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Rehearsal mark"),
             QT_TRANSLATE_NOOP("action", "Add rehearsal mark")
             ),
    UiAction("instrument-change-text",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Instrument change"),
             QT_TRANSLATE_NOOP("action", "Add instrument change")
             ),
    UiAction("fingering-text",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Fingering"),
             QT_TRANSLATE_NOOP("action", "Add fingering")
             ),
    UiAction("sticking-text",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Sticking"),
             QT_TRANSLATE_NOOP("action", "Add sticking")
             ),
    UiAction("chord-text",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Chord symbol"),
             QT_TRANSLATE_NOOP("action", "Add chord symbol")
             ),
    UiAction("roman-numeral-text",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Roman numeral analysis"),
             QT_TRANSLATE_NOOP("action", "Add roman numeral analysis")
             ),
    UiAction("nashville-number-text",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Nashville number"),
             QT_TRANSLATE_NOOP("action", "Add Nashville number")
             ),
    UiAction("lyrics",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Lyrics"),
             QT_TRANSLATE_NOOP("action", "Add lyrics")
             ),
    UiAction("figured-bass",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Figured bass"),
             QT_TRANSLATE_NOOP("action", "Add figured bass")
             ),
    UiAction("tempo",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Tempo marking"),
             QT_TRANSLATE_NOOP("action", "Add tempo marking")
             ),
    UiAction("duplet",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Duplet"),
             QT_TRANSLATE_NOOP("action", "Add duplet")
             ),
    UiAction("triplet",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Triplet"),
             QT_TRANSLATE_NOOP("action", "Add triplet")
             ),
    UiAction("quadruplet",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Quadruplet"),
             QT_TRANSLATE_NOOP("action", "Add quadruplet")
             ),
    UiAction("quintuplet",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Quintuplet"),
             QT_TRANSLATE_NOOP("action", "Add quintuplet")
             ),
    UiAction("sextuplet",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Sextuplet"),
             QT_TRANSLATE_NOOP("action", "Add sextuplet")
             ),
    UiAction("septuplet",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Septuplet"),
             QT_TRANSLATE_NOOP("action", "Add septuplet")
             ),
    UiAction("octuplet",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Octuplet"),
             QT_TRANSLATE_NOOP("action", "Add octuplet")
             ),
    UiAction("nonuplet",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Nontuplet"),
             QT_TRANSLATE_NOOP("action", "Add nontuplet")
             ),
    UiAction("tuplet-dialog",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Other…"),
             QT_TRANSLATE_NOOP("action", "Other tuplets")
             ),
    UiAction("stretch-",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Increase layout stretch"),
             QT_TRANSLATE_NOOP("action", "Increase layout stretch factor of selected measures")
             ),
    UiAction("stretch+",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Decrease layout stretch"),
             QT_TRANSLATE_NOOP("action", "Decrease layout stretch factor of selected measures")
             ),
    UiAction("reset-stretch",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Reset layout stretch"),
             QT_TRANSLATE_NOOP("action", "Reset layout stretch factor of selected measures or entire score")
             ),
    UiAction("reset-text-style-overrides",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Reset text style overrides"),
             QT_TRANSLATE_NOOP("action", "Reset all text style overrides to default")
             ),
    UiAction("reset-beammode",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Reset beams"),
             QT_TRANSLATE_NOOP("action", "Reset beams of selected measures")
             ),
    UiAction("reset",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Reset shapes and positions"),
             QT_TRANSLATE_NOOP("action", "Reset shapes and positions of selected elements to their defaults")
             ),
    UiAction("zoomin",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Zoom in"),
             QT_TRANSLATE_NOOP("action", "Zoom in")
             ),
    UiAction("zoomout",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Zoom out"),
             QT_TRANSLATE_NOOP("action", "Zoom out")
             )
};

const UiActionList NotationUiActions::m_noteInputActions = {
    UiAction(NOTE_INPUT_ACTION_CODE,
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Note input"),
             QT_TRANSLATE_NOOP("action", "Enter notes with a mouse or keyboard"),
             IconCode::Code::EDIT,
             Checkable::Yes
             ),
    UiAction("note-input-steptime",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Default (step time)"),
             QT_TRANSLATE_NOOP("action", "Enter notes with a mouse or keyboard"),
             IconCode::Code::EDIT
             ),
    UiAction("note-input-rhythm",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Rhythm only (not pitch)"),
             QT_TRANSLATE_NOOP("action", "Enter durations with a single click or keypress"),
             IconCode::Code::RHYTHM_ONLY
             ),
    UiAction("note-input-repitch",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Re-pitch existing notes"),
             QT_TRANSLATE_NOOP("action", "Replace pitches without changing rhythms"),
             IconCode::Code::RE_PITH
             ),
    UiAction("note-input-realtime-auto",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Real-time (metronome)"),
             QT_TRANSLATE_NOOP("action", "Enter notes at a fixed tempo indicated by a metronome beat"),
             IconCode::Code::METRONOME
             ),
    UiAction("note-input-realtime-manual",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Real-time (foot pedal)"),
             QT_TRANSLATE_NOOP("action", "Enter notes while tapping a key or pedal to set the tempo"),
             IconCode::Code::FOOT_PEDAL
             ),
    UiAction("note-input-timewise",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Insert"),
             QT_TRANSLATE_NOOP("action", "Insert notes by increasing measure duration"),
             IconCode::Code::NOTE_PLUS
             ),
    UiAction("note-longa",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Longa"),
             QT_TRANSLATE_NOOP("action", "Note duration: Longa"),
             IconCode::Code::LONGO
             ),
    UiAction("note-breve",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Double whole note"),
             QT_TRANSLATE_NOOP("action", "Note duration: double whole note"),
             IconCode::Code::NOTE_WHOLE_DOUBLE
             ),
    UiAction("pad-note-1",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Whole note"),
             QT_TRANSLATE_NOOP("action", "Note duration: whole note"),
             IconCode::Code::NOTE_WHOLE
             ),
    UiAction("pad-note-2",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Half note"),
             QT_TRANSLATE_NOOP("action", "Note duration: half note"),
             IconCode::Code::NOTE_HALF
             ),
    UiAction("pad-note-4",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Quarter note"),
             QT_TRANSLATE_NOOP("action", "Note duration: quarter note"),
             IconCode::Code::NOTE_QUARTER
             ),
    UiAction("pad-note-8",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "8th note"),
             QT_TRANSLATE_NOOP("action", "Note duration: 8th note"),
             IconCode::Code::NOTE_8TH
             ),
    UiAction("pad-note-16",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "16th note"),
             QT_TRANSLATE_NOOP("action", "Note duration: 16th note"),
             IconCode::Code::NOTE_16TH
             ),
    UiAction("pad-note-32",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "32nd note"),
             QT_TRANSLATE_NOOP("action", "Note duration: 32nd note"),
             IconCode::Code::NOTE_32ND
             ),
    UiAction("pad-note-64",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "64th note"),
             QT_TRANSLATE_NOOP("action", "Note duration: 64th note"),
             IconCode::Code::NOTE_64TH
             ),
    UiAction("pad-note-128",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "128th note"),
             QT_TRANSLATE_NOOP("action", "Note duration: 128th note"),
             IconCode::Code::NOTE_128TH
             ),
    UiAction("pad-note-256",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "256th note"),
             QT_TRANSLATE_NOOP("action", "Note duration: 256th note"),
             IconCode::Code::NOTE_256TH
             ),
    UiAction("pad-note-512",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "512th note"),
             QT_TRANSLATE_NOOP("action", "Note duration: 512th note"),
             IconCode::Code::NOTE_512TH
             ),
    UiAction("pad-note-1024",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "1024th note"),
             QT_TRANSLATE_NOOP("action", "Note duration: 1024th note"),
             IconCode::Code::NOTE_1024TH
             ),
    UiAction("pad-dot",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Augmentation dot"),
             QT_TRANSLATE_NOOP("action", "Note duration: augmentation dot"),
             IconCode::Code::NOTE_DOTTED
             ),
    UiAction("pad-dotdot",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Double augmentation dot"),
             QT_TRANSLATE_NOOP("action", "Note duration: double augmentation dot"),
             IconCode::Code::NOTE_DOTTED_2
             ),
    UiAction("pad-dot3",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Triple augmentation dot"),
             QT_TRANSLATE_NOOP("action", "Note duration: triple augmentation dot"),
             IconCode::Code::NOTE_DOTTED_3
             ),
    UiAction("pad-dot4",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Quadruple augmentation dot"),
             QT_TRANSLATE_NOOP("action", "Note duration: quadruple augmentation dot"),
             IconCode::Code::NOTE_DOTTED_4
             ),
    UiAction("pad-rest",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Rest"),
             QT_TRANSLATE_NOOP("action", "Note input: rest"),
             IconCode::Code::REST
             ),
    UiAction("flat",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "♭"),
             QT_TRANSLATE_NOOP("action", "Note input: ♭"),
             IconCode::Code::FLAT
             ),
    UiAction("flat2",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Double ♭"),
             QT_TRANSLATE_NOOP("action", "Note input: Double ♭"),
             IconCode::Code::FLAT_DOUBLE
             ),
    UiAction("nat",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "♮"),
             QT_TRANSLATE_NOOP("action", "Note input: ♮"),
             IconCode::Code::NATURAL
             ),
    UiAction("sharp",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "♯"),
             QT_TRANSLATE_NOOP("action", "Note input: ♯"),
             IconCode::Code::SHARP
             ),
    UiAction("sharp2",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Double ♯"),
             QT_TRANSLATE_NOOP("action", "Note input: Double ♯"),
             IconCode::Code::SHARP_DOUBLE
             ),
    UiAction("tie",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Tie"),
             QT_TRANSLATE_NOOP("action", "Note duration: Tie"),
             IconCode::Code::NOTE_TIE
             ),
    UiAction("add-slur",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Slur"),
             QT_TRANSLATE_NOOP("action", "Add slur"),
             IconCode::Code::NOTE_SLUR
             ),
    UiAction("add-marcato",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Marcato"),
             QT_TRANSLATE_NOOP("action", "Toggle marcato"),
             IconCode::Code::MARCATO
             ),
    UiAction("add-sforzato",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Accent"),
             QT_TRANSLATE_NOOP("action", "Toggle accent"),
             IconCode::Code::ACCENT
             ),
    UiAction("add-tenuto",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Tenuto"),
             QT_TRANSLATE_NOOP("action", "Toggle tenuto"),
             IconCode::Code::TENUTO
             ),
    UiAction("add-staccato",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Staccato"),
             QT_TRANSLATE_NOOP("action", "Toggle staccato"),
             IconCode::Code::STACCATO
             ),
    UiAction("tuplet",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Tuplet"),
             QT_TRANSLATE_NOOP("action", "Add tuplet"),
             IconCode::Code::NOTE_TUPLET
             ),
    UiAction("voice-1",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Voice 1"),
             QT_TRANSLATE_NOOP("action", "Voice 1"),
             IconCode::Code::VOICE_1
             ),
    UiAction("voice-2",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Voice 2"),
             QT_TRANSLATE_NOOP("action", "Voice 2"),
             IconCode::Code::VOICE_2
             ),
    UiAction("voice-3",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Voice 3"),
             QT_TRANSLATE_NOOP("action", "Voice 3"),
             IconCode::Code::VOICE_3
             ),
    UiAction("voice-4",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Voice 4"),
             QT_TRANSLATE_NOOP("action", "Voice 4"),
             IconCode::Code::VOICE_4
             ),
    UiAction("enh-both",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Change enharmonic spelling (both modes)"),
             QT_TRANSLATE_NOOP("action", "Change enharmonic spelling (both modes)"),
             IconCode::Code::NONE
             ),
    UiAction("enh-current",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Change enharmonic spelling (both modes)"),
             QT_TRANSLATE_NOOP("action", "Change enharmonic spelling (current mode)"),
             IconCode::Code::NONE
             ),
    UiAction("flip",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Flip direction"),
             QT_TRANSLATE_NOOP("action", "Flip direction"),
             IconCode::Code::NOTE_FLIP
             ),
    UiAction(TOGGLE_CONCERT_PITCH_CODE,
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Concert pitch"),
             QT_TRANSLATE_NOOP("action", "Toggle 'Concert pitch'"),
             IconCode::Code::TUNING_FORK,
             Checkable::Yes
             ),
    UiAction("print",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Print"),
             QT_TRANSLATE_NOOP("action", "Print score/part"),
             IconCode::Code::PRINT
             ),
    UiAction("toggle-imagecapture",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Image capture"),
             QT_TRANSLATE_NOOP("action", "Toggle 'Image capture' mode"),
             IconCode::Code::CAMERA
             )
};

const UiActionList NotationUiActions::m_scoreConfigActions = {
    UiAction(SHOW_INVISIBLE_CODE,
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Show invisible"),
             QT_TRANSLATE_NOOP("action", "Show invisible"),
             Checkable::Yes
             ),
    UiAction(SHOW_UNPRINTABLE_CODE,
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Show formatting"),
             QT_TRANSLATE_NOOP("action", "Show formatting"),
             Checkable::Yes
             ),
    UiAction(SHOW_FRAMES_CODE,
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Show frames"),
             QT_TRANSLATE_NOOP("action", "Show frames"),
             Checkable::Yes
             ),
    UiAction(SHOW_PAGEBORDERS_CODE,
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Show page margins"),
             QT_TRANSLATE_NOOP("action", "Show page margins"),
             Checkable::Yes
             ),
    UiAction(SHOW_IRREGULAR_CODE,
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Mark irregular measures"),
             QT_TRANSLATE_NOOP("action", "Mark irregular measures"),
             Checkable::Yes
             ),
    UiAction("split-h",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Documents side by side"),
             QT_TRANSLATE_NOOP("action", "Display documents side by side"),
             Checkable::Yes
             ),
    UiAction("split-v",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Documents stacked"),
             QT_TRANSLATE_NOOP("action", "Display documents stacked"),
             Checkable::Yes
             ),
    UiAction("next-lyric",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Next lyric"),
             QT_TRANSLATE_NOOP("action", "Move to lyric on next note"),
             Checkable::Yes
             ),
    UiAction("prev-lyric",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Previous lyric"),
             QT_TRANSLATE_NOOP("action", "Move to lyric on previous note"),
             Checkable::Yes
             ),
    UiAction("next-lyric-verse",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Next lyric verse"),
             QT_TRANSLATE_NOOP("action", "Move to lyric in the next verse"),
             Checkable::Yes
             ),
    UiAction("prev-lyric-verse",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Previous lyric verse"),
             QT_TRANSLATE_NOOP("action", "Move to lyric in the previous verse"),
             Checkable::Yes
             ),
    UiAction("next-syllable",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Next syllable"),
             QT_TRANSLATE_NOOP("action", "Add hyphen and move to lyric on next note"),
             Checkable::Yes
             ),
    UiAction("add-melisma",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Add melisma"),
             QT_TRANSLATE_NOOP("action", "Add melisma line and move to lyric on next note"),
             Checkable::Yes
             ),
    UiAction("add-lyric-verse",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Add lyric verse"),
             QT_TRANSLATE_NOOP("action", "Adds a new verse and starts editing"),
             Checkable::Yes
             ),
    UiAction("text-b",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Bold face"),
             QT_TRANSLATE_NOOP("action", "Bold face"),
             Checkable::Yes
             ),
    UiAction("text-i",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Italic"),
             QT_TRANSLATE_NOOP("action", "Italic"),
             Checkable::Yes
             ),
    UiAction("text-u",
             mu::context::UiCtxNotationOpened,
             QT_TRANSLATE_NOOP("action", "Underline"),
             QT_TRANSLATE_NOOP("action", "Underline"),
             Checkable::Yes
             )
};

NotationUiActions::NotationUiActions(std::shared_ptr<NotationActionController> controller)
    : m_controller(controller)
{
}

void NotationUiActions::init()
{
    m_controller->currentNotationNoteInputChanged().onNotify(this, [this]() {
        m_actionCheckedChanged.send({ NOTE_INPUT_ACTION_CODE });
    });

    m_controller->currentNotationChanged().onNotify(this, [this]() {
        actions::ActionCodeList actions;
        for (const UiAction& action : m_scoreConfigActions) {
            actions.push_back(action.code);
        }
        m_actionCheckedChanged.send(actions);

        if (m_controller->currentNotationInteraction()) {
            m_controller->currentNotationInteraction()->scoreConfigChanged().onReceive(this, [this](ScoreConfigType configType) {
                static const std::unordered_map<ScoreConfigType, std::string> configActions = {
                    { ScoreConfigType::ShowInvisibleElements, SHOW_INVISIBLE_CODE },
                    { ScoreConfigType::ShowUnprintableElements, SHOW_UNPRINTABLE_CODE },
                    { ScoreConfigType::ShowFrames, SHOW_FRAMES_CODE },
                    { ScoreConfigType::ShowPageMargins, SHOW_PAGEBORDERS_CODE },
                    { ScoreConfigType::MarkIrregularMeasures, SHOW_IRREGULAR_CODE }
                };

                m_actionCheckedChanged.send({ configActions.at(configType) });
            });
        }
        m_controller->currentNotationStyleChanged().onNotify(this, [this]() {
            m_actionCheckedChanged.send({ TOGGLE_CONCERT_PITCH_CODE });
        });
    });
}

const UiActionList& NotationUiActions::actionsList() const
{
    static UiActionList alist;
    if (alist.empty()) {
        alist.insert(alist.end(), m_actions.begin(), m_actions.end());
        alist.insert(alist.end(), m_noteInputActions.begin(), m_noteInputActions.end());
        alist.insert(alist.end(), m_scoreConfigActions.begin(), m_scoreConfigActions.end());
    }
    return alist;
}

bool NotationUiActions::actionEnabled(const UiAction& act) const
{
    if (!m_controller->canReceiveAction(act.code)) {
        return false;
    }

    return true;
}

bool NotationUiActions::isScoreConfigAction(const actions::ActionCode& code) const
{
    for (const UiAction& a : m_scoreConfigActions) {
        if (a.code == code) {
            return true;
        }
    }
    return false;
}

bool NotationUiActions::isScoreConfigChecked(const actions::ActionCode& code, const ScoreConfig& cfg) const
{
    if (SHOW_INVISIBLE_CODE == code) {
        return cfg.isShowInvisibleElements;
    }
    if (SHOW_UNPRINTABLE_CODE == code) {
        return cfg.isShowUnprintableElements;
    }
    if (SHOW_FRAMES_CODE == code) {
        return cfg.isShowFrames;
    }
    if (SHOW_PAGEBORDERS_CODE == code) {
        return cfg.isShowPageMargins;
    }
    if (SHOW_IRREGULAR_CODE == code) {
        return cfg.isMarkIrregularMeasures;
    }

    return false;
}

bool NotationUiActions::actionChecked(const UiAction& act) const
{
    if (act.code == NOTE_INPUT_ACTION_CODE) {
        auto noteInput = m_controller->currentNotationNoteInput();
        if (noteInput) {
            return noteInput->isNoteInputMode();
        }
    }

    if (act.code == TOGGLE_CONCERT_PITCH_CODE) {
        auto style = m_controller->currentNotationStyle();
        if (style) {
            return style->styleValue(StyleId::concertPitch).toBool();
        }
    }

    if (isScoreConfigAction(act.code)) {
        auto interaction = m_controller->currentNotationInteraction();
        if (interaction) {
            return isScoreConfigChecked(act.code, interaction->scoreConfig());
        }
    }

    return false;
}

mu::async::Channel<mu::actions::ActionCodeList> NotationUiActions::actionEnabledChanged() const
{
    return m_actionEnabledChanged;
}

mu::async::Channel<mu::actions::ActionCodeList> NotationUiActions::actionCheckedChanged() const
{
    return m_actionCheckedChanged;
}

UiActionList NotationUiActions::defaultNoteInputActions()
{
    return m_noteInputActions;
}

DurationType NotationUiActions::actionDurationType(const ActionCode& actionCode)
{
    static QMap<actions::ActionCode, DurationType> durations = {
        { "note-longa", DurationType::V_LONG },
        { "note-breve", DurationType::V_BREVE },
        { "pad-note-1", DurationType::V_WHOLE },
        { "pad-note-2", DurationType::V_HALF },
        { "pad-note-4", DurationType::V_QUARTER },
        { "pad-note-8", DurationType::V_EIGHTH },
        { "pad-note-16", DurationType::V_16TH },
        { "pad-note-32", DurationType::V_32ND },
        { "pad-note-64", DurationType::V_64TH },
        { "pad-note-128", DurationType::V_128TH },
        { "pad-note-256", DurationType::V_256TH },
        { "pad-note-512", DurationType::V_512TH },
        { "pad-note-1024", DurationType::V_1024TH }
    };

    DurationType type = DurationType::V_INVALID;
    if (durations.contains(actionCode)) {
        type = durations[actionCode];
    }

    return type;
}

AccidentalType NotationUiActions::actionAccidentalType(const ActionCode& actionCode)
{
    static QMap<actions::ActionCode, AccidentalType> accidentals = {
        { "flat2", AccidentalType::FLAT2 },
        { "flat", AccidentalType::FLAT },
        { "nat", AccidentalType::NATURAL },
        { "sharp", AccidentalType::SHARP },
        { "sharp2", AccidentalType::SHARP2 }
    };

    AccidentalType type = AccidentalType::NONE;
    if (accidentals.contains(actionCode)) {
        type = accidentals[actionCode];
    }

    return type;
}

int NotationUiActions::actionDotCount(const ActionCode& actionCode)
{
    static QMap<actions::ActionCode, int> dots = {
        { "pad-dot", 1 },
        { "pad-dotdot", 2 },
        { "pad-dot3", 3 },
        { "pad-dot4", 4 }
    };

    int dotCount = 0;
    if (dots.contains(actionCode)) {
        dotCount = dots[actionCode];
    }

    return dotCount;
}

int NotationUiActions::actionVoice(const ActionCode& actionCode)
{
    QMap<actions::ActionCode, int> voices {
        { "voice-1", 0 },
        { "voice-2", 1 },
        { "voice-3", 2 },
        { "voice-4", 3 }
    };

    int voice = 0;
    if (voices.contains(actionCode)) {
        voice = voices[actionCode];
    }

    return voice;
}

SymbolId NotationUiActions::actionArticulationSymbolId(const ActionCode& actionCode)
{
    static QMap<actions::ActionCode, SymbolId> articulations {
        { "add-marcato", SymbolId::articMarcatoAbove },
        { "add-sforzato", SymbolId::articAccentAbove },
        { "add-tenuto", SymbolId::articTenutoAbove },
        { "add-staccato", SymbolId::articStaccatoAbove }
    };

    SymbolId symbolId = SymbolId::noSym;
    if (articulations.contains(actionCode)) {
        symbolId = articulations[actionCode];
    }

    return symbolId;
}

const mu::ui::ToolConfig& NotationUiActions::defaultNoteInputBarConfig()
{
    static ToolConfig config;
    if (!config.isValid()) {
        config.items = {
            { "note-input", true },
            { "note-longa", false },
            { "note-breve", false },
            { "pad-note-1", true },
            { "pad-note-2", true },
            { "pad-note-4", true },
            { "pad-note-8", true },
            { "pad-note-16", true },
            { "pad-note-32", true },
            { "pad-note-64", true },
            { "pad-note-128", false },
            { "pad-note-256", false },
            { "pad-note-512", false },
            { "pad-note-1024", false },
            { "", true },
            { "pad-dot", true },
            { "pad-dotdot", false },
            { "pad-dot3", false },
            { "pad-dot4", false },
            { "", true },
            { "pad-rest", true },
            { "", true },
            { "flat2", false },
            { "flat", true },
            { "nat", true },
            { "sharp", true },
            { "sharp2", false },
            { "tie", true },
            { "add-slur", true },
            { "", true },
            { "add-marcato", true },
            { "add-sforzato", true },
            { "add-tenuto", true },
            { "add-staccato", true },
            { "", true },
            { "tuplet", true },
            { "", true },
            { "voice-1", true },
            { "voice-2", false },
            { "voice-3", false },
            { "voice-4", false },
            { "", true },
            { "flip", true }
        };
    }
    return config;
}