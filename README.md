# ab_server_fiber_poc

A closed-loop Modbus TCP testbed: a simulated water tank, a C control loop using libplctag, and a browser GUI.

## Components
- `plant.py` — simulates a water tank over Modbus TCP (port 5020). Holding register 0 = tank level, coil 0 = pump on/off.
- `client.c` — bang-bang controller. Reads tank level, turns the pump on/off via libplctag, writes state to `www/status.json`.
- `www/index.html` — polls `status.json` and renders the tank level as a filling/draining bar.

## Prerequisites
- Python 3.9+ with `pymodbus<3` (`pip install "pymodbus<3"`)
- MSVC Build Tools (Developer Command Prompt)
- [libplctag](https://github.com/libplctag/libplctag) built from source — `plctag.dll`, `plctag.lib`, `libplctag.h` copied/linked in (not committed here, build separately)

## Build
\`\`\`
cl.exe client.c /I <path_to_libplctag.h> /link /LIBPATH:<path_to_plctag.lib_dir> plctag.lib ws2_32.lib
\`\`\`

## Run
Three terminals, from this folder:
\`\`\`
py plant.py
client.exe
cd www && py -m http.server 8000
\`\`\`
Then open http://localhost:8000
