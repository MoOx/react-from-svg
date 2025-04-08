# Changelog of `react-from-svg`

## 7.1.0 - 2025-04-08

- Add transform for `style="..."` as object
- Fix support for `data-*` and `aria-*`attributes (no transformation)

## 7.0.1 - 2025-04-04

- Fixed: issue with dash to camel case transforming incorrectly negative number

## 7.0.0 - 2025-04-03

Rewritten in TypeScript.
ReScript support as been removed (but feel free to add it back via a PR).

- Remove `--commonjs` option
- Remove `--with-*-for-rescript` options
- Add `--with-web-for-typescript` option for DOM with TypeScript

## 6.0.0 - 2023-01-17

- Add `--with-native-for-typescript` option for `react-native-svg` with TypeScript

## 5.1.3 - 2022-08-18

- Handle `gradientTransform` for ReScript
- Handle float without leading 0 for ReScript

## 5.1.2 - 2021-08-18

- Fix style prop generation

## 5.1.1 - 2021-08-18

- Fix published files

## 5.1.0 - 2021-08-18

- Add support for style prop

## 5.0.3 - 2021-07-07

- Fix negative number transformation for ReScript output.

## 5.0.2 - 2021-05-05

- Fix \*-rescript options, round 2
- Adjust a bit rescript output

## 5.0.1 - 2021-05-05

Fix \*-rescript options

## 5.0.0 - 2021-05-05

### Breaking change for all users

Some alias have been replaced. Please check the README for more information.

### Breaking change for user of `--with-**-reason` options

ReasonML output has been replaced by ReScript. This means:

- `--with-native-for-reason` has been replaced by `--with-native-for-rescript`
- `--with-web-for-reason` has been replaced by `--with-web-for-rescript`

Output is now ReScript code that works with `@rescript/react`, `rescript-react-native` and `@rescript-react-native/svg`.

See <https://rescript-react-native.github.io/blog/2021-05-04-hello-rescript-react-native> for more informations.

## 4.0.6 - 2020-08-08

- `--with-native-for-reason`: Fixed unwanted props transformation (eg: opacity) [b69604f](https://github.com/MoOx/react-from-svg/commit/b69604f) by [@MoOx](https://github.com/MoOx)

## 4.0.5 - 2020-08-08

- `--with-native-for-reason`: Fixed untransformed `offset` prop for `Stop` component [cdcbf0e](https://github.com/MoOx/react-from-svg/commit/cdcbf0e) by [@MoOx](https://github.com/MoOx)

## 4.0.4 - 2020-07-15

- Add missing `Stop` component [#15](https://github.com/MoOx/react-from-svg/pull/15) by [@Naturalclar](https://github.com/Naturalclar)

## 4.0.3 - 2020-06-11

- `--with-native`: Fix JS output error "Error: Text strings must be rendered within a `<Text>` [#14](https://github.com/MoOx/react-from-svg/pull/14) by [@Freddy03h](https://github.com/Freddy03h)

## 4.0.2 - 2020-05-01

- `--with-native-for-reason`: Fix 4.0.1 regression where size is undefined

## 4.0.1 - 2020-04-16

- `--with-native-for-reason`: Avoid bucklescript shadow warnings for `ReactNative.Style.size` by [@MoOx](https://github.com/MoOx)

## 4.0.0 - 2020-04-16

In addition to some fixes, this release introduce a breaking change for the CLI.
Now you must use one of the `--with-*` options options to have output for you desired platform/language:

- `--with-native`: Output code using React Native & `react-native-svg` (compatible with React Native Web)
- `--with-web`: Output code using React DOM. If `--with-native` is also used, will be output as `.web.js` files
- `--with-native-for-reason`: Output code for Reason React Native & `@reason-react-native/svg`
- `--with-web-for-reason`: Output code for Reason React DOM

CLI has also been improved a little to be more gentle & can offer some `--help`.

Also, now, no `postinstall` step are necessary for this package as we ship a bundled version.

### 💥 Breaking Changes

- Add `--with-native`, & `--with-web` options ([070a85f](https://github.com/MoOx/react-from-svg/commit/070a85f)) by [@MoOx](https://github.com/MoOx)
- Remove `--with-reason` & `--bs-module-path` ([8034065](https://github.com/MoOx/react-from-svg/commit/8034065)) by [@MoOx](https://github.com/MoOx)
  This change make sense as you can now directly output reason code that are directly svgs, not just bindings (see `--with*-for-reason` new options).
- Add `--with-native-for-reason`, `--with-web-for-reason` ([8034065](https://github.com/MoOx/react-from-svg/commit/8034065)) by [@MoOx](https://github.com/MoOx)
- File are now renamed to pascale case (eg: `some-file.svg` become `SVGSomeFile.*`) ([c62989f](https://github.com/MoOx/react-from-svg/commit/c62989f)) by [@MoOx](https://github.com/MoOx)

### 🐛 BugFixes

- Fix `strokeLinejoin`, `strokeLinecap` & `strokeMiterlimit` props ([#8](https://github.com/MoOx/react-from-svg/pull/8)) by [@Freddy03h](https://github.com/Freddy03h)
- Fix incorrect replacement for width/height/fill incorrectly removed ([4533c64](https://github.com/MoOx/react-from-svg/commit/4533c64)) by [@MoOx](https://github.com/MoOx)

### 🎉 New

- Add `--remove-stroke` option + `stroke` component prop ([#8](https://github.com/MoOx/react-from-svg/pull/8)) by [@Freddy03h](https://github.com/Freddy03h)
- Add `--commonjs` ([070a85f](https://github.com/MoOx/react-from-svg/commit/070a85f)) by [@MoOx](https://github.com/MoOx)

### 🚧 Notable Internal changes

- We now serve the package as a bundle bin to avoid `bs-platform` build on postinstall + artifacts issues ([ed6262c](https://github.com/MoOx/react-from-svg/commit/ed6262c)) by [@MoOx](https://github.com/MoOx)
- Codebase covered by tests (via snapshots) by [@MoOx](https://github.com/MoOx)
- Upgrade to bs-platform 7.2 ([#7](https://github.com/MoOx/react-from-svg/pull/7)) by [@broerjuang](https://github.com/broerjuang)

## 3.1.0 - 2020-02-18

- Fix TSpan import error ([#6](https://github.com/MoOx/react-from-svg/pull/6)) by [@broerjuang](https://github.com/broerjuang)
- bump bs-platform to 7.1.0 ([#6](https://github.com/MoOx/react-from-svg/pull/6)) by [@broerjuang](https://github.com/broerjuang)

## 3.0.0 - 2020-01-23

- Fixed reason generated module name to the js
- `--reason-absolute-path` is now `--reason-module-path` & can support absolute and local path

## 2.1.1 - 2020-01-23

- oopsy path

## 2.1.0 - 2020-01-23

- Add `--reason-absolute-path` option for reason files ([#4](https://github.com/MoOx/react-from-svg/pull/4)) by [@Freddy03h](https://github.com/Freddy03h)
- Fix fill reason type by [@MoOx](https://github.com/MoOx)

## 2.0.1 - 2020-01-22

- Try to autorebuild if compiled artifacts are missing

## 2.0.0 - 2020-01-22

- Try to load compiled transformer differently (not in-source as it's the recommended place - to avoid issue with existing bs compilation, which can override & break nodejs script due to not using commonjs).
- Use bs-platform@^7.0.0

We might in the future rebuild script before running it.

## 1.2.3 - 2020-01-03

- Fix unwanted whitespace that create text nodes

## 1.2.2 - 2020-01-03

- Fix removal of `<?xml` header without encoding

## 1.2.1 - 2020-01-01

- Fix `pct` unit

## 1.2.0 - 2019-12-23

- Add `--remove-fill` option

## 1.1.0 - 2019-12-21

- Ooopsy :) Tons of fixes so it's usable. And `dp` unit

## 1.0.0 - 2019-12-21

Support for

- React Native
- React Native Web
- Reason React Native
- Reason React Native Web

Via `react-native-svg`

## 0.2.1 - 2019-12-21

🥳 Fixes

- xml headers
- comments
- title
- desc
- dashed properties

## 0.2.0 - 2019-05-30

- Remove `[@bs.config {jsx: 3}];`

## 0.1.3 - 2019-04-10

- bs-platform 5.0.1 & reason-react 0.7.0

## 0.1.2 - 2019-04-09

- Add dep (unused in production) to fit development bsconfig that is the same for production

## 0.1.1 - 2019-04-09

- Build bsb on postinstall to avoid missing required files

## 0.1.0 - 2019-04-08

Initial release
