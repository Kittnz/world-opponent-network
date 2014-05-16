#include "SWindow.h"
#include "SDisplayContext.h"

using namespace WONAPI;

static DisplayContext* DefDisplayContextAllocator() { return new SDisplayContext; }
static void DefNativeCursorFunc(Cursor*,bool) { }
static void DefMouseCaptureFunc(bool) { }

SWindow::DisplayContextAllocator gDisplayContextAllocator = NULL;
SWindow::FontAllocator gFontAllocator = NULL;
SWindow::NativeCursorFunc gNativeCursorFunc = DefNativeCursorFunc;
SWindow::MouseCaptureFunc gMouseCaptureFunc = DefMouseCaptureFunc;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
SWindow::SWindow()
{
	mCurKeyMod = 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
SWindow::~SWindow()
{
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::Create(const WONRectangle& theWindowRectR)
{
	Window::Create(theWindowRectR);
	
	mDisplayContext = gDisplayContextAllocator();
	mOffscreenImage = CreateImage(mRootContainer->Width(), mRootContainer->Height());
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::SetFocus()
{
	NotifyFocus(true);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
FontPtr SWindow::GetNativeFont(const FontDescriptor &theDescriptor)
{
	return gFontAllocator(theDescriptor);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::SetNativeCursor(Cursor *theCursor)
{
	gNativeCursorFunc(theCursor,true);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::ShowNativeCursorHook(bool show)
{
	gNativeCursorFunc(NULL,show);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::SetMouseCapture(bool on)
{
	gMouseCaptureFunc(on);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::SetDisplayContextAllocator(DisplayContextAllocator theAllocator)
{
	gDisplayContextAllocator = theAllocator;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::SetFontAllocator(FontAllocator theAllocator)
{
	gFontAllocator = theAllocator;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::SetNativeCursorFunc(NativeCursorFunc theFunc)
{
	gNativeCursorFunc = theFunc;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::SetMouseCaptureFunc(MouseCaptureFunc theFunc)
{
	gMouseCaptureFunc = theFunc;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::NotifySize(int theWidth, int theHeight)
{
	PostEvent(new SizeEvent(-1,-1,theWidth,theHeight));
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::NotifyMouseMove(int x, int y)
{
	PostEvent(new MouseEvent(InputEvent_MouseMove, x, y, mCurKeyMod));
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::NotifyMouseDown(MouseButton theButton)
{
	PostEvent(new MouseEvent(InputEvent_MouseDown, GetMouseX(), GetMouseY(), mCurKeyMod, theButton));
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::NotifyMouseDoubleClick(MouseButton theButton)
{
	PostEvent(new MouseEvent(InputEvent_MouseDoubleClick, GetMouseX(), GetMouseY(), mCurKeyMod, theButton));
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::NotifyMouseUp(MouseButton theButton)
{
	PostEvent(new MouseEvent(InputEvent_MouseUp, GetMouseX(), GetMouseY(), mCurKeyMod, theButton));
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::NotifyMouseWheel(int theAmount)
{
	PostEvent(new MouseEvent(InputEvent_MouseWheel, GetMouseX(), GetMouseY(), mCurKeyMod, theAmount));
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::NotifyFocus(bool gotFocus)
{
	if(gotFocus)
		PostEvent(new InputEvent(InputEvent_GotFocus)); 
	else
		PostEvent(new InputEvent(InputEvent_LostFocus)); 
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::NotifyKeyMod(int theKeyMod)
{
	mCurKeyMod = theKeyMod;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::NotifyKeyUp(int theKey)
{
	PostEvent(new KeyEvent(InputEvent_KeyUp, theKey, mCurKeyMod)); 		
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::NotifyKeyDown(int theKey)
{
	PostEvent(new KeyEvent(InputEvent_KeyDown, theKey, mCurKeyMod)); 
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SWindow::NotifyKeyChar(int theKey)
{
	PostEvent(new KeyEvent(InputEvent_KeyChar, theKey, mCurKeyMod)); 
}

