// ####ECOSHOSTGPLCOPYRIGHTBEGIN####                                        
// -------------------------------------------                              
// This file is part of the eCos host tools.                                
// Copyright (C) 1998, 1999, 2000 Free Software Foundation, Inc.            
//
// This program is free software; you can redistribute it and/or modify     
// it under the terms of the GNU General Public License as published by     
// the Free Software Foundation; either version 2 or (at your option) any   
// later version.                                                           
//
// This program is distributed in the hope that it will be useful, but      
// WITHOUT ANY WARRANTY; without even the implied warranty of               
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU        
// General Public License for more details.                                 
//
// You should have received a copy of the GNU General Public License        
// along with this program; if not, write to the                            
// Free Software Foundation, Inc., 51 Franklin Street,                      
// Fifth Floor, Boston, MA  02110-1301, USA.                                
// -------------------------------------------                              
// ####ECOSHOSTGPLCOPYRIGHTEND####                                          
// mltwin.h :
//
//===========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):   julians
// Contact(s):  julians
// Date:        2000/09/04
// Version:     $Id: mltwin.h,v 1.1.1.1 2010-03-29 09:12:06 musterc Exp $
// Purpose:
// Description: Header file for ecMemoryLayoutWindow
// Requires:
// Provides:
// See also:
// Known bugs:
// Usage:
//
//####DESCRIPTIONEND####
//
//===========================================================================

#ifndef _ECOS_MLTWIN_H_
#define _ECOS_MLTWIN_H_

#ifdef __GNUG__
#pragma interface "mltwin.h"
#endif

#if ecUSE_MLT

#include "memmap.h"

typedef struct tagREGIONRECT
{
    std::list <mem_region>::iterator Region;
    wxRect Rect;
}
REGIONRECT;

typedef struct tagSECTIONRECT
{
    std::list <mem_section_view>::iterator SectionView;
    wxRect Rect;
}
SECTIONRECT;

#endif

class ecMemoryLayoutWindow : public wxScrolledWindow
{
public:
// Ctor(s)
    ecMemoryLayoutWindow(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style);
    ~ecMemoryLayoutWindow();

//// Event handlers

    //void OnPaint(wxPaintEvent& event);
    void OnMouseEvent(wxMouseEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnProperties(wxCommandEvent& event);

//// Operations
    void RefreshMLT();

#if ecUSE_MLT
	void DrawRegion (wxDC& dc, int uRegion, int uUnitCount, int uPixelsPerUnit, std::list <mem_region>::iterator region);
    SECTIONRECT * SectionHitTest (wxPoint pntTest);
    REGIONRECT * RegionHitTest (wxPoint pntTest);
#endif

	void CalcUnitCountMax ();


//// Accessors
    wxMenu* GetPropertiesMenu() const { return m_propertiesMenu; }

protected:
    wxMenu*     m_propertiesMenu;

    wxList      m_listSectionRect;
    wxList      m_listRegionRect;

#if ecUSE_MLT
    std::list <mem_section_view>::iterator m_sviSelectedSectionView;
    std::list <mem_region>::iterator m_riSelectedRegion;
#endif

    int         m_uViewWidth, m_uClientWidth;
    int         m_uUnitCountMax;
	wxRect      m_rectSelectedItem;

private:
    DECLARE_EVENT_TABLE()
    DECLARE_CLASS(ecMemoryLayoutWindow)
};


#endif
        // _ECOS_MLTWIN_H_
