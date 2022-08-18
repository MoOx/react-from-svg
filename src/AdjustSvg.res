let cleanupStart = svg =>
  svg
  ->Js.String2.replaceByRe(%re("/'/g"), "\"")
  ->Js.String2.replaceByRe(%re("/\\sversion=\"1.1\"/g"), "")
  ->Js.String2.replaceByRe(%re("/<\\?xml(.*)\\?>/g"), "")
  ->Js.String2.replaceByRe(%re("/\\sxmlns=\"http:\\/\\/www\\.w3\\.org\\/2000\\/svg\"/g"), "")
  ->Js.String2.replaceByRe(%re("/\\sxmlns:xlink=\"http:\\/\\/www.w3.org\\/1999\\/xlink\"/g"), "")
  // remove useless data
  ->Js.String2.replaceByRe(%re("/<title>(.*)<\\/title>/g"), "")
  ->Js.String2.replaceByRe(%re("/<desc>(.*)<\\/desc>/g"), "")
  ->Js.String2.replaceByRe(%re("/<!--(.*)-->/g"), "")

let prepareSvgProps = svg =>
  svg
  // remove future props
  ->Js.String2.replaceByRe(%re("/<svg\\s?([^>]*)?\\swidth=\"[^\\\"]*\"/g"), j`<svg \\$1`)
  ->Js.String2.replaceByRe(%re("/<svg\\s?([^>]*)?\\sheight=\"[^\\\"]*\"/g"), j`<svg \\$1`)
  ->Js.String2.replaceByRe(%re("/<svg\\s?([^>]*)?\\sfill=\"[^\\\"]*\"/g"), j`<svg \\$1`)

let injectSvgJsProps = svg =>
  svg->Js.String2.replace(
    ">",
    " width={width} height={height} fill={fill} stroke={stroke} style={style}>",
  )

let injectSvgReScriptProps = svg =>
  svg->Js.String2.replace(">", " ?width ?height ?fill ?stroke ?style>")

let dashToCamelCaseProps = svg =>
  svg->Js.String2.unsafeReplaceBy1(%re("/\\s([a-z-]+)/g"), (
    _matchPart,
    p1,
    _offset,
    _wholeString,
  ) => " " ++ p1->Case.toCamel)

let tagToPascalCase = svg =>
  svg->Js.String2.unsafeReplaceBy2(%re("/<(\\/?)([a-z])/g"), (
    _matchPart,
    p1,
    p2,
    _offset,
    _wholeString,
  ) => "<" ++ (p1 ++ p2->Case.toPascal))

let cleanupEndWithSpace = svg =>
  svg->Js.String2.replaceByRe(%re("/>\\s+</g"), "> <")->Js.String2.replaceByRe(%re("/></g"), "> <")

let cleanupEndWithoutSpace = svg => svg->Js.String2.replaceByRe(%re("/>\\s+</g"), "><")

let deleteFill = svg => svg->Js.String2.replaceByRe(%re("/ fill=\"[^\\\"]*\"/g"), "")
let deleteStroke = svg => svg->Js.String2.replaceByRe(%re("/ stroke=\"[^\\\"]*\"/g"), "")

let toPolyCamel = (s, re) =>
  s->Js.String2.unsafeReplaceBy2(re, (_matchPart, p1, p2, _offset, _wholeString) =>
    p1 ++ ("=#" ++ p2->Case.toCamel)
  )

let transformReScriptNativeProps = svg =>
  svg
  ->toPolyCamel(
    %re(
      "/\\b(alignmentBaseline)=\"(baseline|text-bottom|alphabetic|ideographic|middle|central|mathematical|text-top|bottom|center|top|text-before-edge|text-after-edge|before-edge|after-edge|hanging)\"/g"
    ),
  )
  ->toPolyCamel(%re("/\\b(baselineShift)=\"(sub|super|baseline)\"/g"))
  ->toPolyCamel(%re("/\\b(clipRule)=\"(evenodd|nonzero)\"/g"))
  ->toPolyCamel(%re("/\\b(fillRule)=\"(evenodd|nonzero)\"/g"))
  ->toPolyCamel(
    %re(
      "/\\b(fontStretch)=\"(normal|wider|narrower|ultra-condensed|extra-condensed|condensed|semi-condensed|semi-expanded|expanded|extra-expanded|ultra-expanded)\"/g"
    ),
  )
  ->toPolyCamel(%re("/\\b(fontStyle)=\"(normal|italic|oblique)\"/g"))
  ->toPolyCamel(%re("/\\b(fontVariant)=\"(normal|smallcaps)\"/g"))
  ->toPolyCamel(%re("/\\b(fontVariantLigatures)=\"(normal|none)\"/g"))
  ->toPolyCamel(
    %re("/\\b(fontWeight)=\"(normal|bold|bolder|lighter|100|200|300|400|500|600|700|800|900)\"/g"),
  )
  ->toPolyCamel(%re("/\\b(gradientUnits)=\"(userSpaceOnUse|objectBoundingBox)\"/g"))
  ->toPolyCamel(%re("/\\b(lengthAdjust)=\"(spacing|spacingAndGlyphs)\"/g"))
  ->toPolyCamel(%re("/\\b(markerUnits)=\"(userSpaceOnUse|strokeWidth)\"/g"))
  ->toPolyCamel(%re("/\\b(maskContentUnits)=\"(userSpaceOnUse|objectBoundingBox)\"/g"))
  ->toPolyCamel(%re("/\\b(maskUnits)=\"(userSpaceOnUse|objectBoundingBox)\"/g"))
  ->toPolyCamel(%re("/\\b(method)=\"(align|stretch)\"/g"))
  ->toPolyCamel(%re("/\\b(midLine)=\"(sharp|smooth)\"/g"))
  ->toPolyCamel(%re("/\\b(patternContentUnits)=\"(userSpaceOnUse|objectBoundingBox)\"/g"))
  ->toPolyCamel(%re("/\\b(patternUnits)=\"(userSpaceOnUse|objectBoundingBox)\"/g"))
  ->toPolyCamel(%re("/\\b(spacing)=\"(auto|exact)\"/g"))
  ->toPolyCamel(%re("/\\b(strokeLinecap)=\"(butt|square|round)\"/g"))
  ->toPolyCamel(%re("/\\b(strokeLinejoin)=\"(miter|bevel|round)\"/g"))
  ->toPolyCamel(%re("/\\b(textAnchor)=\"(start|middle|end)\"/g"))
  ->toPolyCamel(%re("/\\b(textDecoration)=\"(|none|underline|overline|line-through|blink )\"/g"))
  ->toPolyCamel(%re("/\\b(vectorEffect)=\"(none|default|non-scaling-stroke|inherit|uri)\"/g"))

type t = string
@send
external unsafeReplaceBy4: (t, Js_re.t, @uncurry (t, t, t, t, t, int, t) => t) => t = "replace"

let undefinedString: string = Js.undefined->Obj.magic

let transformReScriptNativeSizeProps = svg =>
  svg->unsafeReplaceBy4(
    %re(
      "/\\b(cx|cy|dx|dy|fontSize|fx|fy|height|inlineSize|kerning|letterSpacing|markerHeight|markerWidth|offset|originX|originY|r|refX|refY|rotate|rotation|rx|ry|scale|startOffset|strokeDashoffset|strokeMiterlimit|strokeWidth|verticalAlign|width|wordSpacing|x|x1|x2|y|y1|y2)=\"(-?[0-9]*)(\\.[0-9]+)?(%)?\"/g"
    ),
    (_matchPart, attributeName, digits, decimals, unit, _offset, _wholeString) =>
      attributeName ++
      ("={" ++
      ((digits === "" ? "0" : digits) ++
      ((decimals !== undefinedString ? decimals : ".") ++
      ("->Style." ++ ((unit === "%" ? "pct" : "dp") ++ "}"))))),
  )
