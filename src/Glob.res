open Belt

@module("glob")
external glob: (string, (Js.Nullable.t<Js.Exn.t>, array<string>) => unit) => unit = "glob"

let glob = path =>
  Future.makePure(resolve =>
    glob(path, (err, value) =>
      Js.Nullable.toOption(err)
      ->Option.map(e => resolve(Result.Error(e)))
      ->Option.getWithDefault(resolve(Result.Ok(value)))
    )
  )
