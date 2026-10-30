# GrafX2 for AmigaChrome

## Intake status

**State:** source intake and backend design; implementation has not started.  
**Target:** AmigaOS 3.x on AC090 / 68040 + FPU, then m68k AROS.  
**Upstream:** [GrafX2](https://gitlab.com/GrafX2/grafX2), GPL-2.0-only.  
**Source pin:** `678a0f54ea7f3eeebc3fa4135213ea63f45a28bd` (upstream master; checkout retrieved 30 October 2026, GrafX2 2.9 line).

GrafX2 is a high-value standalone pixel-art and bitmap editor. Existing Amiga ports establish that the application and workflow are viable, but their SDL dependencies do not meet this port's native Open-family target.

## Prior-art review

| Platform / package | Evidence | Reuse value |
| --- | --- | --- |
| AmigaOS 3.x, 68k RTG | Official downloads page lists version 2.8 (24 October 2022). | Closest CPU and OS ABI reference; inspect the package/source patch for OS3 build and RTG details. |
| AmigaOS 4, PPC | Official downloads page lists version 2.0.874 (2009). | Historical packaging and platform glue only. |
| MorphOS, PPC | MorphOS Storage has GrafX2 2.9 by BeWorld. Its readme says the 23 September 2026 update follows upstream's latest commit and builds with SDL2, the MorphOS 3.20 SDK, and Lua 5.4. | Current feature/packaging reference; not a native backend to carry forward. |
| AROS x86_64 (AROS One ABIv11 first; mainline ABIv1 secondary) | [Current AROS port project](https://github.com/tomaszstaniak/aros-grafx2) pins upstream commit `f84cb09dc59d706d6e7b28778b01ba911f52298c` and maintains patches `0001`–`0012`. It retains SDL2. Patches include PNG stdio callbacks, software-renderer preference, AROS file paths/locks, no-console startup and SDL2 mouse/key fallbacks. | Strong behavior and packaging reference, but it targets x86_64 and keeps SDL2; it is not the m68k AROS/native Open-family implementation. Mine the non-SDL portability changes and translate the needed input/display behavior to native APIs. |

The current upstream `src/Makefile` has legacy AmigaOS 3/4, AROS, and MorphOS branches, but those recipes select SDL 1.2 (`sdl-config`) and SDL_image. The current MorphOS package uses SDL2. These are useful build-history clues; none is the approved AmigaChrome implementation.

## Source shape and native seams

- **Display and palette:** `sdlscreen.c` owns SDL video-mode setup, the indexed 8-bit display surface, palette updates, dirty rectangles, and screen blits. Define a separate Amiga backend and map presentation to native screens/bitmaps and graphics.library calls, using OpenGfx/OpenGPU acceleration where the native API supports it.
- **Input and window events:** `input.c` contains SDL event decoding and currently handles mouse, keyboard, window focus/resize, wheel and joystick events. Use Intuition IDCMP for the desktop mouse/keyboard/window lifecycle; map optional controllers through OpenInput only where its game-controller API fits. Keep GrafX2's existing action/tool logic independent of event transport.
- **Image loading:** SDL_image is linked by the Amiga recipes and is used by the current source. Audit each loader and choose native DataTypes/OpenImage paths or the approved static image libraries, preserving GrafX2's supported-format behavior where feasible.
- **Text:** The Amiga make recipes set `NOTTF=1`; GrafX2 has its own UI bitmap-font path. Keep this as the baseline, and assess OpenFont separately for optional scalable text.
- **Audio:** no SDL audio API calls were found in the pinned source. OpenAudio is not part of the initial port.
- **Other SDL touch points:** SDL mode enumeration in `init.c`, screen helpers in `graph.c`, window-system events in `loadsave.c` / `osdep.c`, and SDL timing in input. Keep these behind the platform backend or replace them with appropriate Exec/Intuition timing and system messages.

Do not add a compatibility layer that makes GrafX2 appear to use SDL while retaining SDL as a runtime dependency. The port should have an explicit native Amiga API selection in the build.

## Implementation sequence

1. **Recover prior-art patches:** obtain and diff the AROS 2.9 patch and the OS3 2.8 package/source against the pinned upstream. Record source URLs, original authors, licensing, and reusable changes.
2. **Freeze the backend contract:** define screen open/close, indexed pixel access, palette changes, dirty-rectangle presentation, mouse/keyboard translation, mode selection, clipboard/file-drop behavior, and error dialogs.
3. **Add the native screen path:** use an 8-bit indexed bitmap where available, preserving GrafX2's palette semantics; prove full and dirty updates, resize/mode changes, and restoration on exit.
4. **Add native input and OS integration:** IDCMP input mapping, focus-loss handling, file requester integration, and safe window/screen teardown.
5. **Replace SDL_image:** map PNG/JPEG and other supported formats to approved native DataTypes/OpenImage dependencies; retain the built-in loaders and RECOIL path.
6. **Build and qualify:** reproducible GCC16 build, package with fonts/docs/licenses, then interactive AC090 qualification for drawing, palette edits, undo/redo, loading/saving, mode changes, and clean exit. No release claim until these gates pass.

## Release gates

- No SDL, SDL_image, SDL_ttf, Mesa, or X11 runtime dependency.
- GCC16 build for the stated 68040 + FPU target.
- Open-family/native Amiga screen and input integration; no direct framebuffer assumptions that bypass OS screen ownership.
- Format support and any intentionally omitted formats documented.
- AC090 runtime check covers drawing, palette updates, mouse/keyboard actions, load/save, screen changes, and teardown.
- Preserve upstream GPL-2.0-only notices for GrafX2-derived code; keep Team-authored build/port glue separately licensed and identified.

## References

- [GrafX2 upstream source](https://gitlab.com/GrafX2/grafX2)
- [Official GrafX2 downloads](http://grafx2.chez.com/index.php?static3/downloads)
- [MorphOS Storage GrafX2 2.9 package](https://www.morphos-storage.net/?id=2468088)
- [MorphOS package readme](https://www.morphos-storage.net/Graphics/Draw/GrafX2_2.9.readme)
- AROS patch location is not yet captured in the repository; find and pin it during step 1.
