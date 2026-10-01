# IBKR_SMA_STRATEGY

## Project Summary

Simple Moving Average (SMA) backtester integration implementned in modern C++ (C++23). The repo contains:
- deterministic backtester (SMA strategy)
- CSV input loader and deterministic trade logging

## Features
- Backtesting engine with configurable parameters for SMA strategy
- CSV dataset loader and example dataset(s) for backtesting
- Deterministic portfolio simulation with order execution and PnL calculation (sample output `console_output.txt`)
- Unit tests, integration tests, and performance benchmarks for the backtester and order-simulation engine
- Optional: TWS API integration using protobuf-generated bindings for live trading experiments

## Compiling and Execution

### Prequisites
- Visual Studio (MSVC) with C++23 workload (Windows) or GCC/Clang on Linux/macOS
- Build: CMake (>= 3.25) and Ninja build system
- Dependency Management: vcpkg package manager (manifest mode)


Required vcpkg packages (from `vcpkg.json`):
- Protobuf (5.29.5) compiler (protoc) for generating C++ classes from .proto files
- Intelrdfpmathlib 
- cpr
- glaze
- magic-enum

Notes: 
- `Threads` is used for standard threading support for concurrent execution
- On Windows the project may link the `ws2_32` library when TWS API code is enabled.

## Quickstart - Build (Windows PowerShell, MSVC + Ninja)

1. From project root, configure with vcpkg toolchain (adjust path):
```powershell
cmake -S . -B build -G "Ninja" `
  -DCMAKE_BUILD_TYPE=Release `
  -DCMAKE_TOOLCHAIN_FILE="C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

2. Build:
```powershell
cmake --build build --config Release
```

3. Run demo/backtest (adjust binary path/name):
```powershell
.\build\apps\your_backtester_exe.exe --input apps/VOO_1d_data.csv --output build/results/console_output.txt
```

4. Optional: disable TWS/protobuf generation if you only need the backtester core:
```powershell
cmake -S . -B build -G "Ninja" ` 
  -DBUILD_TWS_API=OFF `
  -DCMAKE_TOOLCHAIN_FILE="C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build build --config Release
```

## Testing

- GoogleTest + GoogleMock are used for unit and integration testing.
- Unit tests: SMA computations, signal generation, order sizing, portfolio/accounting math, CSV parsing
- Integration tests: short deterministic backtest on small CSV asserting final capital and trade count

### Using vcpkg for Dependency Management

This project utilizes Microsoft's `vcpkg` package manager in **Manifest Mode** for C++ 
libraries. 

#### Automated Dependency Management with Visual Studio 2022

- Building the code in Visual Studio 2022 and later versions is straightforward. The IDE 
automatically detects the `vcpkg.json` file and installs the required dependencies.

#### Manual Dependency Management with vcpkg

If you prefer to manage dependencies manually, you can use `vcpkg` commands to install 
the required libraries.

#### Generate the build configuration files using CMake
```bash
cmake -S . -B build \
	-DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config x64-release
```