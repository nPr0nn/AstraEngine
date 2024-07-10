#ifndef __GLFW_IMPL_H__
#define __GLFW_IMPL_H__

#include "src/glfw3.h"

#ifdef GLFW_IMPL

#if defined(_WIN32)
    #define _GLFW_WIN32
#endif
#if defined(__linux__)
    #if !defined(_GLFW_WAYLAND)     // Required for Wayland windowing
        #define _GLFW_X11
    #endif
#endif
#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
    #define _GLFW_X11
#endif
#if defined(__APPLE__)
    #define _GLFW_COCOA
    #define _GLFW_USE_MENUBAR       // To create and populate the menu bar when the first window is created
    #define _GLFW_USE_RETINA        // To have windows use the full resolution of Retina displays
#endif
#if defined(__TINYC__)
    #define _WIN32_WINNT_WINXP      0x0501
#endif

#include "src/context.c"
#include "src/init.c"
#include "src/input.c"
#include "src/monitor.c"
#include "src/vulkan.c"
#include "src/window.c"

#if (defined _WIN32 | defined _WIN64)
    #include "src/win32_init.c"
    #include "src/win32_joystick.c"
    #include "src/win32_monitor.c"
    #include "src/win32_time.c"
    #include "src/win32_thread.c"
    #include "src/win32_window.c"
    #include "src/wgl_context.c"
    #include "src/egl_context.c"
    #include "src/osmesa_context.c"
#endif

#if (defined __linux__ || defined _linux || defined __linux)
    #if defined(_GLFW_WAYLAND)
        #include "src/wl_init.c"
        #include "src/wl_monitor.c"
        #include "src/wl_window.c"
        #include "src/wayland-pointer-constraints-unstable-v1-client-protocol.c"
        #include "src/wayland-relative-pointer-unstable-v1-client-protocol.c"
        #endif
    #if defined(_GLFW_X11)
        #include "src/x11_init.c"
        #include "src/x11_monitor.c"
        #include "src/x11_window.c"
        #include "src/glx_context.c"
    #endif

    #include "src/linux_joystick.c"
    #include "src/posix_thread.c"
    #include "src/posix_time.c"
    #include "src/xkb_unicode.c"
    #include "src/egl_context.c"
    #include "src/osmesa_context.c"
#endif

#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
    #include "src/x11_init.c"
    #include "src/x11_monitor.c"
    #include "src/x11_window.c"
    #include "src/xkb_unicode.c"
    // TODO: Joystick implementation
    #include "src/null_joystick.c"
    #include "src/posix_time.c"
    #include "src/posix_thread.c"
    #include "src/glx_context.c"
    #include "src/egl_context.c"
    #include "src/osmesa_context.c"
#endif

#if defined(__APPLE__)
    #include "src/cocoa_init.m"
    #include "src/cocoa_joystick.m"
    #include "src/cocoa_monitor.m"
    #include "src/cocoa_window.m"
    #include "src/cocoa_time.c"
    #include "src/posix_thread.c"
    #include "src/nsgl_context.m"
    #include "src/egl_context.c"
    #include "src/osmesa_context.c"
#endif

#endif // GLFW_IMPL

#endif // __GLFW_IMPL_H__
