Ebcdic2vdt
==========

The `ebcdic2vdt` tools have been written to extract Videotex pages from 8"
Unitel disc images.

Requirements
------------

These tools need a Linux environment with Bash and GCC.

Compilation
-----------

Running `make` will generate the `searchpage` command in the current directory.

It is used by the `splitpages.bash` script.

Usage
-----

### Converting a raw Unitel disc image to ASCII

Unitel discs come from systems using EBCDIC. Since the Videotex pages use the
ASCII encoding, the images must be converted.

This is the role of the `ebcdic2vdt.bash` script:

    cat disc.img | ./ebcdic2vdt.bash > disc.img.vdts

### Extracting the Videotex pages

Once the Unitel disc image has been converted, Videotex pages can be extracted:

    ./splitpages.bash disc.img.vdts

The generated files will look like this:

    disc.img-46336-47376.vdt
    disc.img-48384-49400.vdt
    disc.img-50432-51841.vdt
    disc.img-52480-54110.vdt

Notes
-----

These are quick and dirty tools, don't expect too much!