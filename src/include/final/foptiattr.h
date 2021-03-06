/***********************************************************************
* foptiattr.h - Sets video attributes in optimized order               *
*                                                                      *
* This file is part of the Final Cut widget toolkit                    *
*                                                                      *
* Copyright 2016-2019 Markus Gans                                      *
*                                                                      *
* The Final Cut is free software; you can redistribute it and/or       *
* modify it under the terms of the GNU Lesser General Public License   *
* as published by the Free Software Foundation; either version 3 of    *
* the License, or (at your option) any later version.                  *
*                                                                      *
* The Final Cut is distributed in the hope that it will be useful,     *
* but WITHOUT ANY WARRANTY; without even the implied warranty of       *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
* GNU Lesser General Public License for more details.                  *
*                                                                      *
* You should have received a copy of the GNU Lesser General Public     *
* License along with this program.  If not, see                        *
* <http://www.gnu.org/licenses/>.                                      *
***********************************************************************/

/*  Standalone class
 *  ════════════════
 *
 * ▕▔▔▔▔▔▔▔▔▔▔▔▏
 * ▕ FOptiAttr ▏
 * ▕▁▁▁▁▁▁▁▁▁▁▁▏
 */

#ifndef FOPTIATTR_H
#define FOPTIATTR_H

#if !defined (USE_FINAL_H) && !defined (COMPILE_FINAL_CUT)
  #error "Only <final/final.h> can be included directly."
#endif

// Typecast to c-string
#define C_STR const_cast<char*>

#include <assert.h>

#if defined(__sun) && defined(__SVR4)
  #include <termio.h>
  typedef struct termio SGTTY;
  typedef struct termios SGTTYS;

  #ifdef _LP64
    typedef unsigned int chtype;
  #else
    typedef unsigned long chtype;
  #endif

  #include <term.h>   // need for tparm
#else
  #include <term.h>   // need for tparm
#endif

#include <algorithm>  // need for std::swap

#include "final/fstring.h"

namespace finalcut
{

//----------------------------------------------------------------------
// class FOptiAttr
//----------------------------------------------------------------------

class FOptiAttr final
{
  public:
    // Typedef
    typedef struct
    {
      char* t_enter_bold_mode;
      char* t_exit_bold_mode;
      char* t_enter_dim_mode;
      char* t_exit_dim_mode;
      char* t_enter_italics_mode;
      char* t_exit_italics_mode;
      char* t_enter_underline_mode;
      char* t_exit_underline_mode;
      char* t_enter_blink_mode;
      char* t_exit_blink_mode;
      char* t_enter_reverse_mode;
      char* t_exit_reverse_mode;
      char* t_enter_standout_mode;
      char* t_exit_standout_mode;
      char* t_enter_secure_mode;
      char* t_exit_secure_mode;
      char* t_enter_protected_mode;
      char* t_exit_protected_mode;
      char* t_enter_crossed_out_mode;
      char* t_exit_crossed_out_mode;
      char* t_enter_dbl_underline_mode;
      char* t_exit_dbl_underline_mode;
      char* t_set_attributes;
      char* t_exit_attribute_mode;
      char* t_enter_alt_charset_mode;
      char* t_exit_alt_charset_mode;
      char* t_enter_pc_charset_mode;
      char* t_exit_pc_charset_mode;
      char* t_set_a_foreground;
      char* t_set_a_background;
      char* t_set_foreground;
      char* t_set_background;
      char* t_set_color_pair;
      char* t_orig_pair;
      char* t_orig_colors;
      int   max_color;
      int   attr_without_color;
      bool  ansi_default_color;
    } termEnv;

    // Constructor
    FOptiAttr();

    // Disable copy constructor
    FOptiAttr (const FOptiAttr&) = delete;

    // Destructor
    virtual ~FOptiAttr();

    // Disable assignment operator (=)
    FOptiAttr& operator = (const FOptiAttr&) = delete;

    // Friend operator functions
    friend bool operator == (const FChar&, const FChar&);
    friend bool operator != (const FChar&, const FChar&);

    // Accessors
    const FString getClassName() const;

    // Mutators
    void  setTermEnvironment (termEnv&);
    void  setMaxColor (const int&);
    void  setNoColorVideo (int);
    void  setDefaultColorSupport();
    void  unsetDefaultColorSupport();
    void  set_enter_bold_mode (char[]);
    void  set_exit_bold_mode (char[]);
    void  set_enter_dim_mode (char[]);
    void  set_exit_dim_mode (char[]);
    void  set_enter_italics_mode (char[]);
    void  set_exit_italics_mode (char[]);
    void  set_enter_underline_mode (char[]);
    void  set_exit_underline_mode (char[]);
    void  set_enter_blink_mode (char[]);
    void  set_exit_blink_mode (char[]);
    void  set_enter_reverse_mode (char[]);
    void  set_exit_reverse_mode (char[]);
    void  set_enter_secure_mode (char[]);
    void  set_exit_secure_mode (char[]);
    void  set_enter_protected_mode (char[]);
    void  set_exit_protected_mode (char[]);
    void  set_enter_crossed_out_mode (char[]);
    void  set_exit_crossed_out_mode (char[]);
    void  set_enter_dbl_underline_mode (char[]);
    void  set_exit_dbl_underline_mode (char[]);
    void  set_enter_standout_mode (char[]);
    void  set_exit_standout_mode (char[]);
    void  set_set_attributes (char[]);
    void  set_exit_attribute_mode (char[]);
    void  set_enter_alt_charset_mode (char[]);
    void  set_exit_alt_charset_mode (char[]);
    void  set_enter_pc_charset_mode (char[]);
    void  set_exit_pc_charset_mode (char[]);
    void  set_a_foreground_color (char[]);
    void  set_a_background_color (char[]);
    void  set_foreground_color (char[]);
    void  set_background_color (char[]);
    void  set_term_color_pair (char[]);
    void  set_orig_pair (char[]);
    void  set_orig_orig_colors (char[]);

    // Inquiry
    static bool   isNormal (FChar*&);

    // Methods
    void          initialize();
    static FColor vga2ansi (FColor);
    char*         changeAttribute (FChar*&, FChar*&);

  private:
    // Typedefs and Enumerations
    typedef struct
    {
      char* cap;
      bool  caused_reset;
    } capability;

    enum init_reset_tests
    {
      no_test         = 0x00,
      test_ansi_reset = 0x01,  // ANSI X3.64 terminal
      test_adm3_reset = 0x02,  // Lear Siegler ADM-3 terminal
      same_like_ue    = 0x04,
      same_like_se    = 0x08,
      same_like_me    = 0x10,
      all_tests       = 0x1f
    };

    enum attr_modes
    {
      standout_mode    = 1,
      underline_mode   = 2,
      reverse_mode     = 4,
      blink_mode       = 8,
      dim_mode         = 16,
      bold_mode        = 32,
      invisible_mode   = 64,
      protected_mode   = 128,
      alt_charset_mode = 256,
      horizontal_mode  = 512,
      left_mode        = 1024,
      low_mode         = 2048,
      right_mode       = 4096,
      top_mode         = 8192,
      vertical_mode    = 16384,
      italic_mode      = 32768,
      no_mode          = 65536
    };

    // Mutators
    bool  setTermBold (FChar*&);
    bool  unsetTermBold (FChar*&);
    bool  setTermDim (FChar*&);
    bool  unsetTermDim (FChar*&);
    bool  setTermItalic (FChar*&);
    bool  unsetTermItalic (FChar*&);
    bool  setTermUnderline (FChar*&);
    bool  unsetTermUnderline (FChar*&);
    bool  setTermBlink (FChar*&);
    bool  unsetTermBlink (FChar*&);
    bool  setTermReverse (FChar*&);
    bool  unsetTermReverse (FChar*&);
    bool  setTermStandout (FChar*&);
    bool  unsetTermStandout (FChar*&);
    bool  setTermInvisible (FChar*&);
    bool  unsetTermInvisible (FChar*&);
    bool  setTermProtected (FChar*&);
    bool  unsetTermProtected (FChar*&);
    bool  setTermCrossedOut (FChar*&);
    bool  unsetTermCrossedOut (FChar*&);
    bool  setTermDoubleUnderline (FChar*&);
    bool  unsetTermDoubleUnderline (FChar*&);
    bool  setTermAttributes ( FChar*&
                            , bool, bool, bool
                            , bool, bool, bool
                            , bool, bool, bool );
    bool  unsetTermAttributes (FChar*&);
    bool  setTermAltCharset (FChar*&);
    bool  unsetTermAltCharset (FChar*&);
    bool  setTermPCcharset (FChar*&);
    bool  unsetTermPCcharset (FChar*&);
    bool  setTermDefaultColor (FChar*&);
    void  setAttributesOn (FChar*&);
    void  setAttributesOff (FChar*&);

    // Inquiries
    static bool  hasColor (FChar*&);
    static bool  hasAttribute (FChar*&);
    static bool  hasNoAttribute (FChar*&);

    // Methods
    bool  hasColorChanged (FChar*&, FChar*&);
    void  resetColor (FChar*&);
    void  prevent_no_color_video_attributes (FChar*&, bool = false);
    void  deactivateAttributes (FChar*&, FChar*&);
    void  changeAttributeSGR (FChar*&, FChar*&);
    void  changeAttributeSeparately (FChar*&, FChar*&);
    void  change_color (FChar*&, FChar*&);
    void  change_to_default_color (FChar*&, FChar*&, FColor&, FColor&);
    void  change_current_color (FChar*&, FColor, FColor);
    void  resetAttribute (FChar*&);
    void  reset (FChar*&);
    bool  caused_reset_attributes (char[], uChar = all_tests);
    bool  hasCharsetEquivalence();
    void  detectSwitchOn (FChar*&, FChar*&);
    void  detectSwitchOff (FChar*&, FChar*&);
    bool  switchOn();
    bool  switchOff();
    bool  append_sequence (char[]);

    // Data members
    capability F_enter_bold_mode{};
    capability F_exit_bold_mode{};
    capability F_enter_dim_mode{};
    capability F_exit_dim_mode{};
    capability F_enter_italics_mode{};
    capability F_exit_italics_mode{};
    capability F_enter_underline_mode{};
    capability F_exit_underline_mode{};
    capability F_enter_blink_mode{};
    capability F_exit_blink_mode{};
    capability F_enter_reverse_mode{};
    capability F_exit_reverse_mode{};
    capability F_enter_standout_mode{};
    capability F_exit_standout_mode{};
    capability F_enter_secure_mode{};
    capability F_exit_secure_mode{};
    capability F_enter_protected_mode{};
    capability F_exit_protected_mode{};
    capability F_enter_crossed_out_mode{};
    capability F_exit_crossed_out_mode{};
    capability F_enter_dbl_underline_mode{};
    capability F_exit_dbl_underline_mode{};
    capability F_set_attributes{};
    capability F_exit_attribute_mode{};
    capability F_enter_alt_charset_mode{};
    capability F_exit_alt_charset_mode{};
    capability F_enter_pc_charset_mode{};
    capability F_exit_pc_charset_mode{};
    capability F_set_a_foreground{};
    capability F_set_a_background{};
    capability F_set_foreground{};
    capability F_set_background{};
    capability F_set_color_pair{};
    capability F_orig_pair{};
    capability F_orig_colors{};

    FChar      on{};
    FChar      off{};
    FChar      reset_byte_mask{};

    int        max_color{1};
    int        attr_without_color{0};
    char*      attr_ptr{attr_buf};
    char       attr_buf[8192]{'\0'};
    bool       ansi_default_color{false};
    bool       alt_equal_pc_charset{false};
    bool       monochron{true};
    bool       fake_reverse{false};
};


// FOptiAttr inline functions
//----------------------------------------------------------------------
inline bool operator == ( const FChar& lhs,
                          const FChar& rhs )
{
  return lhs.ch           == rhs.ch
      && lhs.fg_color     == rhs.fg_color
      && lhs.bg_color     == rhs.bg_color
      && lhs.attr.byte[0] == rhs.attr.byte[0]
      && lhs.attr.byte[1] == rhs.attr.byte[1]
      && lhs.attr.bit.fullwidth_padding \
                          == rhs.attr.bit.fullwidth_padding;
}

//----------------------------------------------------------------------
inline bool operator != ( const FChar& lhs,
                          const FChar& rhs )
{ return ! ( lhs == rhs ); }

//----------------------------------------------------------------------
inline const FString FOptiAttr::getClassName() const
{ return "FOptiAttr"; }

//----------------------------------------------------------------------
inline void FOptiAttr::setMaxColor (const int& c)
{ max_color = c; }

//----------------------------------------------------------------------
inline void FOptiAttr::setNoColorVideo (int attr)
{ attr_without_color = attr; }

//----------------------------------------------------------------------
inline void FOptiAttr::setDefaultColorSupport()
{ ansi_default_color = true; }

//----------------------------------------------------------------------
inline void FOptiAttr::unsetDefaultColorSupport()
{ ansi_default_color = false; }

}  // namespace finalcut

#endif  // FOPTIATTR_H
