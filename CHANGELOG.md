# Changelog of `react-from-svg`

## 2.1.1 - 2020-01-23

- oopsy path

## 2.1.0 - 2020-01-23

- Add `--reason-absolute-path` option for reason files
  ([#4](https://github.com/MoOx/react-from-svg/pull/4)) by @Freddy03h
- Fix fill reason type by @MoOx

## 2.0.1 - 2020-01-22

- Try to autorebuild if compiled artifacts are missing

## 2.0.0 - 2020-01-22

- Try to load compiled transformer differently (not in-source as it's the
  recommended place - to avoid issue with existing bs compilation, which can
  override & break nodejs script due to not using commonjs).
- Use bs-platform@^7.0.0

We might in the future rebuild script before running it.

## 1.2.3 - 2020-01-03

- Fix unwanted whitespace that create text nodes

## 1.2.2 - 2020-01-03

- Fix removal of `<?xml` header without encoding

## 1.2.1 - 2020-01-01

- Fix `pct` unit

## 1.2.0 - 2019-12-23

Add `--remove-fill` option

## 1.1.0 - 2019-12-21

Ooopsy :) Tons of fixes so it's usable. And `dp` unit

## 1.0.0 - 2019-12-21

Support for

- React Native
- React Native Web
- Reason React Native
- Reason React Native Web

Via react-native-svg

## 0.2.1 - 2019-12-21

🥳 Fixes

- xml headers
- comments
- title
- desc
- dashed properties

## 0.2.0 - 2019-05-30

Remove `[@bs.config {jsx: 3}];`

## 0.1.3 - 2019-04-10

bs-platform 5.0.1 & reason-react 0.7.0

## 0.1.2 - 2019-04-09

Add dep (unused in production) to fit development bsconfig that is the same for
production

## 0.1.1 - 2019-04-09

Build bsb on postinstall to avoid missing required files

## 0.1.0 - 2019-04-08

Initial release
