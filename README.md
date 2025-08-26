# BeagleBone Black Embedded Linux Build (Learning Project)

> **Purpose & scope**: This repository is a **learning project** that blends instructions from EEL4734 class materials with **updated notes and practices** verified during my own build. It is **not** an official distribution. Upstream projects retain their own licenses and documentation.

---

## Repository Layout

* `external/` – external sources as Git submodules

  * `crosstool-ng/` – [Crosstool-NG](https://github.com/crosstool-ng/crosstool-ng)
* `docs/` – reference notes and assignment PDFs (for learning)
* `tools/` – helper scripts or local installs (ignored)
* `build/` – working build directories (ignored)
* `x-tools/` – generated cross toolchains (ignored)

> Tip: build and output directories are intentionally ignored so the repo stays small and reproducible.

---

## Prerequisites

**OS**: Ubuntu 22.04+ recommended

**Packages** (build tools):

```bash
sudo apt-get update
sudo apt-get install -y gcc g++ make gawk bison flex texinfo help2man \
  autoconf automake libtool libtool-bin libncurses5-dev git wget xz-utils
```

> These are sufficient for Crosstool-NG itself. Kernel/U-Boot may need a few extras later (documented in their sections).

**Disk**: \~25–50 GB free (toolchain + kernel + rootfs builds)

---

## Quick Start

```bash
# Clone and init submodules
git clone https://github.com/<your-user>/BBB.git
cd BBB
git submodule update --init --recursive
```

---

## Crosstool-NG (Cross-Compilation Tool)

We vendor the Crosstool‑NG **source** as a submodule in `external/crosstool-ng/` but install the **binaries** outside of Git. This keeps the repo clean while making the tool easy to rebuild.

### Install Crosstool‑NG (User‑local install)

```bash
cd external/crosstool-ng
./bootstrap
./configure --prefix="$HOME/.local"
make -j"$(nproc)"
make install
```

Add it to your `PATH` (temporary):

```bash
export PATH="$HOME/.local/bin:$PATH"
```

Make it permanent by adding the same line to `~/.bashrc` or `~/.zshrc`.

**Verify**:

```bash
ct-ng version
# Expected: This is crosstool-NG version 1.27.0.86_eb03952 (or close)
```

---

## U-Boot (Bootloader)

*Not yet configured. Placeholder for when U-Boot setup begins.*

---

## Linux Kernel

*Not yet configured. Placeholder for when kernel setup begins.*

---

## Root Filesystem (RFS)

*Not yet configured. Placeholder for when rootfs setup begins.*
