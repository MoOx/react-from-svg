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
  --allow-override-fill, -aof           --allow-override-fill, -aof           Replace all 'fill' properties by a dynamic prop (fills) in SVGs, e.g. fill={fills[N]}.

Example
  $ react-from-svg src/svgs src/svgs/components --with-web-for-typescript --allow-override-fill
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

## Options

### `--remove-fill`

Remove all `fill` properties from SVGs, convenient for icons.

### `--remove-stroke`

Remove all `stroke` properties from SVGs, convenient for icons.

### `--allow-override-fill`

Replace all `fill` properties by a dynamic prop (fills) in SVGs, e.g. fill={fills[N]}.  
If `fills[N]` is undefined, fallback to the original value (except if `--remove-fill` is used). Useful to dynamically control icon color(s).

## Examples

### Usage with `--allow-override-fill` and children

When using `--allow-override-fill`, you can pass children to the component to override the fill(s).
You can for example update a black SVG path to one using a gradient.

Assuming you have a SVG in `src/svgs/logo.svg`, let's generate an SVG component :

```console
react-from-svg src/svgs src/svgs/components --with-web-for-typescript
```

You should have an SVG component in `src/svgs/components/SVGLogo.tsx`.

Now let's boost this SVG component to use a gradient.

```tsx
import SVGLogo from "@/src/svgs/components/SVGLogo";
import { colors } from "@/src/tokens.stylex"; // your colors could be just a simple object

const logoGradientId = "logo-gradient-id";
export default function LogoWithGradient() {
  return (
    <SVGLogo width={149} height={32} fills={[`url(#${logoGradientId})`]}>
      <linearGradient x1="50%" y1="100%" x2="50%" y2="0%" id={logoGradientId}>
        <stop stopColor={colors.textSecondary} offset="0%"></stop>
        <stop stopColor={colors.textTertiary} offset="100%"></stop>
      </linearGradient>
    </SVGLogo>
  );
}
```

That's it. You started from a simple single color SVG path and ended up with a gradient SVG path.
