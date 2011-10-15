SUBDIRS = src translations tests

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = wikt.spec.in

UPLOAD_URI = klic.name:/var/ftp/wikt
.PHONY: upload
upload:
	make dist-xz
	scp $(distdir).tar.xz $(UPLOAD_URI)

RPM_DIRS = --define "_sourcedir `pwd`" \
           --define "_rpmdir `pwd`" \
           --define "_specdir `pwd`" \
           --define "_builddir `pwd`" \
           --define "_srcrpmdir `pwd`"

rpm: dist-xz wikt.spec
	rpmbuild $(RPM_DIRS) -ba wikt.spec
srpm: dist-xz wikt.spec
	rpmbuild $(RPM_DIRS) -bs wikt.spec
