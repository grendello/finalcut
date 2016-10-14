// File: fdialog.h
// Provides: class FDialog
//
//  Inheritance diagram
//  ═══════════════════
//
// ▕▔▔▔▔▔▔▔▔▔▏ ▕▔▔▔▔▔▔▔▔▔▏
// ▕ FObject ▏ ▕  FTerm  ▏
// ▕▁▁▁▁▁▁▁▁▁▏ ▕▁▁▁▁▁▁▁▁▁▏
//      ▲           ▲
//      │           │
//      └─────┬─────┘
//            │
//       ▕▔▔▔▔▔▔▔▔▏
//       ▕ FVTerm ▏
//       ▕▁▁▁▁▁▁▁▁▏
//            ▲
//            │
//       ▕▔▔▔▔▔▔▔▔▔▏
//       ▕ FWidget ▏
//       ▕▁▁▁▁▁▁▁▁▁▏
//            ▲
//            │
//       ▕▔▔▔▔▔▔▔▔▔▏
//       ▕ FWindow ▏
//       ▕▁▁▁▁▁▁▁▁▁▏
//            ▲
//            │
//       ▕▔▔▔▔▔▔▔▔▔▏
//       ▕ FDialog ▏
//       ▕▁▁▁▁▁▁▁▁▁▏

#ifndef _FDIALOG_H
#define _FDIALOG_H

#include "fmenu.h"
#include "fmenuitem.h"
#include "ftooltip.h"
#include "fwindow.h"


//----------------------------------------------------------------------
// class FDialog
//----------------------------------------------------------------------

#pragma pack(push)
#pragma pack(1)

class FDialog : public FWindow
{
 public:
   enum DialogCode
   {
     Reject = 0,
     Accept = 1
   };

 private:
   FString      tb_text;          // title bar text
   int          result_code;
   bool         zoom_button_pressed;
   bool         zoom_button_active;
   FPoint       titlebar_click_pos;
   FPoint       resize_click_pos;
   FRect        save_geometry;     // required by move/size by keyboard
   FMenu*       dialog_menu;
   FMenuItem*   dgl_menuitem;
   FMenuItem*   move_size_item;
   FMenuItem*   zoom_item;
   FMenuItem*   close_item;
   FToolTip*    tooltip;

 private:
   // Disable copy constructor
   FDialog (const FDialog&);
   // Disable assignment operator (=)
   FDialog& operator = (const FDialog&);

   void         init();
   // make every drawBorder from FWidget available
   using FWidget::drawBorder;
   virtual void drawBorder();
   void         drawTitleBar();
   void         leaveMenu();
   void         openMenu();
   void         selectFirstMenuItem();
   void         setZoomItem();

   // Callback methods
   void         cb_move (FWidget*, void*);
   void         cb_zoom (FWidget*, void*);
   void         cb_close (FWidget*, void*);

   static void  addDialog (FWidget*);
   static void  delDialog (FWidget*);

 protected:
   virtual void done (int);
   virtual void draw();
   virtual void onShow (FShowEvent*);
   virtual void onHide (FHideEvent*);
   virtual void onClose (FCloseEvent*);

 public:
   // Constructors
   explicit FDialog (FWidget* = 0);
   FDialog (const FString&, FWidget* = 0);
   // Destructor
   virtual ~FDialog();

   virtual const char* getClassName() const;

   // Event handlers
   void     onKeyPress (FKeyEvent*);
   void     onMouseDown (FMouseEvent*);
   void     onMouseUp (FMouseEvent*);
   void     onMouseMove (FMouseEvent*);
   void     onMouseDoubleClick (FMouseEvent*);
   void     onAccel (FAccelEvent*);
   void     onWindowActive (FEvent*);
   void     onWindowInactive (FEvent*);
   void     onWindowRaised (FEvent*);
   void     onWindowLowered (FEvent*);

   void     activateDialog();
   void     drawDialogShadow();
   void     show();
   void     hide();
   int      exec();
   void     setPos (int, int, bool = true);
   // make every setPos from FWindow available
   using FWindow::setPos;
   void     move (int, int);
   // make every move from FWindow available
   using FWindow::move;
   void     setSize (int, int, bool = true);

   bool     setFocus (bool);
   bool     setFocus();
   bool     unsetFocus();
   bool     setDialogWidget (bool);
   bool     setDialogWidget();
   bool     unsetDialogWidget();
   bool     setModal (bool);
   bool     setModal();
   bool     unsetModal();
   bool     isModal();
   bool     setResizeable (bool);
   // make every setResizeable from FWindow available
   using FWindow::setResizeable;
   bool     setScrollable (bool);
   bool     setScrollable();
   bool     unsetScrollable();
   bool     isScrollable();
   FString  getText() const;
   void     setText (const FString&);

 private:
   // Friend function from FMenu
   friend void FMenu::hideSuperMenus();
};
#pragma pack(pop)

// FDialog inline functions
//----------------------------------------------------------------------
inline const char* FDialog::getClassName() const
{ return "FDialog"; }

//----------------------------------------------------------------------
inline bool FDialog::setFocus()
{ return setFocus(true); }

//----------------------------------------------------------------------
inline bool FDialog::unsetFocus()
{ return setFocus(false); }

//----------------------------------------------------------------------
inline bool FDialog::setDialogWidget()
{ return setDialogWidget(true); }

//----------------------------------------------------------------------
inline bool FDialog::unsetDialogWidget()
{ return setDialogWidget(false); }

//----------------------------------------------------------------------
inline bool FDialog::setModal()
{ return setModal(true); }

//----------------------------------------------------------------------
inline bool FDialog::unsetModal()
{ return setModal(false); }

//----------------------------------------------------------------------
inline bool FDialog::isModal()
{ return ((flags & fc::modal) != 0); }

//----------------------------------------------------------------------
inline bool FDialog::setScrollable()
{ return setScrollable(true); }

//----------------------------------------------------------------------
inline bool FDialog::unsetScrollable()
{ return setScrollable(false); }

//----------------------------------------------------------------------
inline bool FDialog::isScrollable()
{ return ((flags & fc::scrollable) != 0); }

//----------------------------------------------------------------------
inline FString FDialog::getText() const
{ return tb_text; }

//----------------------------------------------------------------------
inline void FDialog::setText (const FString& txt)
{ tb_text = txt; }


#endif  // _FDIALOG_H
