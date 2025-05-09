import React from "react";
const SVGPctUnit = (props: React.SVGProps<SVGSVGElement>) => {
  return (
    <svg {...props}>
      {props.children}
      <circle cx="2%" cy="-4.0%" />
    </svg>
  );
};

export default SVGPctUnit;
