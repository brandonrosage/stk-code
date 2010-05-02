//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2009 Marianne Gagnon
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "graphics/irr_driver.hpp"
#include "guiengine/engine.hpp"
#include "guiengine/widgets/list_widget.hpp"

#include "io/file_manager.hpp"

#include "guiengine/CGUISpriteBank.h"

using namespace GUIEngine;
using namespace irr::core;
using namespace irr::gui;

// -----------------------------------------------------------------------------

ListWidget::ListWidget() : Widget(WTYPE_LIST)
{
    m_use_icons = false; //TODO: make configurable if needed
}

// -----------------------------------------------------------------------------

void ListWidget::add()
{
    rect<s32> widget_size = rect<s32>(x, y, x + w, y + h);
    
    IGUIListBox* list = GUIEngine::getGUIEnv()->addListBox (widget_size, m_parent, getNewID());
    list->setAutoScrollEnabled(false);
    
    if (m_use_icons)
    {
        //TODO: allow choosing which icons to use
        video::ITexture* icon = irr_driver->getTexture( file_manager->getGUIDir() + "/difficulty_medium.png" );
        
        // TODO: delete the bank when done using, it currently leaks
        STKModifiedSpriteBank* bank = new STKModifiedSpriteBank( GUIEngine::getGUIEnv() );
        bank->setScale(0.5f);
        bank->addTextureAsSprite(icon);
        list->setSpriteBank(bank);
        list->setItemHeight( icon->getSize().Height*0.5f );
    }
    
    m_element = list;
}

// -----------------------------------------------------------------------------

void ListWidget::clear()
{
    IGUIListBox* list = getIrrlichtElement<IGUIListBox>();
    assert(list != NULL);
    
    list->clear();
}

// -----------------------------------------------------------------------------

void ListWidget::addItem(const char* item)
{
    IGUIListBox* list = getIrrlichtElement<IGUIListBox>();
    assert(list != NULL);
    
    if (m_use_icons)
    {
        //TODO: allow choosing which icon to use
        u32 newItem = list->addItem( stringw(item).c_str(), 0 /* icon */ );
        list->setItemOverrideColor( newItem, gui::EGUI_LBC_ICON, video::SColor(255,255,255,255) );
        list->setItemOverrideColor( newItem, gui::EGUI_LBC_ICON_HIGHLIGHT, video::SColor(255,255,255,255) );
    }
    else
    {
        list->addItem( stringw(item).c_str() );
    }
}

// -----------------------------------------------------------------------------

std::string ListWidget::getSelectionName() const
{
    const IGUIListBox* list = getIrrlichtElement<IGUIListBox>();
    assert(list != NULL);
    return stringc( list->getListItem( list->getSelected() ) ).c_str();
}

// -----------------------------------------------------------------------------

void ListWidget::unfocused(const int playerID)
{
    IGUIListBox* list = getIrrlichtElement<IGUIListBox>();

    // remove selection when leaving list
    if (list != NULL) list->setSelected(-1);
}

// -----------------------------------------------------------------------------

int ListWidget::getSelectionID() const
{
    return getIrrlichtElement<IGUIListBox>()->getSelected();
}

// -----------------------------------------------------------------------------

void ListWidget::setSelectionID(const int index)
{
    IGUIListBox* irritem = getIrrlichtElement<IGUIListBox>();
    
    // auto-scroll to item when selecting something, don't auto-scroll when selecting nothing
    if (index != -1)
    {
        irritem->setAutoScrollEnabled(true);
    }
    
    irritem->setSelected(index);
    
    if (index != -1)
    {
        irritem->setAutoScrollEnabled(false);
    }
}

// -----------------------------------------------------------------------------

int ListWidget::getItemCount() const
{
    return getIrrlichtElement<IGUIListBox>()->getItemCount();
}

// -----------------------------------------------------------------------------
