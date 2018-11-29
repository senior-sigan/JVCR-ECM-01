all: build-python exec

mkdir_build: clean
	[ -d ./cmake-build-debug ] | mkdir -p cmake-build-debug

reload: mkdir_build
	cd cmake-build-debug;cmake ..

build-python: reload
	cd cmake-build-debug;make JVCR-ECM-01-PYTHON -j4

build-example: reload
	cd cmake-build-debug;make JVCR-ECM-01-EXAMPLE -j4

build-test: reload
	cd cmake-build-debug;make JVCR-ECM-01-TEST -j4

exec:
	./cmake-build-debug/python/JVCR-ECM-01-PYTHON ./python/examples/

clean:
	rm -rf cmake-build-debug

fast_build:
	cd cmake-build-debug;make JVCR-ECM-01-PYTHON -j4

run: fast_build exec