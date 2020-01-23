# react-from-svg

[![Build Status](https://github.com/MoOx/react-from-svg/workflows/Build/badge.svg)](https://github.com/MoOx/react-from-svg/actions)
[![Version](https://img.shields.io/npm/v/react-from-svg.svg)](https://www.npmjs.com/react-from-svg)

[![Repo on GitHub](https://img.shields.io/badge/repo-GitHub-3D76C2.svg)](https://github.com/MoOx/react-from-svg)
[![Repo on GitLab](https://img.shields.io/badge/repo-GitLab-6C488A.svg)](https://gitlab.com/MoOx/react-from-svg)

> Turns SVG files into React Native (Web) (+ optional ReasonML) components

## Usage

```console
react-from-svg [sourcePath] [outputPath] [--with-reason] [--remove-fill] [--reason-absolute-path]
```

### Examples

Just React Native / React Native Web SVGs, with fill svg props removed, nice for
icons

```console
react-from-svg assets/svgs src/Svgs --remove-fill
```

React Native (Web) + ReasonML bindings SVGs

```console
react-from-svg assets/svgs src/Svgs --with-reason
```

React Native (Web) + ReasonML bindings SVGs and absolute path : it's usefull if
you defined a webpack alias and you don't generate your bucklescript output
"in-source"

```console
react-from-svg assets/svgs src/Svgs --with-reason --reason-absolute-path=src/components
```
