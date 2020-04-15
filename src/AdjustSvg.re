let cleanupStart = svg =>
  svg
  ->Js.String2.replaceByRe([%re "/'/g"], "\"")
  ->Js.String2.replaceByRe([%re "/\\sversion=\"1.1\"/g"], "")
  ->Js.String2.replaceByRe([%re "/<\\?xml(.*)\\?>/g"], "")
  ->Js.String2.replaceByRe(
      [%re "/\\sxmlns=\"http:\\/\\/www\\.w3\\.org\\/2000\\/svg\"/g"],
      "",
    )
  ->Js.String2.replaceByRe(
      [%re "/\\sxmlns:xlink=\"http:\\/\\/www.w3.org\\/1999\\/xlink\"/g"],
      "",
    )
  // remove useless data
  ->Js.String2.replaceByRe([%re "/<title>(.*)<\\/title>/g"], "")
  ->Js.String2.replaceByRe([%re "/<desc>(.*)<\\/desc>/g"], "")
  ->Js.String2.replaceByRe([%re "/<!--(.*)-->/g"], "");

let prepareSvgProps = svg =>
  svg
  // remove future props
  ->Js.String2.replaceByRe(
      [%re "/<svg\\s?([^>]*)?\\swidth=\"[^\\\"]*\"/g"],
      {j|<svg \$1|j},
    )
  ->Js.String2.replaceByRe(
      [%re "/<svg\\s?([^>]*)?\\sheight=\"[^\\\"]*\"/g"],
      {j|<svg \$1|j},
    )
  ->Js.String2.replaceByRe(
      [%re "/<svg\\s?([^>]*)?\\sfill=\"[^\\\"]*\"/g"],
      {j|<svg \$1|j},
    );

let injectSvgJsProps = svg =>
  svg->Js.String2.replace(
    ">",
    " width={width} height={height} fill={fill} stroke={stroke}>",
  );

let injectSvgReasonProps = svg =>
  svg->Js.String2.replace(">", " ?width ?height ?fill ?stroke>");

let dashToCamelCaseProps = svg =>
  svg->Js.String2.unsafeReplaceBy1(
    [%re "/\\s([a-z-]+)/g"], (_matchPart, p1, _offset, _wholeString) =>
    " " ++ p1->Case.toCamel
  );

let tagToPascalCase = svg =>
  svg->Js.String2.unsafeReplaceBy2(
    [%re "/<(\\/?)([a-z])/g"], (_matchPart, p1, p2, _offset, _wholeString) =>
    "<" ++ p1 ++ p2->Case.toPascal
  );

let cleanupEnd = svg =>
  svg
  ->Js.String2.replaceByRe([%re "/>\\s+</g"], "> <")
  ->Js.String2.replaceByRe([%re "/></g"], "> <");

let deleteFill = svg =>
  svg->Js.String2.replaceByRe([%re "/ fill=\"[^\\\"]*\"/g"], "");
let deleteStroke = svg =>
  svg->Js.String2.replaceByRe([%re "/ stroke=\"[^\\\"]*\"/g"], "");

let polyCamel = (_matchPart, p1, p2, _offset, _wholeString) =>
  p1 ++ "=`" ++ p2->Case.toCamel;

let toPolyCamel = (s, re) => s->Js.String2.unsafeReplaceBy2(re, polyCamel);

let transformReasonNativeProps = svg =>
  svg
  ->toPolyCamel(
      [%re
        "/(alignmentBaseline)=\"(baseline|text-bottom|alphabetic|ideographic|middle|central|mathematical|text-top|bottom|center|top|text-before-edge|text-after-edge|before-edge|after-edge|hanging)\"/g"
      ],
    )
  ->toPolyCamel([%re "/(baselineShift)=\"(sub|super|baseline)\"/g"])
  ->toPolyCamel([%re "/(clipRule)=\"(evenodd|nonzero)\"/g"])
  ->toPolyCamel([%re "/(fillRule)=\"(evenodd|nonzero)\"/g"])
  ->toPolyCamel(
      [%re
        "/(fontStretch)=\"(normal|wider|narrower|ultra-condensed|extra-condensed|condensed|semi-condensed|semi-expanded|expanded|extra-expanded|ultra-expanded)\"/g"
      ],
    )
  ->toPolyCamel([%re "/(fontStyle)=\"(normal|italic|oblique)\"/g"])
  ->toPolyCamel([%re "/(fontVariant)=\"(normal|smallcaps)\"/g"])
  ->toPolyCamel([%re "/(fontVariantLigatures)=\"(normal|none)\"/g"])
  ->toPolyCamel(
      [%re
        "/(fontWeight)=\"(normal|bold|bolder|lighter|100|200|300|400|500|600|700|800|900)\"/g"
      ],
    )
  ->toPolyCamel(
      [%re "/(gradientUnits)=\"(userSpaceOnUse|objectBoundingBox)\"/g"],
    )
  ->toPolyCamel([%re "/(lengthAdjust)=\"(spacing|spacingAndGlyphs)\"/g"])
  ->toPolyCamel([%re "/(markerUnits)=\"(userSpaceOnUse|strokeWidth)\"/g"])
  ->toPolyCamel(
      [%re "/(maskContentUnits)=\"(userSpaceOnUse|objectBoundingBox)\"/g"],
    )
  ->toPolyCamel([%re "/(maskUnits)=\"(userSpaceOnUse|objectBoundingBox)\"/g"])
  ->toPolyCamel([%re "/(method)=\"(align|stretch)\"/g"])
  ->toPolyCamel([%re "/(midLine)=\"(sharp|smooth)\"/g"])
  ->toPolyCamel(
      [%re "/(patternContentUnits)=\"(userSpaceOnUse|objectBoundingBox)\"/g"],
    )
  ->toPolyCamel(
      [%re "/(patternUnits)=\"(userSpaceOnUse|objectBoundingBox)\"/g"],
    )
  ->toPolyCamel([%re "/(spacing)=\"(auto|exact)\"/g"])
  ->toPolyCamel([%re "/(strokeLinecap)=\"(butt|square|round)\"/g"])
  ->toPolyCamel([%re "/(strokeLinejoin)=\"(miter|bevel|round)\"/g"])
  ->toPolyCamel([%re "/(textAnchor)=\"(start|middle|end)\"/g"])
  ->toPolyCamel(
      [%re
        "/(textDecoration)=\"(|none|underline|overline|line-through|blink )\"/g"
      ],
    )
  ->toPolyCamel(
      [%re
        "/(vectorEffect)=\"(none|default|non-scaling-stroke|inherit|uri)\"/g"
      ],
    );
