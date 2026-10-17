# Star Wars Episode I: Racer — reverse engineering and modding

This repository is a Windows PC research and modding project for **Star Wars Episode I: Racer**. It documents selected parts of the original game, re-implements selected functions, and develops tools and runtime hooks for the modding community.

It is an ongoing reverse-engineering project, **not** a complete decompilation, a matching-compilation project, or a standalone recreation of the entire game. Most gameplay code still comes from the original executable.

## What lives in this repository?

| Area | Purpose |
| --- | --- |
| `src/` and `data_symbols.syms` | Function research, type definitions, addresses, and known global variables for the original game. |
| `scripts/` | Hook generation, asset extraction and validation, conversion tools, and developer checks. |
| `dinput_hook/` | The Windows `dinput.dll` mod: runtime hooks, the replacement renderer, debugging tools, and custom-track support. |
| `assets/custom_tracks/` | Legacy custom tracks stored as packed model/spline/texture blocks. |
| `assets/tracks/` and `assets/content/` | Manifest-based track definitions and content-addressed assets. This newer path is under active development; consult the code, issues, and pull requests for the exact current limits. |
| `src/generated/hook_generated.c` | Generated function-hook table. Change its source/template and regenerate rather than making a manual-only edit. |

The repository also contains a track catalog/browser path for discovering and downloading track assets. Treat network/catalog features as mod tooling, not as a requirement for the original game to run.

### Related projects

- **Upstream decompilation project:** [tim-tim707/SW_RACER_RE](https://github.com/tim-tim707/SW_RACER_RE). This repository is a working fork; check upstream for its broader reverse-engineering history and community changes.
- **Asset format tools:** [blender-swe1r](https://github.com/louriccia/blender-swe1r) and [swe1r-assets](https://github.com/akopetsch/swe1r-assets) are useful independent references for working with packed game assets.
- **GameCube/Wii prototype:** [boonta-reborn-88](https://github.com/Master-Chiken/boonta-reborn-88) is a separate project with its own code and roadmap. It is not built by this repository.
- **Community:** [Star Wars Episode I: Racer Discord](https://discord.com/servers/star-wars-episode-i-racer-441839750555369474).

## Quick start: build the PC mod

The supported mod build targets **32-bit Windows** and produces `dinput.dll`. The easiest documented setup is a Windows development environment with the LLVM-MinGW toolchain.

### Prerequisites

- Git
- Python 3 (CI currently uses Python 3.12)
- CMake 3.21 or newer
- Ninja, when using the provided CMake presets
- LLVM-MinGW targeting i686 Windows; the CI workflow pins [llvm-mingw 20260922](https://github.com/mstorsjo/llvm-mingw/releases/tag/20260922). A suitable WinLibs package that includes LLVM/Clang may also work.
- `jinja2` for hook/source generation scripts
- A legally obtained Windows game installation for in-game testing. The original executable and game assets are not included here.

### Configure and build

Run these commands from the repository root in a Windows terminal, with LLVM-MinGW available at `LLVM_MINGW_ROOT` or its `bin` directory on `PATH`:

```powershell
python -m pip install jinja2
cmake --preset clang-release -DGAME_DIR="C:/Games/Star Wars Episode I Racer"
cmake --build --preset clang-release
```

Replace the example path with your local game directory. When `GAME_DIR` is set, CMake places the built `dinput.dll` in that directory. Keep local paths and proprietary game files out of commits.

The presets use Ninja. If Ninja is unavailable, configure with the MinGW Makefiles generator and the repository toolchain file, then build the resulting directory:

```powershell
cmake -S . -B build/local -G "MinGW Makefiles" --toolchain cmake/toolchains/clang-mingw-i686.cmake -DGAME_DIR="C:/Games/Star Wars Episode I Racer"
cmake --build build/local
```

If you are only exploring the source and are not ready to build the DLL, start with the Python checks below and the reverse-engineering setup.

## Tests and validation

Run the platform-independent Python regression checks from the repository root:

```powershell
python tests/test_raw_model_validator.py
python tests/test_track_catalog_server.py
python scripts/Ghidra/CheckHeaderDuplicates.py
python scripts/Ghidra/check_data_symbols_dups.py
python scripts/check_hook_annotations.py
python scripts/check_hd_replacement_default.py
```

The GitHub Actions integrity workflow also builds the Windows mod in hardened Release mode, builds AddressSanitizer and UndefinedBehaviorSanitizer variants, runs the cinematic-audio regression test, and performs Clang static analysis. The asset-boundary workflow runs synthetic tests for malformed packed model/spline/texture blocks and asset round-trips. Check the current workflow results for the branch you are working on; results from an older commit do not validate newer changes.

### Sanitizers and static analysis

Available CMake build presets include `clang-asan` and `clang-ubsan`:

```powershell
cmake --preset clang-asan -DGAME_DIR="C:/Games/Star Wars Episode I Racer"
cmake --build --preset clang-asan

cmake --preset clang-ubsan -DGAME_DIR="C:/Games/Star Wars Episode I Racer"
cmake --build --preset clang-ubsan
```

The AddressSanitizer runtime is deployed next to the DLL when configured to do so. Reports are written under `<game directory>/crashes/`; symbolize a report with:

```powershell
python scripts/asan_symbolize.py "C:/path/to/game/crashes/asan.<pid>"
```

Make sure `llvm-symbolizer` from the same toolchain is on `PATH`, or pass its path with `--symbolizer`.

After configuring the Release preset, the static-analysis helper can be run with the generated compilation database:

```powershell
python scripts/static_analysis.py --cdb build/clang-release/compile_commands.json --out static-analysis --clang "C:/llvm-mingw/bin/clang.exe"
```

Only code compiled into `dinput.dll` is instrumented by these sanitizer builds; the original game executable is not.

## Reverse engineering with Ghidra

The documented decompilation workflow uses **Ghidra 10.2.2**. If you use another version, note it when reporting results so that other contributors can reproduce your setup.

1. Open the appropriate local game executable in Ghidra.
2. Parse the C source in `src/types.h` before importing function prototypes.
3. Run `scripts/Ghidra/GenerateMasterHeader.py` to generate `master_header.h`, then run `scripts/Ghidra/ImportHeaderInfos.py` inside Ghidra to import the header information.
4. Run `scripts/Ghidra/importDataSymbols.py` inside Ghidra to import global-variable addresses from `data_symbols.syms`.
5. Use disassembly, callers, data references, runtime observations, and a matching prototype to support any proposed implementation.

The source of truth for global-variable addresses is `data_symbols.syms`. Generated hooks are produced by `scripts/GenerateHooks.py` from `hook_generated_c.j2` and written to `src/generated/hook_generated.c`.

The upstream project reported **71.2% of functions analysed (1,518 of 2,132) on 12 June 2026**. “Analysed” does not mean “re-implemented”; this is a dated upstream metric, not a claim that this fork or the full game is 71.2% complete.

## Custom tracks and assets

There are two workflows in the repository:

- **Legacy packed-block workflow:** custom tracks under `assets/custom_tracks/` supply packed model, spline, and texture blocks.
- **Manifest/content-store workflow:** `scripts/convert_track_pack.py` compares a packed track with a local stock installation, extracts changed entries into discrete assets, and writes track manifests plus content-addressed blobs. The runtime's virtual-block layer substitutes declared entries and falls back to the local stock archive for entries the track does not provide.

The converter needs the original game's local `SWEP1RCR.EXE` and stock files under `data/lev01/` to identify stock track placement and compare packed entries. Those inputs must remain local and must not be committed.

For asset-format changes, prefer synthetic fixtures for automated tests. Where a lawful local installation is needed, record the game version, exact reproduction steps, and observed result without uploading the executable or proprietary data. A successful parser test alone does not prove that a track can be selected, loaded, raced, and exited safely; verify the in-game path separately.

## Contributing

Contributions of substantial size are welcome: function analysis, implementations, test coverage, asset tools, runtime features, performance work, build fixes, and documentation.

1. Read [CONTRIBUTING.md](CONTRIBUTING.md), [GOVERNANCE.md](GOVERNANCE.md), and [ACCESS_CONTROL.md](ACCESS_CONTROL.md).
2. Search existing issues and pull requests before starting work.
3. Use a focused branch and pull request. Larger architectural work should be coordinated early, but contributions are not limited to trivial fixes.
4. State exactly what you tested. Separate automated results from manual in-game testing and from assumptions that remain unverified.
5. Update the source/template rather than hand-editing generated files.

The Project Owner retains final review and merge authority for the project's default branch. See [GOVERNANCE.md](GOVERNANCE.md) for the intended workflow.

## Copyright and project boundaries

Star Wars Episode I: Racer and its original code, executable, and assets remain the property of their respective rights holders. This repository is an independent research and modding project and is not an official LucasArts or Star Wars product.

**Do not commit or redistribute the commercial game executable, disc images, unpacked proprietary game assets, asset dumps, credentials, or private local paths.** Share your own code, analysis, test fixtures that you may distribute, and documentation instead.

## Acknowledgements

Thanks to the original LucasArts team and to the community contributors who have worked on Racer's decompilation, asset formats, custom tracks, symbols, and renderer—including JayFoxRox, LightningPirate, Galeforce, Aphex, Urgon, Ben1138, Angello, tly000, and the wider SWEP1RCR community.

For technical notes and historical findings, see [NOTES.md](NOTES.md).
