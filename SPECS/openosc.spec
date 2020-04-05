Name:           openosc
Version:        PACKAGE_VERSION
Release:        1%{?dist}
Summary:        Open Object Size Check Library
Group:          System Environment/Libraries

License:        ASL 2.0
URL:            https://github.com/cisco/openosc
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc
BuildRequires:  make

%description
OpenOSC is an open-source object size check library written in C. It has been
developed in order to promote the use of compiler builtin object size check
capability for enhanced security. It provides robust support for detecting
buffer overflows in various functions that perform operations on memory and
strings. Not all types of buffer overflows can be detected with this library,
but it does provide an extra level of validation for some functions that are
potentially a source of buffer overflow flaws. It protects both C and C++ code.


%package devel
Summary: The OpenOSC development package
Group: Development/Libraries
Requires:  openosc%{?_isa} = %{version}-%{release}

%description devel
OpenOSC development package, containing both header files and runtime library.

%package tools
Summary: The OpenOSC tools package
Group: Development/Libraries

%description tools
OpenOSC tools package, containing the tools to decode OSC tracebacks and
collect OSC metrics.

%package static
Summary: The OpenOSC static library package
Group: Development/Libraries
Requires: openosc-devel = %{version}-%{release}

%description static
OpenOSC static package, containing the static library.

%prep
%autosetup -n openosc-%{version}


%build
%configure
make %{?_smp_mflags}


%install
%make_install


%files
%{_libdir}/lib*.so.0*

%files devel
%{_libdir}/lib*.so
%{_includedir}/*.h

%files tools
%{_bindir}/oscdecode.py
%{_bindir}/oscmetrics.py

%files static
%{_libdir}/lib*.a


%changelog
* Sun Nov 25 2018 Yongkui Han <yonhan@cisco.com> PACKAGE_VERSION-1
- Initial packaging.
