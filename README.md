# react-from-svg

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
    --with-native, -native  Output code for react-native-svg
    --with-web, -web        Output code for DOM. If --with-native is also used, will be output as .web.js files
    --with-reason, -bs      Output ReasonML bindings code
    --remove-fill, -rf      Remove all 'fill' properties from SVGs, convenient for icons
    --remove-stroke, -rs    Remove all 'stroke' properties from SVGs, convenient for icons
    --commonjs, -cjs        Export as commonjs instead of es6 import/export
    --bs-module-path, -bsp  Allow to customise ReasonML output path

  Example
    $ react-from-svg assets/svgs src/Svgs --remove-fill
```

### Examples

#### React DOM, no options

```console
react-from-svg assets/svgs src/Svgs --with-web
```

#### React Native with fill svg props removed

```console
react-from-svg assets/svgs src/Svgs --with-native --remove-fill
```

#### React Native + ReasonML bindings SVGs

```console
react-from-svg assets/svgs src/Svgs --with-native --with-reason
```

#### React Native + ReasonML bindings SVGs and absolute path

It's usefull if you defined a webpack alias and you don't generate your
bucklescript output `"in-source"`

```console
react-from-svg assets/svgs src/Svgs --with-reason --reason-module-path=./src/components
```
