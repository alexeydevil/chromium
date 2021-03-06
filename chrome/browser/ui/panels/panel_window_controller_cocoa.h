// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_PANELS_PANEL_WINDOW_CONTROLLER_COCOA_H_
#define CHROME_BROWSER_UI_PANELS_PANEL_WINDOW_CONTROLLER_COCOA_H_

// A class acting as the Objective-C controller for the Panel window
// object. Handles interactions between Cocoa and the cross-platform
// code. Each window has a single titlebar and is managed/owned by Panel.

#import <Cocoa/Cocoa.h>

#import "base/mac/cocoa_protocols.h"
#include "base/memory/scoped_nsobject.h"
#include "base/memory/scoped_ptr.h"
#include "base/time.h"
#import "chrome/browser/ui/cocoa/browser_command_executor.h"
#import "chrome/browser/ui/cocoa/chrome_browser_window.h"
#import "chrome/browser/ui/cocoa/tab_contents/tab_contents_controller.h"
#import "chrome/browser/ui/cocoa/themed_window.h"
#import "chrome/browser/ui/cocoa/tracking_area.h"
#include "chrome/browser/ui/panels/panel.h"

@class FindBarCocoaController;
class PanelBrowserWindowCocoa;
@class PanelTitlebarViewCocoa;

@interface PanelWindowCocoaImpl : ChromeBrowserWindow {
}
@end

@interface PanelWindowControllerCocoa : NSWindowController
                                            <NSWindowDelegate,
                                             NSAnimationDelegate,
                                             BrowserCommandExecutor> {
 @private
  IBOutlet PanelTitlebarViewCocoa* titlebar_view_;
  scoped_ptr<PanelBrowserWindowCocoa> windowShim_;
  scoped_nsobject<NSString> pendingWindowTitle_;
  scoped_nsobject<TabContentsController> contentsController_;
  NSViewAnimation* boundsAnimation_;  // Lifetime controlled manually, needs
                                      // more then just |release| to terminate.
  BOOL animateOnBoundsChange_;
  BOOL throbberShouldSpin_;
  BOOL playingMinimizeAnimation_;
  float animationStopToShowTitlebarOnly_;
  BOOL canBecomeKeyWindow_;
  scoped_nsobject<NSView> overlayView_;
}

// Load the browser window nib and do any Cocoa-specific initialization.
- (id)initWithBrowserWindow:(PanelBrowserWindowCocoa*)window;

- (ui::ThemeProvider*)themeProvider;
- (ThemedWindowStyle)themedWindowStyle;
- (NSPoint)themePatternPhase;

- (void)tabInserted:(content::WebContents*)contents;
- (void)tabDetached:(content::WebContents*)contents;

// Sometimes (when we animate the size of the window) we want to stop resizing
// the WebContents's Cocoa view to avoid unnecessary rendering and issues
// that can be caused by sizes near 0.
- (void)disableTabContentsViewAutosizing;
- (void)enableTabContentsViewAutosizing;

// Shows the window for the first time. Only happens once.
- (void)revealAnimatedWithFrame:(const NSRect&)frame;

- (void)updateTitleBar;
- (void)updateIcon;
- (void)updateThrobber:(BOOL)shouldSpin;
- (void)updateTitleBarMinimizeRestoreButtonVisibility;

// Adds the FindBar controller's view to this Panel. Must only be
// called once per PanelWindowControllerCocoa.
- (void)addFindBar:(FindBarCocoaController*)findBarCocoaController;

// Initiate the closing of the panel, starting from the platform-independent
// layer. This will take care of PanelManager, other panels and close the
// native window at the end.
- (void)closePanel;

// Minimize/Restore the panel or all panels, depending on the modifier.
// Invoked when the minimize/restore button is clicked.
- (void)minimizeButtonClicked:(int)modifierFlags;
- (void)restoreButtonClicked:(int)modifierFlags;

// Uses nonblocking animation for moving the Panels. It's especially
// important in case of dragging a Panel when other Panels should 'slide out',
// indicating the potential drop slot.
// |frame| is in screen coordinates, same as [window frame].
// |animate| controls if the bounds animation is needed or not.
- (void)setPanelFrame:(NSRect)frame
              animate:(BOOL)animate;

// Used by PanelTitlebarViewCocoa when user rearranges the Panels by dragging.
// |mouseLocation| is in Cocoa's screen coordinates.
- (void)startDrag:(NSPoint)mouseLocation;
- (void)endDrag:(BOOL)cancelled;
- (void)drag:(NSPoint)mouseLocation;

// Accessor for titlebar view.
- (PanelTitlebarViewCocoa*)titlebarView;
// Returns the height of titlebar, used to show the titlebar in
// "Draw Attention" state.
- (int)titlebarHeightInScreenCoordinates;

// Invoked when user clicks on the titlebar. Attempts to flip the
// Minimized/Restored states.
- (void)onTitlebarMouseClicked:(int)modifierFlags;

// Executes the command in the context of the current browser.
// |command| is an integer value containing one of the constants defined in the
// "chrome/app/chrome_command_ids.h" file.
- (void)executeCommand:(int)command;

// NSAnimationDelegate method, invoked when bounds animation is finished.
- (void)animationDidEnd:(NSAnimation*)animation;
// Terminates current bounds animation, if any.
- (void)terminateBoundsAnimation;

- (BOOL)isAnimatingBounds;

// Removes the Key status from the panel to some other window.
- (void)deactivate;

// Changes the canBecomeKeyWindow state
- (void)preventBecomingKeyWindow:(BOOL)prevent;

// See Panel::FullScreenModeChanged.
- (void)fullScreenModeChanged:(bool)isFullScreen;

// Helper for NSWindow, returns NO for minimized panels in some cases, so they
// are not un-minimized when another panel is minimized.
- (BOOL)canBecomeKeyWindow;

// Returns true if browser window requested activation of the window.
- (BOOL)activationRequestedByBrowser;

- (void)ensureFullyVisible;

- (void)updateWindowLevel;

// Turns on user-resizable corners/sides indications and enables live resize.
- (void)enableResizeByMouse:(BOOL)enable;

@end  // @interface PanelWindowController

#endif  // CHROME_BROWSER_UI_PANELS_PANEL_WINDOW_CONTROLLER_COCOA_H_
