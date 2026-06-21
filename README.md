# frename

Simple CLI tool to rename files in bulk based on a user-provided naming standard. It scans a directory for files matching a pattern, finds gaps in the numeric sequence, and renames non-matching files to fill those gaps before extending the sequence.

## Build

Requires CMake 3.20+ and a C++20 compiler.

```bash
git clone https://github.com/r3ichal/frename.git
cd frename
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

The binary will be at `build/frename`.

### Install system-wide

```bash
sudo cmake --install build
```

### Windows (cross-compile via MinGW)

```bash
cmake -B build-windows -S . -DCMAKE_TOOLCHAIN_FILE=mingw-toolchain.cmake
cmake --build build-windows
```

## Usage

```bash
frename -d <directory> -s <standard> [-l <delimiter>] [-r] [-h]
```

### Options

| Flag | Description |
|------|-------------|
| `-d` | Target directory to scan |
| `-s` | Base filename standard to match (e.g. `img` for files like `img_1.jpg`) |
| `-l` | Delimiter separating the standard from the index. Default: `_` |
| `-r` | Preview changes without renaming any files |
| `-h` | Show usage information |

### Example

Directory `./photos` contains 4 files: `img_1.jpg`, `img_3.jpg`, `vacation.jpg`, `screenshot.png`.

```bash
frename -d ./photos -s img -l _
```

`img_0.jpg` and `img_2.jpg` already match the standard and are left untouched. `vacation.jpg` and `screenshot.png` don't match it, so they're renamed to fill the gap below the highest index and extend past it — becoming `img_1.jpg` and `img_3.jpg`.

To preview without applying:

```bash
frename -d ./photos -s img -r
```