MODULE_big = pg_sphere
OBJS       = sscan.o sparse.o sbuffer.o vector3d.o point.o \
             euler.o circle.o line.o ellipse.o polygon.o \
             path.o box.o output.o gq_cache.o gist.o key.o \
             crossmatch.o

DATA_built  = pg_sphere.sql
DOCS        = README.pg_sphere COPYRIGHT.pg_sphere
REGRESS     = init tables points euler circle line ellipse poly path box index
EXTRA_CLEAN = pg_sphere.sql pg_sphere.sql.in $(PGS_SQL) 

CRUSH_TESTS  = init_extended circle_extended 

# order of sql files is important
PGS_SQL    =  pgs_types.sql pgs_point.sql pgs_euler.sql pgs_circle.sql \
   pgs_line.sql pgs_ellipse.sql pgs_polygon.sql pgs_path.sql \
   pgs_box.sql pgs_gist.sql pgs_crossmatch.sql

ifdef USE_PGXS
  ifndef PG_CONFIG
    PG_CONFIG := pg_config
  endif
  PGXS := $(shell $(PG_CONFIG) --pgxs)
  include $(PGXS)
else
  subdir = contrib/pg_sphere
  top_builddir = ../..
  PG_CONFIG := $(top_builddir)/src/bin/pg_config/pg_config
  include $(top_builddir)/src/Makefile.global
  include $(top_srcdir)/contrib/contrib-global.mk
endif

PGVERSION += $(shell $(PG_CONFIG) --version | sed 's,^PostgreSQL[[:space:]][[:space:]]*,,' | awk '{ split($$1,a,"."); printf( "v%02d%02d%02d" ,a[1], a[2], a[3]); }' )

crushtest: REGRESS += $(CRUSH_TESTS)
crushtest: installcheck

pg_sphere.sql.in : $(addsuffix .in, $(PGS_SQL))
	echo 'BEGIN;' > $@
	for i in $+ ; do $(AWK) -v pg_version=$(PGVERSION) -f sql.awk < $$i >> $@ ; done
	echo 'COMMIT;' >> $@

sscan.o : sparse.c

sparse.c: sparse.y
ifdef YACC
	$(YACC) -d $(YFLAGS) -p sphere_yy -o sparse.c $<
else
	@$(missing) bison $< $@
endif

sscan.c : sscan.l
ifdef FLEX
	$(FLEX) $(FLEXFLAGS) -Psphere -o$@ $<
else
	@$(missing) flex $< $@
endif

dist : clean sparse.c sscan.c
	find . -name '*~' -type f -exec rm {} \;
	cd .. && tar  --exclude CVS -czf pg_sphere.tar.gz pg_sphere && cd -
 	