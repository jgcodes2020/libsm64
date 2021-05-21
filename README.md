# libsm64
A project for interfacing with [Wafel](https://github.com/branpk/wafel)'s internal DLLs and doing SM64 stuff.
Currently, it depends on closed-source software (libsm64, [the SM64 Decomp](https://github.com/n64decomp/sm64), 
so all rights are reserved until further notice.

# Functionality
libsm64 provides:

- a (crude) interface to the internal Wafel DLLs
- a method of savestating the Wafel DLLs
- facilities for reading Mupen64 input files

This readme will be updated later when new functionality gets added.

# Building

## Requirements
- `python` 3.8+ (may work with earlier versions)
- `java` 8+

To build the project, simply clone the Git repository and run:

- `gradlew build` on Windows
- ~~`./gradlew build` on Linux~~ (Linux support coming as soon as bad_boot gets around to supporting it)

The resulting build files can be found in `lib/build/lib/main/debug`. Cheers!

# Notes
- I tried to add `clangd` support, but it's broken. If you want to try to fix it yourself run `gradlew rebuild`.
  The relevant code is in `lib/build.gradle` and `ccgen.py`.