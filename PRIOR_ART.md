# Amiga-Family Prior Art

Snapshot date: **9 October 2026**

Purpose: record existing AROS, classic AmigaOS, AmigaOS 4 and MorphOS application-port work that may reduce the cost or risk of AmigaChrome ports.

This is not a claim that historical source can always be reused directly. Licence, source availability, age, architecture and provenance must be checked per application.

## AROS Contrib / AROS Ports

AROS is especially valuable because it often contains explicit Amiga-like portability patches rather than only finished binaries.

### Multimedia and codec foundations

Confirmed in AROS Contrib:

- **FFmpeg 8.1.2**
  - explicit AROS target support;
  - static build;
  - m68k-specific configuration;
  - m68k recipe disables networking and HEVC decode;
  - patch file: `MultiMedia/libs/ffmpeg/ffmpeg-8.1.2-aros.diff`.
- **FLAC**
- **Ogg**
- **Vorbis**
- **Opus**
- **Speex**
- **Theora**
- **FAAD2**
- **OpenAL**
- **freealut**
- **MikMod**
- **ModPlug**
- **PTPlay**
- **SoX 12.17.4** portability patch.

These are high-value because FFmpeg/OpenMedia, game audio, media players, transcoding and audio-editing all depend on overlapping pieces of this stack.

### Applications

Confirmed AROS application prior art includes:

- **MilkyTracker 1.05.01**
- **ScreenRecorder**
- **Radium**
- **GrafX2 2.9** — [current AROS port project](https://github.com/tomaszstaniak/aros-grafx2) targets x86_64 and keeps SDL2; useful portability and behavior patches, not a native m68k port.
- **LodePaint**
- **ZunePaint**
- **ZuneView**
- **Netpbm**
- **Potrace**
- **POV-Ray**
- **XaoS**
- **c-ray**
- **MUIbase 3.3**
- **AROSPDF**
- **VPDF**
- **Text2PDF**
- **FryingPan**
- **Vim**
- **Antiword**
- **GOCR**
- **Mathomatic**

### Emulation

Emulator and emulator-frontend prior art is maintained in `DalsinAI/amigachrome-gameports/EMULATOR_PRIOR_ART.md`. Emulators are treated as part of the games catalogue rather than the productivity/application backlog.

## Aminet / classic AmigaOS

The classic 68k ecosystem is the most important prior-art source when code or patches are available because it is closest to our actual ABI/CPU target.

High-value discoveries from the current sweep:

- **FFmpeg** classic m68k history.

For classic ports, source availability must be checked carefully. A binary package is useful evidence but not automatically reusable implementation work.

## AmigaOS 4 / OS4Depot

OS4 is valuable for relatively modern upstream versions and for seeing how large Unix/SDL/C++ applications were adapted to Amiga APIs.

High-value findings:

- **FFmpeg 9.0.1** — modern Amiga-family FFmpeg evidence.
- **FFmpegGUI** — proves the small-native-GUI-over-FFmpeg application pattern.
- **VideoClipper** — another useful FFmpeg-driven workflow/UI reference.
- **MilkyTracker** SDL2 lineage.
- **ImageMagick 6.8.9** binary/source port lineage.
- **Blender 2.48** lineage.
- **GIMP 2.6** via AmiCygnix/X11.
- subtitle/editor utilities such as **SimpleSub**.

The main architectural lesson is that OS4 proves many large applications can be made Amiga-aware, but AmigaChrome should avoid copying heavyweight X11/GTK/Cygnix frontend strategies when an OpenGadTools/Open-family solution is cleaner.

## MorphOS Storage

MorphOS is especially valuable for maintained SDL2/OpenGL/FFmpeg-era applications and native non-SDL backends.

High-value findings:

- **MPlayer 1.5.2 / FFmpeg 6.1.6 lineage**
  - valuable source of Amiga-family video/audio/output portability ideas.
- **GrafX2 2.9**
  - current-ish graphics application precedent.
- **MilkyTracker 1.05**
  - corroborates AROS/OS4 tracker portability.
- native audio-editor applications such as **WaveEdit / SoundFX** for UI/feature reference.

## Implications for AmigaChrome

Emulator-specific implications and platform strategy live in `DalsinAI/amigachrome-gameports/EMULATOR_PRIOR_ART.md`.

### FFmpeg / transcoding

FFmpeg is now a **foundation project**, not a speculative application port.

Recommended architecture:

`OpenTranscode UI -> FFmpeg/libav* -> OpenMedia hardware acceleration`

Retain ffmpeg/ffprobe CLI tools for scripting and testing.

Use OS4 FFmpegGUI/VideoClipper as workflow references rather than copying their UI wholesale.

### Audio editing

No verified direct Audacity port was found in the official AROS sweep.

Recommended architecture:

`OpenAudioEdit UI -> SoX / libsndfile / FFmpeg / codec libs -> OpenAudio`

Use MorphOS audio editors and Audacity itself as feature/workflow references.

### Graphics

GrafX2 should be treated as a high-confidence revival candidate because multiple Amiga-family systems already have ports.

ImageMagick, Netpbm and Potrace are complementary CLI foundations rather than competitors to a paint application.

## Standard research record

For every new application candidate, capture:

- upstream project and exact source pin;
- licence;
- last upstream release/activity;
- AROS prior art;
- classic AmigaOS/Aminet prior art;
- AmigaOS 4 prior art;
- MorphOS prior art;
- GUI/toolkit dependencies;
- audio/video/graphics/input/threading dependencies;
- likely Open-family mappings;
- expected RAM/CPU footprint;
- redistributable versus user-supplied data;
- build status;
- AC090 runtime status.

The aim is to stop solving solved Amiga portability problems twice.
