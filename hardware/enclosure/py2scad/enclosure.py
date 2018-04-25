"""
Creates an enclosure
"""
from py2scad import *

# Inside dimensions
x,y,z = 4.6, 2.1, 1.45
hole_list = []

params = {
        'inner_dimensions'        : (x,y,z), 
        'wall_thickness'          : (1.0/8.0), 
        'lid_radius'              : 0.25,  
        'top_x_overhang'          : 0.2,
        'top_y_overhang'          : 0.2,
        'bottom_x_overhang'       : 0.2,
        'bottom_y_overhang'       : 0.2, 
        'lid2front_tabs'          : (0.2,0.5,0.8),
        'lid2side_tabs'           : (0.25, 0.75),
        'side2side_tabs'          : (0.5,),
        'lid2front_tab_width'     : 0.5,
        'lid2side_tab_width'      : 0.5, 
        'side2side_tab_width'     : 0.5,
        'standoff_diameter'       : 0.0,
        'standoff_offset'         : 0.0,
        'standoff_hole_diameter'  : 0.116, 
        'hole_list'               : hole_list,
        }

enclosure = Basic_Enclosure(params)
enclosure.make()

part_assembly = enclosure.get_assembly(explode=(0.1,0.1,0.1))
part_projection = enclosure.get_projection()

prog_assembly = SCAD_Prog()
prog_assembly.fn = 50
prog_assembly.add(part_assembly)
prog_assembly.write('enclosure_assembly.scad')

prog_projection = SCAD_Prog()
prog_projection.fn = 50
prog_projection.add(part_projection)
prog_projection.write('enclosure_projection.scad')
