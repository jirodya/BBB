# BeagleBone Black Embedded Linux Build (Learning Project)

> **Purpose & scope**: This repository is a **learning project** that blends instructions from EEL4734 class materials with **updated notes and practices** verified during my own build. It is **not** an official distribution. Upstream projects retain their own licenses and documentation.

---

## Repository Layout

* `external/` – external sources as Git submodules

  * `crosstool-ng/` – [Crosstool-NG](https://github.com/crosstool-ng/crosstool-ng)
  * `u-boot/` – [U-Boot bootloader](https://github.com/u-boot/u-boot)
* `docs/` – reference notes and assignment PDFs (for learning)
* `nc-tests/` – simple C test programs and their cross-compiled outputs (for verifying toolchain)

> Tip: build and output directories are intentionally ignored so the repo stays small and reproducible.

---

## Prerequisites

**OS**: Ubuntu 22.04+ recommended

**Packages** (build tools):

```bash
sudo apt-get update
sudo apt-get install -y gcc g++ make gawk bison flex texinfo help2man \
  autoconf automake libtool libtool-bin libncurses5-dev git wget xz-utils \
  libssl-dev pkg-config
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

We vendor the Crosstool-NG **source** as a submodule in `external/crosstool-ng/` but install the **binaries** outside of Git. This keeps the repo clean while making the tool easy to rebuild.

### Install Crosstool-NG (User-local install)

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
# Expected: This is crosstool-NG version 1.27.0.xxxxx
```

### Build the Toolchain

```bash
cd external/crosstool-ng
ct-ng arm-cortex_a8-linux-gnueabihf
ct-ng menuconfig   # confirm FPU = vfpv3, hard-float ABI, etc.
ct-ng build
```

This installs the toolchain under `~/x-tools/arm-cortex_a8-linux-gnueabihf/`.

### Toolchain Usage

Add to `PATH`:

```bash
export PATH="$HOME/x-tools/arm-cortex_a8-linux-gnueabihf/bin:$PATH"
```

Optional: add alias in `~/.bashrc` to shorten calls:

```bash
alias armhf-gcc="arm-cortex_a8-linux-gnueabihf-gcc"
```

Reference: [crosstool-NG usage guide](https://crosstool-ng.github.io/docs/toolchain-usage/)

### Test Programs

Inside `nc-tests/`, run:

```bash
arm-cortex_a8-linux-gnueabihf-gcc helloworld.c -o helloworld
arm-cortex_a8-linux-gnueabihf-gcc -static helloworld.c -o helloworld-static
arm-cortex_a8-linux-gnueabihf-gcc math_test.c -o math_test -lm
```

Check results:

```bash
file helloworld
readelf -a math_test | grep "Shared library"
```

### Submodules & Dirty State

You may sometimes see submodules reported as `-dirty`, e.g.:

```
Subproject commit eb03952-dirty
```

This happens if you ran `ct-ng menuconfig` or `ct-ng build` inside the submodule; Crosstool-NG generates temporary files (`.config`, build helpers) that make Git think the submodule is modified. This is expected and does not affect your parent repo.

Best practice:

* Ignore those changes; don’t commit them into the submodule.
* If you want to save your `.config`, copy it into `docs/` (e.g. `docs/ctng-bbb.config`).
* If you want to clean, inside the submodule: `git restore .` or `git clean -fdx`.

---

## U-Boot (Bootloader)

We vendor U-Boot as a submodule in `external/u-boot/`. Current tag: **v2025.07 (stable)**.

### Build U-Boot for BeagleBone Black

```bash
cd external/u-boot

# Environment
export PATH="$HOME/x-tools/arm-cortex_a8-linux-gnueabihf/bin:$PATH"
export CROSS_COMPILE=arm-cortex_a8-linux-gnueabihf-
export ARCH=arm

# Start clean
make distclean

# Configure for AM335x (BBB)
make am335x_evm_defconfig

# Optional: menuconfig tweaks (enable legacy image support, SD/eMMC boot)
make menuconfig

# Build SPL + U-Boot
make -j"$(nproc)"
```

The build produces:

* `MLO` – SPL (secondary program loader)
* `u-boot.img` – bootloader image
* `u-boot.bin`, `u-boot-dtb.img`, etc. – other formats

### Install to SD card (manual)

```bash
lsblk   # identify your SD card, e.g., /dev/sdb
./format-sdcard.sh sdb   # script provided in class/docs
cp MLO u-boot.img /media/<user>/boot/
sudo umount /media/<user>/boot
```

At next boot (with serial console), you should see a U-Boot prompt.

---

## Linux Kernel

*Not yet configured. Placeholder for when kernel setup begins.*

---

## Root Filesystem (RFS)

*Not yet configured. Placeholder for when rootfs setup begins.*
