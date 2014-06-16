# Graphics

EPS = logo.eps  sbox.eps  scircle.eps  sellipse.eps  sline.eps  spath.eps  sphere.eps  spoint.eps  spoly.eps  strans.eps

CONVERT = convert

all: eps

eps : $(EPS)

%.eps: %.jpg
	$(CONVERT) $< eps:$@

clean :
	rm -f $(EPS)
