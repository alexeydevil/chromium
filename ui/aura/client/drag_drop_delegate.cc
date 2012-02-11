// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/aura/client/drag_drop_delegate.h"

#include "ui/aura/window.h"
#include "ui/aura/window_property.h"

DECLARE_WINDOW_PROPERTY_TYPE(aura::client::DragDropDelegate*)

namespace aura {
namespace client {
namespace {

// A property key to store the drag and drop delegate for a window.
const WindowProperty<DragDropDelegate*> kDragDropDelegateProp = {NULL};
const WindowProperty<DragDropDelegate*>* const
    kDragDropDelegateKey = &kDragDropDelegateProp;

}  // namespace

void SetDragDropDelegate(Window* window, DragDropDelegate* delegate) {
  window->SetProperty(kDragDropDelegateKey, delegate);
}

DragDropDelegate* GetDragDropDelegate(Window* window) {
  return window->GetProperty(kDragDropDelegateKey);
}

}  // namespace client
}  // namespace aura
