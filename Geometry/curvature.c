#include  <def_objects.h>

public  Status  create_sphere_from_polygons( polygons, sphere, centre,
                                   x_radius, y_radius, z_radius, max_curvature,
                                   offset_flag, offset_factor )
    polygons_struct   *polygons;
    polygons_struct   *sphere;
    Point             *centre;
    Real              x_radius, y_radius, z_radius;
    Real              max_curvature;
    Boolean           offset_flag;
    Real              offset_factor;
{
    Status        status;
    Status        create_polygons_sphere();
    Status        check_polygons_neighbours_computed();
    int           n_up, size, point_index, vertex_index, poly;
    Real          curvature, base_length;
    Smallest_int  *point_done;
    Point         centroid;
    Vector        normal, offset, sphere_normal;
    Status        compute_polygon_normals();
    void          get_surface_colour();
    void          compute_polygon_point_centroid();

    status = OK;

    if( get_tessellation_of_polygons_sphere( polygons, &n_up ) )
    {
        status = check_polygons_neighbours_computed( polygons );

        if( status == OK )
            status = create_polygons_sphere( centre, x_radius, y_radius,
                             z_radius, n_up, 2 * n_up, FALSE, sphere );

        if( status == OK )
            ALLOC( status, point_done, polygons->n_points );

        if( status == OK )
        {
            if( !offset_flag )
            {
                sphere->colour_flag = PER_VERTEX_COLOURS;

                REALLOC( status, sphere->colours, sphere->n_points );
            }
            else
                sphere->colours[0] = polygons->colours[0];
        }

        if( status == OK )
        {
            for_less( point_index, 0, polygons->n_points )
                point_done[point_index] = FALSE;

            for_less( poly, 0, polygons->n_items )
            {
                size = GET_OBJECT_SIZE( *polygons, poly );

                for_less( vertex_index, 0, size )
                {
                    point_index = polygons->indices[
                        POINT_INDEX(polygons->end_indices,poly,vertex_index)];

                    if( !point_done[point_index] )
                    {
                        point_done[point_index] = TRUE;

                        compute_polygon_point_centroid( polygons, poly,
                                  vertex_index, point_index, &centroid,
                                  &normal, &base_length, &curvature );

                        
                        if( offset_flag )
                        {
                            SUB_POINTS( sphere_normal,
                                        sphere->points[point_index],
                                        *centre );
                            NORMALIZE_VECTOR( sphere_normal, sphere_normal );
                            SCALE_VECTOR( offset, sphere_normal,
                                          offset_factor * curvature );

                            ADD_POINT_VECTOR( sphere->points[point_index],
                                              sphere->points[point_index],
                                              offset );
                        }
                        else
                        {
                            get_surface_colour( curvature, max_curvature,
                                                &sphere->colours[point_index] );
                        }
                    }
                }
            }
        }
    }



    return( status );
}

private  void  get_surface_colour( curvature, max_curvature, colour )
    Real    curvature;
    Real    max_curvature;
    Colour  *colour;
{
    Real   ratio;

    if( curvature < -max_curvature )
        curvature = -max_curvature;
    else if( curvature > max_curvature )
        curvature = max_curvature;

    ratio = (curvature + max_curvature) / max_curvature / 2.0;

    fill_Colour( *colour, ratio, ratio, ratio );
}
