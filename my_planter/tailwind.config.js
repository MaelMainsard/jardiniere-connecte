/** @type {import('tailwindcss').Config} */

import daisyui from "daisyui";

export default {
  content: [
    "./index.data",
    "./src/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {},
  },
  plugins: [
    daisyui,
  ],
}

