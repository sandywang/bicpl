#ifndef  DEF_OBJECTS
#define  DEF_OBJECTS

#include  <def_mni.h>
#include  <def_geom_structs.h>

#define  SET_OBJECT_SIZE( object, n, size ) \
             { \
                 if( (n) == 0 ) \
                     (object).end_indices[0] = (size); \
                 else \
                     (object).end_indices[n] = (size) + \
                                               (object).end_indices[(n)-1]; \
             }

#define  GET_OBJECT_SIZE( object, n ) \
             ( ((n) == 0) ? (object).end_indices[0] : \
                         ((object).end_indices[n] - \
                          (object).end_indices[(n)-1]) )

#define  NUMBER_INDICES( object ) \
             ( ((object).n_items == 0) ? 0 : \
                  (object).end_indices[(object).n_items-1] )

#define  START_INDEX( end_indices, n ) \
             ( ((n) == 0) ? 0 : (end_indices)[(n)-1] )

#define  POINT_INDEX( end_indices, n, edge ) \
             ( START_INDEX(end_indices,n) + (edge) )

typedef enum { ONE_COLOUR, PER_ITEM_COLOURS, PER_VERTEX_COLOURS } Colour_flags;

typedef  struct
{
    Colour_flags   colour_flag;
    Colour         *colours;
    int            line_thickness;

    int            n_points;
    Point          *points;

    int            n_items;
    int            *end_indices;
    int            *indices;
} lines_struct;

typedef  enum  { BOX_MARKER, SPHERE_MARKER,
                 N_MARKER_TYPES } Marker_types;

typedef  struct
{
    Marker_types   type;
    Colour         colour;
    Point          position;
    Real           size;
    String         label;
    int            structure_id;
    int            patient_id;
} marker_struct;

typedef  struct
{
    Colour_flags    colour_flag;
    Colour          *colours;
    Surfprop        surfprop;

    int             n_points;
    Point           *points;
    Vector          *normals;

    int             n_items;
    int             *end_indices;
    int             *indices;

    Smallest_int    *visibilities;
} polygons_struct;

typedef  struct
{
    Colour_flags    colour_flag;
    Colour          *colours;
    Surfprop        surfprop;

    Boolean         m_closed, n_closed;

    int             m, n;
    Point           *points;
    Vector          *normals;
} quadmesh_struct;

typedef enum { FIXED_FONT, SIZED_FONT } Font_types;

typedef  struct
{
    Point       origin;
    Colour      colour;
    Font_types  font;
    Real        size;
    String      string;
} text_struct;

typedef enum { 
                 COLOUR_INDEX_8BIT_PIXEL, COLOUR_INDEX_16BIT_PIXEL, RGB_PIXEL
             } Pixel_types;

typedef  struct
{

    int             x_size;
    int             y_size;
    Pixel_types     pixel_type;
    union
    {
        unsigned char   *pixels_8bit_colour_index;
        unsigned short  *pixels_16bit_colour_index;
        Colour          *pixels_rgb;
    } data;

} pixels_struct;

#define  PIXEL_COLOUR_INDEX_8( pixels, x, y )                                 \
           ((pixels).data.pixels_8bit_colour_index[IJ(y,x,(pixels).x_size)])

#define  PIXEL_COLOUR_INDEX_16( pixels, x, y )                                \
           ((pixels).data.pixels_16bit_colour_index[IJ(y,x,(pixels).x_size)])

#define  PIXEL_RGB_COLOUR( pixels, x, y )                                     \
           ((pixels).data.pixels_rgb[IJ(y,x,(pixels).x_size)])

#endif