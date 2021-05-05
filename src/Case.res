type camelCaseOptions = {pascalCase: bool}
@module
external camelCase: (string, camelCaseOptions) => string = "camelcase"

let toCamel = s => s->camelCase({pascalCase: false})
let toPascal = s => s->camelCase({pascalCase: true})
