OpenOSC Library - README
=======================

Table of Contents
-----------------
* [Licensing](#Licensing)
* [Overview](#Overview)
* [Design Considerations](#Design-Considerations)
* [Relationship to FORTIFY_SOURCE](#Relationship-to-FORTIFY_SOURCE)
* [How to Build OpenOSC Library](#How-to-Build-OpenOSC-Library)
* [How to Build Packages with OpenOSC Library](#How-to-Build-Packages-with-OpenOSC-Library)
* [Tested Platforms](#Tested-Platforms)
* [Known Issues](#Known-Issues)
* [Bibliography](#References)


Licensing
---------

This project's licensing restrictions are documented in the file 'LICENSE'
under the root directory of this release. Basically it's ASL 2.0 licensed.

Overview
--------

OpenOSC is an open-source object size check library written in C. It has been
developed in order to promote the use of compiler builtin object size check
capability for enhanced security. It provides lightweight support for detecting
buffer overflows in various functions that perform operations on memory and
strings. Not all types of buffer overflows can be detected with this library,
but it does provide an extra level of validation for some functions that are
potentially a source of buffer overflow flaws. It protects both C and C++ code.

Design Considerations
---------------------

The OpenOSC library is a standalone library with the following features:
- Metrics to understand buffer overflow detection effectiveness
- Ability to detect source buffer overread as well as buffer overflow
- Truncate overflow past the end of buffer in running process
- Abort behavior configurable
- Extensible to additional data movement routines
- Extension for SafeC bounds checking library available

OpenOSC contains two parts: the mapping header files and the runtime library.

The runtime library libopenosc.so contains the code to do runtime buffer
overflow checks. This library is required to be linked by all packages.

The mapping header files contain the code to perform compile-time buffer
overflow checks and map various memory routines to the runtime check routines
in the runtime library.

The mapping header files are only required in the package build environment,
while the runtime library is required in both the deployment environment and
the package build environment.

Two OSC function mapping methods are supported in OpenOSC:

    #define OPENOSC_ASM_LABEL_REDIRECT_METHOD    1
    #define OPENOSC_FUNC_MACRO_REDEFINE_METHOD   2

They are two different mapping methods. The ASM_LABEL_REDIRECT method uses
`__asm__` label to redirect an alias function to the real function at assembly
language level, while keeping them as different functions at C language level.
The FUNC_MACRO_REDEFINE method uses macro redefining mechanism to directly
redefine a foo function as a new openosc_foo function at C language level.

The two methods both have advantages and disadvantages.

Note that if your compiler is clang, the ASM_LABEL_REDIRECT method requires
that your clang version must be >= 5.0 version.

The default mapping method is 1, the ASM_LABEL_REDIRECT method. User can choose
the FUNC_MACRO_REDEFINE method by adding the below define to CFLAGS:

    CFLAGS += "-DOPENOSC_MM=2"

New mapping method can be added as needed in future.

* *Built-in OSC-METRICS feature*

The built-in OSC-METRICS feature can be enabled by the below flag to CFLAGS:

    CFLAGS += "-DOPENOSC_METRIC_FEATURE_ENABLED"

Additionally, the objsize-METRICS feature can be enabled by the below:

    CFLAGS += "-DOPENOSC_METRIC_OBJSIZE_ENABLED"

After building your binaries with the above CFLAGS, You can run the oscmetrics
tool to collect the OSC-METRICS:

    $ tools/oscmetrics.py -bmwv -d your-dir > metrics-report.txt

One trick: To generate the binary even when buffer overflow errors exist, add
`-DOPENOSC_OVERFLOW_ERROR_OUT_DISABLE` to CFLAGS. This will just print warnings
instead of errors at compile-time so that binary can be generated. If you use
`-DOPENOSC_MM=2` CFLAGS, then you can add `-DOPENOSC_METRIC_ONLY_MODE` to CFLAGS
to collect OSC metrics only.

Trick #2: the oscmetrics.py tool ignores intermediate relocatable \*.o files by
default. You can add `--scan_all_elf_files` option to force the tool to scan the
\*.o files too.

Trick #3: for cross-compilation binaries, you may need to specify the location
of cross-compilation tools: objdump, addr2line, etc. in a configfile, then run
oscmetrics.py with `-c configfile` option to get correct results.

Relationship to FORTIFY_SOURCE
------------------------------
Most compilers (gcc/clang/icc) provide the FORTIFY_SOURCE feature.
It is enabled by adding `-D_FORTIFY_SOURCE=2` option to CFLAGS.

    CFLAGS += "-D_FORTIFY_SOURCE=2"

OpenOSC and compiler's FORTIFY_SOURCE are both built upon the compiler's
builtin object size check capability, thus are equivalent in providing memory
overflow detection/protection. As a result, a package can only be compiled with
one of them: either OpenOSC or FORTIFY_SOURCE, but not both. FORTIFY_SOURCE and
OpenOSC are mutually exclusive. OpenOSC will automatically detect the existence
of _FORTIFY_SOURCE flag, and disable OpenOSC if detected.

OpenOSC can co-exist with FORTIFY_SOURCE. That is, some packages or binaries
can be compiled with OpenOSC, and some other packages/binaries can be compiled
with FORTIFY_SOURCE. They can co-exist on the same Linux system, and will be
protected by different runtime libraries.


How to Build OpenOSC Library
----------------------------
The build system for the OpenOSC library is the well known GNU build system,
a.k.a. Autotools. This system is well understood and supported by many
different platforms and distributions which should allow this libary to be
built on a wide variety of platforms. See the "Tested Platforms" section
for details on what platforms this library was tested on during its
development.

1. *Building*

For those familiar with autotools you can probably skip this part. For those
not and want to get right to building the code see below. And, for those that
need additional information see the 'INSTALL' file in the same directory.

To build you do the following:

Case 1: If you have the openosc taball, then you do:

    $ ./configure
    $ make

Case 2: If you build from the git workspace, then please first install
autotools, and then do:

    $ autoreconf -vfi
    $ ./configure
    $ make

That is, autoreconf only needs to be run if you are building from the git
repository. Optionally, you can do `make check` if you want to run the unit
tests.

To build RedHat RPM packages:

    $ ./configure
    $ make rpm

A few OpenOSC RPM packages are generated:

- openosc RPM contains only the runtime library.
- openosc-devel RPM contains both runtime library and mapping header files.
- openosc-static RPM contains static library.
- openosc-tools RPM contains the tools to decode OSC tracebacks and collect OSC metrics.

To build Debian/Ubuntu DEB packages:

    $ ./configure
    $ make deb

2. *Installing*

Installation must be preformed by `root`, an `Administrator` on most
systems. The following is used to install the library.

    $ sudo make install

To install RedHat RPM packages:

    $ make rpm
    $ sudo rpm -ivh openosc-1.0.0-1.el7.x86_64.rpm
    $ sudo rpm -ivh openosc-devel-1.0.0-1.el7.x86_64.rpm

To install Debian/Ubuntu DEB packages:

    $ make deb
    $ sudo apt install openosc_1.0.0-1_amd64.deb

How to Build Packages with OpenOSC Library
------------------------------------------
The following build changes are required to build a package with OpenOSC.

    CFLAGS += "-include openosc.h"
    LDFLAGS += "-lopenosc"

Please install OpenOSC to your system before building your packages.

* *Mock build on Centos*

In Centos, you can modify the redhat RPM-config macros to add OpenOSC flags
to the global RPM configs so that all packages can pick up the global RPM
build options automatically.

The mock tool is recommended to build RPM packages on Centos.

Here is the steps to build OpenOSC-enabled RPM packages in mock:
 
    mock -r epel-7-x86_64 --rootdir=your-rootdir --resultdir=your-result-dir --init
    mock -r epel-7-x86_64 --rootdir=your-rootdir --resultdir=your-result-dir --install openosc-1.0.0-1.el7.x86_64.rpm
    mock -r epel-7-x86_64 --rootdir=your-rootdir --resultdir=your-result-dir --install openosc-devel-1.0.0-1.el7.x86_64.rpm
    mock -r epel-7-x86_64 --rootdir=your-rootdir --resultdir=your-result-dir --copyin redhat-rpm-config-macros-openosc  usr/lib/rpm/redhat/macros
    mock -r epel-7-x86_64 --rootdir=your-rootdir --resultdir=your-result-dir --no-clean --no-cleanup-after --rebuild your-srpm
    mock -r epel-7-x86_64 --rootdir=your-rootdir --resultdir=your-result-dir --no-clean --no-cleanup-after --rebuild your-srpm2

The redhat-rpm-config-macros-openosc file has been modified to add the below:

    __global_cflags += "-include openosc.h"
    __global_ldflags += "-lopenosc"

Actually a new flag is defined to turn on/off OpenOSC build:

    %_openosc_build 1

Each package can choose to enable or disable OpenOSC build independently in its
RPM spec file:

    # To enable OpenOSC build for your RPM package
    %global _openosc_build 1

    # To disable OpenOSC build for your RPM package
    %undefine _openosc_build

* *Enable the OSC-METRICS feature during package build*

Add below to CFLAGS to enable the OSC-METRICS feature for your package build:

    CFLAGS += "-include openosc.h -DOPENOSC_METRIC_FEATURE_ENABLED"


Tested Platforms
----------------

The library has been tested on the following systems:
- Centos 6/7/8 amd64/i386 glibc 2.12 - 2.28
- Linux Debian 9-11 amd64/i386 glibc 2.24 - 2.28

with most available compilers (gcc/clang/icc).

Note: Clang version >= 5.0 is required for ASM_LABEL_REDIRECT mapping method.
Also, to get better compile-time errors/warnings, the function attributes of
error/warning should be supported by Clang. The -fno-common option is
recommended for Clang too for better detection of buffer overflows/overreads.

Known Issues
------------
1. If you are building the library from the git repository you will have to
   first install autotools, then run autoreconf to create the configure script.

2. OPENOSC_METRIC_FEATURE_ENABLED does not impact compilation performance.
However, OPENOSC_METRIC_OBJSIZE_ENABLED impacts the compilation performance
significantly, especially for Clang.

References
----------
- [1] OpenOSC: Open Source Object Size Checking Library With Built-in
Metrics, *Yongkui Han, Pankil Shah, Van Nguyen, Ling Ma, Richard Livingston
(Cisco Systems)*
