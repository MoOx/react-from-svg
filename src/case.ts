import camelCase from "camelcase";

export const toCamel = (s: string): string =>
  camelCase(s, { pascalCase: false });
export const toPascal = (s: string): string =>
  camelCase(s, { pascalCase: true });
