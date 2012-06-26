all:
	scons

%:
	scons $@

clean:
	scons -c && rm -rf img/*

