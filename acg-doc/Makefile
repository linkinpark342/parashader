all: parallel_raytracing.dvi

parallel_raytracing.pdf: parallel_raytracing.dvi
	dvipdf $<

parallel_raytracing.dvi: parallel_raytracing.tex parashader.bib color_shades.eps \
		normal_gray_scale.eps original_color.eps \
		overly_lit_gray_scale.eps red_scale.eps red_shades.eps \
		blue_gene_bounces_plot.eps blue_gene_pixels_plot.eps \
		taro_desktop_plot.eps timings-test1.eps timings-test2.eps
	latex $<
	bibtex $(<:.tex=)
	latex $<
	latex $<

%.pdf: %.eps
	dvipdf $<

%.eps: %.png
	convert $< $@

%.eps:
	if [ ! -f $@ ]; then \
		make -C ../results; \
		ln -s ../results/$@; \
	fi

clean:
	rm -f *.eps *.aux *.bbl *.blg *.log *.out parallel_raytracing.dvi parallel_raytracing.pdf
