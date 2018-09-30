![FINAL CUT](logo/svg/finalcut-logo.svg)
============================================

### Building and code analysis
*Travis CI:*<br />
&#160;&#160;&#160;&#160;&#160;[![Build Status](https://travis-ci.org/gansm/finalcut.svg?branch=master)](https://travis-ci.org/gansm/finalcut) <br />
*Coverity Scan:*<br />
&#160;&#160;&#160;&#160;&#160;[![Coverity Scan Status](https://scan.coverity.com/projects/6508/badge.svg)](https://scan.coverity.com/projects/6508) <br />
*LGTM:*<br />
&#160;&#160;&#160;&#160;&#160;[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/gansm/finalcut.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/gansm/finalcut/context:cpp) <br />
*Class Reference:*<br />
&#160;&#160;&#160;&#160;&#160;[![documented](https://codedocs.xyz/gansm/finalcut.svg)](https://codedocs.xyz/gansm/finalcut/hierarchy.html)

The Final Cut is a C++ class library and widget toolkit with full mouse support for creating a [text-based user interface](https://en.wikipedia.org/wiki/Text-based_user_interface). The library supports the programmer to develop an application for the text console. It allows the simultaneous handling of multiple text windows on the screen.
The C++ class design was inspired by the Qt framework. It provides common controls like dialog boxes, push buttons, check boxes, radio buttons, input lines, list boxes, status bars and so on.

### Installation
```bash
> git clone git://github.com/gansm/finalcut.git
> cd finalcut
> autoreconf --install --force
> ./configure --prefix=/usr
> make
> su -c "make install"
```

### Supported platforms
* Linux
* FreeBSD
* NetBSD
* OpenBSD
* macOS
* Cygwin
* Solaris

### First steps

[How to use the library](doc/first-steps.md)

### Screenshots

The FFileDialog widget:

![FFileDialog](doc/fileopen-dialog.png)


The Final Cut FProgressbar widget:

![FProgressbar](doc/progress-bar.png)


Scrollable text in the FTextView widget:

 ![FTextView](doc/textview.png)


The Mandelbrot set example:

 ![Mandelbrot set](doc/Mandelbrot.png)


newfont
-------
A [graphical text font](fonts/) for X11 and the Linux console.

![ui example in newfont mode](doc/newfont1.png)


Newfont drive symbols:

![drive symbols](doc/newfont2.png)


The calculator example in newfont mode:

![calculator](doc/calculator.png)


Virtual terminal
----------------
It uses a virtual terminal to print the character via an update method on the screen.
The virtual windows are an overlying layer to realizing window movements.
The update method transmits only the changes to the virtual terminal or the screen.

<pre style="line-height: 1 !important;">
 print(...)
printf(...)
  │
  │           ╔═════════════════════════[ vterm ]═════════════════════════╗
  │           ║createVTerm()                                              ║
  │           ║                                 ┌ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┐ ║
  │           ║                                                           ║
  │           ║                                 │ restoreVTerm(x,y,w,h) │ ║
  │           ║                                                           ║
  │           ║                                 └ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┘ ║
  │           ║                                                           ║
  │   ┌───────╨─────[ vwin ]─────────────┐                                ║
  │   │createArea(area)                  │                                ║
  │   │                                  │                                ║
  │   │                                  │                                ║
  └───┼─────────────►     ──────► updateVTerm(area) ────►                 ║
      │                                  │                                ║
      │                           putArea(x,y,area)                       ║
      │                         ────────────────────►                     ║
      │                           getArea(x,y,area)                       ║
      │                        ◄────────────────────                      ║
      │                                  │                                ║
      │                                  │                                ║
      │                  resizeArea(area)│                                ║
      └───────╥──────────────────────────┘                                ║
              ║                                                           ║
              ║                                                           ║
              ║                                                           ║
              ║   │                                          resizeVTerm()║
              ╚═══▼═══════════════════════════════════════════════════════╝
                  │
                  │    putVTerm()
                  └──────────────────► updateTerminalLine(y)
                    updateTerminal()             │
                                                 ▼
                                         ┌───────────────┐
                                         │ output_buffer │
                                         └───────────────┘
                                                 │
                                                 │ flush_out()
                                                 │     +
                                                 │ Fputchar(char)
                                                 │
                                                 ▼
                                         ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
                                         ▌               ▐
                                         ▌    screen     ▐
                                         ▌ ───────────── ▐
                                         ▌ real terminal ▐
                                         ▌               ▐
                                         ▀▀▀▀▀▀▀███▀▀▀▀▀▀▀
                                                ███
                                             ▀▀▀▀▀▀▀▀▀
</pre>


Class digramm
-------------
<pre style="line-height: 1 !important;">
              1┌──────────────┐
   ┌-----------┤ FTermFreeBSD │
   :           └──────────────┘
   :          1┌──────────────┐                 ┌───────────┐
   ┌-----------┤ FTermOpenBSD │            ┌────┤ FKeyEvent │
   :           └──────────────┘            │    └───────────┘
   :          1┌────────────────┐          │    ┌─────────────┐
   ┌-----------┤ FTermDetection │          ├────┤ FMouseEvent │
   :           └────────────────┘          │    └─────────────┘
   :          1┌────────────────┐          │    ┌─────────────┐
   ┌-----------┤ FTermcapQuirks │          ├────┤ FWheelEvent │
   :           └────────────────┘          │    └─────────────┘
   :          1┌────────────────┐          │    ┌─────────────┐
   ┌-----------┤ FTermXTerminal │          ├────┤ FFocusEvent │
   :           └────────────────┘          │    └─────────────┘
   :          1┌──────────┐                │    ┌─────────────┐
   ┌-----------┤ FTermcap │    ┌────────┐  ├────┤ FAccelEvent │
   :           └──────────┘    │ FEvent │◄─┤    └─────────────┘
   :          1┌──────────┐    └───┬────┘  │    ┌──────────────┐
   ┌-----------┤ FTermios │        :1      ├────┤ FResizeEvent │
   :           └──────────┘        :       │    └──────────────┘
   :          1┌───────────────┐   :       │    ┌────────────┐
   ┌-----------┤ FColorPalette │   :       ├────┤ FShowEvent │
   :           └───────────────┘   :       │    └────────────┘
   :          1┌───────────┐       :       │    ┌────────────┐
   ┌-----------┤ FOptiMove │       :       ├────┤ FHideEvent │
   :           └───────────┘       :       │    └────────────┘
   :          1┌───────────┐       :       │    ┌─────────────┐
   ┌-----------┤ FOptiAttr │       :       ├────┤ FCloseEvent │
   :           └───────────┘       :       │    └─────────────┘
   :          1┌───────────┐       :       │    ┌─────────────┐
   ┌-----------┤ FKeyboard │       :       └────┤ FTimerEvent │
   :           └───────────┘       :            └─────────────┘
   :          1┌───────────────┐   :
   ┌-----------┤ FMouseControl │   :            ┌──────────────┐
   :           └───────────────┘   :       ┌────┤ FApplication │
   :          *┌─────────┐         :       │    └──────────────┘
   :  ┌--------┤ FString │         :       │    ┌─────────┐
   :  :        └─────────┘         :       ├────┤ FButton │
   :  :       *┌────────┐          :       │    └─────────┘
   :  ┌--------┤ FPoint │          :       │    ┌────────┐
   :  :        └────────┘          :       ├────┤ FLabel │
   :  :       *┌───────┐           :       │    └────────┘
   :  ┌--------┤ FRect │           :       │    ┌───────────┐
   :  :        └───────┘           :       ├────┤ FLineEdit │
   :1 :1                           :       │    └───────────┘
 ┌─┴──┴──┐    ┌────────┐           :       │    ┌──────────────┐      ┌──────────────┐
 │ FTerm │◄───┤ FVTerm │◄──┐       :1      ├────┤ FButtonGroup │   ┌──┤ FRadioButton │
 └───────┘    └────────┘   │  ┌────┴────┐  │    └──────────────┘   │  └──────────────┘
                           ├──┤ FWidget │◄─┤    ┌───────────────┐  │  ┌───────────┐
             ┌─────────┐   │  └─────────┘  ├────┤ FToggleButton │◄─┼──┤ FCheckBox │
             │ FObject │◄──┘               │    └───────────────┘  │  └───────────┘
             └─────────┘                   │    ┌──────────────┐   │  ┌─────────┐
                                           ├────┤ FProgressbar │   └──┤ FSwitch │
                                           │    └──────────────┘      └─────────┘
                                           │    ┌────────────┐
                                           ├────┤ FScrollbar │
                                           │    └────────────┘
                                           │    ┌───────────┐
                                           ├────┤ FTextView │
                                           │    └───────────┘
                                           │    ┌──────────┐1     *┌──────────────┐
                                           ├────┤ FListBox ├-------┤ FListBoxItem │
                                           │    └──────────┘       └──────────────┘
 ┌─────────────┐1                          │   1┌───────────┐1    *┌───────────────┐
 │ FTermBuffer ├---------------------------├────┤ FListView ├------┤ FListViewItem │
 └─────────────┘                           │    └───────────┘      └───────────────┘
                                           │    ┌─────────────┐
                                           ├────┤ FScrollView │
                                           │    └─────────────┘
                                           │    ┌────────────┐1   *┌────────────┐
                                           │ ┌──┤ FStatusBar ├-----┤ FStatusKey │
                                           │ │  └────────────┘     └────────────┘
                                           │ │
                                           │ ▼                       ┌─────────────┐
                                       ┌───┴─┴───┐  ┌─────────┐   ┌──┤ FFileDialog │
                                       │ FWindow │◄─┤ FDialog │◄──┤  └─────────────┘
                                       └──┬──┬───┘  └─────────┘   │  ┌─────────────┐
                                          ▲  ▲                    └──┤ FMessageBox │
                                          │  │                       └─────────────┘
                                          │  │      ┌──────────┐
                                          │  └──────┤ FToolTip │
                                          │         └──────────┘
                                          └───────────────┐          ┌──────────┐
                                                          │      ┌───┤ FMenuBar │
                                         ┌───────────┐    └──────┤   └──────────┘
                                         │ FMenuList │◄──────────┤   ┌───────┐
                                         └────┬──────┘           └───┤ FMenu │◄──┐
                                             1:                      └───────┘   │
                                              :            ┌─────────────────┐   │
                                              :            │ FDialogListMenu ├───┘
                                              :            └─────────────────┘
                                              └--------------------------------┐
                                              :*          ┌────────────────┐*  :
                                        ┌─────┴─────┐  ┌──┤ FCheckMenuItem ├---┘
                                        │ FMenuItem │◄─┤  └────────────────┘   :
                                        └───────────┘  │  ┌────────────────┐*  :
                                                       └──┤ FRadioMenuItem ├---┘
                                                          └────────────────┘
</pre>

License
-------
GNU Lesser General Public License Version 3 

Please send bug reports to
--------------------------
https://github.com/gansm/finalcut/issues

