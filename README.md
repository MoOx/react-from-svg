# React from SVG

[![Build Status](https://github.com/MoOx/react-from-svg/workflows/Build/badge.svg)](https://github.com/MoOx/react-from-svg/actions)
[![Version](https://img.shields.io/npm/v/react-from-svg.svg)](https://www.npmjs.com/react-from-svg)

[![Repo on GitHub](https://img.shields.io/badge/repo-GitHub-3D76C2.svg)](https://github.com/MoOx/react-from-svg)
[![Repo on GitLab](https://img.shields.io/badge/repo-GitLab-6C488A.svg)](https://gitlab.com/MoOx/react-from-svg)

> Transform SVG files into React components, Native and/or Web, JavaScript and
> ReasonML. Without shitload of dependencies.

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
    --with-native, -native                Output code for react-native-svg
    --with-web, -web                      Output code for DOM. If --with-native is also used, will be output as .web.js files
    --with-native-for-reason, -bsnative   Output code for @reason-react-native/svg
    --with-web-for-reason, -bsnweb        Output code for reason-react
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
- `fill` (can be removed with `--remove-fill`)
- `stroke` (can be removed with `--remove-stroke`)

⚠️ To see what you can expect from the transformations,
[check our snapshots](./__tests__/__snapshots__) 👀

## Requirements

### `--with-web`

Need you to install have:

- [React](https://reactjs.org)

### `--with-web-for-reason`

Need you to install have:

- [React](https://reactjs.org)
- [`reason-react`](https://reasonml.github.io/reason-react/)

### `--with-native`

Need you to install have:

- [React](https://reactjs.org)
- [React Native](https://reactnative.dev) (or an alternative platform like
  [React Native Web](https://github.com/necolas/react-native-web))
- [`react-native-svg`](https://github.com/react-native-community/react-native-svg)

### `--with-native-for-reason`

In addition to `--with-native` requirements, you need to install & add as
`bs-dependencies` in your `bsconfig.json`:

- [`reason-react`](https://reasonml.github.io/reason-react/)
- [`reason-react-native`](https://reason-react-native.github.io)
- [`@reason-react-native/svg`](https://github.com/reason-react-native/svg)
