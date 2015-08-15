Overview
--------
Prun job serialization library.

Building
--------

Build requirements:

- cmake 2.6 (or higher)
- GCC 4.6 (or higher) or Clang
- boost 1.46 (or higher)
- leveldb

Building debian packages::

> git clone https://github.com/abudnik/prun-leveldb.git
> cd prun-leveldb
> debuild -sa
> ls ../prun-leveldb*.deb

Building RPMs::

> git clone https://github.com/abudnik/prun-leveldb.git
> mv prun-leveldb prun-leveldb-0.1  # add '-version' postfix
> mkdir -p rpmbuild/SOURCES
> tar cjf rpmbuild/SOURCES/prun-leveldb-0.1.tar.bz2 prun-leveldb-0.1
> rpmbuild -ba prun-leveldb-0.1/prun-leveldb-bf.spec
> ls rpmbuild/RPMS/*/*.rpm

Building runtime from sources::

> git clone https://github.com/abudnik/prun-leveldb.git
> cd prun-leveldb
> cmake && make

Configuration
-------------

Example of prun-leveldb config file: prun/conf/history-leveldb.cfg

Config is represented in the JSON formatted file with following properties:

``db_path`` - path to directory containing leveldb database files.
