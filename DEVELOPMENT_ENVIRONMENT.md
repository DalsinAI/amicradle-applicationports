# AmiCradle Development Environment

Snapshot date: **9 October 2026**

## Objective

> **An AmiCradle instance can build, run and serve a real website.**

The development environment is the complete in-instance workflow:

**edit -> build -> link -> run -> serve HTTP/HTTPS -> execute dynamic code -> access data -> inspect logs -> debug**

The AmigaOS instance owns the application, files, configuration, ports, service lifecycle and user-visible process model. Expensive work may execute on the available x86/ARM64 cores through GFOpenMulticore or GFOpenService where that is the correct architecture.

Primary target: **AC090 / AmigaOS 3.x / 68040 + FPU**, with **64-192 surrounding CPU cores** available to accelerated or offloaded workloads.

## Website First Light

A development instance reaches Website First Light when:

1. a site lives on an Amiga filesystem volume inside the instance;
2. an HTTP server starts from the Amiga environment;
3. it binds and listens through GFOpenSocket;
4. a browser outside the instance requests the site and receives 200 OK;
5. access and error logs are written inside the instance;
6. the server stops and restarts cleanly from the instance.

Then add HTTPS, a dynamic endpoint, SQLite-backed state, Node-compatible applications, and full build/debug/source-control inside the instance.

## Toolchain

| Component | AmiCradle treatment | Priority | Direction |
|---|---|---:|---|
| **GFOpenAmigaGCC** | Existing Open-family compiler | P0 | GCC 16.2 with the Team fixes; ACKitchenB uses this baseline. |
| **GNU binutils** - ld, as, ar, ranlib, nm, objdump, strip | Canonical GNU linker/binutils companion | P0 | Package and qualify exact versions with each GFOpenAmigaGCC release. |
| **vasm** | Native 68k assembler | P1 | Current reproducible build with Amiga syntax and object-format support. |
| **vlink** | Native linker | P1 | Companion to vasm and classic Amiga build systems; qualify beside GNU ld. |
| **GNU Make** | Native build tool | P0 | Required for a self-contained development instance. |
| **CMake** | Native build/configuration tool | P1 | Configure and build modern C/C++ projects inside the instance. |
| **Ninja** | Parallel build executor | P2 | Useful with CMake; map independent compile work to GFOpenMulticore where sensible. |
| **pkg-config / pkgconf** | Dependency metadata | P1 | Discover Open-family and third-party libraries consistently. |
| **Autoconf / Automake / libtool compatibility** | Legacy build support | P2 | Carry only what real source trees require. |
| **GDB / OpenDebug integration** | Source debugger | P1 | Integrate with Build Lab instead of creating a disconnected debugger experience. |
| **OpenGit / libgit2** | Source control | P1 | Clone, diff, commit, fetch and push from inside the instance. |
| **GFOpenEdit / Build Lab** | Existing development UI | P0 | Primary edit/build environment. |

## Languages and runtimes

| Runtime | AmiCradle treatment | Priority | Direction |
|---|---|---:|---|
| **Lua** | Native lightweight runtime | P1 | Embedded scripting and application automation. |
| **Python 3** | Native core plus service acceleration where useful | P1 | Build tooling, automation and web applications; define a supported module subset first. |
| **PHP** | Native or service-backed web runtime | P2 | Dynamic web applications with SQLite support. |
| **Perl** | Compatibility/build runtime | P2 | Legacy build and server tooling. |
| **OpenNode** | Node.js-compatible AmiCradle runtime/service | P1 | The Amiga task owns lifecycle, cwd, environment, files, sockets and logs; modern Node/V8 executes on x86/ARM64 cores through a GFOpenService-style boundary. Do not make a native m68k V8 backend the primary plan. |

## Web and server stack

| Component | AmiCradle treatment | Priority | Role |
|---|---|---:|---|
| **OpenHTTPD qualification server** | Small all-GFOpenAmiga HTTP server | P0 | Prove bind/listen/accept, HTTP parsing, static file serving, logs, concurrency and service lifecycle. |
| **OpenApache / Apache HTTP Server 2.4.x** | Native/GFOpenSocket port where practical | P1 | Conventional full web server: static files, logs, virtual hosts, handlers and HTTPS. |
| **GFOpenSocket** | Existing Open-family networking | P0 | Listening sockets and network visibility from the instance. |
| **GFOpenTLS / GFOpenCrypto** | Existing Open-family security stack | P0 | HTTPS and accelerated crypto. |
| **OpenSQLite** | Existing working SQLite port | P0 | First website database. |
| **OpenCurl** | Existing working curl/libcurl port | P0 | HTTP/HTTPS client, health checks and API testing. |
| **CGI / handler bridge** | HTTP-server capability | P1 | First simple dynamic execution model. |
| **FastCGI-style service bridge** | GFOpenService worker model | P2 | Long-running dynamic workers without forcing heavy runtimes into the 68k server task. |
| **Node application bridge** | OpenNode plus GFOpenService | P1 | Node applications appear to run from the instance while V8 executes on x86/ARM64 cores. |
| **PHP application bridge** | Native or service-backed | P2 | Conventional PHP web stack. |

## Server-class support

| Component | Priority | Direction |
|---|---:|---|
| **Service manager** | P1 | Start, stop, status and restart website services from AmigaOS; integrate with Nursery/GFOpenService and instance startup. |
| **Access/error log tools** | P1 | Tail, filter and search logs from the Amiga environment. |
| **Certificate tooling** | P1 | Generate, import and manage keys/certificates around GFOpenTLS/GFOpenCrypto. |
| **DNS/mDNS development tooling** | P1 | Convenient local naming and advertising for development instances. |
| **SQLite CLI** | P1 | Query and inspect the first web database directly. |
| **Compression** | P1 | gzip/zlib and Brotli where useful for static assets and build tooling. |
| **JSON tooling** | P1 | Small formatter/query/parser for APIs, configuration and build scripts. |
| **Process/resource inspection** | P1 | Server tasks, listening ports, sockets, CPU/core activity and memory visible from AmigaOS. |

## Architecture

Static/dynamic site:

    external browser / GFOpenBrowser
              |
          GFOpenSocket
              |
      OpenApache / OpenHTTPD
          |            |
     static files   CGI / service bridge
                       |
             OpenNode / Python / PHP
                       |
                   OpenSQLite

OpenNode:

    Amiga Shell / service manager
              |
          OpenNode task
              |
         GFOpenService
              |
       x86 / ARM64 Node + V8
              |
    Amiga files / environment / sockets / logs

The website belongs to the Amiga instance even when a runtime uses other cores. Paths, configuration, startup, logs, process identity and service control remain Amiga-facing.

## Concurrency

Server software should be designed for the expected **64-192 core environment**. Use event-driven socket handling for connection fan-out, bounded Amiga worker pools for native tasks, and GFOpenMulticore/GFOpenService for CPU-heavy work. Do not blindly create 192 Amiga tasks.

## Delivery order

### DEV0 - static website first light
- GFOpenAmigaGCC + GNU binutils + GNU Make
- GFOpenSocket
- OpenHTTPD qualification server
- OpenCurl test client
- static HTML/CSS/images
- access/error logs

### DEV1 - secure website
- GFOpenTLS/GFOpenCrypto
- HTTPS
- certificate tooling
- service start/stop/restart

### DEV2 - native dynamic site
- CGI/handler contract
- OpenSQLite + SQLite CLI
- Lua and/or Python 3
- dynamic API endpoint plus database read/write

### DEV3 - modern JavaScript server
- OpenNode service contract
- pinned Node LTS runtime on x86/ARM64 cores
- npm/package workflow policy
- Node HTTP application served from the Amiga instance
- filesystem/socket/log semantics verified

### DEV4 - conventional server stack
- OpenApache 2.4.x
- PHP
- virtual hosts
- CGI/FastCGI-style workers
- reverse proxy/service routing where useful

### DEV5 - full development workstation
- vasm/vlink
- CMake/pkg-config/Ninja
- GDB/OpenDebug
- OpenGit
- Build Lab integration
- parallel builds through GFOpenMulticore

## Release test: This Amiga Runs A Website

A clean AmiCradle instance must be able to:

1. open a project in GFOpenEdit/Build Lab;
2. build a native helper with GFOpenAmigaGCC;
3. start its web stack from the Amiga;
4. serve a page stored on an Amiga volume;
5. accept a request from another machine;
6. serve the page over HTTPS;
7. execute at least one dynamic endpoint;
8. read and write an OpenSQLite database;
9. write access/error logs;
10. stop, restart and recover the service cleanly.

At that point the statement **this Amiga runs a website** is literally true rather than a demo trick.