# FrisTracker

A GPS tracking device embedded in an Frisbee disc to capture real-time movement data during games.

![FrisTracker hardware](https://github.com/user-attachments/assets/878ac138-6a1c-410c-b116-b8a4a50f515a)

## What it does

FrisTracker records GPS coordinates during a frisbee game and wirelessly transmits them to a laptop in real-time. The data can show throwing patterns, strategies, and field coverage throughout a match.

## Why it exists

At my Youth club, we are obsesssed with Ultimate Frisbee. However, as we have lost last years anual Cup to another youth club, we were all devestad. So, I Build FrisTracker! It can help us to Analyze our Training games, and spot weaknesses in our Defense (Or more importantly, weaknesses in our Enemys defenses wich we can then exploit to get an very fair advantage)

Also, tracking a flying disc at 60 mph is just fun.

## Hardware

The tracker fits inside a Frisbee disc and includes:
- **ESP32-PICO-V3-02** microcontroller for GPS processing and wireless transmission
- **NEO-6M GPS module** with external antenna for position tracking
- **NRF24L01+PA+LNA** 2.4GHz radio module for real-time data transmission

A separate receiver module plugs into your laptop and captures the incoming GPS data.

The PCB design files are in `hardware/kicad/`. Gerber files for manufacturing are in `hardware/gerbers/fristracker-gerbers.zip`.

## Bill of Materials

| Part | Purpose | Qty | Unit Price | Total | Vendor |
|------|---------|-----|------------|-------|--------|
| [ESP32-PICO-V3-02](https://de.aliexpress.com/item/1005011934924363.html) | Microcontroller (comes as 2-pack) | 1 | $15.11 | $15.11 | AliExpress |
| [CH340E](https://de.aliexpress.com/item/1005012848940494.html) | USB-to-serial converter | 2 | $6.18 | $12.36 | AliExpress |
| [TLV75733PDRV](https://www.ti.com/product/TLV757P) | 3.3V voltage regulator | 2 | $0.44 | $0.88 | Texas Instruments |
| [NRF24L01+PA+LNA](https://de.aliexpress.com/item/1005008770982853.html) | 2.4GHz wireless transceiver | 2 | $3.84 | $7.68 | AliExpress |
| [NEO-6M GPS](https://de.aliexpress.com/item/1005013019346751.html) | GPS module | 1 | $3.42 | $3.42 | AliExpress |
| [Coin cell holder](https://www.sparkfun.com/coin-cell-battery-holder-12mm-smd.html) | Battery holder for GPS backup | 1 | $0.80 | $0.80 | SparkFun |
| [SMA edge connector](https://www.digikey.com/en/products/detail/rf-solutions/CON-SMA-EDGE-S/5845767) | GPS antenna connector | 1 | $2.75 | $2.75 | DigiKey |
| [GPS antenna](https://de.aliexpress.com/item/1005008618780803.html) | External GPS antenna | 1 | $3.45 | $3.45 | AliExpress |
| | | | **Subtotal** | **$46.45** | |
| | | | **Tax & shipping** | **$15.00** | |
| | | | **Total** | **$61.45** | |

Tax and shipping May vary at your place! - Not included Bill of PCB Files.

## Firmware

The tracker and receiver each run separate Arduino sketches:
- `firmware/tracker.ino` — runs on the disc, reads GPS and transmits data
- `firmware/receiver.ino` — runs on the laptop side, receives and logs data

## Status

Hardware design is complete. Firmware is functional but basic. Building instructions coming soon.

## Project structure

```
FrisTracker/
├── hardware/
│   ├── gerbers/           # Manufacturing files
│   ├── kicad/            # PCB design files
│   └── BOM_base.csv      # Component list
├── firmware/
│   ├── tracker.ino       # Disc-side firmware
│   └── receiver.ino      # Laptop-side firmware
└── docs/
    └── JOURNAL.md        # Development log
```

## License

Open source hardware project. Built as part of Half Life.

Built by Jakob. With lots of <3 and some Bugs :)
