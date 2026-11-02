# Unified Application Port Backlog


**[Unified Port Atlas](https://github.com/DalsinAI/amicradle/tree/main/docs/porting)** — searchable cross-programme game/application catalogue with existing Amiga-port evidence, source/rights assessment and proposed Open-family acceleration or development benefit. This does not replace the local source pins, build notes or qualification gates.

Snapshot date: **9 October 2026**

Primary target: **AmiCradle AC090 / AmigaOS 3.x / 68040 + FPU**

This is the single non-game application-port backlog for AmiCradle. The **Category** column groups ports by application type so the catalogue can be reviewed by domain as well as priority. Emulators, emulator frontends and compatibility runtimes live with games in `amicradle-gameports`. It combines fresh candidates with AROS, classic AmigaOS, AmigaOS 4 and MorphOS prior art so priority decisions can be made from the whole field.

Priority scale:

- **P0** — finish / enable now
- **P1** — next delivery wave
- **P2** — planned
- **P3** — stretch
- **PARK** — research / low return for now

## Governing porting rule

Application-port work should be preceded by one question:

> **What need does this remove to use another platform for?**

The highest-value ports are the ones that let an AmiCradle user complete a real task end-to-end without switching to Linux, Windows, macOS or another machine. A port should therefore justify itself in terms of the external workflow it replaces, not merely because the upstream application is technically interesting.

Examples:

- FFmpeg / OpenTranscode -> removes the need to use another platform for media conversion and delivery encoding.
- OpenAudioEdit / SoX -> removes the need to use another platform for recording, trimming and restoring audio.
- GrafX2 / image tools -> removes the need to use another platform for creating and processing graphics.
- OpenRecorder -> removes the need to use another platform for screen and audio capture.
- Vim / developer tooling -> removes the need to use another platform for editing and maintaining source code.
- PDF/document tools -> removes the need to use another platform for routine document viewing, conversion and output.

This **platform-substitution value** should be assessed before engineering effort begins.

A successful compile is not a release. RELEASE still requires reproducible provenance, the approved GCC stove, packaging and AC090 runtime qualification.

| Application / tool | Category | Removes Need For Another Platform? | Platform Substitution Value | Create / Fold Into | Priority | Platform need replaced | Current state | Amiga-family prior art | Intended AmiCradle treatment | Next meaningful gate |
|---|---|---|---|---|---|---|---|---|---|---|
| FFmpeg / ffprobe | Media Infrastructure | YES | HIGH | FOLD INTO OpenMedia / shared CLI infrastructure | P0 | Media conversion, probing, filtering and scripted processing beyond datatype playback | FOUNDATION CANDIDATE | AROS Contrib has FFmpeg 8.1.2 with an m68k configuration; AmigaOS 4 and MorphOS also have modern FFmpeg ports | Keep CLI tools and libraries as creation/editing/transcoding infrastructure; OpenMedia owns hardware codec acceleration and DataTypes own routine playback/viewing | Reproduce the AROS m68k build with the fixed GCC16 baseline, then define the clean OpenMedia acceleration boundary |
| MediaInfo / libmediainfo | Media Infrastructure | YES | MEDIUM | FOLD INTO GFOpenView / OpenTranscode if needed | P2 | Inspect codecs, containers, streams and media metadata beyond current datatype probe fields | CANDIDATE / POSSIBLE THIN TOOL | Cross-platform upstream; existing media.decode/1 PROBE already supplies basic kind/format/frame/size/rate metadata | First assess extending OpenMedia/GFOpenService probe metadata; port libmediainfo only if that is materially better | Gap analysis against media.decode/1 PROBE and GFOpenPlay About-this-file before importing a new dependency |
| TagLib | Media Infrastructure | YES | MEDIUM | FOLD INTO shared media metadata layer | P2 | Read/write common audio metadata and tags locally | CANDIDATE | Cross-platform upstream; Amiga-family prior art to be checked during intake | Shared metadata library for players, editors and music tools | Pin source and GCC16 library build |
| libsndfile | Media Infrastructure | YES | HIGH | FOLD INTO OpenAudioEdit / shared audio infrastructure | P1 | Common PCM/audio-file I/O for editors, converters and analysis tools | CANDIDATE | Cross-platform upstream; Amiga-family prior art to be checked during intake | Shared audio-file library beneath OpenAudioEdit and utilities | Pin source, supported-format audit and GCC16 build |
| libsamplerate | Media Infrastructure | YES | HIGH | FOLD INTO OpenAudioEdit / shared audio infrastructure | P1 | High-quality sample-rate conversion without external tooling | CANDIDATE | Cross-platform upstream; Amiga-family prior art to be checked during intake | Shared resampling engine; expose GFOpenMulticore for batch/offline work where useful | Pin source, GCC16 build and quality/performance test |
| SoX | Audio / Processing | YES | HIGH | FOLD INTO OpenAudioEdit + keep CLI | P1 | Audio conversion, DSP and batch processing | REVIVAL CANDIDATE | AROS Contrib has SoX 12.17.4 portability patch | Revive a current SoX; CLI first; later DSP engine for audio editor | Diff old AROS portability patch against current SoX |
| SoundTouch | Audio / Processing | YES | MEDIUM | FOLD INTO OpenAudioEdit | P2 | Change tempo, pitch and playback rate without leaving AmiCradle | CANDIDATE | Portable LGPL C++ library; upstream designed for cross-platform and embedded use | Shared OpenAudioEdit processing library; parallelise offline/batch jobs where useful | Pin source, GCC16 build and reference quality/performance test |
| RNNoise | Audio / Processing | YES | MEDIUM | FOLD INTO OpenAudioEdit / GFOpenAudio service path | P2 | Speech/noise cleanup without an external workstation | CANDIDATE | BSD-licensed reusable Xiph noise-suppression library | OpenAudioEdit/GFOpenAudio processing backend; prefer host-side/GFOpenMulticore execution for expensive inference | Prove portable scalar build, define offload boundary and process a reference WAV |
| OpenAudioEdit | Audio / Editing | YES | HIGH | CREATE | P1 | Record, trim, repair and edit audio | NEW APPLICATION | No direct Audacity port found in official AROS Contrib/Ports sweep; MorphOS has native audio editor prior art | Audacity-like waveform editor built from portable DSP/audio engines with GFOpenAudio + GFOpenGadTools | Define MVP: record, waveform view, cut/copy/paste, fades, normalize, save/export |
| MilkyTracker | Music / Tracker | YES | MEDIUM | CREATE / standalone revival | P1 | Tracker music creation and module editing | REVIVAL CANDIDATE | AROS Ports has 1.05.01 recipe; OS4 and MorphOS ports also exist | Rebuild on GFOpenGPU/GFOpenAudio/GFOpenInput; keep tracker UI | Import AROS patch set, clean GCC16 build, audio first light |
| Schism Tracker | Music / Tracker | YES | MEDIUM | CREATE / standalone revival | P1 | Create and edit Impulse Tracker-style module music without another platform | REVIVAL CANDIDATE | Current SDL2/GCC project; upstream notes portability to architectures including m68k | Rebuild on GFOpenGPU/GFOpenAudio/GFOpenInput; retain tracker UI and keyboard workflow | Pin current release and prove GCC16/Open SDL2 build |
| libopenmpt / openmpt123 | Music / Module Playback | YES | MEDIUM | FOLD INTO DataTypes/GFOpenPlay + keep CLI | P1 | Play, render and inspect a wide range of tracker module formats locally | FOUNDATION CANDIDATE | Current cross-platform library/CLI with actively maintained 2026 releases | Shared module decoder beneath players/editors plus native CLI renderer/player | Pin 0.8.x, GCC16 build and MOD/XM/S3M/IT playback tests |
| Furnace | Music / Chiptune | YES | MEDIUM | CREATE / standalone revival | P2 | Compose and export multi-system chiptune without leaving AmiCradle | CANDIDATE | Current GPL tracker with SDL/OpenGL/software-renderer support | Prefer GFOpenGPU/GFOpenAudio backend; assess software-renderer path first | Pin current source, dependency audit and first UI/audio build |
| Radium | Music / Tracker | YES | MEDIUM | CREATE / standalone revival if retained | P2 | Advanced music composition/tracker workflow | INVESTIGATE | Present in AROS Contrib | Assess as higher-end tracker/music workstation | Licence/dependency/current-upstream review |
| OpenTranscode | Video / Transcoding | YES | HIGH | CREATE | P1 | Video conversion, resizing, codec/container delivery jobs | NEW APPLICATION | OS4 FFmpegGUI / VideoClipper style prior art proves GUI-over-FFmpeg model | Native GFOpenGadTools transcoder using FFmpeg + OpenMedia hardware acceleration | UI/job model and one H.264 -> H.265 hardware-assisted transcode proof |
| OpenVideoEdit | Video / Editing | YES | HIGH | CREATE | P1 | Cut, arrange, trim, filter and export video projects without another platform | NEW APPLICATION | MLT and existing Amiga-family FFmpeg work provide reusable engine prior art | Native AmiCradle NLE UI over MLT/FFmpeg/OpenMedia; background render/export through GFOpenMulticore | Define MVP timeline, two video/audio tracks, trim/cut, transitions, preview and export |
| MLT Framework | Video / Editing Infrastructure | YES | HIGH | FOLD INTO OpenVideoEdit infrastructure | P2 | Reusable non-linear editing engine for OpenVideoEdit and automation | FOUNDATION CANDIDATE | Current cross-platform multimedia framework; upstream explicitly targets NLE/broadcast/transcode use | Build engine without heavyweight desktop UI assumptions; map decode/encode to FFmpeg/OpenMedia | Pin current 7.x source, dependency audit and headless melt/render proof |
| MKVToolNix CLI | Video / Container Tools | YES | MEDIUM | FOLD INTO OpenTranscode/GFOpenFiles + keep CLI | P2 | Create, alter, inspect and repair Matroska files locally | CANDIDATE | Mature cross-platform CLI suite; Amiga-family prior art to be checked during intake | Port CLI tools first; native GUI only if a real workflow gap remains | Pin current source, isolate CLI dependencies and build mkvmerge/mkvinfo subset |
| GPAC / MP4Box | Video / Container Tools | YES | MEDIUM | FOLD INTO OpenTranscode/GFOpenFiles + keep CLI | P2 | Package, inspect and manipulate MP4/HEIF/DASH/HLS media locally | CANDIDATE | Mature cross-platform media framework/tool suite; Amiga-family prior art to be checked | Start with MP4Box CLI; integrate OpenMedia/FFmpeg only where it materially helps | Pin current 26.x source and build minimal MP4Box feature set |
| OpenRecorder | Video / Capture | YES | HIGH | CREATE | P1 | Screen and audio capture | NEW APPLICATION | AROS Ports contains ScreenRecorder; OpenMedia already targets encode services | Native screen/audio capture recorder using ACRTG/GFOpenAudio/OpenMedia | Capture AC090 display + audio and encode one clip |
| GrafX2 | Graphics / Paint | YES | HIGH | CREATE / standalone revival | P1 | Pixel art and bitmap graphics creation | OS4-BASED PORT INTAKE / BACKEND DESIGN | OS4 source lineage in upstream (2008, 2.0.874 PPC release 2009); AROS x86_64 2.9 SDL2 patches; MorphOS 2.9 SDL2 | Rebase OS4 Amiga-specific paths/volume handling onto 2.9; replace SDL with native indexed screen + Intuition IDCMP, OpenGfx/GFOpenGPU acceleration and native image loading | Recover/adapt OS4 source changes, then GCC16 native screen/input build | [Porting record](ports/grafx2/PORTING.md) |
| LodePaint | Graphics / Paint | YES | MEDIUM | CREATE / standalone revival if retained | P2 | General image editing | REVIVAL CANDIDATE | AROS Ports contains port | Assess lightweight image editor role | Current-source and dependency review |
| ImageMagick | Graphics / Processing | YES | HIGH | FOLD INTO shared image-processing infrastructure + keep CLI | P1 | Scripted/batch image manipulation | REVIVAL CANDIDATE | AmigaOS 4 binary/source port exists | Native CLI image-processing suite | Recover portability changes and build a small command subset |
| Netpbm | Graphics / Processing | YES | MEDIUM | FOLD INTO shared image-processing infrastructure + keep CLI | P1 | Format conversion and simple image processing | REVIVAL CANDIDATE | AROS Contrib port exists | CLI image conversion toolkit | GCC16 clean build |
| Potrace | Graphics / Vectorisation | YES | MEDIUM | FOLD INTO vector editor/GFOpenFiles + keep CLI | P1 | Bitmap-to-vector conversion | REVIVAL CANDIDATE | AROS Ports port exists | Bitmap-to-vector CLI utility | GCC16 clean build and SVG/EPS output test |
| VectorInk / Method Draw lineage | Graphics / Vector Editing | YES | HIGH | CREATE / vector editor product | P1 | Create and edit SVG artwork, logos, diagrams and icons without another platform | REVIVAL / ENGINE CANDIDATE | MorphOS VectorInk 1.1 is based on Method Draw/SVG-edit and proves the workflow on an Amiga-family OS | Prefer the permissive SVG-edit/Method Draw core or equivalent portable logic with an AmiCradle/GFOpenBrowser-friendly or GFOpenGadTools shell; do not import a heavyweight GTK stack | Recover exact source/provenance used by VectorInk, test it in GFOpenBrowser, then decide web-shell versus native GFOpenGadTools wrapper |
| POV-Ray | 3D / Rendering | YES | MEDIUM | CREATE / standalone revival | P1 | Offline 3D rendering | REVIVAL CANDIDATE | AROS Contrib port exists | Offline renderer and strong 64-192-core GFOpenMulticore workload; preserve CLI/batch use and add Open-family integration only where useful | Recover AROS build, render reference scene, then measure tiled/scene parallelism through GFOpenMulticore |
| Blender 2.4x lineage | 3D / Authoring | YES | MEDIUM | CREATE / standalone revival if pursued | P3 | 3D modelling/authoring reference path | PRIOR ART / STRETCH | AmigaOS 4 Blender 2.48 lineage exists | Historical source/portability reference; not the immediate 3D authoring target | Study OS4 changes and decide if a scoped legacy Blender revival has value |
| Ignition | Office / Spreadsheet | YES | HIGH | CREATE / standalone spreadsheet revival | P1 | Create, calculate, chart and exchange spreadsheet work without another platform | REVIVAL CANDIDATE | Open-source AmigaOS spreadsheet written in C; GPLv3 source release 1.10 available | Revive for GCC16/AC090, modernise UI/integration, preserve native Amiga workflow; add GFOpenMulticore only for recalculation jobs that actually benefit | Import source, audit SAS/C assumptions and external gadgets, produce fixed-GCC16 clean build |
| OpenPresent | Office / Presentation | YES | HIGH | CREATE | P1 | Create and edit presentations rather than only viewing PPTX/ODP through gfopendoc.datatype | NEW APPLICATION | No suitable open-source Amiga-family presentation editor found in current sweep; current MorphOS office suites provide feature/workflow reference | Native GFOpenGadTools/GFOpenGPU slide editor; reuse GFOpenWrite text/image handling, DataTypes, GFOpenPrint/PDF and existing PPTX/ODP conversion knowledge | Define MVP: themes, text boxes, images, shapes, slide order, presenter view, PPTX/ODP import/export |
| MuPDF / GFOpenView PDF backend | Documents / PDF | YES | HIGH | FOLD INTO GFOpenView | P1 | Read, navigate, search and print real PDFs without another platform | REVIVAL / PLATFORM INTEGRATION | MuPDF 1.28.x has current 2026 AmigaOS 4 and MorphOS ports | Use MuPDF as GFOpenView's PDF renderer; DataTypes/GFOpenView own the viewer UI, GFOpenPrint owns output | Recover current Amiga-family portability work, build MuPDF library on fixed GCC16 and render one PDF page into GFOpenView |
| QPDF | Documents / PDF Tools | YES | HIGH | FOLD INTO GFOpenView/GFOpenFiles + keep CLI | P1 | Merge, split, reorder, repair and transform PDF files locally | REVIVAL CANDIDATE | Current MorphOS office stack ships QPDF 12.4.1 | CLI first, then expose common operations through GFOpenView/GFOpenFiles without duplicating a full GUI | Pin current source, fixed-GCC16 build and merge/split/reorder smoke tests |
| Tesseract + Leptonica | Documents / OCR | YES | HIGH | FOLD INTO OpenScan/GFOpenService | P1 | OCR scans and images locally or across the host cores instead of using another platform | REVIVAL / OFFLOAD CANDIDATE | Current MorphOS Papio Office uses Tesseract and Leptonica for OCR | Prefer GFOpenService/GFOpenMulticore page-level jobs with a thin Amiga client; native libraries only where useful | Define OCR service boundary, prove one-page OCR, then batch pages across GFOpenMulticore |
| OpenScan | Documents / Scanning | YES | HIGH | CREATE | P1 | Scan from network scanners, crop/rotate, OCR and save searchable PDF without another platform | NEW APPLICATION | Current MorphOS IPP-Scan proves eSCL/AirScan, mDNS discovery, ADF/flatbed workflows, OCR and searchable PDF on an Amiga-family OS | Native GFOpenGadTools client using GFOpenSocket/GFOpenTLS/mDNS; Tesseract OCR via GFOpenService/GFOpenMulticore; MuPDF/QPDF/GFOpenPrint for document output | Implement discovery/capability query, scan one page, preview it, OCR it and save searchable PDF |
| OpenPublish | Office / Desktop Publishing | YES | HIGH | CREATE | P2 | Lay out brochures, newsletters, labels and print-ready pages without another platform | NEW APPLICATION | Current MorphOS DTP suites provide workflow prior art, but no suitable open-source source base has been selected | Reuse GFOpenWrite text/document model, VectorInk/SVG components, DataTypes and GFOpenPrint/PDF rather than importing a heavyweight desktop toolkit | Define MVP: text/image/vector frames, guides, master pages, multi-page layout and PDF export |
| CAD / Electronics toolchain | CAD / Electronics | YES | HIGH | CREATE / product family to be selected | P2 | Create/edit technical drawings, schematics and PCB work without another platform | RESEARCH GAP | MorphOS has DWG-reading and current native CAD-like utilities, but no clean open-source Amiga-family candidate has yet been selected | Do not choose a heavyweight Qt stack by default; research lightweight C/C++ engines and possible host-offload/GFOpenGPU approaches first | Candidate study: 2D CAD, schematic capture and PCB editing separately; select only credible source bases |
| OpenImageWriter | Storage / Image Writing | YES | HIGH | CREATE | P1 | Write .IMG and .ISO images to SD cards, USB removable media and CD/DVD without another platform | NEW APPLICATION | Amiga-family image-writing tools may inform behaviour, but OpenImageWriter itself is an all-GFOpenAmiga/AmiCradle implementation | Native GFOpenGadTools application with our own media-writing engine. SD/USB use the AmiCradle removable/block-device abstraction; CD/DVD use our own optical-device/transport layer. OpenImageWriter owns target validation, raw/image streaming, progress, verification and error recovery. No FryingPan or other third-party application/backend dependency | Define the common image-writer contract, prove write+verify to SD/USB, then implement ISO burn+verify over our own optical transport |
| FryingPan | Storage / Optical Media | YES | HIGH | CREATE / standalone revival | P1 | Optical-disc mastering, ISO creation and CD/DVD burning without another platform | STRONG REVIVAL CANDIDATE | AROS Contrib source explicitly targets AROS, OS3, MorphOS and OS4; application/supporting libraries are LGPL | Revive on fixed GCC16; map physical-drive access to the Amiga/AmiCradle optical device/service layer rather than host-specific code | Build OS3 target with GCC16, inventory drive transport assumptions and create/burn a test ISO |
| xorriso | Storage / Disc Images | YES | MEDIUM | FOLD INTO FryingPan/GFOpenFiles/Build Lab + keep CLI | P2 | Create, inspect, modify and verify ISO images locally | REVIVAL / BACKEND CANDIDATE | AROS Contrib has a 2026 xorriso 1.5.8 patch; its AROS libburn transport is deliberately dummy/file-only | CLI/file-image backend for FryingPan/GFOpenFiles/Build Lab where useful; do not claim physical burning until an AmiCradle MMC transport exists | Reproduce AROS 1.5.8 build on fixed GCC16 and exercise ISO create/list/extract/verify |
| Vim | Developer / Editor | PARTLY / OPTIONAL | LOW | CREATE / optional standalone revival | P3 | Optional modal/terminal editing for users who specifically want Vim; GFOpenEdit already covers the core source-editing need | OPTIONAL REVIVAL | AROS Ports port exists | Keep as a compatibility/power-user port, not as the primary AmiCradle editor | Only revive after GFOpenEdit/Build Lab workflows are qualified |
| libgit2 + OpenGit | Developer / Source Control | YES | HIGH | CREATE OpenGit; fold libgit2 underneath | P1 | Clone, branch, diff, commit, fetch, pull and push without leaving AmiCradle | NEW APPLICATION / LIBRARY PORT | No useful current AROS Git client found in the first sweep; libgit2 is a portable library route that avoids much of full Git's Unix toolchain surface | Port libgit2 on fixed GCC16 and wrap it in a small Amiga CLI/GFOpenGadTools client using GFOpenSocket/GFOpenTLS | Pin libgit2, audit filesystem/TLS/thread assumptions, then clone/status/commit/push a test repository |
| Lua | Developer / Scripting | YES | MEDIUM | FOLD INTO shared scripting/runtime infrastructure | P1 | Run automation, build helpers and application scripts natively | REVIVAL / FOUNDATION CANDIDATE | AROS Contrib already carries Lua and multiple AROS ports depend on it | Current lightweight Lua interpreter/compiler for GCC16; expose Open-family bindings only when concrete consumers need them | Identify current sensible Lua baseline, reproduce an AROS-derived GCC16 build and run interpreter/module tests |
| gnuplot | Scientific / Plotting | YES | MEDIUM | CREATE / standalone revival + integrations later | P1 | Plot functions and datasets and export publication-ready graphs without another platform | REVIVAL CANDIDATE | MorphOS has a gnuplot 5.2.2 port; upstream remains portable and CLI-centric | Native CLI first with SVG/PNG/PDF outputs; integrate with GFOpenWrite/OpenPresent only where useful | Pin current source, recover MorphOS/Amiga portability assumptions, fixed-GCC16 build and plot CSV/function samples |
| Mathomatic | Scientific / Maths | PARTLY / OPTIONAL | LOW | CREATE / standalone revival if retained | P3 | Symbolic mathematics | REVIVAL CANDIDATE | AROS Ports port exists | Scientific/education utility | Clean build |
| OpenAL / freealut | Audio / Compatibility | PARTLY / OPTIONAL | LOW | FOLD INTO compatibility layer only | P3 | Compatibility for ports needing OpenAL-style APIs | PRIOR ART / COMPATIBILITY | AROS Contrib ports exist | Compatibility option only; GFOpenAudio remains preferred native target | Use only where it materially reduces port cost |

## Development environment and server stack

The application roadmap has a dedicated development/server track in [DEVELOPMENT_ENVIRONMENT.md](DEVELOPMENT_ENVIRONMENT.md).

**Objective:** an AmiCradle instance can edit, build, link, run and serve a real website end-to-end.

This track owns:

- GFOpenAmigaGCC 16.2 and its fixed toolchain baseline;
- GNU linker/binutils plus vasm/vlink;
- GNU Make, CMake, Ninja and pkg-config;
- debugger and source-control tooling;
- Lua, Python, PHP and the OpenNode service/runtime model;
- OpenHTTPD first-light server and OpenApache;
- GFOpenSocket, GFOpenTLS/GFOpenCrypto, OpenSQLite and OpenCurl integration;
- service lifecycle, logs, certificates, JSON/compression and server diagnostics.

The first acceptance gate is deliberately small: **serve a static page stored inside an AmiCradle instance to a browser outside that instance over GFOpenSocket.** HTTPS and dynamic endpoints follow.

### Communications ownership

**GFOpenBrowser**, **GFOpenMail**, **GFOpenFTP/GFOpenFiles** and **GFOpenPuTTY** already own the main communications workflows:

- web browsing -> GFOpenBrowser;
- mail -> GFOpenMail;
- file transfer -> GFOpenFTP/GFOpenFiles;
- SSH, Telnet, raw and serial terminal access -> GFOpenPuTTY;
- networking and secure transport -> GFOpenSocket/GFOpenTLS/GFOpenCrypto.

GFOpenPuTTY is already a working AmigaOS 3.2.x application and should remain the remote-shell/terminal product. Applicationports should not create a competing SSH terminal unless a genuinely distinct workflow emerges.

### Missing-workflow rule

When no credible port exists, record the **workflow gap** rather than naming a fashionable heavyweight application. A new Open-family application may be the better answer when it can reuse existing GFOpenWrite, GFOpenView, GFOpenPrint, DataTypes, GFOpenGPU, GFOpenAudio, OpenMedia and GFOpenMulticore services.

### Developer-tool ownership

- **GFOpenEdit** is the primary native source/text editor; another editor must offer a distinct workflow rather than duplicate basic editing.
- **GFOpenAmigaGCC 16.2** is the compiler baseline, including ACKitchenB.
- **ACKitchen/Build Lab** owns the integrated build/debug experience and may use the 64-192-core host environment for compilation and analysis.
- Applicationports should fill missing *user workflows* around that stack: source control, scripting, specialist editors and reusable build-time libraries.

### Removable image-writing rule

**OpenImageWriter** is an all-GFOpenAmiga/AmiCradle application. It does not depend on FryingPan or another external burning application/library for any target.

Its architecture is:

- **SD / USB / removable block media** -> our removable/block-device abstraction;
- **CD / DVD** -> our own optical-device/transport implementation;
- **OpenImageWriter** -> common image stream, target validation, capacity checks, progress, verification, retry/error reporting and user workflow.

External Amiga-family image writers may be studied as behavioural prior art, but their code is not a runtime or architectural dependency.

Safety is part of the product contract: fixed/system disks must not be casually selectable, exact target identity and capacity must be shown before writing, destructive writes require explicit confirmation, and read-back verification should be offered by default.

### Storage and optical rule

Optical/media tools should solve complete workflows and use AmiCradle-owned device abstractions. **OpenImageWriter** owns raw image writing to SD, USB and optical media using our own code and transport layers. **FryingPan** may remain a separate revival candidate for broader disc-authoring workflows, but it is not a dependency of OpenImageWriter. **xorriso** may remain a separate CLI/image-manipulation candidate, but OpenImageWriter does not depend on it either.

### Office and document ownership

- **GFOpenWrite** owns word processing and document conversion/editing; do not revive standalone Word converters that duplicate it.
- **GFOpenBase** owns database/application-builder work; MUIbase remains prior art, not a competing shipping target.
- **gfopendoc.datatype** owns broad document viewing through the service path, including DOCX/XLSX/PPTX/OpenDocument and legacy office formats.
- **GFOpenPrint** owns PDF creation/printing; **GFOpenView + MuPDF** should own full PDF reading.
- Spreadsheet editing remains a real gap: **Ignition** is the preferred revival candidate.
- Presentation editing remains a real gap: **OpenPresent** is the native product target unless a suitable open-source Amiga-family editor emerges.

### Graphics product rule

- **GFOpenView/DataTypes own viewing**, so a separate image-viewer port is not maintained here.
- Prefer **one strong tool per workflow** over multiple overlapping paint/processing packages.
- Vector editing is a real workflow gap; MorphOS VectorInk/Method Draw prior art is preferred over carrying a heavyweight modern GTK/Qt desktop stack onto 68k.
- Offline rendering is especially valuable on AmiCradle because GFOpenMulticore can expose the expected 64-192 host cores.

### Media playback ownership

Routine media playback is not an application-port backlog item. **GFOpenPlay** is the native datatype-driven player and **OpenAmigaVLC** is a separate existing project that drives OpenMedia. Applicationports should only add another playback application when it closes a workflow that those two cannot reasonably cover.

### Video product rule

**OpenTranscode**, **OpenRecorder**, **OpenVideoEdit** and **OpenAmigaVLC** are the user-facing video products. HandBrake/libhb, historical AROS ScreenRecorder code and MPlayer are reference/engine prior art rather than separate shipping targets unless a later gap justifies reviving them directly.

### Audio editing product rule

**OpenAudioEdit** is the shipping audio-editor target. Audacity is a workflow and feature reference, not a port target. Reuse portable algorithms/libraries where licences and architecture make sense, but do not import a heavyweight desktop GUI/toolkit merely to preserve the Audacity application shell.

### Audio codec scope rule

Do not turn every codec supported by FFmpeg into a separate port project. Add a standalone codec/library only when it provides at least one of:

- a materially smaller/lighter native dependency than FFmpeg;
- a common upstream dependency for several applications;
- useful native CLI tooling;
- significantly better encode/decode quality or performance for its format;
- existing Amiga-family prior art worth reviving.

Formats such as WavPack, ALAC and other less-common codecs should normally be served through FFmpeg unless a consuming application gives us a concrete reason to maintain their native libraries separately.

## Create versus fold-in rule

Every candidate must state whether it should:

- **CREATE** — become a distinct user-facing application with its own workflow and identity;
- **FOLD INTO** — become capability inside an existing Open application/service;
- **CREATE / standalone revival** — remain recognisably the upstream application because that identity/workflow has value;
- **FOLD INTO + keep CLI** — provide reusable infrastructure to Open apps while retaining useful command-line tools.

Prefer folding capabilities into coherent products when a standalone application would merely duplicate an existing Open-family workflow.

## Platform ownership: OpenMedia and DataTypes

Before adding a media port, check whether the requirement is already satisfied by the AmiCradle media platform:

- **OpenMedia** owns hardware video codec sessions and zero-copy surfaces: H.264, HEVC, VP9, AV1, MPEG-2, VC-1 and JPEG, with decode/encode capability depending on the provider.
- **OpenAmigaMediaLibrary** already has working AC090-tested libwebp 1.6.0 and libvpx 1.17.0 decoder builds.
- **gfopenpicture.datatype** covers AVIF, HEIC/HEIF, JPEG XL, RAW, PSD, XCF, EXR, HDR, QOI, DDS, JPEG 2000, OpenRaster, Krita, CBZ, SVG and more through `media.decode/1`.
- **gfopensound.datatype** covers FLAC, Ogg/Vorbis, Opus, AAC/M4A, ALAC, WMA, MP3, MIDI, SID and module formats through `media.decode/1`.
- **gfopenmodule.datatype** plays module formats locally using libxmp, with a GFOpenMulticore/offload ladder.
- **gfopenvideo.datatype** covers MP4/MOV, MKV, AVI, WMV, MPEG, FLV and APNG through `media.decode/1`.
- **webp.datatype** and **webm.datatype** provide local WebP and VP8/VP9 paths.
- **GFOpenPlay** is already the user-facing datatype-driven media player.

Therefore, a codec/library does **not** get a standalone application-port row merely because a media format exists. Add it only when creation/editing/encoding, a concrete consuming application, or a material performance/compatibility reason requires a native library.

## Scale assumption: 64-192 host cores

AmiCradle application ports should assume that the surrounding host environment may expose **64 to 192 CPU cores** through GFOpenMulticore.

This does not mean every legacy application should be naively threaded. It means the port intake should explicitly identify work that can be parallelised or offloaded safely:

- media encode/decode pipelines;
- rendering and ray tracing;
- audio analysis, conversion and restoration;
- compression/decompression;
- image batch processing;
- build/compile workloads;
- transcoding queues and independent jobs;
- background indexing, OCR and document conversion.

Where upstream already uses pthreads, worker pools, task graphs or job queues, prefer mapping those onto GFOpenMulticore rather than serialising them for AmigaOS. Where a workload is embarrassingly parallel, the Amiga UI process should remain responsive while the heavy work is distributed across the available host cores.

The target is therefore **Amiga semantics at the application boundary, modern parallel execution underneath**.

## Priority lens

Before assigning engineering time, rank each candidate on:

- **Platform substitution value** — how much it removes the need to use another platform.
- **User value** — how useful the completed workflow is.
- **Probability of success** — likelihood of reaching useful first light on AC090.
- **Reuse value** — whether the port unlocks multiple applications or workflows.
- **Open-family value** — whether it proves or strengthens OpenMedia, GFOpenAudio, GFOpenGPU, GFOpenInput, GFOpenMulticore, GFOpenPrint or related services.
- **Parallel scale value** — whether useful work can exploit the expected 64-192 core host environment through GFOpenMulticore or independent job execution.
- **Effort** — engineering and maintenance cost.
- **Dependency friction** — external libraries/toolchains required first.
- **Workflow completeness** — whether the result solves the whole user task or only one fragment of it.

A technically impressive port that still forces the user onto another platform to finish the job should normally rank below a smaller port that closes a complete workflow.

## Standard intake rule

Before writing Amiga portability code for any application:

1. inspect AROS Contrib and AROS Ports;
2. inspect Aminet and classic AmigaOS source/patches;
3. inspect OS4Depot;
4. inspect MorphOS Storage;
5. inspect current upstream;
6. identify which historical patches are still relevant;
7. map graphics/audio/input/media/threading to Open-family interfaces;
8. pin source and produce a reproducible GCC16 build recipe.

## Porting styles

Every backlog item should eventually be classified as one of:

- **Native revival** — retain the original application's UI and port it cleanly.
- **Engine + Open UI** — reuse portable core functionality but build a native AmiCradle UI.
- **CLI foundation** — expose a command-line engine/tool first.
- **Open service client** — make expensive work use OpenMedia/GFOpenGPU/GFOpenAudio/GFOpenMulticore.
- **Prior-art only** — mine old Amiga-family patches without shipping that historical application.
