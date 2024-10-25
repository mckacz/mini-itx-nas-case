# Mini-ITX NAS case

I've decided to design my own case because I could not find any suitable case for 
a mini-ITX motherboard with two 3.5 HDDs and no ATX power supply :sunglasses:

| Render                                                                                                                                         | Assembled                                                                                                                                          |
|------------------------------------------------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------|
| <img alt="render_front_passive_mini_itx_2x3.5_hdd_fan_lcd.png" src=".assets/render_front_passive_mini_itx_2x3.5_hdd_fan_lcd.png" width="300"/> | <img alt="printed_front_passive_mini_itx_2x3.5_hdd_fan_lcd.jpg" src=".assets/printed_front_passive_mini_itx_2x3.5_hdd_fan_lcd.jpg" width="300"/>   |
| <img alt="render_inside_mini_itx_2x3.5_hdd_fan_lcd.png" src=".assets/render_inside_mini_itx_2x3.5_hdd_fan_lcd.png" width="300"/>               | <img alt="printed_inside_passive_mini_itx_2x3.5_hdd_fan_lcd.jpg" src=".assets/printed_inside_passive_mini_itx_2x3.5_hdd_fan_lcd.jpg" width="300"/> |

## Features

* Highly configurable (few configuration presents provided)
* Support of mini-ITX motherboard with built-in power supply
* Support of mini-ITX motherboard with Pico ATX power supply
* Optional support for multiple 3.5" HDD drives
* Optional support of 120mm case fan
* Optional support of ESP32-S3-Touch-LCD-1.28 module used as a power button :metal:

## Pre-rendered variants

Check [stl](stl) folder for pre-rendered variants. 

## Customizing

1. Clone this repo
2. :warning: Download submodules:
    * `git submodule init`
    * `git submodule update`
3. Open [mini-itx-nas-case.scad](scad/mini-itx-nas-case.scad) and select base configuration preset (or create a new one)
4. You can override any variable defined in [base.scad](scad/config/base.scad)
5. Render all parts using OpenSCAD
   * :warning: do not render the whole case at once - it will not be printable
   * render each part separately - to render a single part, prefix it with `!` in [mini-itx-nas-case.scad](scad/mini-itx-nas-case.scad) and render

## Printing tips

* Recommended material: `PETG` (`PLA` could bend if things get hot)  
* Recommended material for case legs and caps: `TPU` 
* Use 0.6 nozzle to save some time 
* Pillars, caps and legs must be printed in 4 copies
* Print as many copies of the 3.5 HDD frame as you need
* Only front panel with LCD slot requires support

## Assembly guide

1. Print all parts
2. Glue the top and bottom panels to the top/bottom case part
   * :bulb: soldering borders using a soldering iron also works well (join is invisible after assembly)
3. Optionally glue legs to the bottom part of the case
4. Install brass inserts in the bottom part and in all of the pillars
5. Screw the motherboard to the bottom part
   * do not forget to install MB's backplate - later there will be no space for that
6. Screw pillars to the bottom part
7. If you have a 3.5 HHD drive:
   * screw HDDs to frames
   * screw frames to pillars
8. Install side panels
9. If you use a variant with a fancy LCD module as a power button, you will need to assemble an additional PCB board
   and flash the firmware. Check [here](extra/ESP32-S3-Touch-LCD-1.28-firmware#parts) for the details.
10. Screw the top part to the pillars
11. Optionally install caps to hide screws in the top part

## Test setup

* **OS:** TrueNAS SCALE 24.04
* **Motherboard:** ASRock N100DC-ITX
* **Boot volume:** SSD WD Red SN700 250GB M.2 (yep, it's overkill. I know that now :see_no_evil:)
* **Apps volume:** SSD WD Red SN700 250GB M.2 using Ugreen PCIe 3.0 x4 M.2 PCIe NVMe expander
* **Data volumes:** 2x WD Red Pro 3.5" 8TB (mirror)
* **Fan:** Noctua NF-F12 PWM

Works well :rocket:
