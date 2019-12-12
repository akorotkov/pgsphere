#!/bin/bash

##########################################################
#                                                        #
#   Copyright (c) 2003-2018, pgSphere development team   #
#   All rights reserved.                                 #
#                                                        #
##########################################################

PGSPHERE_VERSION="1.1.6"

#
# create the objects
#
cat ./pgs_brin.sql.in

#
# link them to the extension
#

echo ""
echo "-----------------------------------------------"
echo "-- add the needed functions to the extension --"
echo "-----------------------------------------------"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION spoint_overlaps_spherekey(spoint, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION spoint_contains_spherekey(spoint, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION spoint_iscontained_spherekey(spoint, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION sbox_overlaps_spherekey(sbox, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION sbox_contains_spherekey(sbox, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION sbox_iscontained_spherekey(sbox, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION spherekey_overlaps_spherekey(spherekey, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION spherekey_contains_spherekey(spherekey, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION spherekey_iscontained_spherekey(spherekey, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION spherekey_overlaps_spoint(spherekey, spoint);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION spherekey_contains_spoint(spherekey, spoint);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION spherekey_iscontained_spoint(spherekey, spoint);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION spherekey_overlaps_sbox(spherekey, sbox);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION spherekey_contains_sbox(spherekey, sbox);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION spherekey_iscontained_sbox(spherekey, sbox);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION spoint_overlaps_sbox(spoint, sbox);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION sbox_overlaps_spoint(sbox, spoint);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION sbox_iscontained_spoint(sbox, spoint);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION spoint_contains_sbox(spoint, sbox);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION spoint_brin_inclusion_add_value(internal, internal, internal, internal);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD FUNCTION sbox_brin_inclusion_add_value(internal, internal, internal, internal);"

echo ""
echo "-----------------------------------------------"
echo "-- add the needed operators to the extension --"
echo "-----------------------------------------------"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR &&(spherekey, spoint);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR @>(spherekey, spoint);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR <@(spherekey, spoint);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR &&(spoint, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR @>(spoint, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR <@(spoint, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR &&(spherekey, sbox);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR @>(spherekey, sbox);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR <@(spherekey, sbox);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR &&(sbox, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR @>(sbox, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR <@(sbox, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR &&(spherekey, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR @>(spherekey, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR <@(spherekey, spherekey);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR &&(spoint, sbox);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR &&(sbox, spoint);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR @>(sbox, spoint);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR @>(spoint, sbox);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR <@(sbox, spoint);"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR <@(spoint, sbox);"

echo ""
echo "------------------------------------------------------"
echo "-- add the needed operator classes to the extension --"
echo "------------------------------------------------------"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR CLASS brin_spoint_inclusion_ops USING brin;"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR CLASS brin_sbox_inclusion_ops USING brin;"

echo ""
echo "------------------------------------------------------"
echo "-- add the needed operator classes to the extension --"
echo "------------------------------------------------------"
echo "ALTER EXTENSION pgsphere-${PGSPHERE_VERSION} ADD OPERATOR OPERATOR FAMILY brin_inclusion_spheric_ops USING brin;"
