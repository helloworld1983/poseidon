.PHONY: MCSL down_traffic create_xml clean all
SHELL := /bin/bash

all: MCSL

#############################################################
#	Download the MCSL benchmark suite
#	Close to half a GB
#
#	aria2c -c --max-connection-per-server=16 --min-split-size=1M -j 16 \
#	http://www.ece.ust.hk/~eexu/release/MCSL_NoC_Benchmark_Suite_v1.5.tar.gz
#	gzip -d MCSL_NoC_Benchmark_Suite_v1.5.tar.gz
#	tar -xf MCSL_NoC_Benchmark_Suite_v1.5.tar
#############################################################
down_traffic:
	aria2c -c --max-connection-per-server=16 --min-split-size=1M -j 16 \
	http://www.ece.ust.hk/~eexu/release/MCSL_NoC_Traffic_Pattern_Suite_v1.6.tar.gz
	gzip -d MCSL_NoC_Traffic_Pattern_Suite_v1.6.tar.gz
	tar -xf MCSL_NoC_Traffic_Pattern_Suite_v1.6.tar
	@echo "----------------------"
	@echo "-- Traffic downloaded"
	@echo "----------------------"

#############################################################
#	Create the XML files for the different topologies
#	and applications.
#############################################################
create_xml: MCSL
	@-mkdir -p xml 2>&1
	sh create_xml.sh

MCSL:
	@-mkdir -p build 2>&1
	cd build &&	$(COMPILER_FLAGS) cmake ../src && $(MAKE) && echo "MCSL_PATH=$$(pwd)" >> ../../scripts/paths.sh

clean:
	@rm -rf build

