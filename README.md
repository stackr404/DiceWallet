# Dice Wallet

<p align="center">
  <a href="https://opensource.org/licenses/MIT"><img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="MIT License" /></a>
  <img src="https://img.shields.io/badge/version-0.2.0-black" alt="Version 0.2.0" />
  <a href="https://github.com/stackr404/DiceWallet/issues"><img src="https://img.shields.io/github/issues/stackr404/DiceWallet?style=flat&color=2EA44F" alt="GitHub Issues" /></a>
</p>

---

<table>
  <tr>
    <td>
        <a href="assets/readme_images/ui_main_menu.jpg">
        <img src="assets/readme_images/ui_main_menu.jpg" alt="Main menu" width="120">
        </a>     
    </td>
    <td>
        <a href="assets/readme_images/ui_new_wallet_seed_instructions.jpg">
        <img src="assets/readme_images/ui_new_wallet_seed_instructions.jpg" alt="Main menu" width="120">
        </a>    
    </td>      
    <td>
        <a href="assets/readme_images/ui_new_wallet_dice_roll.jpg">
        <img src="assets/readme_images/ui_new_wallet_dice_roll.jpg" alt="Main menu" width="120">
        </a>    
    </td>
    <td>
        <a href="assets/readme_images/ui_new_wallet_verify_seed.jpg">
        <img src="assets/readme_images/ui_new_wallet_verify_seed.jpg" alt="Main menu" width="120">
        </a>    
    </td>
    <td>
        <a href="assets/readme_images/ui_wallet_display_seed_words.jpg">
        <img src="assets/readme_images/ui_wallet_display_seed_words.jpg" alt="Splash screen" width="120">
        </a>    
    </td>      
    <td>
        <a href="assets/readme_images/ui_wallet_view_public_key_btc.jpg">
        <img src="assets/readme_images/ui_wallet_view_public_key_btc.jpg" alt="Main menu" width="120">
        </a>    
    </td>         
  </tr>
  <tr>
    <td align="center">Main menu</td>
    <td align="center">Instructions</td>
    <td align="center">Dice roll</td>
    <td align="center">Confirm words</td>
    <td align="center">BIP39 mnemonic</td>
    <td align="center">View public key</td>    
  </tr>
</table>

**Dice Wallet** is experimental open-source wallet firmware for ESP32-2432S028 CYD (Cheap Yellow Display) boards. These boards are relatively inexpensive and easy to source. Dice Wallet is amnesic and works completely offline. 

When creating a new wallet it turns 100 to 200 physical six-sided dice rolls into a BIP39 seed phrase, then shows watch-only extended public keys (xpubs) as QR codes. 

The design prioritizes **verifiable entropy** and a short secret lifetime. The firmware never starts the Wi-Fi or Bluetooth radio and disables serial at boot. Secrets are held in RAM for the session and wiped on exit. The device does not store a seed in flash. Only xpubs are shown on screen, so another wallet (e.g. phone app) can import a watch-only wallet to view receive-only addresses.

To spend you would need to import the 24 word BIP39 mnemonic seed phrase into another wallet. This wallet does not reveal private keys, nor does it sign transactions.

Version: **0.2.0** (experimental; not a 1.0 release)

To install DiceWallet without compiling it, see [Installing a release](#installing-a-release).

---

## Why Dice?

Most hardware wallets rely on a hardware random number generator (TRNG). While modern TRNGs are excellent, they are opaque. Users must trust that the chip is not biased, that the firmware is not leaking entropy, that the software isn't actually using a PRNG (Pseudo Random Number Generator), and that the manufacturer did not insert a backdoor.

Dice Wallet takes a different approach:

1. The user rolls a physical die **100 to 200 times**. Advanced settings choose the count; the default is 128.
2. The device records each face (1–6).
3. A suite of statistical tests indicate whether the sequence looks like fair dice rolls.
4. The entered rolls are hashed with a domain separator into exactly 256 bits of BIP39 entropy. One hundred fair rolls are about 258.5 bits; 200 are about 516.9 bits.
5. A 24-word BIP39 mnemonic is generated.

The user can see every roll on screen, can re-roll if the tests fail, and can independently verify the mapping from rolls → entropy → mnemonic if they wish.

### Why 128 rolls is the default

A fair six-sided die has log2(6) ≈ 2.585 bits of entropy per roll. A 24-word BIP39 seed needs 256 bits. That is about 99 fair rolls. One hundred fair rolls are about 258.5 bits, which is just over the minimum. Two hundred are about 516.9 bits.

The default is 128, about 330.9 bits, because a real die is not a perfect fair source.

Casino-grade dice are precision made: sharp edges, balanced pips, and tight tolerances. A standard consumer die is not. Drilled or painted pips, air bubbles, rounded edges, and uneven faces all bias the result. The bias is usually small, and the fairness battery can miss a small bias at these sample sizes. Chi-square is a warning aid, not a proof that the die was fair.

128 rolls is the margin for that. A modestly imperfect consumer die can lose some entropy on every roll and still leave well more than 256 bits in the sequence. The domain-separated SHA-256 then compresses whatever was collected into exactly 256 bits of BIP39 entropy. Extra rolls do not make the seed longer than 256 bits. They make it more likely that a cheap die still supplied enough randomness before that compression.

One hundred remains available for a die the user trusts. Two hundred is there for a die the user does not. 128 is the default because it is the middle setting, and because it does not assume a casino die.

---

## Core Features

### New Wallet (Dice Entropy)

- Live visual die faces while entering rolls.
- Real-time progress toward the configured roll count (100–200).
- **Statistical fairness battery** (see [Fairness Testing](#fairness-testing) below).
- Three possible outcomes:
  - **Success** — all tests passed.
  - **Warning** — Chi-square (frequency) passed, but one or more secondary tests failed.
  - **Error** — Chi-square failed (die is biased or the sequence is not random).
- 24-word BIP39 mnemonic display (with optional BIP39 passphrase).
- Seed verification step (user re-enters selected words).

### Import Wallet

<table>
  <tr>
    <td>
        <a href="assets/readme_images/ui_import_wallet_words.jpg">
        <img src="assets/readme_images/ui_import_wallet_words.jpg" alt="Import words" width="150">
        </a>     
    </td>
    <td>
        <a href="assets/readme_images/ui_import_wallet_words_select.jpg">
        <img src="assets/readme_images/ui_import_wallet_words_select.jpg" alt="Select word" width="150">
        </a>    
    </td>              
  </tr>
  <tr>
    <td align="center">Import words</td>
    <td align="center">Select word</td>
  </tr>
</table>

Multiple input methods are supported so users can restore from any existing BIP39 seed:

| Method              | Description                                      |
|---------------------|--------------------------------------------------|
| Word entry          | Type letters; cycling suggestions from the wordlist |
| Word index          | Enter the 0-based index of each word (0–2047)    |
| Hex                 | Enter 0-based word indexes as hex (0x0-0x7FF)                 |
| Binary              | Enter 11-bit word indexes as binary (0000000000-11111111111)                    |

All methods validate the BIP39 checksum before accepting the seed.

### Selecting the 24th word

<img src="assets/readme_images/ui_import_wallet_words_24th_word.gif" alt="Select 24th word">

When importing a wallet using English words you have the option to select the 24th word. This feature could be useful if you have your own method of randomly selecting the first 23 words and you want a completely offline way to calcuate and select a valid 24th word.

A 24-word BIP39 mnemonic is 264 bits: 256 bits of entropy plus an 8-bit checksum. Each word is 11 bits. The first 23 words are 253 bits, so the last word carries the remaining 3 entropy bits and the 8-bit checksum.

After the first 23 words are entered, `bip39_valid_final_words()` tries all 8 possible values of those 3 bits. For each value it builds the 256-bit entropy, takes SHA-256, and uses the first hash byte as the checksum. The 24th-word index is those 3 bits followed by that checksum byte. The screen looks those 8 indexes up in the English wordlist.

The Select 24th Word screen shows one of those 8 words. `<` and `>` cycle through them. Select accepts the shown word. Any of the 8 produces a mnemonic with a valid checksum, but only the word from the original backup is the user's seed. The other 7 are different wallets.

### View the BIP39 seed phrase

<table>
  <tr>
    <td>
        <a href="assets/readme_images/ui_wallet_display_seed_words.jpg">
        <img src="assets/readme_images/ui_wallet_display_seed_words.jpg" alt="View words" width="150">
        </a>     
    </td>
    <td>
        <a href="assets/readme_images/ui_wallet_display_seed_int_indexes.jpg">
        <img src="assets/readme_images/ui_wallet_display_seed_int_indexes.jpg" alt="Integer word indexes" width="150">
        </a>    
    </td>      
    <td>
        <a href="assets/readme_images/ui_wallet_display_seed_binary.jpg">
        <img src="assets/readme_images/ui_wallet_display_seed_binary.jpg" alt="Binary word indexes" width="150">
        </a>    
    </td>        
    <td>
        <a href="assets/readme_images/ui_wallet_display_seed_dots.jpg">
        <img src="assets/readme_images/ui_wallet_display_seed_dots.jpg" alt="Dot grid" width="150">
        </a>    
    </td>     
  </tr>
  <tr>
    <td align="center">View words</td>
    <td align="center">Integer word indexes</td>
    <td align="center">Binary word indexes</td> 
     <td align="center">Dot map view</td> 
  </tr>
</table>


The view seed screen always opens on the 24 words, numbered 1 to 24. With **Wallet mode: Advanced** enabled in Settings, tapping the word list cycles through five views of the same mnemonic. In Simple mode the tap does nothing.

Each BIP39 word is an 11-bit index into the 2048-word English list, from 0 to 2047. The extra views show that index instead of the word.

| View | What it shows | Example for word 1, index 0 |
|------|----------------|------------------------------|
| Words | The English word | `1. abandon` |
| Integer | The index, 0–2047, four digits | `1. 0000` |
| Hex | The index as three hex digits | `1. 000` |
| Binary | The index as 11 bits, high bit first | `1. 00000000000` |
| Dot grid | The same 11 bits as a dot map (found on many physical punch plates). Black square = 1, whites square = 0. | one row of the grid |

The integer, hex, and binary lines are the same value. `0000`, `000`, and `00000000000` are all zero index. Index 2047 is `2047`, `7FF`, and `11111111111`.

The dot grid is a 24 by 11 plate. Each row is one word. Each column is one bit of that word's 11-bit index, with the high bit on the left. A black cell is a 1. A white cell is a 0. Up and down move a red highlight between rows, and the highlighted row number is shown beside the plate. The grid is the binary view drawn for a punch card or a transcription plate, it's not a different encoding.

All five views are the same 24 indexes. Changing the view does not change the seed.

### View Public Keys (Watch-Only)

After a seed is loaded (generated or imported), the device can derive and display, as a QR code, account-level extended public keys:

| Coin       | Path              | Serialization | Notes                  |
|------------|-------------------|---------------|------------------------|
| Bitcoin    | `m/84'/0'/0'`     | zpub          | Native SegWit (BIP84)  |
| Ethereum   | `m/44'/60'/0'`    | xpub          | BIP44                  |
| XRP        | `m/44'/144'/0'`   | xpub          | BIP44                  |

An optional BIP39 passphrase is supported and is wiped from memory after use. Under each xpub the device shows its key origin, for example `[73c5da0a/84'/0'/0']`. The first 8 hex characters are the master key fingerprint. It changes with every passphrase, so write it down with the seed: if a later session shows a different fingerprint, a different passphrase was typed.

### Settings

- **Screen** — Brightness and auto-blank timeout (saved to NVS).
- **Language** — Extensive localization (see [Languages](#languages)).
- **Advanced**
  - Die-roll count, from 100 to 200 (default 128, saved to NVS).
  - Auto-wipe timer (device wipes secrets after a configurable number of minutes of inactivity).
  - Manual secure wipe.
  - Exit / secure shutdown screen.
- **About** — Firmware version and the SHA-256 of the running app image, plus the Secure Boot state. Compare this hex to the published `firmware.sha256`. The running firmware reports this hash itself, so it only proves something when the line below it reads **Secure Boot On**: then the bootloader refused to start anything not signed by the release key. With Secure Boot off, modified firmware could show any hash.
- **Pre-delivery** — Burns the JTAG, UART-download, Bluetooth and ROM-console eFuses. It asks for confirmation first and refuses while Secure Boot is off, because burning `UART_DOWNLOAD_DIS` ends USB updates for good without protecting the flash.

### Security Hardening

- The firmware never initializes Wi-Fi or Bluetooth. The prebuilt Arduino libraries still contain the radio drivers; the Pre-delivery screen can burn the `DISABLE_BT` eFuse.
- Serial is disabled at boot.
- Secrets (rolls, mnemonic word pointers/indexes, passphrase, import buffers) are wiped with volatile stores that the compiler cannot optimize away.
- LVGL allocates from a wiping allocator (`src/app/lv_secure_alloc.cpp`): every block is zeroed when it is freed or moved by a realloc, so old label and textarea text (seed words, indexes, passphrase) does not stay in freed memory. Label and textarea text is also wiped before a screen is deleted.
- Additional scrubbing of free heap blocks, abandoned stack frames, the framebuffer, and the display GRAM.
- Optional automatic wipe after inactivity.
- Firmware can check whether UART download mode has been permanently disabled via eFuse.

---

## Fairness Testing

Before a new wallet is accepted, the entered sequence (100–200 rolls, depending on the setting) is subjected to the following tests (implemented in `src/dice/die_fairness.cpp`):

| Test                  | Purpose                                      | Failure Mode                  |
|-----------------------|----------------------------------------------|-------------------------------|
| **Chi-square**        | Face frequency uniformity                    | Biased die or non-random sequence |
| **Runs test**         | Too few / too many runs of high/low faces    | Human-faked patterns          |
| **Serial correlation**| Dependence between consecutive rolls         | Pattern bias                  |
| **Gap test**          | Distribution of gaps between specific faces  | Over-uniformity               |
| **Longest run**       | Extremely long runs of the same face or high/low | Suspicious streaks         |
| **Poker test**        | Frequency of 5-roll “hands”                  | Non-random grouping           |
| **Autocorrelation**   | Correlation at various lags                  | Hidden dependence             |

**Verdict logic**:
- Chi-square fails (5% level) → **Error** (user must start over).
- Chi-square passes but any other test fails → **Warning** (user may continue or re-roll).
- All tests pass → **Success**.

Each warning test uses a 1% level, so with an honest die about 4% of sequences get a warning (and about 5% get the chi-square error). The serial test is Good's serial statistic (36 − 6 = 30 degrees of freedom), because overlapping pairs are not independent; the poker test pools the rare hands into one class; the longest-run limits depend on the roll count; and the gap test also flags too few immediate repeats, which is how most made-up sequences give themselves away. `test/test_dice` checks the false-warning rate and a few made-up sequences.

This gives the user transparent, quantitative feedback about the quality of their entropy source.

---

## Entropy Pipeline

```
100–200 physical d6 rolls (faces 1–6, count from Advanced settings)
        │
        ▼
Domain-separated SHA-256
  (prefix: 'D','6',0x01, length=count + raw faces)
        │
        ▼
Exactly 256 bits of BIP39 entropy
        │
        ▼
BIP39 checksum (SHA-256 of entropy → first 8 bits)
        │
        ▼
24-word mnemonic (English wordlist by default)
```

The hashing step eliminates the bias that a naive base-6 → 256-bit modular reduction would introduce.

---

## Languages

The UI is fully translated. Supported languages include:

- English
- French, German, Polish, Swedish, Dutch, Italian, Spanish, Portuguese
- Russian (Cyrillic font)
- Chinese (Simplified), Japanese, Korean (custom CJK fonts)

All language translations other than English may require modification by someone who speaks the language natively. 

Font assets are embedded as C arrays (`custom_*.c`) for the required character sets.

---

## Hardware

<a href="assets/readme_images/ESP32-2432S028-CYD-cheap-yello-display.png">
  <img src="assets/readme_images/ESP32-2432S028-CYD-cheap-yello-display.png" alt="ESP32-2432S028 CYD (cheap Yellow Display)" width="250">
</a>    


Target platform: **ESP32-CYD** (Cheap Yellow Display) boards running the Arduino framework via PlatformIO.  
These boards are inexpensive, widely available, and include a color touchscreen with enough resources to run Dice Wallet comfortably.

### Where to buy

Buy a generic **ESP32-2432S028** (CYD) board. Search for `ESP32-2432S028` or `ESP32 Cheap Yellow Display`. Confirm the listing is the 2.8 inch 240×320 resistive-touch board. Some panels are ST7789. This build expects ILI9341 but could be easily modified for other displays.

Dice Wallet is not affiliated with any of the sellers or links below.

- [AliExpress — ESP32-2432S028](https://www.aliexpress.com/item/1005011857768315.html)
- [Amazon — ESP32-2432S028](https://www.amazon.com/AOICRIE-Development-ESP32-2432S028R-Bluetooth-Resistive/dp/B0FFGZTGYN/ref=sr_1_6?th=1)

> **Privacy note:** Ordering a generic ESP32 development board does not create a customer record tied to crypto wallet firmware.

### Display & Touch

- **Display**: ILI9341 (`ILI9341_2_DRIVER`), 240×320, SPI. Some CYD boards are ST7789; this build does not enable `ST7789_DRIVER`.
- **Touch**: XPT2046 on its own SPI bus, chip select GPIO 33
- **Backlight**: PWM on GPIO 21

### Pinout (from `platformio.ini`)

| Signal     | GPIO |
|------------|------|
| TFT_MISO   | 12   |
| TFT_MOSI   | 13   |
| TFT_SCLK   | 14   |
| TFT_CS     | 15   |
| TFT_DC     | 2    |
| TFT_RST    | -1 (tied high) |
| TFT_BL     | 21   |
| TOUCH_CS   | 33   |

The project uses **TFT_eSPI** (Bodmer) + **LVGL 9**.

---

## Installing a release

You don't need to compile anything. Each [GitHub release](https://github.com/stackr404/DiceWallet/releases) has ready-made firmware files. You need a computer (Windows, macOS or Linux), a data USB cable, and Python 3 for `esptool`, Espressif's flashing tool.

### Choose a version

Each release comes in two versions. Pick one before you start.

| | Secure Boot (signed) | Unsigned |
|---|---|---|
| Files | `dicewallet-<version>-secure-bootloader.bin`, `-secure-partitions.bin`, `-secure-app.bin` | `dicewallet-<version>-unsigned-full.bin` (and `-unsigned-app.bin` for updates) |
| Board only runs DiceWallet releases | Yes. The bootloader checks the signature on every start. | No. Any firmware will run. |
| About screen | **Secure Boot On** | **Secure Boot Off: unverified** |
| Can you go back? | **No.** It is permanent for that board. | Yes. Flash anything else later. |
| Use it for | A board you will keep as a wallet | Trying DiceWallet, or a board you want to reuse |

> **Secure Boot is permanent.** On the first start of the signed version, the ESP32 burns the digest of the DiceWallet release key into its eFuses (one-time-programmable memory). From then on the board only starts firmware signed with that key, so it only runs official DiceWallet releases. You can never put unsigned, self-built or other firmware on that board again. Only flash the signed version if that is what you want.

The signed version needs an ESP32 chip revision v3.0 or later. Step 4 shows how to check.

### 1. Install esptool

`esptool` 5.x also installs `espsecure` (signature checks) and `espefuse` (eFuse status).

**Windows:** install Python from [python.org](https://www.python.org/downloads/) (tick *Add python.exe to PATH*), then in PowerShell:

```powershell
py -m pip install esptool
```

On Windows, start every command below with `py -m`: `py -m esptool`, `py -m espsecure`, `py -m espefuse`.

**macOS:** with [Homebrew](https://brew.sh/):

```bash
brew install pipx && pipx ensurepath   # then open a new terminal
pipx install esptool
```

**Linux (Ubuntu, Debian, Fedora):**

```bash
sudo apt install pipx        # Fedora: sudo dnf install pipx
pipx ensurepath              # then open a new terminal
pipx install esptool
sudo usermod -aG dialout $USER   # serial port access; log out and back in once
```

Check it works: `esptool version`.

### 2. Download the release

From the [Releases page](https://github.com/stackr404/DiceWallet/releases), download **every** file of the release into one empty folder, and open a terminal in that folder. In the commands below, replace `<version>` with the release version, for example `0.2.0`.

### 3. Verify the files

Verify before you flash. Each step must pass. If one fails, stop and don't flash.

**a) Check the public key.** `dicewallet-secure-boot.pub.pem` is the release public key. Its SHA-256 must be:

```text
79c0f81466f6b9ad0268db99330680b99ec2ee0e9598da69c358fe1f0d5bfb86
```

| OS | Command |
|----|---------|
| Linux | `sha256sum dicewallet-secure-boot.pub.pem` |
| macOS | `shasum -a 256 dicewallet-secure-boot.pub.pem` |
| Windows (PowerShell) | `Get-FileHash dicewallet-secure-boot.pub.pem` (prints upper case; same value) |

The same key is in this repository as [`secure/dicewallet-secure-boot.pub.pem`](secure/dicewallet-secure-boot.pub.pem). Compare against this README or the repository, not only the release page: anyone who could replace the release files could also replace a key uploaded with them.

**b) Check the signature on the checksum list.** `SHA256SUMS` lists the SHA-256 of every release file, and `SHA256SUMS.sig` is its signature by the release key. This covers the unsigned version too.

```bash
openssl dgst -sha256 -verify dicewallet-secure-boot.pub.pem -signature SHA256SUMS.sig SHA256SUMS
```

It must print `Verified OK`. macOS and Linux include `openssl`. On Windows it comes with [Git for Windows](https://git-scm.com/download/win):

```powershell
& "C:\Program Files\Git\usr\bin\openssl.exe" dgst -sha256 -verify dicewallet-secure-boot.pub.pem -signature SHA256SUMS.sig SHA256SUMS
```

**c) Check every file against the list.**

Linux:

```bash
sha256sum -c SHA256SUMS
```

macOS:

```bash
shasum -a 256 -c SHA256SUMS
```

Windows (PowerShell):

```powershell
Get-Content SHA256SUMS | ForEach-Object {
  $hash, $file = $_ -split '\s+', 2
  if ((Get-FileHash $file -Algorithm SHA256).Hash.ToLower() -eq $hash) { "OK      $file" } else { "FAILED  $file" }
}
```

Every line must say `OK`.

**d) Signed version: check the image signatures.** This is the same check the board's bootloader makes. Run it for each of the three signed files:

```bash
espsecure verify-signature --version 2 --keyfile dicewallet-secure-boot.pub.pem dicewallet-<version>-secure-bootloader.bin
espsecure verify-signature --version 2 --keyfile dicewallet-secure-boot.pub.pem dicewallet-<version>-secure-partitions.bin
espsecure verify-signature --version 2 --keyfile dicewallet-secure-boot.pub.pem dicewallet-<version>-secure-app.bin
```

Each must print `verification successful`. Lines saying `Signature block 1 invalid. Skipping.` are normal: a release has one signature, and the other two slots are empty.

**What this proves.** The files were released by whoever holds the DiceWallet signing key, and nobody changed them afterwards. It does not prove the firmware is free of bugs. To check the code itself, read the source at the commit named in the release notes.

### 4. Connect the board

Plug the CYD board in with a **data** USB cable (some cables only charge) and find its serial port:

| OS | Port looks like | How to find it |
|----|-----------------|----------------|
| Windows | `COM3`, `COM5` … | Device Manager → *Ports (COM & LPT)*. If nothing appears, install the [CH340](https://www.wch-ic.com/downloads/CH341SER_EXE.html) or [CP210x](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers) driver, depending on the USB chip on your board. |
| macOS | `/dev/cu.usbserial-XXXX` or `/dev/cu.wchusbserial-XXXX` | `ls /dev/cu.*` before and after plugging in. |
| Linux | `/dev/ttyUSB0` | `ls /dev/ttyUSB*` |

Replace `PORT` in the commands below with your port. For the signed version, check the chip revision first:

```bash
esptool --port PORT chip-id
```

The `Chip type` line must say `revision v3.0` or later (for example `ESP32-D0WD-V3 (revision v3.1)`). On older chips, use the unsigned version.

### 5. Flash

The `--flash-mode keep --flash-freq keep --flash-size keep` options make `esptool` write the files exactly as they are. Leave them in: changing the bootloader header would break its signature.

**Unsigned version:**

```bash
esptool --chip esp32 --port PORT write-flash --flash-mode keep --flash-freq keep --flash-size keep \
  0x0 dicewallet-<version>-unsigned-full.bin
```

**Signed version, first install** (this is the permanent step):

```bash
esptool --chip esp32 --port PORT write-flash --flash-mode keep --flash-freq keep --flash-size keep \
  0x1000  dicewallet-<version>-secure-bootloader.bin \
  0xD000  dicewallet-<version>-secure-partitions.bin \
  0x20000 dicewallet-<version>-secure-app.bin
```

On Windows, put the whole command on one line and start it with `py -m esptool`, for example:

```powershell
py -m esptool --chip esp32 --port COM5 write-flash --flash-mode keep --flash-freq keep --flash-size keep 0x1000 dicewallet-0.2.0-secure-bootloader.bin 0xD000 dicewallet-0.2.0-secure-partitions.bin 0x20000 dicewallet-0.2.0-secure-app.bin
```

Then press the board's **RST** button, or unplug and replug it. The first start of the signed version takes a few seconds longer, because the bootloader burns the key digest. **Keep the board powered until the DiceWallet main menu appears.**

If `esptool` says `Failed to connect`: hold the **BOOT** button, press and release **RST**, release **BOOT**, then run the command again.

### 6. Check the board

Open **Settings → About**:

- The firmware hash must match the **About screen hash** in the release notes for the version you flashed.
- The signed version must show **Secure Boot On**. If it shows **Secure Boot Off**, the board is not protected; don't use it as a wallet.

Optional, for the signed version: `espefuse --port PORT summary` should show `ABS_DONE_1` as True, and `BLOCK2` should no longer be all zeros. It holds the digest of the release key:

```text
410aa203e32b846927fd7dc147d658650f1e32c1229f084ffc2efa46d3b1691c
```

### Updating

**Unsigned board:** verify the new release (step 3), then flash the new `unsigned-full.bin` exactly as in step 5.

**Signed board:** verify the new release (step 3), then write only the new signed app:

```bash
esptool --chip esp32 --port PORT write-flash --flash-mode keep --flash-freq keep --flash-size keep \
  0x20000 dicewallet-<version>-secure-app.bin
```

The release notes say if a release also needs the new bootloader or partition table. In that case use the three-file command from step 5.

> **Never flash the unsigned version onto a Secure Boot board.** `esptool` will not stop you, but the board refuses to start unsigned firmware, so it stays dark. To recover, flash the three signed files again as in step 5.

If you use **Settings → Pre-delivery** to burn the lock eFuses, USB flashing is disabled for good and the board can never be updated.

---

## Building & Flashing

### Development environment

Development uses VS Code and the PlatformIO extension. The CLI commands below work in the PlatformIO terminal that the extension opens.

1. Install [VS Code](https://code.visualstudio.com/).
2. Install the PlatformIO IDE extension from the Extensions view. The extension installs the PlatformIO core and the toolchains it needs.
3. Open the Dice Wallet folder with File → Open Folder. PlatformIO reads `platformio.ini` from that folder. Do not open a parent directory.
4. The first build downloads the Espressif 32 platform and the libraries. That takes several minutes. Later builds are incremental.

The board used for development and testing is an ESP32-2432S028 CYD (Cheap Yellow Display). The PlatformIO board id is `esp32dev`. Other ESP32 boards need pin and driver changes. This build selects `ILI9341_2_DRIVER`. Some CYD panels are ST7789 and will not work with this configuration.

Connect the board with a data USB cable. On first plug-in the host may need a CP210x or CH340 driver, depending on the board's USB-UART chip. Select the serial port from the PlatformIO device list if upload cannot find it.

PlatformIO installs the libraries in `lib_deps`. They are not vendored in this repository:

| Library | Use |
|---------|-----|
| `bodmer/TFT_eSPI` ^2.5.43 | Display |
| `PaulStoffregen/XPT2046_Touchscreen` v1.4 | Touch |
| `lvgl/lvgl` ^9.6.0 | UI |
| `throwtheswitch/Unity` ^2.6.1 | On-device tests |

Build with the PlatformIO checkmark, or from the PlatformIO terminal:

### Build

```bash
pio run
```

### Upload

```bash
pio run -t upload
```

### Unit Tests

Official BIP39, BIP32, and SLIP-0132 vectors run on the device with Unity, using the default `esp32dev` environment. There is no separate test environment. `pio test` defines `UNIT_TEST`, so `main.cpp` does not supply `setup()` or `loop()`.

```bash
pio test
```

Vector files and their sources are in `test/test_vectors/`.

---

## Project Structure

```
.
├── platformio.ini          # Build configuration, pin defines, library deps
├── include/
│   ├── app/                # Wallet state, secure memory, version
│   ├── dice/               # Die fairness test declarations
│   ├── drivers/            # Display / hardware init
│   ├── ui/                 # LVGL screens, theme, text, assets
│   └── lv_conf.h           # LVGL configuration
└── src/
    ├── main.cpp            # setup() / loop(), LVGL timer, screen poll
    ├── app/                # Wallet rolls + generation state, secure wipe
    ├── bip39/              # Entropy → mnemonic, wordlist, checksum
    ├── coins/              # HD derivation (BIP32/secp256k1), coin registry
    ├── third_party/        # Vendored RIPEMD-160 (not in the Arduino Mbed TLS build)
    ├── dice/               # Statistical fairness tests
    ├── drivers/            # TFT + LVGL driver init, framebuffer wipe
    └── ui/
        ├── screens/        # One file per screen (new wallet, import, settings…)
        ├── text/           # Translation tables + custom fonts
        ├── theme/          # Color palette, layout constants
        └── assets/         # Icons (secure wipe, etc.)
```

### Key Modules

| Module                  | Responsibility                                      |
|-------------------------|-----------------------------------------------------|
| `bip39_generator`       | Dice rolls → 256-bit entropy → 24-word mnemonic     |
| `die_fairness`           | Battery of statistical tests on roll sequences      |
| `hd_coins`              | BIP32 derivation of account xpubs for BTC/ETH/XRP   |
| `third_party/ripemd160` | RIPEMD-160 for HASH160 in account xpub derivation   |
| `wallet`                | In-memory storage of rolls and generated mnemonic   |
| `secure_mem`            | Volatile wipes, heap/stack scrubbing                |
| `ui_*` screens          | All user-facing flows (LVGL)                        |
| `ui_text`               | Runtime language switching                          |


### Vendored RIPEMD-160

`derive_account_xpub()` needs HASH160, which is RIPEMD-160 of a SHA-256 digest. The Arduino-ESP32 Mbed TLS library is not built with `MBEDTLS_RIPEMD160_C`, so `mbedtls_ripemd160()` is not in the prebuilt library. `src/third_party/ripemd160.c` supplies that function.

The original file is:

https://github.com/Mbed-TLS/mbedtls/blob/mbedtls-3.6/library/ripemd160.c

Two lines were changed so the implementation is compiled into this firmware: line 16 and line 494, the `#if defined(MBEDTLS_RIPEMD160_C)` guard and its matching `#endif`. Both are commented out. The rest of the file is the upstream source.

---

## Usage Flow (High Level)

1. **Splash** — Identicon from the firmware hash, and security status. The hash hex is on About.
2. **Main Menu** — New Wallet / Import Wallet / View Public Keys / Settings.
3. **New Wallet**
   - Roll the die for the configured count, 100–200 (default 128).
   - Fairness report.
   - Display 24-word seed (+ optional passphrase).
   - Verify each of the 24-word seed.
   - Optional passphrase → view seed → display xpubs.
4. **Import** — Choose method → enter data → checksum validation → optional passphrase → seed display → view public keys.
5. **Settings** — Brightness, timeout, language, auto-wipe, about, secure exit.

On every transition away from a secret screen, the device performs a multi-stage wipe of RAM, heap, stack, and display memory.

---

## Design Principles

- **No network use** — The firmware never starts Wi-Fi or Bluetooth, and serial is disabled at boot. The ESP32 radio silicon, ROM bootloader, and USB-UART bridge are still on the board.
- **Verifiable entropy** — The user enters physical dice rolls. Statistical tests are a warning aid, not a proof that a die was fair.
- **Minimal secret lifetime** — Secrets exist in RAM while the device is powered on and are wiped on exit. They are not written to NVS.
- **Watch-only UI** — The screen shows xpubs. 
- **Transparent UI** — Every roll is visible; fairness results are explained.
- **Localization first** — Broad language support with proper fonts.

---

## Secure Boot

Secure boot is a separate environment, `esp32dev_secure`. The default `esp32dev` build is unsigned and leaves Secure Boot off.

Secure Boot v2 needs a bootloader built with `CONFIG_SECURE_BOOT`. A plain `framework = arduino` build always uses Arduino's prebuilt bootloader, which never checks signatures, and ignores any sdkconfig. So `esp32dev_secure` builds Arduino as an ESP-IDF component (`framework = arduino, espidf`). Its IDF settings are in `sdkconfig.defaults`, and its partition table is `partitions_secure.csv` (table at `0xD000`, because the secure bootloader is larger). PlatformIO builds the secure bootloader and signs the bootloader, partition table and app.

This needs an ESP32 revision v3.0 or later. Secure Boot v2 is not available on older ESP32 chips. Check first (your port may differ):

```bash
espefuse --port /dev/ttyUSB0 summary
```

### Signing Key

The private key lives outside the repository, at:

```text
~/.dicewallet/secure_boot_signing_key.pem
```

Or set the `DICEWALLET_SIGNING_KEY` environment variable to its path. `scripts/ask_signing_key.py` looks for it before the build. If the key is missing, the secure build **stops** with an error; it never produces an unsigned "secure" image.

Generate it once, on a machine you keep the key on:

```bash
mkdir -p ~/.dicewallet
espsecure generate-signing-key --version 2 --scheme rsa3072 ~/.dicewallet/secure_boot_signing_key.pem
chmod 600 ~/.dicewallet/secure_boot_signing_key.pem
```

Losing this file means no new firmware can ever be installed on a board whose digest was burned from it. Keep an offline copy. Do not commit it (`.gitignore` excludes every `*.pem` except the public key).

### Build and flash

```bash
pio run -e esp32dev_secure            # build and sign
pio run -e esp32dev_secure -t upload  # flash signed bootloader, partition table and app
```

The signed files are under `.pio/build/esp32dev_secure/`:

```text
bootloader-signed.bin
partitions-signed.bin
firmware-signed.bin
dicewallet-<version>-esp32dev_secure.signed.bin   (copy of firmware-signed.bin for releases)
```

Signing appends a signature block. It does not change the app validation hash, so the About screen still shows the hash that `firmware.sha256` lists.

On the first boot the secure bootloader writes the key digest into `BLOCK2` and burns `ABS_DONE_1`. After that, only images signed by this key will start. This is permanent.

### Verify

```bash
espefuse --port /dev/ttyUSB0 summary
```

Secure boot is on when `ABS_DONE_1` is True and `BLOCK2` is no longer all zeros. The splash screen and the About screen show **Secure Boot On** or **Secure Boot Off**.

Do not burn `ABS_DONE_1` by hand. Let the bootloader do it, so the digest matches the key that signed the image.

### Making a release

Releases are built and signed on the machine that holds the signing key, never in CI: a key stored as a CI secret could sign firmware that every Secure Boot DiceWallet board would accept. Binaries go on the GitHub Releases page, not into the repository (`release/` and `*.bin` are ignored).

1. Set the new version in `include/app/version.h` and the README, commit, and push.
2. Build, package and verify both versions:

   ```bash
   python3 scripts/make_release.py
   ```

   This builds `esp32dev` and `esp32dev_secure` and writes `release/v<version>/`: the three signed images, the merged unsigned image and the unsigned app, the public key, `SHA256SUMS`, `SHA256SUMS.sig` (signed with the release key) and `RELEASE-NOTES.md` (About-screen hashes, key digest and flash commands). It stops if the tree has uncommitted changes, and it checks every signature against `secure/dicewallet-secure-boot.pub.pem`, so a release can't be signed with any other key.
3. Publish as a GitHub release (it asks for confirmation, and needs `gh auth login`):

   ```bash
   python3 scripts/make_release.py --no-build --publish
   ```

   Or create the release on GitHub by hand, using tag `v<version>`, the notes from `RELEASE-NOTES.md`, and every file in `release/v<version>/` except the notes.

Never replace files in a published release. If something is wrong, release a new version, so published hashes never change.

---

## Limitations & Notes

- Experimental firmware for a development board. Not a 1.0 hardware wallet.
- No secure element. This is a development board running the seed in ordinary RAM.
- eFuse locks (JTAG, UART download, Bluetooth, ROM console) are optional and irreversible.

### Device threat model

The seed is not written to flash. It exists in RAM for the session and is wiped on exit. Power-off drops it. A later dump of the flash does not contain any secret data.

Remote attack is not feasible. The firmware never starts Wi-Fi or Bluetooth. An attacker needs physical access to the device itself.

#### Entropy weakness

The device does not create randomness. It records what the user enters and hashes it. The seed is only as unpredictable as the die rolls.

A fair physical die, rolled by hand, is the source this firmware is built for. The fairness battery can catch a sequence that is too even, too repetitive, or too patterned. It cannot tell a real die from a person copying numbers off a screen. A sequence that looks fair will pass.

Numbers from a website, a phone app, a spreadsheet, or another digital RNG are not dice rolls. Whoever runs that generator, or whoever watches the request, can know the sequence. The device will accept it, hash it, and produce a valid mnemonic. The checksum will pass. The wallet will look normal. The entropy came from a machine the user does not control.

Typing a pattern, reusing a sequence, or letting someone else call out the rolls is the same failure. The hash does not add randomness. It only compresses what was entered. One hundred twenty-eight copied numbers are still copied numbers.

The mitigation is the procedure, not a setting. Roll a physical die. Enter the faces yourself. Re-roll if the fairness screen warns. Do not import a sequence from a computer.

#### With secure boot

Secure Boot v2 is on, the download fuses are burned, and the user checked the About-screen hash against the published `firmware.sha256`. An unsigned image will not start. Replacing the firmware is closed, as long as the signing key stayed offline.

That leaves the powered-on window. The attacker has to have physical access and read the running device: the board is on, the session has not been wiped, and they can reach RAM or the display. Power-off ends that window. Secure boot does not hide the seed while it is on screen or in RAM.

#### Without secure boot

There is no signature check, so a different image will run. Before the seed is entered, the attacker replaces the firmware. The user then enters rolls or a mnemonic into that image. Burning the UART-download fuse closes the normal write path. It does not help if the attacker can reflash the chip another way, and it does not help if the image was already malicious when it was flashed. The About-screen hash does not help here: the replaced firmware reports whatever hash it likes. Only Secure Boot lets the device prove which image is running.

The powered-on window is the same as with secure boot. A running device with the seed in RAM can be read. Power-off ends that window.

#### Other threats

With physical access to the device, an attacker could swap the CYD board with one containing their own malicious firmware. Secure physical access to the device and make a mark on the device that you recognize and would be difficult to repeat.

---

## License

MIT License. SPDX-License-Identifier: MIT

Copyright (c) 2026 Dice Wallet contributors

Permission is granted to use, copy, modify, merge, publish, distribute, sublicense, and sell copies of this firmware. The copyright notice and license must be included in copies or substantial portions. The firmware is provided as is, without warranty. Full text: `LICENSE`.

---

## Acknowledgments

- **LVGL** — Lightweight embedded GUI library.
- **TFT_eSPI** — Fast SPI display driver.
- **mbedTLS** — Cryptographic primitives (SHA-256, ECC, PBKDF2).
- The BIP39 and BIP32 specifications.
- The statistical testing literature that inspired the fairness battery.

---

**Dice Wallet** — Entropy you can hold in your hand.
