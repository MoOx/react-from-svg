import React from "react";
const SVGSimple = (props: React.SVGProps<SVGSVGElement>) => {
  return (
    <svg viewBox="0 0 512 512" {...props}>
      <path
        d="M336 192h40a40 40 0 0140 40v192a40 40 0 01-40 40H136a40 40 0 01-40-40V232a40 40 0 0140-40h40M336 128l-80-80-80 80M256 321V48"
        fill="none"
        stroke="#000"
        strokeLinecap="round"
        strokeLinejoin="round"
        strokeWidth="32"
        opacity="0.1"
      />
    </svg>
  );
};

export default SVGSimple;
