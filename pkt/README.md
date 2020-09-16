# What is json ?
https://spec.json5.org/  

# Sending packets from a file  
Syntax:
```
!<filename> <argname>:<argvalue>, <argname>:<argvalue>,
```
Where: ``<filename>`` is a path to json5 file either absolute or relative to current program directory!  
If: ``<filename>`` can not be found aditional lookup is made as ``pkt/quick/<filename>.js``  
Where: ``<argname>:<argvalue>, <argname>:<argvalue>,`` is parsed as if it were json5 object ``{ <argname>:<argvalue>, <argname>:<argvalue>, }``  

Example:
```
!reskin name:"Teemo"
```

# Using multiple lines
Syntax:
```
!send reskin \
"Teemo", \
0 \
\
```

# Arguments 
After parsing a file, lookup is performed on all string values to replace them with arguments and constants.  
| Name               | Value                                                              |
|--------------------|--------------------------------------------------------------------|
| ${cid}             | client id of sender                                                |
| ${heroNetID}       | currently hardcoded to 0x40000001                                  |
| ${newNetID}        | generates new NetID                                                |
| ${lastPingX}       | last ping X location                                               |
| ${lastPingY}       | last ping Y location                                               |
| ${lastOrderX}      | last order X location                                              |
| ${lastOrderY}      | last order Y location                                              |
| ${lastOrderZ}      | last order Z location                                              |
| ${lastPingNetID}   | last ping target netID                                             |
| ${lastOrderNetID}  | last order target netID                                            |
| ${lastSelectNetID} | last select(left click) object netID, currently unimplemented      |  
Check build_replacements() function in game.cpp for any possible changes.  

# Packet definitions
Currently in ``src/proto_pkt.hpp``  
Note: Arrays must contain exactly as much as elements as specified in structure definition.  

# Automatically run
```
"pkt/on_spawn/all.js"
"pkt/on_spawn/<protocol version>.js"
```
and
```
"pkt/on_start/all.js"
"pkt/on_start/<protocol version>.js"
```
