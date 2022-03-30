This is an R-Tree implementation using GiST for spherical objects
like spherical points and spherical circles with 
useful functions and operators.


NOTICE:
     This version will work only with postgresql version 9.1 and above.

INSTALLATION:

  -- build and install
  gmake USE_PGXS=1 PG_CONFIG=/usr/bin/pg_config
  gmake USE_PGXS=1 PG_CONFIG=/usr/bin/pg_config install
  -- load extension
  psql -c "CREATE EXTENSION pg_sphere;" <database>

REGRESSION TEST (as the same user as the currently running postgresql server):

  make USE_PGXS=1 installcheck

LONG REGRESSION TEST:

  make USE_PGXS=1 crushtest

The 'make' program must be compatible with GNU make.

For more information, have a look at http://pgsphere.projects.postgresql.org
and https://github.com/akorotkov/pgsphere

Have a lot of fun!

