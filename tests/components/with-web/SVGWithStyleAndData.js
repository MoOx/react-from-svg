import React from "react";
const SVGWithStyleAndData = (props) => {
  return (
    <svg {...props}>
      <mask style={{ maskType: "alpha" }} />
      <circle cx="90" cy="90" data-circle="true" fill="black" />
    </svg>
  );
};

export default SVGWithStyleAndData;
