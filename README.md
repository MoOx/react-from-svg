# React from SVG

<a href="https://github.com/MoOx/react-from-svg?sponsor=1">
  <img width="140" align="right" alt="Sponsoring button" src="https://github.com/moox/.github/raw/main/FUNDING.svg">
</a>

[![GitHub package.json version](https://img.shields.io/github/package-json/v/MoOx/react-from-svg) ![npm downloads](https://img.shields.io/npm/dm/react-from-svg)](https://www.npmjs.com/package/react-from-svg)
[![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/MoOx/react-from-svg/build.yml?branch=main)](https://github.com/MoOx/react-from-svg/actions)
[![License](https://img.shields.io/github/license/MoOx/react-from-svg)](https://github.com/MoOx/react-from-svg)  
[![GitHub followers](https://img.shields.io/github/followers/MoOx?style=social&label=Follow%20me)](https://github.com/MoOx)
[![Twitter Follow](https://img.shields.io/twitter/follow/MoOx?style=social&label=Follow%20me)](https://twitter.com/MoOx)
[![Sponsor my work](https://github.com/moox/.github/raw/main/FUNDING-button.svg)](https://github.com/MoOx/react-from-svg?sponsor=1)

> Transform SVG files into React components, Native and/or Web, JavaScript and
> rescriptML. Without shitload of dependencies.

## Install

```console
npm install react-from-svg

# or

yarn add react-from-svg
```

## Usage

```console
react-from-svg --help

Usage
  $ react-from-svg <sourcePath> <outputPath> [--with-native|--with-web]

Options
  --with-native, -rn                    Output code for react-native-svg
  --with-web, -rnw                      Output code for DOM. If --with-native is also used, will be output as .web.js files
  --with-native-for-rescript, -rrn      Output code for @rescript-react-native/svg
  --with-web-for-rescript, -rrnw        Output code for @rescript/react
  --remove-fill, -rf                    Remove all 'fill' properties from SVGs, convenient for icons
  --remove-stroke, -rs                  Remove all 'stroke' properties from SVGs, convenient for icons
  --commonjs, -cjs                      Export as commonjs instead of es6 import/export

Example
  $ react-from-svg assets/svgs src/Svgs --with-native --remove-fill
```

Generated components will have the following props that you can inject to the
SVG components:

- `width`
- `height`
- `fill` (if you use `--remove-fill`)
- `stroke` (if you use `--remove-stroke`)

⚠️ To see what you can expect from the transformations,
[check our snapshots](./__tests__/__snapshots__) 👀

## Requirements

### `--with-web`

Need you to have:

- [React](https://reactjs.org)

### `--with-web-for-rescript`

Need you to have:

- [React](https://reactjs.org)
- [`rescript-react`](https://rescriptml.github.io/rescript-react/)

### `--with-native`

Need you to have:

- [React](https://reactjs.org)
- [React Native](https://reactnative.dev) (or an alternative platform like
  [React Native Web](https://github.com/necolas/react-native-web))
- [`react-native-svg`](https://github.com/react-native-community/react-native-svg)

### `--with-native-for-rescript`

In addition to `--with-native` requirements, you need to have:

- [`@rescript/react`](https://rescript-lang.org/docs/react/latest/introduction)
- [`rescript-react-native`](https://rescript-react-native.github.io)
- [`@rescript-react-native/svg`](https://github.com/rescript-react-native/svg)

Ensure as that this dependencies are in the `bs-dependencies` of your `bsconfig.json`.
