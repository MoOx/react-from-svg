import React from "react";
const SVGMatrixNegative = (props: React.SVGProps<SVGSVGElement>) => {
  return (
    <svg viewBox="0 0 288 272" {...props}>
      <linearGradient
        id="a"
        x1="19.028507%"
        x2="89.260976%"
        y1="0%"
        y2="73.030917%"
      >
        <stop offset="0" stopColor="#fecf24" />
        <stop offset="1" stopColor="#fd12c9" />
      </linearGradient>
      <linearGradient
        id="b"
        x1="89.260976%"
        x2="14.927787%"
        y1="69.255008%"
        y2="31.222246%"
      >
        <stop offset="0" stopColor="#90f0ff" />
        <stop offset="1" stopColor="#79e3ea" />
      </linearGradient>
      <path
        d="m462.778216 3445.9274 220.369072 201.66557-243.031084 72.59684z"
        fill="url(#a)"
        fillRule="evenodd"
        stroke="url(#b)"
        strokeWidth="8.170213"
        transform="matrix(.20791169 .9781476 -.9781476 .20791169 3554.703395 -1163.351461)"
      />
    </svg>
  );
};

export default SVGMatrixNegative;
