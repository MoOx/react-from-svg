# React from SVG

<a href="https://github.com/MoOx/react-from-svg?sponsor=1">
  <img width="140" align="right" alt="Sponsoring button" src="https://github.com/moox/.github/raw/main/FUNDING.svg">
</a>

[![GitHub package.json version](https://img.shields.io/github/package-json/v/MoOx/react-from-svg) ![npm downloads](https://img.shields.io/npm/dm/react-from-svg)](https://www.npmjs.com/package/react-from-svg)
[![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/MoOx/react-from-svg/build.yml?branch=main)](https://github.com/MoOx/react-from-svg/actions)
[![License](https://img.shields.io/github/license/MoOx/react-from-svg)](https://github.com/MoOx/react-from-svg)  
[![GitHub followers](https://img.shields.io/github/followers/MoOx?style=social&label=Follow%20me)](https://github.com/MoOx)
[![LinkedIn Follow](https://img.shields.io/badge/Follow%20Me-on%20LinkedIn-gray?style=social&logo=invision&logoColor=%230077B5)](https://www.linkedin.com/in/maxthirouin/)
[![BlueSky Follow](https://img.shields.io/badge/Follow%20Me-on%20BlueSky-gray?style=social&logo=bluesky)](https://bsky.app/profile/moox.io)
[![X Follow](https://img.shields.io/twitter/follow/MoOx?style=social&label=Follow%20me)](https://x.com/MoOx)

> Transform SVG files into React components, Native and/or Web, JavaScript and/or TypeScript.
> Without minimal dependencies.

## Install

```console
npm install react-from-svg
```

## Usage

```console
react-from-svg --help

Usage
  $ react-from-svg <sourcePath> <outputPath> [--with-native|--with-web]

Options
  --with-native, -rn                    Output code for react-native-svg
  --with-native-for-typescript, -rnts   Output code for react-native-svg with TypeScript
  --with-web, -rnw                      Output code for DOM. If --with-native is also used, will be output as .web.js files
  --with-web-for-typescript, -rnwts     Output code for DOM with TypeScript. If --with-native is also used, will be output as .web.tsx files
  --remove-fill, -rf                    Remove all 'fill' properties from SVGs, convenient for icons
  --remove-stroke, -rs                  Remove all 'stroke' properties from SVGs, convenient for icons
  --allow-override-fill, -aof                 Replace all 'fill' properties by a dynamic prop (fills) in SVGs, e.g. fill={fills[N]}. If fills[N] is undefined, fallback to the original value. Useful to dynamically control icon color(s).

Example
  $ react-from-svg assets/svgs src/Svgs --with-native --remove-fill
  $ react-from-svg assets/svgs src/Svgs --with-web --allow-override-fill
```

Generated components will allow you to inject all the props you could use on an `<svg>`/`<Svg>`, such as:

- `width`
- `height`
- `fill` (if you use `--remove-fill`)
- `stroke` (if you use `--remove-stroke`)
- `style`

⚠️ To see what you can expect from the transformations, [check our snapshots](./tests/) 👀

## Requirements

### `--with-web(-*)`

Need you to have:

- [React](https://reactjs.org)

Note: if you use [React Native for Web](https://github.com/necolas/react-native-web), see requirements below.

### `--with-native(-*)`

Need you to have:

- [React](https://reactjs.org)
- [React Native](https://reactnative.dev) (or an alternative platform like
  [React Native Web](https://github.com/necolas/react-native-web))
- [`react-native-svg`](https://github.com/react-native-community/react-native-svg)
