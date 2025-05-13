# TODO
- [x] Port over the button util 
- [x] Fix up the vector nav lib
- [x] Create the new default .blend file
- [ ] Get neopixels showing something useful
- [ ] Test
- [ ] Ball

# How to use this (WIP)
### A high level overview
There is the platformio project (the .ini file, include/src directories, other hidden things) and then all the default blender stuff in the blender directory. Once you push the code to a coneLogger^{tm} and get a set of points of some cones or other track landmark/feature, then follow these steps

#### FBX Export settings
Object Types = Mesh
Scale = 0.01
Apply Scalings = FBX ALL

#### SDK Path
`/path_to_steamapps/common/assettocorsa/sdk/editor`

### Random details about the Kunos map maker 
You cannot have any individual object have more than 64k verts, if anything is it will freeze and die
For some reason it always defaults to black and white, just go to illumination and change the filters and whatnot
ksAmbient is the brightness in the shadows
ksDiffuse is the brightness in nominal light
ksSpecular is the brightness of the "glossy" affect
