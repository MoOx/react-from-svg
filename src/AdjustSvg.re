let cleanupStart = svg =>
  svg
  |> Js.String.replaceByRe([%re "/'/g"], "\"")
  |> Js.String.replaceByRe([%re "/\\sversion=\"1.1\"/g"], "")
  |> Js.String.replaceByRe([%re "/<\\?xml(.*)\\?>/g"], "")
  |> Js.String.replaceByRe(
       [%re "/\\sxmlns=\"http:\\/\\/www\\.w3\\.org\\/2000\\/svg\"/g"],
       "",
     )
  |> Js.String.replaceByRe(
       [%re "/\\sxmlns:xlink=\"http:\\/\\/www.w3.org\\/1999\\/xlink\"/g"],
       "",
     )
  // remove useless data
  |> Js.String.replaceByRe([%re "/<title>(.*)<\\/title>/g"], "")
  |> Js.String.replaceByRe([%re "/<desc>(.*)<\\/desc>/g"], "")
  |> Js.String.replaceByRe([%re "/<!--(.*)-->/g"], "");

let prepareProps = svg =>
  svg
  // remove future props
  |> Js.String.replaceByRe(
       [%re "/<svg\\s?([^>]*)?\\swidth=\"[^\\\"]*\"/g"],
       {j|<svg \$1|j},
     )
  |> Js.String.replaceByRe(
       [%re "/<svg\\s?([^>]*)?\\sheight=\"[^\\\"]*\"/g"],
       {j|<svg \$1|j},
     )
  |> Js.String.replaceByRe(
       [%re "/<svg\\s?([^>]*)?\\sfill=\"[^\\\"]*\"/g"],
       {j|<svg \$1|j},
     )
  // inject props
  |> Js.String.replace(
       ">",
       " width={width} height={height} fill={fill} stroke={stroke}>",
     );

let dashToCamelCaseProps = svg =>
  svg
  |> Js.String.replaceByRe([%re "/\\s([a-z]+)-a([a-z]+)/g"], {j| \$1A\$2|j})
  |> Js.String.replaceByRe([%re "/\\s([a-z]+)-b([a-z]+)/g"], {j| \$1B\$2|j})
  |> Js.String.replaceByRe([%re "/\\s([a-z]+)-c([a-z]+)/g"], {j| \$1C\$2|j})
  |> Js.String.replaceByRe([%re "/\\s([a-z]+)-d([a-z]+)/g"], {j| \$1D\$2|j})
  |> Js.String.replaceByRe([%re "/\\s([a-z]+)-e([a-z]+)/g"], {j| \$1E\$2|j})
  |> Js.String.replaceByRe([%re "/\\s([a-z]+)-f([a-z]+)/g"], {j| \$1F\$2|j})
  |> Js.String.replaceByRe([%re "/\\s([a-z]+)-g([a-z]+)/g"], {j| \$1G\$2|j})
  |> Js.String.replaceByRe([%re "/\\s([a-z]+)-h([a-z]+)/g"], {j| \$1H\$2|j})
  |> Js.String.replaceByRe([%re "/\\s([a-z]+)-l([a-z]+)/g"], {j| \$1L\$2|j})
  |> Js.String.replaceByRe([%re "/\\s([a-z]+)-m([a-z]+)/g"], {j| \$1M\$2|j})
  |> Js.String.replaceByRe([%re "/\\s([a-z]+)-o([a-z]+)/g"], {j| \$1O\$2|j})
  |> Js.String.replaceByRe([%re "/\\s([a-z]+)-p([a-z]+)/g"], {j| \$1P\$2|j})
  |> Js.String.replaceByRe([%re "/\\s([a-z]+)-s([a-z]+)/g"], {j| \$1S\$2|j})
  |> Js.String.replaceByRe([%re "/\\s([a-z]+)-t([a-z]+)/g"], {j| \$1T\$2|j})
  |> Js.String.replaceByRe([%re "/\\s([a-z]+)-r([a-z]+)/g"], {j| \$1R\$2|j})
  |> Js.String.replaceByRe([%re "/\\s([a-z]+)-w([a-z]+)/g"], {j| \$1W\$2|j});

let tagToPascalCase = svg =>
  svg
  |> Js.String.replaceByRe([%re "/<(\\/?)a/g"], "<$1A")
  |> Js.String.replaceByRe([%re "/<(\\/?)b/g"], "<$1B")
  |> Js.String.replaceByRe([%re "/<(\\/?)c/g"], "<$1C")
  |> Js.String.replaceByRe([%re "/<(\\/?)d/g"], "<$1D")
  |> Js.String.replaceByRe([%re "/<(\\/?)e/g"], "<$1E")
  |> Js.String.replaceByRe([%re "/<(\\/?)f/g"], "<$1F")
  |> Js.String.replaceByRe([%re "/<(\\/?)g/g"], "<$1G")
  |> Js.String.replaceByRe([%re "/<(\\/?)h/g"], "<$1H")
  |> Js.String.replaceByRe([%re "/<(\\/?)i/g"], "<$1I")
  |> Js.String.replaceByRe([%re "/<(\\/?)j/g"], "<$1J")
  |> Js.String.replaceByRe([%re "/<(\\/?)k/g"], "<$1K")
  |> Js.String.replaceByRe([%re "/<(\\/?)l/g"], "<$1L")
  |> Js.String.replaceByRe([%re "/<(\\/?)m/g"], "<$1M")
  |> Js.String.replaceByRe([%re "/<(\\/?)o/g"], "<$1O")
  |> Js.String.replaceByRe([%re "/<(\\/?)p/g"], "<$1P")
  |> Js.String.replaceByRe([%re "/<(\\/?)q/g"], "<$1Q")
  |> Js.String.replaceByRe([%re "/<(\\/?)r/g"], "<$1R")
  |> Js.String.replaceByRe([%re "/<(\\/?)s/g"], "<$1S")
  |> Js.String.replaceByRe([%re "/<(\\/?)t/g"], "<$1T")
  |> Js.String.replaceByRe([%re "/<(\\/?)u/g"], "<$1U")
  |> Js.String.replaceByRe([%re "/<(\\/?)v/g"], "<$1V")
  |> Js.String.replaceByRe([%re "/<(\\/?)w/g"], "<$1W")
  |> Js.String.replaceByRe([%re "/<(\\/?)x/g"], "<$1X")
  |> Js.String.replaceByRe([%re "/<(\\/?)y/g"], "<$1Y")
  |> Js.String.replaceByRe([%re "/<(\\/?)z/g"], "<$1Z");

let cleanupEnd = svg => svg |> Js.String.replaceByRe([%re "/>\\s+</g"], "><");

let deleteFill = svg =>
  svg |> Js.String.replaceByRe([%re "/ fill=\"[^\\\"]*\"/g"], "");
let deleteStroke = svg =>
  svg |> Js.String.replaceByRe([%re "/ stroke=\"[^\\\"]*\"/g"], "");
