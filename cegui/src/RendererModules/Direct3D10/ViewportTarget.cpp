/***********************************************************************
    filename:   CEGUIDirect3D10ViewportTarget.cpp
    created:    Sat Mar 7 2009
    author:     Paul D Turner (parts based on code by Rajko Stojadinovic)
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2011 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#include "CEGUI/RendererModules/Direct3D10/ViewportTarget.h"
#include "CEGUI/Exceptions.h"

// Start of CEGUI namespace section
namespace CEGUI
{
//----------------------------------------------------------------------------//
Direct3D10ViewportTarget::Direct3D10ViewportTarget(Direct3D10Renderer& owner) :
    Direct3D10RenderTarget<>(owner)
{
    // initialise renderer size
    D3D10_VIEWPORT vp;
    UINT vp_count = 1;
    d_device.RSGetViewports(&vp_count, &vp);
    if (vp_count != 1)
        CEGUI_THROW(RendererException(
            "Unable to access required view port information from "
            "ID3D10Device."));

    Rectf area(
        glm::vec2(static_cast<float>(vp.TopLeftX), static_cast<float>(vp.TopLeftY)),
        Sizef(static_cast<float>(vp.Width), static_cast<float>(vp.Height))
    );

    setArea(area);
}

//----------------------------------------------------------------------------//
Direct3D10ViewportTarget::Direct3D10ViewportTarget(Direct3D10Renderer& owner,
                                                   const Rectf& area) :
    Direct3D10RenderTarget<>(owner)
{
    setArea(area);
}

//----------------------------------------------------------------------------//
bool Direct3D10ViewportTarget::isImageryCache() const
{
    return false;
}

//----------------------------------------------------------------------------//

} // End of  CEGUI namespace section

//----------------------------------------------------------------------------//
// Implementation of template base class
#include "./RenderTarget.inl"

