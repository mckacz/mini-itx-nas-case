// Preset for:
//   - fanless mini-ITX motherboard (like N100DC-ITX)
//   - 2x 3.5" HDD
//   - 120mm fan
//
// Dimensions:
//  - width: 210mm
//  - depth: 210mm
//  - height: 161mm (156mm without legs)

include <base.scad>; // any setting can be overwritten

// pillar height
pillar_height = 140;

// pillar shelves location (Z axis) for additional equipment
pillar_shelves = [55, 95];

// enable fan mounts
fan = true;

// fan on left?
fan_on_left = true;
