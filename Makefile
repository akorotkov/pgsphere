
PGSPHERE_VERSION = 1.1.6

# the base dir name may be changed depending on git clone command
SRC_DIR = $(shell basename $(shell pwd))

MODULE_big = pg_sphere

ifndef PG_CONFIG
  PG_CONFIG := pg_config
endif

PG_FULL_VERSION := $(shell $(PG_CONFIG) --version)
PG_MAJOR_VERSION := $(shell echo $(PG_FULL_VERSION) | cut -d' ' -f2 | cut -d. -f1)
PG_MINOR_VERSION := $(shell echo $(PG_FULL_VERSION) | cut -d' ' -f2 | cut -d. -f2)
BRIN_CHECK := $(shell [ $(PG_MAJOR_VERSION)$(PG_MINOR_VERSION) -gt 94 ] && echo 1 || echo 0 )
ifeq ($(BRIN_CHECK), 1)
  BRIN_OBJ := brin.o
  BRIN_SQL := pgs_brin.sql
  BRIN_REGRESS := spoint_brin
endif

OBJS       = sscan.o sparse.o sbuffer.o vector3d.o point.o \
             euler.o circle.o line.o ellipse.o polygon.o \
             path.o box.o output.o gq_cache.o gist.o key.o \
             $(BRIN_OBJ) \
             gnomo.o

EXTENSION   = pg_sphere
DATA_built  = pg_sphere--1.1.sql
DOCS        = README.pg_sphere COPYRIGHT.pg_sphere
REGRESS     = init tables points euler circle line ellipse poly path box index \
              contains_ops contains_ops_compat bounding_box_gist gnomo \
              $(BRIN_REGRESS)

EXTRA_CLEAN = pg_sphere--1.1.sql $(PGS_SQL) sscan.c

CRUSH_TESTS  = init_extended circle_extended 

# order of sql files is important
PGS_SQL    =  pgs_types.sql pgs_point.sql pgs_euler.sql pgs_circle.sql \
   pgs_line.sql pgs_ellipse.sql pgs_polygon.sql pgs_path.sql \
   pgs_box.sql pgs_contains_ops.sql pgs_contains_ops_compat.sql \
   pgs_gist.sql gnomo.sql \
   $(BRIN_SQL)

ifdef USE_PGXS
  PGXS := $(shell $(PG_CONFIG) --pgxs)
  include $(PGXS)
else
  subdir = contrib/pg_sphere
  top_builddir = ../..
  PG_CONFIG := $(top_builddir)/src/bin/pg_config/pg_config
  include $(top_builddir)/src/Makefile.global
  include $(top_srcdir)/contrib/contrib-global.mk
endif

crushtest: REGRESS += $(CRUSH_TESTS)
crushtest: installcheck

pg_sphere--1.1.sql: $(addsuffix .in, $(PGS_SQL))
	cat $^ > $@

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
	cd .. && tar --transform s/$(SRC_DIR)/pgsphere-$(PGSPHERE_VERSION)/ --exclude CVS -czf pgsphere-$(PGSPHERE_VERSION).tar.gz $(SRC_DIR) && cd -
