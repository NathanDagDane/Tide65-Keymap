# Custom QMK Keymap for Epomaker Tide65

Current support for QMK customisation on the Tide65 is non-functioning, as wireless code is not included in the official [qmk-firmware](https://github.com/qmk/qmk_firmware/tree/master/keyboards/epomaker/tide65) or [Epomaker](https://github.com/Epomaker/tide65) repositories.<br>
This means wireless functionality works when using the factory firmware, but compiling your own QMK firmware and flashing this to the board will result in a wired-only with no Bluetooth or 2.4GHz connectivity.

This repo is forked from a [pull request](https://github.com/qmk/qmk_firmware/pull/24209) focused on adding back the wireless functionality features. Here I have my own keymap configured, which you can compile using the following QMK MSYS command:<br>
<p align="center">
  <code>qmk compile -kb epomaker/tide65 -km mine</code>
</p>

I will include a description of my own keymap, and some tips on how you can make your own keymap using this repo.

> This repo also contains the <B>default keymap</B> for this keyboard, however this will <B>fail to compile</B> as, in the code's current state, the keyboard's general code is not separate from the keymap-specific code, and <B>I have modified this code</B> to work for my keymap.

> This code will <B>not</B> work for the <B>Tide75</B>. For this, you would need to correct all pins and layouts.

## Keyboard Layout

The keyboard has <B>68 keys</B> and <B>1 encoder</B>. These, along with their function on my keymap and their LED's index in the RGB matrix is shown below:

<div align="center">
    <picture>
        <source media="(prefers-color-scheme: light)" srcset="docs/readme/Tide65-Layout.png">
        <img class="image" src="docs/readme/Tide65-Layout-Dark.png" width="75%">
    </picture>
</div>

> Thele LED indexes took me too long to figure out and I have lost touch with reality.

When changing the keymap, such as changing the key for <B>BT1</B>, the indicator LED to light up also needs to be updated. This can be referenced form the diagram.

## My Keymap

The keymap `mine` has the following 7 layers:

* `_BL, _MBL` <B>Base layers</B> - These only differ in the modifier keys and respective layer shifts.
* `_FL, _MFL` <B>Function layers</B> - Active when <B>Fn key</B> held.
* `_EL, _MEL` <B>System layers</B> - Active when <B>Esc key</B> held. (Tapping works as normal)
* `_CL` <B>Keyboard layer</B> - Active when <B>Caps Lock</B> is held. For both <B>Win</B> and <B>Mac</B>. (Tapping works as normal)

For a full list of shortcuts on the keyboard, refer to the keymap file here, or to the [section below](https://github.com/NathanDagDane/Tide65-Keymap?tab=readme-ov-file#shortcuts).

### Features
* <B>OS Detection</B> - Automatically changes the base layer depending on the OS <I>(Mac/iOS vs Other)</I>
* <B>Tap Hold</B> - Tap <B>Esc</B> or <B>Caps</B> for their usual function, or hold to switch layer.
* <B>Encoder</B> - The encoder controls different things depending on the lactive layer.
* <B>RGB Lighting</B> - Space bar shines <B>red</B> when caps lock is on. Each layer lights up special keys.

<details>
<summary><h3>Shortcuts</h3></summary>

* `Caps Lock` +
    * `1-3` - Connect to <I>Bluetooth 1-3</I>
    * `4` - Connect to <I>2.4GHz dongle</I>
    * `5` - Connect to <I>wired mode</I>
    * `5` - Display battery lavel <I>(on keys 1-0)</I>
    * `W` - Set to <I>Windows mode</I>
    * `M` - Set to <I>MacOS mode</I>
    * `←,→` - Previous/next keyboard RGB effect
    * `↑,↓` - Increase/Decrease keyboard RGB speed
    * `Encoder press` - Keyboard RGB on/off
    * `Encoder ↺` - Keyboard RGB brightness -
    * `Encoder ↻` - Keyboard RGB brightness +
#### Windows
* `Fn` +
    * `1-+` - <B>F1-F12</B>
    * `Encoder ↺` - Keyboard RGB hue -
    * `Encoder ↻` - Keyboard RGB hue +
* `Esc` +
    * `E` - Open File Explorer
    * `T` - Open Task Manager
    * `S` - Take Screenshot
    * `A` - <B>Ctrl+Shift+Alt+A</B> <I>(Toggles speakers/headphones for me)</I>
    * `Del` - Media previous
    * `PgUp` - Media play/pause
    * `PgDn` - Media next
    * `Encoder ↺` - System brightness -
    * `Encoder ↻` - System brightness +
#### MacOS
* `Fn` +
    * `1-+` - <B>F1-F12</B>
    * `Encoder ↺` - Keyboard RGB hue -
    * `Encoder ↻` - Keyboard RGB hue +
* `Esc` +
    * `S` - Take Screenshot
    * `Del` - Media previous
    * `PgUp` - Media play/pause
    * `PgDn` - Media next
    * `Encoder ↺` - System brightness -
    * `Encoder ↻` - System brightness +
</details>

## Customising the Layout
> <I>TODO</I>

## QMK Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [VitePress](https://vitepress.dev/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

