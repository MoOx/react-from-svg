# React from SVG

[![Build Status](https://github.com/MoOx/react-from-svg/workflows/Build/badge.svg)](https://github.com/MoOx/react-from-svg/actions)
[![Version](https://img.shields.io/npm/v/react-from-svg.svg)](https://www.npmjs.com/react-from-svg)

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
