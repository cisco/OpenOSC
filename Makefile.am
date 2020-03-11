SUBDIRS = src test tools
EXTRA_DIST = SPECS DEBIAN LICENSE VERSION README.md

rpm: dist
	if type -P "rpmbuild" &> /dev/null ; then \
	    echo "rpmbuild exists on the path." ; \
	else \
	    echo "rpmbuild does not exist, please install it before building RPM." ; exit 1 ; \
	fi
	@echo "Creating RPM package..."
	mkdir -p rpmbuild/SPECS ; cp SPECS/openosc.spec rpmbuild/SPECS/ ; 
	sed -i 's/PACKAGE_VERSION/$(PACKAGE_VERSION)/g' rpmbuild/SPECS/openosc.spec ;
	mkdir -p rpmbuild/SOURCES ; cp openosc-$(PACKAGE_VERSION).tar.gz rpmbuild/SOURCES/ ; 
	cd rpmbuild; rpmbuild --define "_topdir `pwd`" -ba SPECS/openosc.spec
	@echo "Done creating RPM package."

deb:
	if type -P "dpkg-buildpackage" &> /dev/null ; then \
	    echo "dpkg-buildpackage exists on the path." ; \
	else \
	    echo "dpkg-buildpackage does not exist, please install it before building debian package." ; exit 1 ; \
	fi
	if type -P "dh" &> /dev/null ; then \
	    echo "dh exists on the path." ; \
	else \
	    echo "dh does not exist, please install it before building debian package." ; exit 1 ; \
	fi
	@echo "Creating debian package..."
	mkdir -p debian ; cp DEBIAN/* debian/ ;
	sed -i 's/PACKAGE_VERSION/$(PACKAGE_VERSION)/g' debian/changelog ;
	dpkg-buildpackage -b -uc -us
	@echo "Done creating debian package."
