# What is json ?
TODO: find a link showing json for dummies  

# Sending packets from a file  
Syntax:  
``
!open <filename> <arg0>, <arg1>
``  
Where `<filename>` is a path to json5 file either absolute or relative to current program directory!  
If `<filename>` can not be found aditional lookup is made as `pkt/quick/<filename>.js`  
Where `<arg0>, <arg1>` is parsed as if it were json5 array `[ <arg0>, <arg1> ]`  

Example:  
``
!open reskin "Teemo", 0
``  

# Sending packets directly from game  
``
!send <packetname> <field>:<value>, <field>:<value>
``
Where `<packetname>` is packet name  
Where `<field>:<value>, <field>:<value>` is parsed as if it were json5 object `{ <field>:<value>, <field>:<value> }`

# Using multiple lines
``
!send reskin \
"Teemo", \
0 \
\
``

# Arguments 
After parsing a file, lookup is performed on all string values to replace them with arguments and constants.  
``
| Name               | Value
| ${0}               | <arg0>
| ${1}               | <arg1>
| ${N}               | <argN>
| ${cid}             | client id of sender
| ${heroNetID}       | currently hardcoded to 0x40000001
| ${lastPingX}       | last ping X location
| ${lastPingY}       | last ping Y location, this is height in older versions, 0 in newer
| ${lastPingZ}       | last ping Z location
| ${lastPingNetID}   | last ping object netID
| ${lastSelectNetID} | last select(left click) object netID, currently unimplemented
``
Check build_replacements() function in game.cpp for any possible changes.  

# Packet definitions
Currently in `src/proto_pkt.hpp`  
Note: Arrays must contain exactly as much as elements as specified in structure definition.  
